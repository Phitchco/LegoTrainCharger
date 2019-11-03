/*
  Name:       LegoTrainCharger.ino
  Created:    10/12/2019
  Author:     Paul


  revision    date        notes
  0.0       10/29/2019   initial release
	0.1				11/02/2019	 version added
*/
//******************* Defining  external librarys *********************************************************************//
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <Adafruit_ADS1015.h>

#ifndef STASSID
#define STASSID "unevilnetwork"
#define STAPSK  "familylaundry"
#endif

//******************* Define variable names and constants ************************************************************//
const char* ssid = STASSID;
const char* password = STAPSK;

Adafruit_ADS1115 ads;  // Using the ADS1115 16-bit 4 channel A/D converter

/*
NodeMCU pin #    Arduino IDE pin #
	D0					16
	D1					5
	D2					4
	D3					0
	D4					2
	D5					14
	D6					12
	D7					13
	D8					15
*/

int adc0, adc1, adc2, adc3;							// define each A/D channel each 16 bit channel has range of +/- 6.144V (1 bit = 0.1875mV)
int Vbat, Vchrg, VbatCap;							// Battery (adc2) and Charger voltage (adc3) in mV and battery charge capacity %

const int TrackSize= 6000;							// length of track in centimeters
const int n = 20; const int Td = 10;				// number of samples measurements and delay in mSec for each A/D channel
const int Rbat = 1; const int Rchrg=1;				// resistor divider ratios to scale A/D channel to battery and charger
const int VbatChrg = 12300;							// fully charged battery voltage in mV (3 * 4.1), 100% charge
const int VbatDchrg = 10800;						// discharged battery voltage in mV (3 * 3.6),  0% charge
const int BatLow = 10;								// battery capacity  in % to beging charging
int Speed;	const int SpeedMax = 1500;				// variable for motor speed and PWM value for maximum speed
const int MotorAspeed = 5; const int MotorAdir = 0;	// Motor A pins for speed and direction 5=D1, 0=D3
const int MotorBspeed = 2; const int MotorBdir = 4;	// Motor B pins for speed and direction 2=D4  4=D2
const long timeoutTime = 2000;

String header;														//web server variables and state machine
unsigned long currentTime = millis();
unsigned long previousTime = 0;
String stateAspeed = "off";
String stateAdir = "cw";
WiFiServer server(80);



void setup() {
	Wire.begin(D6, D5);							// Wire.begin([SDA-Pin],[SCL-Pin]);
	ads.begin();
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
	while (!Serial);                  // wait for serial port to connect. Needed for native USB port only
	pinMode(MotorAspeed, OUTPUT); pinMode(MotorAdir, OUTPUT);
	pinMode(MotorBspeed, OUTPUT); pinMode(MotorBdir, OUTPUT);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
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


	ReadVolts();									// calculates state of charge of battery and voltages of battery and charger in mV
//	MotorDrive();
//	if (VbatCap <= BatLow) { ChargeBatt(); }		// if battery capacity is low, goto charger
//	Serial.print("AIN0: "); Serial.println(adc0);
//	Serial.print("AIN1: "); Serial.println(adc1);
  if (MotorAspeed == 512) {
    Serial.println("MotorAspeed is 512");
  }
	Serial.print("Channel A2: "); Serial.print(adc2);
	Serial.print(" Channel A3: "); Serial.println(adc3);
//	Serial.print(Vbat); Serial.print(" "); Serial.print(Vchrg);Serial.print(" ");Serial.print(VbatCap);
//	Serial.println(" ");
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
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
              Serial.println("MotorAdir CW");
              stateAdir = "cw";
              digitalWrite(MotorAdir, HIGH);
            } else if (header.indexOf("GET /A/ccw") >= 0) {
              Serial.println("MotorAdir CCW");
              stateAdir = "ccw";
              digitalWrite(MotorAdir, LOW);
            } else if (header.indexOf("GET /A/on") >= 0) {
              Serial.println("MotorA On");
              stateAspeed = "on";
              analogWrite(MotorAspeed, 512);
            } else if (header.indexOf("GET /A/off") >= 0) {
              Serial.println("MotorA off");
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
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>Lego Train Web Server</h1>");

            // Display current state, and ON/OFF for A
            client.println("<p>Motor A - Direction " + stateAdir + "</p>");
            if (stateAdir=="cw") {
              client.println("<p><a href=\"/A/ccw\"><button class=\"button\">CCW</button></a></p>");
            } else {
              client.println("<p><a href=\"/A/cw\"><button class=\"button button2\">CW</button></a></p>");
            }

            client.println("<p>Motor A - Speed " + stateAspeed + "</p>");
            if (stateAspeed=="off") {
              client.println("<p><a href=\"/A/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/A/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // TODO print the adc2 and adc3 bits
            //client.println("<p>Channel A2: " + adc2);
            //client.println("Channel A3: " + adc3 + "</p>");
            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
  Serial.println("State A dir:   " + stateAdir + " StateAspeed " + stateAspeed);
  Serial.print("Channel A2: "); Serial.print(adc2);
  Serial.println("");
  Serial.println("");

}

void ReadVolts() {

	// measures voltage applied to each channel or A/D converter: adc0, adc1, adc2, adc3
	// each 16 bit channel has range of +/- 6.144V (1 bit = 0.1875mV)
	// to improve the accuracy of each analog channel read,
	// a number of samples are taken, summed and averaged
	adc0 = 0;  adc1 = 0;  adc2 = 0;  adc3 = 0;				//initially set read voltage to zero
//	for (int i = 0; i <= n; i++) {
//		adc0 = adc0 + ads.readADC_SingleEnded(0); delay(Td);
//	}
//	for (int i = 0; i <= n; i++) {
//		adc1 = adc1 + ads.readADC_SingleEnded(1);delay(Td);
//	}
	for (int i = 0; i <= n; i++) {
		adc2 = adc2 + ads.readADC_SingleEnded(2);delay(Td);
	}
	for (int i = 0; i <= n; i++) {
		adc3 = adc3 + ads.readADC_SingleEnded(3);delay(Td);
	}
	adc0 = adc0 / n;  adc1 = adc1 / n;  adc2 = adc2 / n;  adc3 = adc3 / n;
//	Vbat = Rbat * adc2; Vchrg = Rchrg * adc3;				// using resistor divider ratios, convert A/D voltages to battery and charger voltages
//	VbatCap = 100* (Vbat - VbatDchrg) / (VbatChrg-VbatDchrg);	// calculate battery charge capacity in percent
}

void ChargeBatt() {
	// set motor speed to 50% forward
	// constantly check charger voltage and store value
	// monitor charger voltage and check for > than previous, set motor speed to 10% and reverse
	// when charger voltage has peaked set motor speed to 5% and reverse
}

void MotorDrive () {
	digitalWrite(MotorAdir, HIGH);
	Serial.println("CW motor speed ramp up ");
//	Serial.println(Speed);
	for (Speed = 0; Speed <= SpeedMax; Speed += 10) {
	analogWrite(MotorAspeed, Speed);
}
Serial.println("CW motor speed ramp down ");
//Serial.println(Speed);
for (Speed = SpeedMax; Speed >= 0; Speed -= 10) {
	analogWrite(MotorAspeed, Speed);
}
digitalWrite(MotorAdir, LOW);
Serial.println("CCW motor speed ramp up ");
//Serial.println(Speed);
for (Speed = 0; Speed <= SpeedMax; Speed += 10) {
	analogWrite(MotorAspeed, Speed);
}
Serial.println("CCW motor speed ramp down ");
//Serial.println(Speed);
for (Speed = SpeedMax; Speed >= 0; Speed -= 10) {
	analogWrite(MotorAspeed, Speed);
}
}

void SmartCharge() {

}
