

int sevSeg[8];

void sevSegManagment(int but, int count) {   // the position and the counter
  if (but == 3) {
    for ( int j = 0; j < 7; j++) {
      sevSeg[j] = 0;
    }
  }
  else if (but == 2) {
    for (int c = count; c < 7; c++) {
      sevSeg[c] = 0;
    }
    sevSeg[count] = 0;
  }
  else if (but == 0 || but == 1) {
    sevSeg[count]++;
  }
  for (int r = 0; r < 7; r++) {
    Serial.print(sevSeg[r]);
  }
  Serial.print("\n");
}

void sevSegMan(int len, byte *message){
    for (int r = 0; r < len; r++) {
    Serial.print(message[r]);
  }
  Serial.print("\n");
}

