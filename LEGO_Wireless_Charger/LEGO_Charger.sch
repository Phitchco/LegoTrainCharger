EESchema Schematic File Version 4
LIBS:LEGO_Charger-cache
EELAYER 29 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 6
Title "Lego Train wireless charger"
Date "2019-10-22"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:Battery_Cell BT?
U 1 1 5DA6D0B2
P 2000 3050
F 0 "BT?" H 2118 3146 50  0000 L CNN
F 1 "3.3v" H 2118 3055 50  0000 L CNN
F 2 "" V 2000 3110 50  0001 C CNN
F 3 "~" V 2000 3110 50  0001 C CNN
	1    2000 3050
	1    0    0    -1  
$EndComp
$Sheet
S 3350 5600 550  850 
U 5DA86F48
F0 "Receiver" 50
F1 "Receiver.sch" 50
F2 "Coil+" I L 3350 5700 50 
F3 "Coil-" I L 3350 6200 50 
F4 "-Output" I R 3900 5850 50 
F5 "+Output" I R 3900 6050 50 
F6 "DCsense" I R 3900 6350 50 
$EndSheet
$Sheet
S 2350 3550 1000 1050
U 5DA886D6
F0 "LiIonCharger" 50
F1 "LiIonCharger.sch" 50
F2 "B-" I L 2350 3700 50 
F3 "B+" I L 2350 4450 50 
F4 "-InputOutput" I R 3350 4450 50 
F5 "+InputOutput" I R 3350 3700 50 
F7 "B1" I L 2350 3950 50 
$EndSheet
Wire Wire Line
	3350 5700 3150 5700
Wire Wire Line
	3150 6200 3350 6200
$Comp
L pspice:INDUCTOR L1
U 1 1 5DA8F7EC
P 2900 5950
F 0 "L1" V 2600 5950 50  0000 C CNN
F 1 "Tx Coil" V 2500 5900 50  0000 C CNN
F 2 "" H 2900 5950 50  0001 C CNN
F 3 "~" H 2900 5950 50  0001 C CNN
	1    2900 5950
	0    1    -1   0   
$EndComp
Wire Wire Line
	2700 5700 2900 5700
Wire Wire Line
	2900 6200 2700 6200
$Comp
L pspice:INDUCTOR L2
U 1 1 5DA84626
P 3150 5950
F 0 "L2" V 2850 5850 50  0000 C CNN
F 1 "Rx Coil" V 2700 5900 50  0000 C CNN
F 2 "" H 3150 5950 50  0001 C CNN
F 3 "~" H 3150 5950 50  0001 C CNN
	1    3150 5950
	0    -1   -1   0   
$EndComp
$Sheet
S 2150 5500 550  950 
U 5DA91141
F0 "Transmitter" 50
F1 "Transmitter.sch" 50
F2 "Coil+" I R 2700 5700 50 
F3 "Coil-" I R 2700 6200 50 
F4 "-DCInput" I L 2150 6100 50 
F5 "+DCInput" I L 2150 5900 50 
$EndSheet
$Comp
L Converter_ACDC:RAC04-12SGA PS1
U 1 1 5DAA9874
P 1600 6000
F 0 "PS1" H 1600 6367 50  0000 C CNN
F 1 "115Vac  12Vdc" H 1600 6276 50  0000 C CNN
F 2 "Converter_ACDC:Converter_ACDC_RECOM_RAC04-xxSGx_THT" H 1600 5650 50  0001 C CNN
F 3 "https://www.recom-power.com/pdf/Powerline-AC-DC/RAC04-GA.pdf" H 1500 6300 50  0001 C CNN
	1    1600 6000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_WallPlug_Earth P1
U 1 1 5DAAE453
P 850 6000
F 0 "P1" H 917 6325 50  0000 C CNN
F 1 "WallPlug" H 917 6234 50  0000 C CNN
F 2 "" H 1250 6000 50  0001 C CNN
F 3 "~" H 1250 6000 50  0001 C CNN
	1    850  6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 5900 1200 5900
Wire Wire Line
	1150 6100 1200 6100
Wire Wire Line
	3900 6050 4300 6050
Connection ~ 4300 3700
Wire Wire Line
	2000 2250 2000 2450
Wire Wire Line
	2000 3700 2350 3700
Wire Wire Line
	2350 4450 1500 4450
Wire Wire Line
	1500 2250 2000 2250
Wire Wire Line
	1750 2750 1750 3950
Wire Wire Line
	1750 3950 2350 3950
Wire Wire Line
	4300 3700 4300 4900
Wire Wire Line
	2000 5900 2150 5900
Wire Wire Line
	2000 6100 2150 6100
$Comp
L MCU_Espressif:ESP12-ESP8266 U1
U 1 1 5DB117A7
P 8000 4400
F 0 "U1" H 8000 2475 50  0000 C CNN
F 1 "ESP12-ESP8266" H 8000 2384 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-32-1EP_5x5mm_P0.5mm_EP3.45x3.45mm" H 8200 2250 50  0001 C CNN
F 3 "http://espressif.com/sites/default/files/documentation/0a-esp8266ex_datasheet_en.pdf" H 8100 3100 50  0001 C CNN
	1    8000 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 3250 7700 3400
Wire Wire Line
	7700 3250 7500 3250
Wire Wire Line
	7500 3250 7500 3400
Wire Wire Line
	7500 3250 6950 3250
Wire Wire Line
	6950 3250 6950 3750
Wire Wire Line
	6950 3750 7100 3750
Connection ~ 7500 3250
Wire Wire Line
	6950 4150 7100 4150
Connection ~ 6950 3750
Wire Wire Line
	6950 4150 6950 4850
Wire Wire Line
	6950 4850 7100 4850
Connection ~ 6950 4150
$Comp
L power:GND #PWR?
U 1 1 5DB2DFA3
P 6950 4850
F 0 "#PWR?" H 6950 4600 50  0001 C CNN
F 1 "GND" H 6955 4677 50  0001 C CNN
F 2 "" H 6950 4850 50  0001 C CNN
F 3 "" H 6950 4850 50  0001 C CNN
	1    6950 4850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4300 2750 4300 3700
Wire Wire Line
	7800 2750 7800 3400
Connection ~ 6950 4850
Wire Wire Line
	7800 2750 7600 2750
Wire Wire Line
	6950 3750 6950 4150
Wire Wire Line
	6250 3750 6950 3750
Wire Wire Line
	6250 4150 6500 4150
Wire Wire Line
	6500 4150 6500 3050
Wire Wire Line
	9300 2950 6400 2950
Wire Wire Line
	6400 2950 6400 3850
Wire Wire Line
	6250 3850 6400 3850
Wire Wire Line
	1500 2250 1500 4450
$Comp
L Device:R_US R1
U 1 1 5DBDDF35
P 4800 3850
F 0 "R1" H 4868 3896 50  0000 L CNN
F 1 "8.2K" H 4868 3805 50  0000 L CNN
F 2 "" V 4840 3840 50  0001 C CNN
F 3 "~" H 4800 3850 50  0001 C CNN
	1    4800 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R2
U 1 1 5DBDDF42
P 4800 4150
F 0 "R2" H 4868 4196 50  0000 L CNN
F 1 "2.4K" H 4868 4105 50  0000 L CNN
F 2 "" V 4840 4140 50  0001 C CNN
F 3 "~" H 4800 4150 50  0001 C CNN
	1    4800 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 3050 9200 3050
Wire Wire Line
	8900 4400 9300 4400
Wire Wire Line
	9300 2950 9300 4400
Wire Wire Line
	9200 3050 9200 4300
Wire Wire Line
	9200 4300 8900 4300
$Sheet
S 5650 3450 600  900 
U 5DB65BB9
F0 "ADS1115" 50
F1 "ADS1115.sch" 50
F2 "GND" I R 6250 3750 50 
F3 "ADDR" I R 6250 3950 50 
F4 "ALRT" I R 6250 4050 50 
F5 "A0" I L 5650 3700 50 
F6 "A1" I L 5650 3850 50 
F7 "SCL" I R 6250 4150 50 
F8 "SDA" I R 6250 3850 50 
F9 "VCC" I R 6250 4250 50 
F10 "A2" I L 5650 4150 50 
F11 "A3" I L 5650 4000 50 
$EndSheet
Wire Wire Line
	8900 4100 9100 4100
Wire Wire Line
	9100 4100 9100 3150
Wire Wire Line
	9100 3150 6650 3150
Wire Wire Line
	6650 3150 6650 4250
Wire Wire Line
	6650 4250 6250 4250
$Comp
L Power_Management:BTS6133D U?
U 1 1 5DC65499
P 4400 5200
F 0 "U?" H 4400 4925 50  0000 C CNN
F 1 "BTS6133D" H 4600 5800 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-252-4" H 4400 4950 50  0001 C CNN
F 3 "http://www.infineon.com/dgdl/Infineon-BTS6133D-DS-v01_00-EN.pdf?fileId=5546d4625a888733015aa3e3286f102a" H 4400 4800 50  0001 C CNN
	1    4400 5200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4300 5500 4300 6050
Wire Wire Line
	3900 5850 4050 5850
Wire Wire Line
	4050 5850 4050 4450
Wire Wire Line
	4500 5500 4500 5550
Wire Wire Line
	4500 4900 5000 4900
$Comp
L Device:R_US R3
U 1 1 5DC77E7B
P 5000 5150
F 0 "R3" H 5068 5196 50  0000 L CNN
F 1 "82K" H 5068 5105 50  0000 L CNN
F 2 "" V 5040 5140 50  0001 C CNN
F 3 "~" H 5000 5150 50  0001 C CNN
	1    5000 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 4900 5000 5000
$Comp
L power:GND #PWR?
U 1 1 5DD83B3D
P 5000 5300
F 0 "#PWR?" H 5000 5050 50  0001 C CNN
F 1 "GND" H 5005 5127 50  0001 C CNN
F 2 "" H 5000 5300 50  0001 C CNN
F 3 "" H 5000 5300 50  0001 C CNN
	1    5000 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 4450 3350 4450
$Comp
L power:GND #PWR?
U 1 1 5DFAE232
P 4500 5550
F 0 "#PWR?" H 4500 5300 50  0001 C CNN
F 1 "GND" H 4505 5377 50  0001 C CNN
F 2 "" H 4500 5550 50  0001 C CNN
F 3 "" H 4500 5550 50  0001 C CNN
	1    4500 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 2750 1750 2750
$Comp
L Device:Battery_Cell BT1
U 1 1 5DA61F55
P 2000 2650
F 0 "BT1" H 2118 2746 50  0000 L CNN
F 1 "3.3v" H 2118 2655 50  0000 L CNN
F 2 "" V 2000 2710 50  0001 C CNN
F 3 "~" V 2000 2710 50  0001 C CNN
	1    2000 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 3150 2000 3700
Wire Wire Line
	2000 2850 2000 2750
Connection ~ 2000 2750
$Comp
L Device:R_US R4
U 1 1 5DFD9EA0
P 4300 6250
F 0 "R4" H 4368 6296 50  0000 L CNN
F 1 "8.2K" H 4368 6205 50  0000 L CNN
F 2 "" V 4340 6240 50  0001 C CNN
F 3 "~" H 4300 6250 50  0001 C CNN
	1    4300 6250
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R5
U 1 1 5DFD9EA6
P 4300 6550
F 0 "R5" H 4368 6596 50  0000 L CNN
F 1 "2.4K" H 4368 6505 50  0000 L CNN
F 2 "" V 4340 6540 50  0001 C CNN
F 3 "~" H 4300 6550 50  0001 C CNN
	1    4300 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 6100 4300 6050
Wire Wire Line
	4300 6700 4300 6800
Connection ~ 4300 6050
$Comp
L power:GND #PWR?
U 1 1 5DFEC464
P 4300 6800
F 0 "#PWR?" H 4300 6550 50  0001 C CNN
F 1 "GND" H 4305 6627 50  0001 C CNN
F 2 "" H 4300 6800 50  0001 C CNN
F 3 "" H 4300 6800 50  0001 C CNN
	1    4300 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 2750 7600 3400
Connection ~ 7600 2750
Wire Wire Line
	7600 2750 4300 2750
Wire Wire Line
	3350 3700 4300 3700
Wire Wire Line
	4300 3700 4800 3700
Wire Wire Line
	4800 4300 4800 4450
Wire Wire Line
	4800 4450 4050 4450
Connection ~ 4050 4450
Wire Wire Line
	4800 4000 5650 4000
Connection ~ 4800 4000
Wire Wire Line
	5650 3850 5250 3850
Wire Wire Line
	5250 3850 5250 4900
Wire Wire Line
	5250 4900 5000 4900
Connection ~ 5000 4900
Wire Wire Line
	5650 4150 5500 4150
Wire Wire Line
	5500 4150 5500 6400
Wire Wire Line
	5500 6400 4300 6400
Connection ~ 4300 6400
$Comp
L Device:LED_Dual_AAC D1
U 1 1 5E0131DD
P 9750 5650
F 0 "D1" V 9796 5440 50  0000 R CNN
F 1 "LED_Dual_AAC" V 9705 5440 50  0000 R CNN
F 2 "" H 9750 5650 50  0001 C CNN
F 3 "~" H 9750 5650 50  0001 C CNN
	1    9750 5650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9750 5950 9750 6050
$Comp
L power:GND #PWR?
U 1 1 5E014B46
P 9750 6050
F 0 "#PWR?" H 9750 5800 50  0001 C CNN
F 1 "GND" H 9755 5877 50  0001 C CNN
F 2 "" H 9750 6050 50  0001 C CNN
F 3 "" H 9750 6050 50  0001 C CNN
	1    9750 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R7
U 1 1 5E016F0A
P 9850 4950
F 0 "R7" H 9918 4996 50  0000 L CNN
F 1 "330" H 9918 4905 50  0000 L CNN
F 2 "" V 9890 4940 50  0001 C CNN
F 3 "~" H 9850 4950 50  0001 C CNN
	1    9850 4950
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R6
U 1 1 5E01C475
P 9650 5200
F 0 "R6" H 9718 5246 50  0000 L CNN
F 1 "330" H 9718 5155 50  0000 L CNN
F 2 "" V 9690 5190 50  0001 C CNN
F 3 "~" H 9650 5200 50  0001 C CNN
	1    9650 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 3600 9850 3600
Wire Wire Line
	9850 3600 9850 4800
Wire Wire Line
	9850 5100 9850 5350
Wire Wire Line
	8900 4600 9650 4600
Wire Wire Line
	9650 4600 9650 5050
Wire Wire Line
	8050 2350 8000 2350
Wire Wire Line
	8050 2000 8050 2350
Wire Wire Line
	7900 2000 7900 3400
Wire Wire Line
	8000 3400 8000 2350
$Sheet
S 7200 1350 950  650 
U 5DA797D8
F0 "Lego Motor" 50
F1 "Lego Motor.sch" 50
F2 "Wire1-ID2" I B 7300 2000 50 
F3 "Wire2-ID1" I B 7450 2000 50 
F4 "Wire3-Vcc" I B 7600 2000 50 
F5 "Wire5-W2" I B 7900 2000 50 
F6 "Wire6-W1" I B 8050 2000 50 
F7 "Wire4-Gnd" I B 7750 2000 50 
$EndSheet
$EndSCHEMATC
