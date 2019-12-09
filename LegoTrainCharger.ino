/*
  Name:       LegoTrainCharger.ino
  Created:    10/12/2019
  Author:     Paul


  revision    date        notes
  0.0       10/29/2019   initial release
  0.1       11/02/2019   version added
  0.2       11/07/2019   added ParknCharge clean up, added ADC conversion factors
*/
//******************* Defining  external librarys *********************************************************************//
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <Adafruit_ADS1015.h>

// config setup
#ifndef STASSID
#define STASSID "unevilnetwork"
#define STAPSK  "familylaundry"
#define STA_WEB_SERVER_ON 1
#define STA_SERIAL_DEBUG_ON 1
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
const int web_server_on = STA_WEB_SERVER_ON;
const int serial_debug = STA_SERIAL_DEBUG_ON;
Adafruit_ADS1115 ads(0x48);
//  Adafruit_ADS1115 ads;  // Using the ADS1115 16-bit 4 channel A/D converter

//******************* Define Pins, variable names, and constants ************************************************************//
/*
  NodeMCU pin #    Arduino IDE pin #
  D0          16
  D1          5
  D2          4
  D3          0
  D4          2
  D5          14
  D6          12
  D7          13
  D8          15
*/
const int ChrgEn = 13;                              // pin to enable wireless charger, must be high charge battery and see current
const int MotorAspeed = 5; const int MotorAdir = 0; // Motor A pins for speed and direction 5=D1, 0=D3
const int MotorBspeed = 2; const int MotorBdir = 4;// Motor B pins for speed and direction 2=D4  4=D2

int16_t adc0,  adc1, adc2, adc3;                   // define each A/D channel each 16 bit channel has range of +/- 6.144V (1 bit = 0.1875mV)
float AD0, AD1, AD2, AD3;
float Ichrg, Idelta, Imax;                         // charger current, change in charging current, temp max charge current (will not work if VbatPcent is int)
int Vbat, Vchrg, Speed, Vdelta;                    // Battery volts, Charger voltage, Battery charge percent, motor speed, charger battery voltage delta
int VbatPcent;
const int Izero = 60; const float M = 1.1;         // constants
float Pcent = 15;
const int Track = 6000;                            // length of track in centimeters
const int n = 5; const int Td = 5;                 // number of samples measurements and delay in mSec for each A/D channel
const float Rbat = 4.4002 ; const float Ramp = 1.45; // resistor divider ratios to scale A/D channel to battery and charger
const float Rchrg = 4.4277;                        // voltage divider ratio to scale A/D channel to charger voltage
const int VbatMax = 8600;                          // 100% state of charge battery voltage in mV (2 * 4.3)
const int VbatMin = 6200;                          // 0% state of charge battery voltage in mV (2 * 3.1)
const int MinChrg = 250;                           // minimum charging current needed to park
const int FullCharge = 95;                         // percent amount considered fully charged
const int LowCharge = 75;                          // percent amount to begin charging
const int SpeedMax = 800;                         // PWM value for motor speed corresponding to 100% speed
const int SpeedMin = 150;                           // PWM value for motor speed corresponding to 0% speed
const int Slow1 = 300;                             // PWM value for motor speed to coarse locate charger loop
const long timeoutTime = 1200;
char ChrgState;                                    // define a character to contain state of charge current into battery: Zero, Increasing, Decreasing, Park
bool Charged;                                      // variable to hold parked position
bool Dir;

String header;                                     //web server variables and state machine
unsigned long currentTime = millis();
unsigned long previousTime = 0;
unsigned long StartLoop;
String stateAspeed = "off";
String stateAdir = "cw";
WiFiServer server(80);

void setup() {
  Wire.begin(D6, D5);                              // Wire.begin([SDA-Pin],[SCL-Pin]);
  ads.begin();
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);                    // Initialize the LED_BUILTIN pin as an output
  while (!Serial);                                 // wait for serial port to connect. Needed for native USB port only
  pinMode(MotorAspeed, OUTPUT); pinMode(MotorAdir, OUTPUT);
  pinMode(MotorBspeed, OUTPUT); pinMode(MotorBdir, OUTPUT);
  pinMode(ChrgEn, OUTPUT);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {

  // pseudo code TODO
  // read the volts of the battery
  // if volts is high
  // operate train (what's our speed and direction)
  // else
  // do charge routine
  // webserver handle loop (display data and buttons to speed/directly and charge command)
  // ideas for hardware things --> led that has charge and instruction status (color?)?

  if (serial_debug) {
    Serial.print("Channel A0: "); Serial.print(adc0);
    Serial.print(" Channel A1: "); Serial.print(adc1);
    Serial.print(" Channel A2: "); Serial.print(adc2);
    Serial.print(" Channel A3: "); Serial.println(adc3);
    Serial.print("Charger current of "); Serial.print(Ichrg); Serial.println("mA");
    Serial.print("Charger voltage: "); Serial.print(Vchrg);
    Serial.print(" Battery voltage: "); Serial.print(Vbat);
    Serial.print("mV @ "); Serial.print(VbatPcent); Serial.println("%");
  }

  digitalWrite(ChrgEn, LOW);
  //  TrackTest();
  ServeInfo();
  ReadVolts();
  //  if (VbatPcent <=0){ ReadVolts();}
  if (VbatPcent <= LowCharge) {
    Serial.println(VbatPcent);
    Charged = 0;
    ParknCharge();
  }
  //     MotorDrive();
  TrackTest();
}
