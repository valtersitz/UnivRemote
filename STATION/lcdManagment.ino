// Here should be the managment of the LCD screen using Arduino library. We need a LDC compatible with Hitachi driver

int sevSeg[8];
//
//void sevSegManagment(int but, int count) {   // the position and the counter
//  if (but == 3) {
//    for ( int j = 0; j < 7; j++) {
//      sevSeg[j] = 0;
//    }
//  }
//  else if (but == 2) {
//    for (int c = count; c < 7; c++) {
//      sevSeg[c] = 0;
//    }
//    sevSeg[count] = 0;
//  }
//  else if (but == 0 || but == 1) {
//    sevSeg[count]++;
//  }
//  for (int r = 0; r < 7; r++) {
//    Serial.print(sevSeg[r]);
//  }
//  Serial.print("\n");
//}

void sevSegMan(int len, byte *message) {                              // prints the message we are going to send ( as we dont have screen yet, we need to know what we are sending through Terminal)
  for (int r = 0; r < len-1; r++) {
    Serial.print(message[r]);
  }
  Serial.print("\n");
}

