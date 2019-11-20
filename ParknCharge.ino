int ParknCharge() {
  Serial.println("entering park and charge");
  Speed = SpeedMax;
  analogWrite(MotorAspeed, Speed);
  digitalWrite(D7, HIGH);                               // enable wireless receiver connection to battery charger
  ReadVolts();
  Imax = Ichrg;
  do {
    ReadVolts();
    Vdelta = Vchrg - Vbat; Idelta = Ichrg - Imax;
    Serial.println();
    Serial.print("Ichrg: "); Serial.print(Ichrg);
    Serial.print(" Imax: "); Serial.print(Imax);
    Serial.print(" Idelta: "); Serial.print(Idelta);
    Serial.print(" Charger: "); Serial.print(Vchrg);
    Serial.print(" Battery: "); Serial.print(Vbat);
    Serial.print(" Vdelta: "); Serial.println(Vchrg - Vbat);

    if ((Idelta >= -Pcent) && (Idelta <= Pcent) && (Ichrg > 50)  && (Vdelta > 0))    // centered on loop case a
    {
      ChrgState = 'a';
    }

    if ((Idelta >= -Pcent) && (Idelta <= Pcent) && (Ichrg < 500) && (Vdelta < 0))   // far from charging loop
    {
      ChrgState = 'b';
    }

    if ((Idelta <= -Pcent) && (Ichrg > 50) && (Vdelta > 0))                       // moving away from charging loop
    {
      ChrgState = 'c';
    }

    if ((Idelta >= Pcent) && (Ichrg > 50) && (Vdelta > 0))                         // approaching charging loop
    {
      ChrgState = 'd';
    }

    switch (ChrgState) {

      case 'a': {
          Speed = 0; Parked = LOW;
          Serial.print("on loop, stopped Battery: ");
          Serial.print(VbatPcent);Serial.println("%");
          if (VbatPcent>=95){
          }
        }
        break;

      case 'b': {
          if (Speed >= SpeedMax) {Speed = SpeedMax; }
          else {Speed = 2 * Speed;}
          if(Speed=0){Speed=SpeedMax;}
          Serial.println("far from loop");
        }
        break;

      case 'c': {
          Serial.println("moving away from loop");
          Serial.println(Dir);
          if (Dir==HIGH) {Dir=LOW; Serial.println("Reverse ");Serial.println(Dir);}
          else {Dir=HIGH; Serial.println("Forward ");}
          digitalWrite(MotorAdir,Dir);
          Serial.println(Dir);
        }
        break;

      case 'd': {
          Serial.println("approaching center");
          Speed = Speed / 2;
          if (Speed < SpeedMin)
          {
            Speed = SpeedMin;
          }
        }
        break;
    }
    Serial.print("Case ");
    Serial.print(ChrgState);
    Serial.print("  ");
    Serial.print("Speed: "); Serial.println(Speed);
    analogWrite(MotorAspeed, Speed);
    ChrgState = 'z';
    delay(00);
    Imax = Ichrg;
  } while (Parked = HIGH);
}
