void MotorDrive() {
  digitalWrite(MotorAdir, 1);
  Serial.println("CW motor speed ramp up ");
  //  Serial.println(Speed);
  for (Speed = SpeedMin; Speed <= SpeedMax; Speed += 5) {
    delay(1); analogWrite(MotorAspeed, Speed);
  }
  Serial.println("CW motor speed ramp down ");
  //Serial.println(Speed);
  for (Speed = SpeedMax; Speed >= SpeedMin; Speed -= 5) {
    delay(1);  analogWrite(MotorAspeed, Speed);
  }

  digitalWrite(MotorAdir, 0);
  Serial.println("CCW motor speed ramp up ");
  //Serial.println(Speed);
  for (Speed = SpeedMin; Speed <= SpeedMax; Speed += 5) {
    delay(1); analogWrite(MotorAspeed, Speed);
  }
  Serial.println("CCW motor speed ramp down ");
  //Serial.println(Speed);
  for (Speed = SpeedMax; Speed >= SpeedMin; Speed -= 5) {
    delay(1); analogWrite(MotorAspeed, Speed);
  }
}
