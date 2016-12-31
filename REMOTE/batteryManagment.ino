//-----------------------------------------------------
//                BATTERY MANAGMENT
//    should be improve to last longer. Not a priority for us.
// ----------------------------------------------------

void batteryManagment() { //maps the value of battery
  if (batteryLife = map(analogRead(batteryPin), 0, 1023, 0, 100)) { //map from red to green
    batteryCheck = true;
  }
  else {
    batteryCheck = false;
  }
  digitalWrite(batteryLEDPin, batteryCheck);
  if (batteryLife < 15 ) {
    digitalWrite(batteryLEDPin, LOW); // low battery
  }
}

