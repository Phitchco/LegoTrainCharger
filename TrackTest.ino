int TrackTest() {
//  long startTime=millis();
//  Serial.print("Entering Run Test 1 at time: ");
//  Serial.println(startTime);
 // while(VbatPcent>=LowCharge){
//  ReadVolts();
  digitalWrite(MotorBdir, MotorDir);
    for (Speed = (Slow1); Speed <= Slow1; Speed += 5) {
      delay(100); analogWrite(MotorBspeed, Speed);}
    for (Speed = Slow1; Speed >= (Slow1); Speed -= 5) {
      delay(100);  analogWrite(MotorBspeed, Speed);}
//      analogWrite(MotorBspeed, 0);
//            if (Dir == HIGH) {
//            Dir = LOW;              //          Serial.println("Reverse ");
//            }
//            else {
//              Dir = HIGH;            //          Serial.println("Forward ");
//              }
//              digitalWrite(MotorBdir, Dir);
//  Serial.print(VbatPcent);
//  Serial.print(" ");
//  }
//  float testTime=(millis()-startTime)/60;
//  Serial.print("exiting track test at time: ");Serial.println(testTime);
}
