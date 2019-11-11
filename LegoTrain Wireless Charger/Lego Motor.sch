EESchema Schematic File Version 4
LIBS:LEGO_Charger-cache
EELAYER 29 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 3 8
Title "Lego Motor"
Date "2019-10-15"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Motor:Motor_DC_ALT M?
U 1 1 5DA7A020
P 5700 3900
AR Path="/5DA7A020" Ref="M?"  Part="1" 
AR Path="/5DA797D8/5DA7A020" Ref="M?"  Part="1" 
F 0 "M?" H 5847 3896 50  0000 L CNN
F 1 "Motor_DC_ALT" H 5847 3805 50  0000 L CNN
F 2 "" H 5700 3810 50  0001 C CNN
F 3 "~" H 5700 3810 50  0001 C CNN
	1    5700 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DA7A026
P 6650 4050
AR Path="/5DA7A026" Ref="C?"  Part="1" 
AR Path="/5DA797D8/5DA7A026" Ref="C?"  Part="1" 
F 0 "C?" H 6765 4096 50  0000 L CNN
F 1 "C" H 6765 4005 50  0000 L CNN
F 2 "" H 6688 3900 50  0001 C CNN
F 3 "~" H 6650 4050 50  0001 C CNN
	1    6650 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 5DA7A765
P 4650 4200
AR Path="/5DA7A765" Ref="R?"  Part="1" 
AR Path="/5DA797D8/5DA7A765" Ref="R1"  Part="1" 
F 0 "R?" V 4550 4150 50  0000 L CNN
F 1 "ML05" V 4450 4050 50  0000 L CNN
F 2 "" H 4650 4200 50  0001 C CNN
F 3 "~" H 4650 4200 50  0001 C CNN
	1    4650 4200
	0    -1   -1   0   
$EndComp
Text HLabel 4000 2950 0    50   Input ~ 0
Wire1-ID2
Text HLabel 4000 3200 0    50   Input ~ 0
Wire2-ID1
Text HLabel 4000 3450 0    50   Input ~ 0
Wire3-Vcc
Text HLabel 4000 3950 0    50   Input ~ 0
Wire5-W2
Text HLabel 4000 4200 0    50   Input ~ 0
Wire6-W1
Text HLabel 4000 3700 0    50   Input ~ 0
Wire4-Gnd
Wire Wire Line
	4000 4200 4550 4200
Wire Wire Line
	4750 4200 5700 4200
Wire Wire Line
	5700 4200 6650 4200
Connection ~ 5700 4200
Wire Wire Line
	6650 3900 6650 3700
Wire Wire Line
	6650 3700 5700 3700
Wire Wire Line
	5700 3700 5150 3700
Wire Wire Line
	5150 3700 5150 3950
Wire Wire Line
	5150 3950 4000 3950
Connection ~ 5700 3700
Wire Wire Line
	4000 3700 4900 3700
Wire Wire Line
	4900 3700 4900 2950
Wire Wire Line
	4900 2950 4000 2950
Wire Wire Line
	4000 3200 4500 3200
Wire Wire Line
	4500 3200 4500 3450
Wire Wire Line
	4500 3450 4000 3450
$EndSCHEMATC
