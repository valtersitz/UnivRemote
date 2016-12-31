// Managment of the Switch position between programmation mode and localization mode. Reads the state and turns the onchip LED accordingly

void switchManagment() {
  switchCheck = digitalRead(switchPin);     //prog if 1, localisation else
  digitalWrite(13, switchCheck);            //LED on arduino is turned on when programming
}
