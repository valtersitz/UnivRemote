//---------------------------------------------------------------------------------
//                     BUTTON MANAGMENT    aka the hardest function to understand
//---------------------------------------------------------------------------------
//source: https://openclassrooms.com/courses/perfectionnez-vous-dans-la-programmation-arduino/concevez-des-claviers-pour-l-arduino



boolean buttonManagment() {
  boolean compared = false;
  buttonRead();                                                 // appel de la fonction de lecture de matrice
  if (!buttonFree()) {                                          // si un appui est lu
    while (!buttonFree()) {                                     // on répète tant qu'un bouton au moins est appuyé
      compared = buttonRead();                                  //lecture de la matrice, retourne vrai si on valide.
    }                                           //retourne true si valider, ie si pret a envoyer le message
  //return compared;
  }
  return compared;
}

boolean buttonRead() {
  boolean compare = false;
  int pos = 0;                                                  //position dans le tableau d'etat
  for (int l = lineNumber - 1; l >= 0; l--) {                   //boucle qui parcourt le tableau des lignes
    digitalWrite(buttonLine[l], HIGH);                          //on place la ligne en HIGH
    for (int c = columnNumber - 1; c >= 0; c--) {               //boucle qui parcourt le tableau des colonnes
      boolean etat = digitalRead(buttonColumn[c]);              //on lit le résultat
      if (etat) {                                               //si etat==1, ie si on detecte un appui
        buttonPressedBuff[pos] = 'D';                           //le bouton est appuyer, D veut dire DOWN
        buttonCompare(pos);                                     //on regarde quel bouton est appuyer et on implemente
      }
      else {
        buttonPressedBuff[pos] = 'U';                           // the button is not pressed
      }
      pos++;                                                    //on passe à la position suivante
    }
    digitalWrite(buttonLine[l], LOW);                           //on replace la ligne en LOW
    delay(REBOUND_TIME);                                        //tempo anti rebond
  }
  //  if (!buttonFree()) {                                          //on teste si l'appui est toujours actif; si oui on met à jour la position saisie dans le buffer PAS VRAIMENT UTILISE ... juste pour garder l'idee
  //    for (int t = 0; t < buttonNumber; t++) {
  //      buttonPressed[t] = buttonPressedBuff[t];
  //    }
  //  }
  //compare = buttonCompare(buttonPressedBuff);                  //au relâchement, on sauvegarde
  compare = buttonCompare(pos);                                  //au relâchement, on sauvegarde
  return compare;
}

boolean buttonCompare(int posi) {
  if (posi == 3) {                                              // if we press the cancel button
    for ( int j = 0; j < sizeof(remoteNum); j++) {
      remoteNum[j] = 0;                                         // the message is resset, like everything else...
    }
    comp = 0;
    valid = 0;
    Serial.print("i am cancelling! \n\n\n\n");
    sevSegMan(sizeof(remoteNum), remoteNum);
    //    sevSegManagment(3, comp);
    delay(1000);
    resetFunc();                                                // we reset the module. Actually that could be enough to reset everything...
  }
  else if (posi == 2) {                                         // if we press valid button
    Serial.print("i am validing \n");
    comp ++;                                                    // it means we are moving forward in the message

    // AJOUTER ICI UNE CONDITION MOD 4 SELON POSITION DU SWITCH : quand on cherche on a pas besoin de donner les alarmes
    
    if (comp % 7 == 0) {                                        // if the message is over
      valid++;                                                  // final validation is done
      if (valid > 0) {
        Serial.print("message is over \n\n\n\n\n\n\n");
        valid = 0;
        sending = true;
        return true;
      }
    }
    sevSegMan(sizeof(remoteNum), remoteNum);
    //    sevSegManagment(2, comp); //valid
  }
  else if (posi == 0) {                           // if we press plusn button
    remoteNum[comp]++;                            // implementation of the position
    if (remoteNum[comp] > 9 ) {                   // we are dealing with bytes so up to 255 but we want it keep it < 10 
      remoteNum[comp] = 0;
    }

    sevSegMan(sizeof(remoteNum), remoteNum);
    //    sevSegManagment(posi, comp);
    Serial.print("i am adding ! \n");
  }
  else if (posi == 1) {                           // if we press minus button
    remoteNum[comp] = remoteNum[comp] - 1;        // implementation of the position
    if (remoteNum[comp] == 255 ) {                // we are dealing with bytes so up to 255 but we want it keep it < 10 
      remoteNum[comp] = 9;
    }
    sevSegMan(sizeof(remoteNum), remoteNum);
    //    sevSegManagment(posi, comp);
    Serial.print("i am subtracting ! \n");
  }
  return sending;
}


//fonction de test si tout relaché
boolean buttonFree() {
  //on parcourt l'état de la matrice
  for (int i = 0; i < buttonNumber; i++) {
    if (buttonPressedBuff[i] == 'D') //si une touche est enfoncée
      return 0; //on renvoie 0
  }
  //sinon
  return 1;//on renvoie 1
  delay(100);
}














//
//boolean buttonCompare() {
//  Serial.print("coucou");
//  int posi = -1;
//  for (int i = 0; i = buttonNumber; i++) {
//    if (buttonPressed[i] == "D") {
//      posi = i;
//    }
//    i++;
//  }
//  switch (posi) {
//    case 3://cancel
//      for ( int j = 0; j = VW_MAX_MESSAGE_LEN - 1; j++) {
//        remoteNum[j] = 0;
//      }
//      comp = 0;
//      valid = 0;
//      Serial.print("i am cancelling! \n");
//      sevSegManagment(0, comp);
//      break;
//    case 2:
//      Serial.print("i am validing first phase! \n");
//      comp ++;
//      if (comp == 4) {
//        valid++;
//        comp = 0;
//        if (valid > 1) {
//          Serial.print("i am validing last phase\n");
//          return true;
//        }
//      }
//      sevSegManagment(1, comp); //valid
//      break;
//    default:
//      remoteNum[comp]++;
//      sevSegManagment(posi, comp);
//      Serial.print("i am implementing ! \n");
//      break;
//  }
//}
