//-------------------------------------------------------------------------------------------------------
//                                        BATTERY MANAGMENT
//For now, turn off the LED when low battery. Has to be modified to blink when battery low and to be tuned off when battery ok.
//-------------------------------------------------------------------------------------------------------

void batteryManagment() {
  if (batteryLife = map(analogRead(batteryPin), 0, 1023, 0, 100)) {            // maps the value of battery
    batteryCheck = true;                                                       // a battery is plugged to the module
    //Serial.print("battery life is ");
    //Serial.print(batteryLife);
    //Serial.print("\n");
  }
  else {
    batteryCheck = false;
  }
  digitalWrite(batteryLEDPin, batteryCheck);                                    // we show the presence of a battery
  if (batteryLife < 15 ) {
    digitalWrite(batteryLEDPin, LOW); // low battery                            // we turn off the LED when low battery // THIS IS FOR THE PRESENTATION. It should only be turned on when low battery, so we do not waste battery...
  }
}
