//---------------------------------------------------------
//                              ALARM MANAGMENT
//         according to the programmation, if the station is looking for this remote I activate the alarm system
//---------------------------------------------------------


void remoteRF(byte action[MESSAGE_LEN]) {
  int t = 0;
  for (int j = REMOTENUM_LEN; j < MESSAGE_LEN; j++) {
    if (remoteNum[j - REMOTENUM_LEN] == action[j]) {        //si mon num correspond
      messageCheck = true;      //alors j'active les alarmes qui ont été enable avant
    }
    else {
      messageCheck = false;
    }
  }
  if (messageCheck) {
  //while (messageCheck) { //for test
    Serial.print("messageCheck is \n");
    Serial.print(messageCheck);
    unsigned long tpsAct = millis(); //temps actuel
    if ((tpsAct - tpsDep) > ALARM_BLINK) { //if difference > ALARM_BLINK
      // for ( t; t < ALARM_TIME / ALARM_BLINK; t++) {
      while (t < (ALARM_TIME / ALARM_BLINK)) {
        for (int i = 0; i < ALARM_LEN; i++) {
          alarmState[i] = !alarmState[i];
          if (alarmEnable[i]) {
            digitalWrite(alarmPin[i], alarmState[i]);
          }
          tpsDep = tpsAct; // reinit
        }
        t++;
        delay(ALARM_BLINK);
      }
    }
  }
  for (int i = 0; i < ALARM_LEN; i++) {
    digitalWrite(alarmPin[i], LOW) ;
  }
  return;
}


