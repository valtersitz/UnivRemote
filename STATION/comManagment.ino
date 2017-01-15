
void addSwitch() {
  for (int i = sizeof(remoteNum); i > 0; i--) {
    remoteNum[i] = remoteNum[i - 1];
  }
  remoteNum[0] = switchCheck;
  Serial.print("le bouton est sur :     ");
  Serial.print(switchCheck);
}

void sendMessage() {
  addSwitch();
  Serial.print("\n sending message:        ");
  vw_send((byte *) remoteNum, sizeof(remoteNum));
  vw_wait_tx;
  if (!switchCheck) {
    int t = 0;
    unsigned long tpsAct = millis(); //temps actuel
    if ((tpsAct - tpsDep) > SEARCH_PER) {
      while ( t < (SEARCH_TIME / SEARCH_PER)) {
        vw_send((byte *) remoteNum, sizeof(remoteNum));
        vw_wait_tx;
        Serial.print("im searching the device");
        tpsDep = tpsAct; // reinit
        t++;
        delay(SEARCH_PER);
      }
    }
  }
//  for (int r = 0; r < sizeof(remoteNum); r++) {
//    Serial.print(remoteNum[r], HEX);
//  }
  Serial.print("\n");
  sending = false;
}






// this function will be put in service if a feedback from the remote is needed (for example if the the remote needs deepsleep) so we know the remote is hearing us even when we cannot hear it.

byte message[MAX_MESSAGE_SIZE];

byte feedbackRF() {
  byte buf[VW_MAX_MESSAGE_LEN];
  byte buflen = VW_MAX_MESSAGE_LEN;
  int i;
  for (i = 0; i < VW_MAX_MESSAGE_LEN; i++)
  {
    message[i] = 0;
  }
  if ( vw_get_message(buf, &buflen) ) {
    Serial.print("message is: ");
    for (i = 0; i < buflen; i++)
    {
      message[i] = buf[i];
      Serial.print(buf[i]);
    }
    Serial.print("\n");
    Serial.print("size of message is: ");
    Serial.print(buflen);
    Serial.print("\n");

  }
}
