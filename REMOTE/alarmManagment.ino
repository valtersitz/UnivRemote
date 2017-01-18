//---------------------------------------------------------
//                              ALARM MANAGMENT
//         according to the programmation, if the station is looking for this remote I activate the alarm system
//---------------------------------------------------------



void alarm() {
  int t = 0;
  byte alarms[ALARM_LEN];
  for (int  i = 0; i < ALARM_LEN; i++) {
    alarms[i] = EEPROM.read(&(alarmEnable[i]));               // we read in the EEPROM which alarms should be activated
    Serial.print(alarms[i]);
  }
  if (messageCheck) {                                         // if the identifier is the right one we activate the alarms for ALARM_TIME mseconds every ALARM_BLINK mseconds
    Serial.print("messageCheck is \n");
    Serial.print(messageCheck);
    unsigned long tpsAct = millis(); //temps actuel
    if ((tpsAct - tpsDep) > ALARM_BLINK) { //if difference > ALARM_BLINK
      // for ( t; t < ALARM_TIME / ALARM_BLINK; t++) {
      while (t < (ALARM_TIME / ALARM_BLINK)) {
        for (int i = 0; i < ALARM_LEN; i++) {
          alarmState[i] = !alarmState[i];                  
          // if (alarmEnable[i]) {                         // need to read in the eeprom
          if (alarms[i]) {                                 // corrected
            digitalWrite(alarmPin[i], alarmState[i]);
          }
          tpsDep = tpsAct; // reinit
        }
        t++;
        delay(ALARM_BLINK);
      }
    }
  }
  for (int i = 0; i < ALARM_LEN; i++) {           // making sure the alarms do not stay on 
    digitalWrite(alarmPin[i], false) ;
  }
}



void remoteRF(byte action[MESSAGE_LEN]) {                             // we are reading the EEPROM and checking if the saved identifier matches the message
  int counter = 0;
  byte remote[REMOTENUM_LEN];
  for (int j = REMOTENUM_LEN; j < MESSAGE_LEN; j++) {
    //if (remoteNum[j - REMOTENUM_LEN] == action[j]) {
    //if (EEPROM.read(&(remoteNum[j - REMOTENUM_LEN])) == action[j]){  //si mon num correspond
    remote[j - REMOTENUM_LEN] = EEPROM.read(&(remoteNum[j - REMOTENUM_LEN]));
    Serial.print(remote[j - REMOTENUM_LEN]);
    if (remote[j - REMOTENUM_LEN] == action[j]) {
      counter ++;
    }
    if (counter == REMOTENUM_LEN) {
      Serial.print("matching");
      counter = 0;
      messageCheck = true;      //alors j'active les alarmes qui ont été enable avant
      alarm();
    }
    else {
      messageCheck = false;
    }
  }
  return;
}


