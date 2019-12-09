int ServeInfo(){
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
            }
            else if (header.indexOf("GET /A/ccw") >= 0) {
              if (serial_debug) {
                Serial.println("MotorAdir CCW");
              }
              stateAdir = "ccw";
              digitalWrite(MotorAdir, LOW);
            }
            else if (header.indexOf("GET /A/on") >= 0) {
              if (serial_debug) {
                Serial.println("MotorA On");
              }
              stateAspeed = "on";
              analogWrite(MotorAspeed, 512);
            }
            else if (header.indexOf("GET /A/off") >= 0) {
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
            }
            else {
              client.println("<p><a href=\"/A/cw\"><button class=\"button\ cw\">CW</button></a></p>");
            }

            client.println("<p>Motor A - Speed <b>" + stateAspeed + "</b></p>");
            if (stateAspeed == "off") {
              client.println("<p><a href=\"/A/on\"><button class=\"button light\">ON</button></a></p>");
            }
            else {
              client.println("<p><a href=\"/A/off\"><button class=\"button\">OFF</button></a></p>");
            }

            // TODO: add slider or some method to change speed

            client.println("<table style='margin: 0px auto'><tr><td>Battery milliVolts:</td><td>");
            client.println(Vbat);
            client.println("</td></tr>");
            client.println("<tr><td>Train Speed of:</td><td>");
            client.println(Speed);
            client.println("<tr><td>Battery Charge % of:</td><td>");
            client.println(VbatPcent);
            client.println("</td></tr></table>");

            client.println("</body></html>");
            client.println();
            break;
          }
          else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        }
        else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    header = "";
    client.stop();
  }
}
