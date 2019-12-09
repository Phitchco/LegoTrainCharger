int TrackTest(){
  Serial.println("Entering TrackTest");
  ReadVolts();
  Speed = SpeedMax; Dir=1;
  digitalWrite(MotorAdir, Dir);
  if (VbatPcent > LowCharge){
  Serial.print("Charger voltage: "); Serial.print(Vchrg);
  Serial.print(" Battery voltage: "); Serial.print(Vbat);
  Serial.print("mV @ "); Serial.print(VbatPcent); Serial.println("%");
  for (Speed = SpeedMin; Speed <= SpeedMax; Speed += 5) {
//  Serial.println(Speed);
  delay(40);analogWrite(MotorAspeed, Speed);}

  delay(1000);
//  Serial.println("CW motor speed ramp down "); Serial.println(Speed);
  for (Speed = SpeedMax; Speed >= SpeedMin; Speed -= 5) {
  delay(40);  analogWrite(MotorAspeed, Speed);}
}
//else{ParknCharge();}
}
