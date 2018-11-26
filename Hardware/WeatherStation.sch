EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_01x08 J2
U 1 1 5BFC4002
P 2800 2050
F 0 "J2" H 2720 1425 50  0000 C CNN
F 1 "Conn_01x08" H 2720 1516 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 2800 2050 50  0001 C CNN
F 3 "~" H 2800 2050 50  0001 C CNN
	1    2800 2050
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Switching:TSR_1-2450 U1
U 1 1 5BFC40E7
P 5300 1900
F 0 "U1" H 5300 2267 50  0000 C CNN
F 1 "TSR_1-2450" H 5300 2176 50  0000 C CNN
F 2 "Converter_DCDC:Converter_DCDC_TRACO_TSR-1_THT" H 5300 1750 50  0001 L CIN
F 3 "http://www.tracopower.com/products/tsr1.pdf" H 5300 1900 50  0001 C CNN
	1    5300 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5BFC414E
P 5300 2100
F 0 "#PWR0101" H 5300 1850 50  0001 C CNN
F 1 "GND" H 5305 1927 50  0000 C CNN
F 2 "" H 5300 2100 50  0001 C CNN
F 3 "" H 5300 2100 50  0001 C CNN
	1    5300 2100
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 5BFC41CF
P 5800 1800
F 0 "#PWR0103" H 5800 1650 50  0001 C CNN
F 1 "+5V" H 5815 1973 50  0000 C CNN
F 2 "" H 5800 1800 50  0001 C CNN
F 3 "" H 5800 1800 50  0001 C CNN
	1    5800 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 1800 4900 1800
Wire Wire Line
	5700 1800 5800 1800
$Comp
L Connector_Generic:Conn_01x04 J3
U 1 1 5BFC4276
P 4500 2700
F 0 "J3" V 4466 2412 50  0000 R CNN
F 1 "Conn_01x04" V 4375 2412 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 4500 2700 50  0001 C CNN
F 3 "~" H 4500 2700 50  0001 C CNN
	1    4500 2700
	0    -1   -1   0   
$EndComp
Text GLabel 4400 2900 3    39   Input ~ 0
+5V
Text GLabel 4500 2900 3    39   Input ~ 0
GND
Text GLabel 4600 2900 3    39   Input ~ 0
SCL
Text GLabel 4700 2900 3    39   Input ~ 0
SDA
$Comp
L Connector:Barrel_Jack_Switch J4
U 1 1 5BFC4B46
P 2450 3000
F 0 "J4" H 2505 3317 50  0000 C CNN
F 1 "Barrel_Jack_Switch" H 2505 3226 50  0000 C CNN
F 2 "Connector_BarrelJack:BarrelJack_Horizontal" H 2500 2960 50  0001 C CNN
F 3 "~" H 2500 2960 50  0001 C CNN
	1    2450 3000
	1    0    0    -1  
$EndComp
Text GLabel 2750 2900 2    39   Output ~ 0
+VDC
Text GLabel 2750 3100 2    39   Output ~ 0
GND
Text GLabel 4800 1800 0    39   Input ~ 0
+VDC
$Comp
L Connector_Generic:Conn_01x08 J1
U 1 1 5BFC3FA4
P 3500 2050
F 0 "J1" H 3580 2042 50  0000 L CNN
F 1 "Conn_01x08" H 3580 1951 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 3500 2050 50  0001 C CNN
F 3 "~" H 3500 2050 50  0001 C CNN
	1    3500 2050
	-1   0    0    -1  
$EndComp
Text GLabel 3700 1950 2    39   Output ~ 0
SCL
Text GLabel 3700 2050 2    39   Output ~ 0
SDA
Text GLabel 3700 2350 2    39   Input ~ 0
GND
Text GLabel 3700 2450 2    39   Input ~ 0
+5V
$EndSCHEMATC
