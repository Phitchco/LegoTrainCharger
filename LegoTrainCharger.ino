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
#define STASSID ""
#define STAPSK  ""
#define STA_WEB_SERVER_ON 0
#define STA_SERIAL_DEBUG_ON 1
#define Forward 1
#define Reverse 0
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
const int web_server_on = STA_WEB_SERVER_ON;
const int serial_debug = STA_SERIAL_DEBUG_ON;
Adafruit_ADS1115 ads;  // Using the ADS1115 16-bit 4 channel A/D converter

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

int adc0, adc1, adc2, adc3;                         // define each A/D channel each 16 bit channel has range of +/- 6.144V (1 bit = 0.1875mV)
int Vbat, VbatPcent, Ichrg, Iref, Speed;            // Battery voltage, Percent battery charge, charger current, reference current, and present PWM motor speed
int Idelta;
const int Track = 6000;                             // length of track in centimeters
const int Level_1=12;                               // maximum mA difference between current measurements during steady state
const int n = 75; const int Td = 50;                // number of samples measurements and delay in mSec for each A/D channel
const float Rbat = .8090; const float Rchrg = 23;   // resistor divider ratios to scale A/D channel to battery and charger
const int VbatMax = 12100;                          // 100% state of charge battery voltage in mV (3 * 4.1)
const int VbatMin = 10600;                          // 0% state of charge battery voltage in mV (3 * 3.6)
const int BatLow = 10;                              // battery SOC to beging charging
const int BatHigh = 95;                             // battery SOC to end charging
const int SpeedMax = 1048;                          // PWM value for motor speed corresponding to 100% speed
const int Slow1 = 500;                              // PWM value for motor speed to coarse locate charger loop
const int Slow2 = 150;                              // PWM value for motor speed to fine locate charger loop
const int SpeedMin = 50;                            // PWM value for motor speed corresponding to 0% speed
const int ChrgEn = 13;                              // pin to enable wireless charger, must be high charge battery and see current
const int N1 = 15; const int N2 = 5;                // factors used in ChargePark to check measured current to reference current ratio
const int MotorAspeed = 5; const int MotorAdir = 0; // Motor A pins for speed and direction 5=D1, 0=D3
const int MotorBspeed = 2; const int MotorBdir = 4; // Motor B pins for speed and direction 2=D4  4=D2
const long timeoutTime = 1200;
char* ChrgState; char* CaseWas;                   // define a string to contain state of charge current into battery: Zero, Increasing, Decreasing

String header;                                      //web server variables and state machine
unsigned long currentTime = millis();
unsigned long previousTime = 0;
String stateAspeed = "off";
String stateAdir = "cw";
WiFiServer server(80);

void setup() {
  Wire.begin(D6, D5);                               // Wire.begin([SDA-Pin],[SCL-Pin]);
  ads.begin();
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);                     // Initialize the LED_BUILTIN pin as an output
  while (!Serial);                                  // wait for serial port to connect. Needed for native USB port only
  pinMode(MotorAspeed, OUTPUT); pinMode(MotorAdir, OUTPUT);
  pinMode(MotorBspeed, OUTPUT); pinMode(MotorBdir, OUTPUT);
  pinMode(ChrgEn, OUTPUT);
  // Connect to Wi-Fi network with SSID and password
  Serial.print( "Connecting to ");
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
  //      operate train (what's our speed and direction)
  // else
  //      do charge routine
  // webserver handle loop (display data and buttons to speed/directly and charge command)
  // ideas for hardware things --> led that has charge and instruction status (color?)?
  digitalWrite(ChrgEn, HIGH);
  ReadVolts();                  // read battery voltage, and charger current if enabled
  ParknCharge();
//  digitalWrite(ChrgEn, LOW);
//  MotorDrive();
//  if (VbatCap <= BatLow) { ParknCharge; }    // if battery capacity is low, goto charger


  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    if (serial_debug) {
      Serial.println("New Client."); // print a message out in the serial port
    }
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the direction CW versus CCW
            if (header.indexOf("GET /A/cw") >= 0) {
              if (serial_debug) {
                Serial.println("MotorAdir CW");
              }
              stateAdir = "cw";
              digitalWrite(MotorAdir, HIGH);
            } else if (header.indexOf("GET /A/ccw") >= 0) {
              if (serial_debug) {
                Serial.println("MotorAdir CCW");
              }
              stateAdir = "ccw";
              digitalWrite(MotorAdir, LOW);
            } else if (header.indexOf("GET /A/on") >= 0) {
              if (serial_debug) {
                Serial.println("MotorA On");
              }
              stateAspeed = "on";
              analogWrite(MotorAspeed, 512);
            } else if (header.indexOf("GET /A/off") >= 0) {
              if (serial_debug) {
                Serial.println("MotorA off");
              }
              stateAspeed = "off";
              analogWrite(MotorAspeed, 0);
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px; text-decoration: none;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".cw {background-color: #d4ac0d} .ccw {background-color: #9b59b6}");
            client.println(".on {background-color: #27ae60} .off {background-color: #e74c3c}");
            client.println(".light {background-color: #77878A;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>Lego Train Control <a href='/' class='button'><span>&#x21bb;</span></a></h1>");

            // Display current state, and ON/OFF for A
            client.println("<p>Motor A - Direction <b>" + stateAdir + "</b></p>");
            if (stateAdir == "cw") {
              client.println("<p><a href=\"/A/ccw\"><button class=\"button ccw\">CCW</button></a></p>");
            } else {
              client.println("<p><a href=\"/A/cw\"><button class=\"button\ cw\">CW</button></a></p>");
            }

            client.println("<p>Motor A - Speed <b>" + stateAspeed + "</b></p>");
            if (stateAspeed == "off") {
              client.println("<p><a href=\"/A/on\"><button class=\"button light\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/A/off\"><button class=\"button\">OFF</button></a></p>");
            }

            // TODO: add slider or some method to change speed

            client.println("<table style='margin: 0px auto'><tr><td>Channel A2:</td><td>");
            client.println(adc2);
            client.println("</td></tr>");
            client.println("<tr><td>Channel A3:</td><td>");
            client.println(adc3);
            client.println("</td></tr></table>");

            client.println("</body></html>");
            client.println();
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    header = "";
    client.stop();
  }
}

void ReadVolts() {
  // measures voltage applied to each channel or A/D converter: adc0, adc1, adc2, adc3
  // each 16 bit channel has range of +/- 6.144V (1 bit = 0.1875mV)
    adc0 = ads.readADC_SingleEnded(0);
    adc1 = ads.readADC_SingleEnded(1);
    adc2 = ads.readADC_SingleEnded(2);
    adc3 = ads.readADC_SingleEnded(3);
    Vbat = Rbat * adc3; Ichrg = adc2/Rchrg;                             // using resistor divider ratios, convert A/D voltages to battery and charger voltages
    VbatPcent = 100 * (Vbat - VbatMin) / (VbatMax - VbatMin);           // calculate battery charge capacity in percent
      if (serial_debug) {
//      Serial.print("Channel A2: "); Serial.println(adc2);
//      Serial.print("Channel A3: "); Serial.println(adc3);
//      Serial.print("Charger current of ");Serial.print(Ichrg);Serial.println("mA");
      Serial.print("Battery volts of "); Serial.print(Vbat);
      Serial.print("mV and "); Serial.print(VbatPcent); Serial.println("%");
  }
}

void ParknCharge(){
    adc2=0;
    for (int i=1; i<n;i++){
    adc2 = adc2+ ads.readADC_SingleEnded(2);}   // get latest charger current
    Ichrg=adc2/Rchrg/n;
    Serial.print("Ichrg=");Serial.print(Ichrg);
    Idelta=Ichrg-Iref;
   if (serial_debug){
    Serial.print(" Iref=");Serial.print(Iref);
    Serial.print(" Idelta= ");Serial.println(Idelta);
  }
     Iref = Ichrg;
  if ((-Level_1<=Idelta) or (Idelta<=Level_1)){
    CaseWas="Zero";
    ChrgState="Zero";
  }

/* 
  switch "ChrgState" {

  case "Zero": {  // help command
    if ((CaseWas="Increasing") or (CaseWas="Decreasing" and (Ichrg>Level_1)){
      analogWrite(Motorspeed,0);                                // STOP train, charger apperas positioned on loop
    }
    break;  }
  
  digitalWrite(ChrgEn, HIGH);                                 // enable wireless receiver connection to battery charger
  analogWrite(MotorAspeed, Slow1);                            // set train speed to Slow1
  adc2 = 0;
  for (int i = 0; i <= n; i++) {
    delay (Td); adc2 = adc2 + ads.readADC_SingleEnded(2); }   // get average of latest charger current
    adc2=adc2/n; Ichrg=adc2/Rchrg;
  Iref = Ichrg;                                               // set charge reference current to present measurement
  delay (300);                                                // wait 300ms of train travel before checking current
  Ichrg = ads.readADC_SingleEnded(2)/ Rchrg;
  if (Ichrg<= (N1* Iref)){                                     // check for drop of measured current, if so reverse train
       analogWrite(Motorspeed, Slow2);
      if (Dir = Forward) {Dir = Reverse};
      if (Dir = Reverse) {Dir = Forward};
   }
   */
}

void MotorDrive () {
  digitalWrite(MotorAdir, Forward);
  Serial.println("CW motor speed ramp up ");
  //  Serial.println(Speed);
  for (Speed = SpeedMin ; Speed <= SpeedMax; Speed += 10) {
    delay(10); analogWrite(MotorAspeed, Speed);
  }
  Serial.println("CW motor speed ramp down ");
  //Serial.println(Speed);
  for (Speed = SpeedMax; Speed >= SpeedMin; Speed -= 10) {
    delay (10);  analogWrite(MotorAspeed, Speed);
  }

  digitalWrite(MotorAdir, Reverse);
  Serial.println("CCW motor speed ramp up ");
  //Serial.println(Speed);
  for (Speed = SpeedMin; Speed <= SpeedMax; Speed += 10) {
    delay(10); analogWrite(MotorAspeed, Speed);
  }
  Serial.println("CCW motor speed ramp down ");
  //Serial.println(Speed);
  for (Speed = SpeedMax; Speed >= SpeedMin; Speed -= 10) {
    delay (10); analogWrite(MotorAspeed, Speed);
  }
}
