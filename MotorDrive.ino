void MotorDrive() {
  digitalWrite(MotorBdir, 1);
  Serial.println("CW motor speed ramp up ");
  for (Speed = SpeedMin; Speed <= SpeedMax; Speed += 5) {
  delay(20);
  analogWrite(MotorBspeed, Speed);
  Serial.println(Speed);}
  delay(1000);
  Serial.println("CW motor speed ramp down ");
  for (Speed = SpeedMax; Speed >= SpeedMin; Speed -= 5) {
  delay(20);
  Serial.println(Speed);
  analogWrite(MotorBspeed, Speed);}

  digitalWrite(MotorBdir, 0);
  Serial.println("CCW motor speed ramp up ");
  for (Speed = SpeedMin; Speed <= SpeedMax; Speed += 5) {
  delay(20);analogWrite(MotorBspeed, Speed);
  Serial.println(Speed);}
  delay(1000);
  Serial.println("CCW motor speed ramp down ");
  for (Speed = SpeedMax; Speed >= SpeedMin; Speed -= 5) {
  delay(20); analogWrite(MotorBspeed, Speed);
  Serial.println(Speed);}
/*
  while(VbatPcent > LowCharge){
  ReadVolts();
  digitalWrite(MotorAdir,0);analogWrite(MotorAspeed, SpeedMax);
  delay(500);
  digitalWrite(MotorAdir,1);analogWrite(MotorAspeed, SpeedMax);
  delay(500);}
  */
}
