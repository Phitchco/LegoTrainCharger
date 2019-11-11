EESchema Schematic File Version 4
LIBS:LEGO_Charger-cache
EELAYER 29 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 8
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
L Device:Battery_Cell BT1
U 1 1 5DA61F55
P 1600 1300
F 0 "BT1" H 1718 1396 50  0000 L CNN
F 1 "3.3v" H 1718 1305 50  0000 L CNN
F 2 "" V 1600 1360 50  0001 C CNN
F 3 "~" V 1600 1360 50  0001 C CNN
	1    1600 1300
	1    0    0    -1  
$EndComp
$Comp
L TLP222AF-ND:TLP222AF-ND RLY?
U 1 1 5DA66EBC
P 6200 1350
F 0 "RLY?" V 6154 1653 50  0000 L CNN
F 1 "TLP222AF-ND" V 6245 1653 50  0000 L CNN
F 2 "digikey-footprints:DIP-4_W7.62mm" H 6650 1730 50  0001 L CNN
F 3 "" H 6350 1650 60  0001 L CNN
	1    6200 1350
	0    1    1    0   
$EndComp
$Comp
L Device:Battery_Cell BT?
U 1 1 5DA6CAA9
P 1600 1600
F 0 "BT?" H 1718 1696 50  0000 L CNN
F 1 "3.3v" H 1718 1605 50  0000 L CNN
F 2 "" V 1600 1660 50  0001 C CNN
F 3 "~" V 1600 1660 50  0001 C CNN
	1    1600 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT?
U 1 1 5DA6D0B2
P 1600 1900
F 0 "BT?" H 1718 1996 50  0000 L CNN
F 1 "3.3v" H 1718 1905 50  0000 L CNN
F 2 "" V 1600 1960 50  0001 C CNN
F 3 "~" V 1600 1960 50  0001 C CNN
	1    1600 1900
	1    0    0    -1  
$EndComp
$Sheet
S 2450 1050 1000 1050
U 5DA72456
F0 "Lego Bluetooth Rx" 50
F1 "Lego Bluetooth Rx.sch" 50
F2 "Bat+" I L 2450 1250 50 
F3 "Bat-" I L 2450 1850 50 
F4 "Wire1-ID2" I R 3450 1200 50 
F5 "Wire2-ID1" I R 3450 1350 50 
F6 "Wire3-Vcc" I R 3450 1500 50 
F7 "Wire5-W2" I R 3450 1800 50 
F8 "Wire6-W1" I R 3450 1950 50 
F9 "Wire4-Gnd" I R 3450 1650 50 
$EndSheet
$Comp
L TLP222AF-ND:TLP222AF-ND RLY?
U 1 1 5DA7900D
P 4700 1350
F 0 "RLY?" V 4654 1653 50  0000 L CNN
F 1 "TLP222AF-ND" V 4745 1653 50  0000 L CNN
F 2 "digikey-footprints:DIP-4_W7.62mm" H 5150 1730 50  0001 L CNN
F 3 "" H 4850 1650 60  0001 L CNN
	1    4700 1350
	0    1    1    0   
$EndComp
$Sheet
S 9550 1050 650  950 
U 5DA797D8
F0 "Lego Motor" 50
F1 "Lego Motor.sch" 50
F2 "Wire1-ID2" I L 9550 1150 50 
F3 "Wire2-ID1" I L 9550 1300 50 
F4 "Wire3-Vcc" I L 9550 1450 50 
F5 "Wire5-W2" I L 9550 1750 50 
F6 "Wire6-W1" I L 9550 1900 50 
F7 "Wire4-Gnd" I L 9550 1600 50 
$EndSheet
$Sheet
S 3350 5150 550  850 
U 5DA86F48
F0 "Receiver" 50
F1 "Receiver.sch" 50
F2 "Coil+" I L 3350 5250 50 
F3 "Coil-" I L 3350 5750 50 
F4 "-Output" I R 3900 5400 50 
F5 "+Output" I R 3900 5600 50 
F6 "DCsense" I R 3900 5900 50 
$EndSheet
$Sheet
S 1950 3100 1000 1050
U 5DA886D6
F0 "LiIonCharger" 50
F1 "LiIonCharger.sch" 50
F2 "B-" I L 1950 3250 50 
F3 "B+" I L 1950 4000 50 
F4 "-InputOutput" I R 2950 4000 50 
F5 "+InputOutput" I R 2950 3250 50 
F6 "B2" I L 1950 3750 50 
F7 "B1" I L 1950 3500 50 
$EndSheet
Wire Wire Line
	3350 5250 3150 5250
Wire Wire Line
	3150 5750 3350 5750
$Comp
L pspice:INDUCTOR L1
U 1 1 5DA8F7EC
P 2900 5500
F 0 "L1" V 2600 5500 50  0000 C CNN
F 1 "Tx Coil" V 2500 5450 50  0000 C CNN
F 2 "" H 2900 5500 50  0001 C CNN
F 3 "~" H 2900 5500 50  0001 C CNN
	1    2900 5500
	0    1    -1   0   
$EndComp
Wire Wire Line
	2700 5250 2900 5250
Wire Wire Line
	2900 5750 2700 5750
$Comp
L pspice:INDUCTOR L2
U 1 1 5DA84626
P 3150 5500
F 0 "L2" V 2850 5400 50  0000 C CNN
F 1 "Rx Coil" V 2700 5450 50  0000 C CNN
F 2 "" H 3150 5500 50  0001 C CNN
F 3 "~" H 3150 5500 50  0001 C CNN
	1    3150 5500
	0    -1   -1   0   
$EndComp
$Sheet
S 4550 3100 800  1100
U 5DA9A1FB
F0 "DC-DCregulator" 50
F1 "DC-DCregulator.sch" 50
F2 "+DCin" I L 4550 3250 50 
F3 "-DCin" I L 4550 4000 50 
F4 "-DCout" I R 5350 3700 50 
F5 "+DCout" I R 5350 3250 50 
$EndSheet
$Sheet
S 2150 5050 550  950 
U 5DA91141
F0 "Transmitter" 50
F1 "Transmitter.sch" 50
F2 "Coil+" I R 2700 5250 50 
F3 "Coil-" I R 2700 5750 50 
F4 "-DCInput" I L 2150 5650 50 
F5 "+DCInput" I L 2150 5450 50 
$EndSheet
$Comp
L Converter_ACDC:RAC04-12SGA PS1
U 1 1 5DAA9874
P 1600 5550
F 0 "PS1" H 1600 5917 50  0000 C CNN
F 1 "115Vac 9-12Vdc" H 1600 5826 50  0000 C CNN
F 2 "Converter_ACDC:Converter_ACDC_RECOM_RAC04-xxSGx_THT" H 1600 5200 50  0001 C CNN
F 3 "https://www.recom-power.com/pdf/Powerline-AC-DC/RAC04-GA.pdf" H 1500 5850 50  0001 C CNN
	1    1600 5550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_WallPlug_Earth P1
U 1 1 5DAAE453
P 850 5550
F 0 "P1" H 917 5875 50  0000 C CNN
F 1 "WallPlug" H 917 5784 50  0000 C CNN
F 2 "" H 1250 5550 50  0001 C CNN
F 3 "~" H 1250 5550 50  0001 C CNN
	1    850  5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 5450 1200 5450
Wire Wire Line
	1150 5650 1200 5650
Wire Wire Line
	3900 5600 4300 5600
Connection ~ 4300 3250
Wire Wire Line
	4300 3250 4550 3250
Wire Wire Line
	2450 1250 1900 1250
Wire Wire Line
	1900 1250 1900 900 
Wire Wire Line
	1900 900  1600 900 
Wire Wire Line
	1600 900  1600 1100
Wire Wire Line
	1600 2000 1600 2250
Wire Wire Line
	1600 2250 1900 2250
Wire Wire Line
	1900 2250 1900 1850
Wire Wire Line
	1900 1850 2450 1850
Wire Wire Line
	1600 3250 1600 2250
Wire Wire Line
	1600 3250 1950 3250
Connection ~ 1600 2250
Wire Wire Line
	1950 4000 1100 4000
Wire Wire Line
	1100 900  1600 900 
Connection ~ 1600 900 
Wire Wire Line
	1600 1400 1250 1400
Wire Wire Line
	1250 1400 1250 3750
Wire Wire Line
	1250 3750 1950 3750
Connection ~ 1600 1400
Wire Wire Line
	1400 3500 1400 1700
Wire Wire Line
	1400 1700 1600 1700
Wire Wire Line
	1400 3500 1950 3500
Connection ~ 1600 1700
Wire Wire Line
	3450 1350 3700 1350
Wire Wire Line
	3700 1350 3700 1500
Wire Wire Line
	3700 1500 3450 1500
Wire Wire Line
	3450 1200 3550 1200
Wire Wire Line
	3550 1200 3550 1650
Wire Wire Line
	3550 1650 3450 1650
Wire Wire Line
	3450 1950 4500 1950
Wire Wire Line
	4500 1950 4500 1750
Wire Wire Line
	4900 1900 4900 1750
$Comp
L power:GND #PWR?
U 1 1 5DADC93D
P 4300 950
F 0 "#PWR?" H 4300 700 50  0001 C CNN
F 1 "GND" H 4305 777 50  0001 C CNN
F 2 "" H 4300 950 50  0001 C CNN
F 3 "" H 4300 950 50  0001 C CNN
	1    4300 950 
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4300 950  4500 950 
Wire Wire Line
	4300 3250 4300 4450
Wire Wire Line
	2000 5450 2150 5450
Wire Wire Line
	2000 5650 2150 5650
$Comp
L MCU_Espressif:ESP12-ESP8266 U1
U 1 1 5DB117A7
P 8800 3950
F 0 "U1" H 8800 2025 50  0000 C CNN
F 1 "ESP12-ESP8266" H 8800 1934 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-32-1EP_5x5mm_P0.5mm_EP3.45x3.45mm" H 9000 1800 50  0001 C CNN
F 3 "http://espressif.com/sites/default/files/documentation/0a-esp8266ex_datasheet_en.pdf" H 8900 2650 50  0001 C CNN
	1    8800 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 1800 6000 1750
Wire Wire Line
	6000 950  4900 950 
Wire Wire Line
	8800 2950 8800 2800
Wire Wire Line
	8800 2800 8500 2800
Wire Wire Line
	8500 2800 8500 2950
Wire Wire Line
	8500 2800 8300 2800
Wire Wire Line
	8300 2800 8300 2950
Connection ~ 8500 2800
Wire Wire Line
	8300 2800 7750 2800
Wire Wire Line
	7750 2800 7750 3300
Wire Wire Line
	7750 3300 7900 3300
Connection ~ 8300 2800
Wire Wire Line
	7750 3700 7900 3700
Connection ~ 7750 3300
Wire Wire Line
	7750 3700 7750 4400
Wire Wire Line
	7750 4400 7900 4400
Connection ~ 7750 3700
$Comp
L power:GND #PWR?
U 1 1 5DB2DFA3
P 7750 4400
F 0 "#PWR?" H 7750 4150 50  0001 C CNN
F 1 "GND" H 7755 4227 50  0001 C CNN
F 2 "" H 7750 4400 50  0001 C CNN
F 3 "" H 7750 4400 50  0001 C CNN
	1    7750 4400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5350 3250 5700 3250
Wire Wire Line
	4300 2050 4300 3250
Wire Wire Line
	8600 2050 8600 2950
Connection ~ 7750 4400
Wire Wire Line
	6400 1750 8900 1750
Wire Wire Line
	4900 1900 9000 1900
$Comp
L power:GND #PWR?
U 1 1 5DB888F8
P 5500 3750
F 0 "#PWR?" H 5500 3500 50  0001 C CNN
F 1 "GND" H 5505 3577 50  0001 C CNN
F 2 "" H 5500 3750 50  0001 C CNN
F 3 "" H 5500 3750 50  0001 C CNN
	1    5500 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 3700 5500 3700
Wire Wire Line
	5500 3700 5500 3750
Wire Wire Line
	3450 1800 6000 1800
Wire Wire Line
	8600 2050 4300 2050
Wire Wire Line
	8900 2950 8900 1750
Connection ~ 8900 1750
Wire Wire Line
	8900 1750 9550 1750
Wire Wire Line
	9000 2950 9000 1900
Connection ~ 9000 1900
Wire Wire Line
	9000 1900 9550 1900
Wire Wire Line
	8700 2950 8700 950 
Wire Wire Line
	6400 950  8700 950 
Wire Wire Line
	7750 3300 7750 3700
Wire Wire Line
	8400 2200 5700 2200
Wire Wire Line
	8400 2950 8400 2200
Wire Wire Line
	5700 2200 5700 3250
Wire Wire Line
	7050 3300 7750 3300
Wire Wire Line
	7050 3700 7300 3700
Wire Wire Line
	7300 3700 7300 2600
Wire Wire Line
	10100 2500 7200 2500
Wire Wire Line
	7200 2500 7200 3400
Wire Wire Line
	7050 3400 7200 3400
Wire Wire Line
	1100 900  1100 4000
$Comp
L Device:R_US R?
U 1 1 5DBDDF35
P 4050 3450
F 0 "R?" H 4118 3496 50  0000 L CNN
F 1 "R_US" H 4118 3405 50  0000 L CNN
F 2 "" V 4090 3440 50  0001 C CNN
F 3 "~" H 4050 3450 50  0001 C CNN
	1    4050 3450
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 5DBDDF42
P 4050 3750
F 0 "R?" H 4118 3796 50  0000 L CNN
F 1 "R_US" H 4118 3705 50  0000 L CNN
F 2 "" V 4090 3740 50  0001 C CNN
F 3 "~" H 4050 3750 50  0001 C CNN
	1    4050 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 2600 10000 2600
Wire Wire Line
	9700 3950 10100 3950
Wire Wire Line
	10100 2500 10100 3950
Wire Wire Line
	10000 2600 10000 3850
Wire Wire Line
	10000 3850 9700 3850
$Sheet
S 6450 3000 600  900 
U 5DB65BB9
F0 "ADS1115" 50
F1 "ADS1115.sch" 50
F2 "GND" I R 7050 3300 50 
F3 "ADDR" I R 7050 3500 50 
F4 "ALRT" I R 7050 3600 50 
F5 "A0" I L 6450 3250 50 
F6 "A1" I L 6450 3400 50 
F7 "SCL" I R 7050 3700 50 
F8 "SDA" I R 7050 3400 50 
F9 "VCC" I R 7050 3800 50 
F10 "A2" I L 6450 3700 50 
F11 "A3" I L 6450 3550 50 
$EndSheet
Wire Wire Line
	9700 3650 9900 3650
Wire Wire Line
	9900 3650 9900 2700
Wire Wire Line
	9900 2700 7450 2700
Wire Wire Line
	7450 2700 7450 3800
Wire Wire Line
	7450 3800 7050 3800
$Comp
L Power_Management:BTS6133D U?
U 1 1 5DC65499
P 4400 4750
F 0 "U?" H 4400 4475 50  0000 C CNN
F 1 "BTS6133D" H 4600 5350 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-252-4" H 4400 4500 50  0001 C CNN
F 3 "http://www.infineon.com/dgdl/Infineon-BTS6133D-DS-v01_00-EN.pdf?fileId=5546d4625a888733015aa3e3286f102a" H 4400 4350 50  0001 C CNN
	1    4400 4750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4300 5050 4300 5600
$Comp
L power:GND #PWR?
U 1 1 5DC77E74
P 4500 5500
F 0 "#PWR?" H 4500 5250 50  0001 C CNN
F 1 "GND" H 4505 5327 50  0001 C CNN
F 2 "" H 4500 5500 50  0001 C CNN
F 3 "" H 4500 5500 50  0001 C CNN
	1    4500 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 4000 4050 4000
Wire Wire Line
	3900 5400 4050 5400
Wire Wire Line
	4050 5400 4050 4000
Connection ~ 4050 4000
Wire Wire Line
	2950 3250 4050 3250
Wire Wire Line
	4500 5050 4500 5100
Connection ~ 4050 3600
Wire Wire Line
	4050 3300 4050 3250
Connection ~ 4050 3250
Wire Wire Line
	4050 3250 4300 3250
$Comp
L Device:R_US R?
U 1 1 5DCF9177
P 7200 4300
F 0 "R?" H 7268 4346 50  0000 L CNN
F 1 "10K" H 7268 4255 50  0000 L CNN
F 2 "" V 7240 4290 50  0001 C CNN
F 3 "~" H 7200 4300 50  0001 C CNN
	1    7200 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 3400 7200 4150
Connection ~ 7200 3400
Wire Wire Line
	9700 4050 9950 4050
Wire Wire Line
	9950 4050 9950 6150
Wire Wire Line
	9950 6150 7200 6150
Wire Wire Line
	6450 3550 6150 3550
Wire Wire Line
	6150 3550 6150 2750
Wire Wire Line
	6450 3700 6150 3700
Wire Wire Line
	6150 3700 6150 4450
Wire Wire Line
	7200 5300 4800 5300
Wire Wire Line
	7200 4450 7200 5300
Wire Wire Line
	4500 4450 5000 4450
$Comp
L Device:R_US R?
U 1 1 5DC77E7B
P 5000 4700
F 0 "R?" H 5068 4746 50  0000 L CNN
F 1 "82K" H 5068 4655 50  0000 L CNN
F 2 "" V 5040 4690 50  0001 C CNN
F 3 "~" H 5000 4700 50  0001 C CNN
	1    5000 4700
	1    0    0    -1  
$EndComp
Connection ~ 7200 5300
Wire Wire Line
	7200 5300 7200 5550
Wire Wire Line
	5000 4450 5000 4550
Wire Wire Line
	5000 4450 6150 4450
Connection ~ 5000 4450
$Comp
L power:GND #PWR?
U 1 1 5DD83B3D
P 5000 4850
F 0 "#PWR?" H 5000 4600 50  0001 C CNN
F 1 "GND" H 5005 4677 50  0001 C CNN
F 2 "" H 5000 4850 50  0001 C CNN
F 3 "" H 5000 4850 50  0001 C CNN
	1    5000 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 3900 4050 4000
Wire Wire Line
	4050 4000 2950 4000
Wire Wire Line
	6150 2750 3750 2750
Wire Wire Line
	3750 2750 3750 3600
Wire Wire Line
	3750 3600 4050 3600
$Comp
L Transistor_BJT:2N3904 Q?
U 1 1 5DD98E16
P 4600 5300
F 0 "Q?" H 4791 5346 50  0000 L CNN
F 1 "2N3904" H 4791 5255 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4800 5225 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 4600 5300 50  0001 L CNN
	1    4600 5300
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 5DD9D192
P 7200 5700
F 0 "R?" H 7268 5746 50  0000 L CNN
F 1 "1K" H 7268 5655 50  0000 L CNN
F 2 "" V 7240 5690 50  0001 C CNN
F 3 "~" H 7200 5700 50  0001 C CNN
	1    7200 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 5850 7200 6150
NoConn ~ 8600 1750
NoConn ~ 8600 1900
$EndSCHEMATC
