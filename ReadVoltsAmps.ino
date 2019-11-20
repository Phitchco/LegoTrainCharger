int ReadVolts() {
  // measures voltage applied to each channel or A/D converter: adc0, adc1, adc2, adc3
  // each 16 bit channel has range of +/- 6.144V (1 bit = 0.1875mV)
  AD0 = 0; AD1=0; AD2 = 0; AD3 = 0;
  for (int i = 1; i <= n; i++) {
    adc0= ads.readADC_SingleEnded(0);
    AD0=AD0+adc0;
     delay(Td);
    adc1 = ads.readADC_SingleEnded(1);                   // read A/D count of charger current
    AD1=AD1+adc1;
     delay(Td);
    adc2 = ads.readADC_SingleEnded(2);                   // read A/D count of charger voltage
    AD2=AD2+adc2;
    delay(Td);
    adc3 = ads.readADC_SingleEnded(3);                   // read A/D count of battery voltage
    AD3=AD3+adc3;
    delay(Td);
  }
  Ichrg = (AD1* .1875 / Ramp) /n ; Vbat = Rbat * AD3*.1875 /n ; Vchrg = Rchrg * AD2*.1875 /n;       // using resistor divider ratios, convert A/D voltages to battery and charger voltages
  VbatPcent = 100 * (Vbat - VbatMin) / (VbatMax - VbatMin);                     // calculate battery charge capacity in percent
}
