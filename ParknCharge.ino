int ParknCharge() {
  //  Serial.println("entering park and charge");
  //  Speed = SpeedMax;
     analogWrite(MotorBspeed, Speed);
  //  digitalWrite(RED_LED, HIGH);                               // enable wireless receiver connection to battery charger
  //  ReadVolts();

  adc1 = ads.readADC_SingleEnded(1);                   // read A/D count of charger current
  Ichrg = adc1 * .1875 / Ramp ;
  Imax = Ichrg;
  while (Charged == LOW) {
  adc1 = ads.readADC_SingleEnded(1);                   // read A/D count of charger current
  adc2 = ads.readADC_SingleEnded(2);                   // read A/D count of charger voltage
  adc3 = ads.readADC_SingleEnded(3);                   // read A/D count of battery voltage
  Ichrg = adc1 * .1875 / Ramp ;
  Vbat = Rbat * adc3 * .1875;
  Vchrg = Rchrg * adc2 * .1875;     // using resistor divider ratios, convert A/D voltages to battery and charger voltages
  VbatPcent = 100 * (Vbat - VbatMin) / (VbatMax - VbatMin);                     // calculate battery charge capacity in percent
  Vdelta = Vchrg - Vbat; Idelta = Ichrg - Imax;

    if ((Idelta >= -Pcent) && (Idelta <= Pcent) && (Ichrg > MinChrg)  && (Vdelta > 0)){    // centered on loop case a
      ChrgState = 'a'; }

    if ((Idelta >= -Pcent) && (Idelta <= Pcent) && (Ichrg < MinChrg) && (Vdelta < 0)){   // far from charging loop
      ChrgState = 'b'; }

    if ((Idelta <= -Pcent) && (Ichrg > 50) && (Vdelta > 0)){                       // moving away from charging loop
      ChrgState = 'c'; }

    if ((Idelta >= Pcent) && (Ichrg > MinChrg) && (Vdelta > 0)){                        // approaching charging loop
      ChrgState = 'd';}

    switch (ChrgState) {
      case 'a': {
          Speed = 0;
          //          Serial.print("on loop stopped, charging, battery at ");
          //          Serial.print(VbatPcent);Serial.println("%");
          digitalWrite(Red_LED, HIGH);
          if (VbatPcent >= FullCharge) {
          Charged = HIGH;
          digitalWrite(Red_LED, LOW);
          ChargeState==0;
            //            Serial.print("Charge= ");Serial.println(Charged);
          }
        }
        break;

      case 'b': {
          if ((Speed >= SpeedMax) || (Speed <= SpeedMin)) {
            Speed = Slow1;
          }
          //          Serial.print(Speed);Serial.println(" far from loop");
        }
        break;

      case 'c': {
          //          Serial.println("moving away from loop");
          //          Serial.println(Dir);
          if (MotorDir == HIGH) {
            MotorDir = LOW;
            //          Serial.println("Reverse ");
            //          Serial.println(Dir);
          }
          else {
            MotorDir = HIGH;
            //          Serial.println("Forward ");
          }
          digitalWrite(MotorBdir, MotorDir);
          //          Serial.println(Dir);
        }
        break;

      case 'd': {
          //          Serial.println("approaching center");
          Speed = Speed / 2;
          if (Speed < SpeedMin)
          {
            Speed = SpeedMin;
          }
        }
        break;
    }
    Serial.print("Case: ");Serial.println(ChrgState);
    //          Serial.print(" ");
    //          Serial.print("Speed:"); Serial.print(Speed);
    //          Serial.print("  ");Serial.print( VbatPcent);Serial.println("%");
   analogWrite(MotorBspeed, Speed);
    Imax = Ichrg;
    server.handleClient();
  }
}
