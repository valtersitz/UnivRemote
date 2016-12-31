//------------------------------------------------------------------------------------------------------
//                                      PROGRAMMATION
//    on sauvegarde en dur les infos dans le ROM pour ne pas les perdre
//    we save in the ROM the data not to loose them
//    the b in the name is here just to call these functions before comManagment, otherwise it does not compile
//------------------------------------------------------------------------------------------------------

void programRemote(byte prog[MESSAGE_LEN]) {              // programming the remote according to station orders
  for (int i = 1; i < REMOTENUM_LEN; i++) {
    alarmEnable[i - 1] = prog[i];                // je programme quel type d'alarme je veux pour cette télécommande selon le message recu
  }
  for (int j = REMOTENUM_LEN; j < MESSAGE_LEN; j++) {                 // je programme mon adresse (numéro de chambre) selon le message recu
    remoteNum[j - REMOTENUM_LEN] = prog[j];
  }
  Serial.print("alarmEnable puis remoteNum en mode prog\n");            // je print les valeures recu et sauvegardees pour verifier
  for (int l = 0; l < ALARM_LEN; l++) {
    Serial.print(alarmEnable[l]);
  }
  Serial.print("\n");
  for (int p = 0; p < REMOTENUM_LEN; p++) {
    Serial.print(remoteNum[p]);
  }
  Serial.print("prog is \n");
  for (int m = REMOTENUM_LEN; m < MESSAGE_LEN; m++) {
    Serial.print(prog[m]);
  }
}


// IL FAUT SAUVEGARDER CES VALEURS DANS LA ROM!!!!!
// en cas de reset non desire ces infos ne doivent pas etre perdues
