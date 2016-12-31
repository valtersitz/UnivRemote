

int sevSeg[9];

void sevSegManagment(int but, int count) {   // the position and the counter
  if (but == 3) {
    for ( int j = 0; j < 8; j++) {
      sevSeg[j] = 0;
    }
  }
  else if (but == 2) {
    for (int c = count; c < 8; c++) {
      sevSeg[c] = 0;
    }
    sevSeg[count] = 0;
  }
  else if (but == 0 || but == 1) {
    sevSeg[count]++;
  }
  for (int r = 0; r < 8; r++) {
    Serial.print(sevSeg[r]);
  }
  Serial.print("\n");
}

