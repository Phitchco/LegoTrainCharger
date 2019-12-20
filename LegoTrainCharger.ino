/*
  Name:       LegoTrainCharger.ino
  Created:    12/14/2019
  Author:     Paul


  revision    date        notes
  0.0       10/29/2019   initial release
  0.1       11/02/2019   version added
  0.2       11/07/2019   added ParknCharge clean up, added ADC conversion factors
  0.3       12/14/2019   added access point web page
*/
//******************* Defining  external librarys *********************************************************************//

#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Adafruit_ADS1015.h>

#include "config.h"

// config setup
#define STA_WEB_SERVER_ON 1
#define STA_SERIAL_DEBUG_ON 1

const char* ssid = STASSID; // see config.h
const char* password = STAPSK; // see config.h
String AP_SSID="Lego";
String AP_Password="LegoChugger";
const int AP_CHANNEL = 4;
const int web_server_on = STA_WEB_SERVER_ON;
const int serial_debug = STA_SERIAL_DEBUG_ON;

//AsyncWebServer server(80);
//WiFiServer server(80);
ESP8266WebServer server(80);

Adafruit_ADS1115 ads(0x48);  // Using the ADS1115 16-bit 4 channel A/D converter

/******************* Define Pins, variable names, and constants ************************************************************/
/* NodeMCU pin #    Arduino IDE pin #
  D0                16
  D1                 5
  D2                 4
  D3                 0
  D4                 2
  D5                 14
  D6                 12
  D7                 13
  D8                 15 */

const int Red_LED = 15;                             // pin to light Red LED, active high
const int Yel_LED = 16;                             // pin to light Yellow LED, active high
const int MotorAspeed = 5; const int MotorAdir = 0; // Motor A pins for speed and direction 5=D1, 0=D3
const int MotorBspeed = 4; const int MotorBdir = 2; // Motor B pins for speed and direction 2=D4  4=D2

int16_t adc0,  adc1, adc2, adc3;                   // define each A/D channel each 16 bit channel has range of +/- 6.144V (1 bit = 0.1875mV)
float AD0, AD1, AD2, AD3;
float Ichrg, Idelta, Imax;                         // charger current, change in charging current, temp max charge current
int Vbat, VbatPcent, Vchrg;                        // Battery volts, Battery charge percent, Charger voltage
int Speed, Vdelta,IntIchrg;                        // motor speed, charger to battery voltage delta, interger of charger current
float Pcent = 15;                                  // test amount used to check change Idelta change between measurements
const int n = 10; const int Td = 50;               // number of samples measurements and delay in mSec for each A/D channel
const float Rbat = 4.4002 ; const float Ramp = 1.45; // resistor divider ratios to scale A/D channel to battery and charger
const float Rchrg = 4.4277;                        // voltage divider ratio to scale A/D channel to charger voltage
const int VbatMax = 8750;                          // 100% state of charge battery voltage in mV (2 * 4.3)
const int VbatMin = 6600;                          // 0% state of charge battery voltage in mV (2 * 3.1)
const int MinChrg = 250;                           // minimum charging current needed to park
const int FullCharge = 99;                         // percent of battery charge to complete charging
const int LowCharge = 36;                          // percent of battery charge to start charge
const int SpeedMax = 800;                          // PWM value for motor speed corresponding to 100% speed
const int SpeedMin = 225;                          // PWM value for motor speed corresponding to 0% speed
const int Slow1 = 550;                             // PWM value for motor speed for locating charger loop
const long timeoutTime = 1200;
char ChrgState;                                    // define a character to contain state of charge current into battery: Zero, Increasing, Decreasing, Park
bool Charged;                                      // variable to hold parked position
bool MotorDir = false;                             // Train direction 1= forward  0= reverse
int ChargeState = false;                           // variable to hold command to charge battery
int TrainState= true;                              // variable that holds state of train running or stopped  true=running
String header;                                     //web server variables and state machine
unsigned long currentTime = millis();
unsigned long previousTime = 0;
unsigned long StartLoop;
String stateAspeed = "off";
String stateAdir = "cw";
bool Red_ledState = false;
bool TrainGo;                                       // bit to allow running train

void setup() {
  Wire.begin(D6, D5);                              // Wire.begin([SDA-Pin],[SCL-Pin]);
  ads.begin();
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);                    // Initialize the LED_BUILTIN pin as an output
  while (!Serial);                                 // wait for serial port to connect. Needed for native USB port only
  pinMode(MotorAspeed, OUTPUT); pinMode(MotorAdir, OUTPUT);
  pinMode(MotorBspeed, OUTPUT); pinMode(MotorBdir, OUTPUT);
  pinMode(Red_LED, OUTPUT);
  pinMode(Yel_LED, OUTPUT);
  digitalWrite(Red_LED, LOW);
  digitalWrite(Yel_LED, LOW);

/********************************************client WiFi connection properties****************************************************/

 //Connect to Wi-Fi network with SSID and password
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

/*******************************************************Access point WiFi connection properties**************************************************************/
/*

IPAddress local_IP(192,168,100,2);
IPAddress gateway(192,168,100,1);
IPAddress subnet(255,255,255,0);

Serial.print("Setting soft-AP ... ");
Serial.println(WiFi.softAP(AP_SSID,AP_Password, AP_CHANNEL) ? "Ready" : "Failed!");

Serial.print("Setting access point configuration ... ");
Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

Serial.print("access point IP address = ");
Serial.println(WiFi.softAPIP());
Serial.println(WiFi.localIP());
*/

  server.on ( "/", handleRoot );
  server.on ( "/led=1", handleRoot); server.on ( "/led=0", handleRoot);
  server.on ( "/Dir=1", handleRoot); server.on ( "/Dir=0", handleRoot);
  server.on ( "/TrainGo=1", handleRoot); server.on ( "/TrainGo=0", handleRoot);
  server.on ( "/inline", []() {
    server.send ( 200, "text/plain", "this works as well" );
  } );
  server.onNotFound ( handleNotFound );
  server.begin();

  Serial.println("HTTP server started");
  Serial.println("Setup Complete");

}

void loop() {
  ReadVolts();
  server.handleClient();

  if (TrainGo==1){
    TrackTest();
   } else{
      analogWrite(MotorBspeed,0);
   }
  // if ((VbatPcent <= LowCharge) || (ChargeState==1)) {
  //   Serial.println(VbatPcent);
  //     Charged = 0;
  //     ParknCharge(); }

  //    MotorDrive();
  //  TrackTest();
}

  void handleRoot(){
  IntIchrg=int(Ichrg);                //convert Ichrg to Int, html page does not like displaying float variables
  digitalWrite (Red_LED, server.arg("led").toInt());
  Red_ledState = digitalRead(Red_LED);
  digitalWrite (MotorBdir, server.arg("Dir").toInt());
  MotorDir = digitalRead(MotorBdir);


 /* Dynamically generate the charge now toggle link, based on its current state (on or off)*/

  char GoTrain[80];
  if (TrainGo) {
    strcpy(GoTrain, "Train is running. <a href=\"/?TrainGo=0\">Stop</a>");
  }
  else {
    strcpy(GoTrain, "Train is stopped. <a href=\"/?TrainGo=1\">Run</a>");
  }
  TrainGo=server.arg("TrainGo").toInt();

  char TrainDir[80];
    if (MotorDir) {
    strcpy(TrainDir, "Direction is reverse. <a href=\"/?Dir=0\">Forward</a>");
  }
  else {
    strcpy(TrainDir, "Direction is forward. <a href=\"/?Dir=1\">Reverse</a>");
  }
    MotorDir = digitalRead(MotorBdir);


   char ledText[80];
    if (Red_ledState) {
    strcpy(ledText, "Red LED is on. <a href=\"/?led=0\">Turn off</a>");
  }
  else {
    strcpy(ledText, "Red LED is on. <a href=\"/?led=1\">Turn on</a>");
  }
  Red_ledState = digitalRead(Red_LED);

  char html[1000];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

// HTML page to display on the web-server root address
  snprintf ( html, 1000,
"<html>\
  <head>\
    <title>Bookery Lego Train WiFi</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; font-size: 1.5em; Color: #000000; }\
      h1 { Color: #AA0000; }\
    </style>\
  </head>\
  <body>\
    <h1>Bookery Lego Train Station</h1>\
    <p>Time since last charge: %02d:%02d:%02d</p>\
    <p>Battery percent charge: %d%</p>\
    <p>Battery milliVolts: %d%</p>\
    <p>Charge current: %d%</p>\
    <p>Train speed: %d%</p>\
    <p>%s<p>\
    <p>%s<p>\
    <p>%s<p>\
  </body>\
</html>",

    hr, min % 60, sec % 60,
    VbatPcent,
    Vbat,
    IntIchrg,
    Speed,
    GoTrain,
    TrainDir,
    ledText
);
  server.send ( 200, "text/html", html );
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
}
