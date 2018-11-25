#include <Arduino.h>
#include <Wire.h>
#include <SparkFunBME280.h>
#include <ESP8266WiFI.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <Ticker.h>

// NETWORK SETUP HERE

char tempC[16];
char humi[16];
char pres[16];

IPAddress staticIP(192,168,0,10);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
IPAddress dns(192,168,0,1);

WiFiClient espClient;
PubSubClient mqttClient(espClient);
BME280 sensor;
Ticker sensorPoller;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    char* clientId = "ShedStation";
    // Attempt to connect
    if (mqttClient.connect(clientId, mqttUser, mqttPassword)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      mqttClient.publish("shed/gen", "BME280 online");
      mqttClient.subscribe("gen/stat");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void pollSensors(){
  snprintf(tempC,sizeof(tempC), "%.2f", sensor.readTempC());
  mqttClient.publish("shed/temp",tempC);
  snprintf(humi,sizeof(humi), "%.2f", sensor.readFloatHumidity());
  mqttClient.publish("shed/humi",humi);
  snprintf(pres,sizeof(pres), "%.2f", sensor.readFloatPressure());
  mqttClient.publish("shed/pres",pres);
  Serial.println("Published data");
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  sensor.settings.commInterface = I2C_MODE;
  sensor.settings.I2CAddress = 0x76;
  delay(10);
  Serial.print("Starting BME280: 0x");
  Serial.println(sensor.begin(), HEX);
  // configure wifi for static address
  WiFi.hostname("TempMQTT");
  WiFi.config(staticIP,gateway,subnet,dns);
  WiFi.begin(ssid,password);
  WiFi.mode(WIFI_STA);
  // wait for connection
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(250);
  }
  mqttClient.setServer(mqttServer,mqttPort);
  mqttClient.setCallback(callback);
  sensorPoller.attach(10,pollSensors);
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();
}