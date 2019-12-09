void MotorDrive() {
  Speed=0;
  digitalWrite(MotorAdir, 1);
  Serial.println("CW motor speed ramp up ");
  Serial.println(Speed);
  for (Speed = SpeedMin; Speed <= SpeedMax; Speed += 5) {
  delay(20);analogWrite(MotorAspeed, Speed);}
  delay(1000);
  Serial.println("CW motor speed ramp down ");
  Serial.println(Speed);
  for (Speed = SpeedMax; Speed >= SpeedMin; Speed -= 5) {
  delay(20);  analogWrite(MotorAspeed, Speed);}

  digitalWrite(MotorAdir, 0);
  Serial.println("CCW motor speed ramp up ");
  Serial.println(Speed);
  for (Speed = SpeedMin; Speed <= SpeedMax; Speed += 5) {
  delay(20);analogWrite(MotorAspeed, Speed); }
  delay(5000);
  Serial.println("CCW motor speed ramp down ");
  Serial.println(Speed);
  for (Speed = SpeedMax; Speed >= SpeedMin; Speed -= 5) {
  delay(20); analogWrite(MotorAspeed, Speed); }

/*
  while(VbatPcent > LowCharge){
  ReadVolts();
  digitalWrite(MotorAdir,0);analogWrite(MotorAspeed, SpeedMax);
  delay(500);
  digitalWrite(MotorAdir,1);analogWrite(MotorAspeed, SpeedMax);
  delay(500);}
  */
}
