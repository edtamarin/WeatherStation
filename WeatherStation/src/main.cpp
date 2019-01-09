#include <Arduino.h>
#include <Wire.h>
#include <SparkFunBME280.h>
#include <ESP8266WiFI.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <Ticker.h>
#include <ESP8266httpUpdate.h>

#define DEVICE "wsta"
#define FW_VERSION "0_2_1"

const char* ssid = "Convention 48";
const char* password = "zurich4ccords";
const char* mqttServer = "192.168.0.111";
const int mqttPort = 1883;
const char* mqttUser = "mosqSH";
const char* mqttPassword = "smartMQTT";

const char* updateUrl = "http://192.168.0.111:1880/update/"DEVICE;

char tempC[16];
char humi[16];
char pres[16];

bool dataSent = false;

IPAddress staticIP(192,168,0,10);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
IPAddress dns(192,168,0,1);

WiFiClient espClient;
PubSubClient mqttClient(espClient);
BME280 sensor;
Ticker sensorPoller;
Ticker blinker;

int ledPins[2] = {D0,D6};

void runUpdate(){
  t_httpUpdate_return httpResult;
  ESPhttpUpdate.rebootOnUpdate(false);
  httpResult = ESPhttpUpdate.update(updateUrl,FW_VERSION);
  switch(httpResult){
    case HTTP_UPDATE_NO_UPDATES:
      mqttClient.publish("info","No update to weather station required");
      break;
    case HTTP_UPDATE_OK:
      mqttClient.publish("info","Weather station updated");
      ESP.restart();
      break;
    case HTTP_UPDATE_FAILED:
      mqttClient.publish("info","Weather station update failed");
      Serial.println(ESPhttpUpdate.getLastErrorString());
      break;
    default:
      mqttClient.publish("info","Weather station not updated");
      Serial.println(ESPhttpUpdate.getLastErrorString());
      break;
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String messageReceived = "";
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    messageReceived += (char)payload[i];
  }
  Serial.println(messageReceived);
  if (messageReceived == "WSTA_update"){
    mqttClient.publish("info","Weather station requested update");
    runUpdate();
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttClient.connect("ShedStation", mqttUser, mqttPassword)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      mqttClient.publish("info", "Weather station online, version "FW_VERSION);
      mqttClient.subscribe("control");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  blinker.detach();
  digitalWrite(ledPins[0],HIGH);
}

void mqttBlinkLed(){
  byte pinStatus = digitalRead(ledPins[1]);
  digitalWrite(ledPins[1],pinStatus = !pinStatus);
}

void pollSensors(){
  snprintf(tempC,sizeof(tempC), "%.2f", sensor.readTempC());
  mqttClient.publish("shed/temp",tempC);
  snprintf(humi,sizeof(humi), "%.2f", sensor.readFloatHumidity());
  mqttClient.publish("shed/humi",humi);
  snprintf(pres,sizeof(pres), "%.2f", sensor.readFloatPressure());
  mqttClient.publish("shed/pres",pres);
  dataSent = true;
  Serial.println("Published data");
}

void blinkStatusLED(){
  byte pinStatus = digitalRead(ledPins[0]);
  digitalWrite(ledPins[0],pinStatus = !pinStatus);
}

void setupBME(){
  sensor.settings.commInterface = I2C_MODE;
  sensor.settings.I2CAddress = 0x76;
  delay(10);
  Serial.print("Starting BME280: 0x");
  Serial.println(sensor.begin(), HEX);
}

void setupWiFi(){
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
}

void setup() {
  blinker.attach(0.25, blinkStatusLED);
  // start serial and I2C
  Serial.begin(115200);
  Wire.begin();
  // set up LED pins
  for (int i=0;i<2;i++){
    pinMode(ledPins[i],OUTPUT);
  }
  // set up BME and WiFi
  setupBME();
  setupWiFi();
  // set up the MQTT client
  mqttClient.setServer(mqttServer,mqttPort);
  mqttClient.setCallback(callback);
  // attach the timed events
  sensorPoller.attach(10,pollSensors);
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  // blink a LED when MQTT data is being sent
  if (dataSent){
    mqttBlinkLed();
    delay(100);
    mqttBlinkLed();
    dataSent = false;
  }
  mqttClient.loop();
}