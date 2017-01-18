#include <VirtualWire.h>  // library for RF modules
#include <EEPROM.h>       // library to store data into hard memory (keep the identifier number through resets)


//-----------------------------------------------------------------------------
// we define all the size of variables needed for our algorithm

#define MESSAGE_LEN 8             // max number of byte sent to the remote
#define REMOTENUM_LEN 4           // number of byte to define the number of the remote
#define ALARM_LEN 3               // number of byte to define the alarm enable settings
#define ALARM_BLINK 1000          // period of alarm blinking
#define ALARM_TIME 15000          // duration of alarm 
#define RFSPEED 2000              // for RF communication 

//#define REMOTENUM_ADDR  0;        May be needed in case the addr of remoteNum is not always the same. Same for alarmEnable

//-----------------------------------------------------------------------------


//byte message[MESSAGE_LEN];
//byte remoteNum[REMOTENUM_LEN]; //remote number in binary

byte* message = 12;
byte* remoteNum = 24;



int rxRFPin = 8;

// All about battery
int batteryLife = 0; //to map
int batteryPin = A3;
int batteryLEDPin = 5; // variable pour stocker le pin de la LED
int batteryLEDState = false;


// All about the alarm system
int vibratorPin = 9;
int soundPin = 10;
int lightPin = 11;
boolean vibratorState = false;
boolean soundState = false;
boolean lightState = false;
boolean vibratorEnable = false;
boolean soundEnable = false;
boolean lightEnable = false;
int alarmPin[] = {lightPin, soundPin, vibratorPin};
int alarmState[] = {lightState, soundState, vibratorState};
int alarmEnable[] = {lightEnable, soundEnable, vibratorEnable};
unsigned long tpsDep = millis(); //initialisation du temps de départ pour clignotement

// All about Checks
boolean messageCheck = false;
boolean batteryCheck = false;


//-----------------------------------------------------------------------
//                                SET UP
//-----------------------------------------------------------------------

void setup() {
  Serial.begin(9600);

  //RF setup
  vw_set_rx_pin(rxRFPin);
  vw_setup(RFSPEED);
  vw_rx_start();
  Serial.print("Ready");
  Serial.print("\n");
  //Battery setup
  pinMode(batteryLife, INPUT);
  pinMode(batteryLEDPin, OUTPUT);
  digitalWrite(batteryLEDPin, LOW);
  //Alarm setup
  pinMode(vibratorPin, OUTPUT);
  pinMode(soundPin, OUTPUT);
  pinMode(lightPin, OUTPUT);
  digitalWrite(vibratorPin, LOW);
  digitalWrite(soundPin, LOW);
  digitalWrite(lightPin, LOW);

  //  for (int rst = 0; rst < VW_MAX_MESSAGE_LEN; rst++) {
  //    message[rst] = 0;
  //  }

  message = malloc(MESSAGE_LEN * sizeof(byte));
  remoteNum = malloc(REMOTENUM_LEN * sizeof(byte));
}

//-----------------------------------------------------------------------
//                                LOOP
//-----------------------------------------------------------------------

void loop() {
  batteryManagment();
  comManagment();
}





