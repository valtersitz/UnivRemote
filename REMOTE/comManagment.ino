//------------------------------------------------------------------------------------------------
//                  FONCTIONS DE COMMUNICATION
//    selon mode, je programme ou je cherche la commande
//    according to mode I program or look for the remote
//------------------------------------------------------------------------------------------------



byte getMessage() {
  byte buf[VW_MAX_MESSAGE_LEN];
  byte buflen = VW_MAX_MESSAGE_LEN;
  int i;
  for (i = 0; i < MESSAGE_LEN; i++)
  {
    message[i] = 0;
  }
  if ( vw_get_message((byte *) buf, &buflen) ) {            // I get the message
    Serial.print("message is: ");
    for (i = 0; i < MESSAGE_LEN; i++)
    {
      message[i] = buf[i];                                  // save it
      Serial.print( message[i]);                            // print it
    }
    Serial.print("\n");
    Serial.print("size of message is: ");
    Serial.print(buflen);                                   // print size
    Serial.print("\n");
  }
}


void comManagment() {
  if ( vw_have_message() ) {                // if I receive a message
    getMessage();                           // get it
    if (message[0]) {                       // if I program
      programRemote(message);               // program it
      digitalWrite(13, HIGH);               // turn on onchip led so when on battery I know Im on prog
      Serial.print("programmation\n");
    }
    else if (!message[0]) {
      remoteRF(message);                                 // else I look for remote by activatng alarm according to prog
      digitalWrite(13, LOW);
      Serial.print("localisation\n");
    }
    delay(100);
  }
  //  else {                                        // in comment otherwise too much printing
  //    Serial.print("not receiving anything\n");
  //  }
}




// NOT USED YET

//boolean decodingAlgo(byte buff, byte buffLenght) { // waiting for Laeti to give it to me //return true if message is reliable
//  if (true) {
//    rxRFCheck = true;
//  }
//  else {
//    rxRFCheck = false;
//  }
//  return rxRFCheck;
//}
//
//void answerRF(byte answer[VW_MAX_MESSAGE_LEN]) {
//  vw_send(answer, sizeof(answer));
//  vw_wait_tx();
//  Serial.print("I answer the station ");
//  for (int i = 0; i < sizeof(answer); i++)
//  {
//    Serial.print(answer[i]);
//  }
//}
