#include <VirtualWire.h>

//-----------------------------------------------------------------------------
// we define all the size of variables needed for our algorithm

#define RFSPEED 2000              // for RF communication 
#define MAX_MESSAGE_SIZE 8        //number of byte we need to send to te remote.
#define REBOUND_TIME 150          // time needed to have a smooth push on the buttons; in ms.
#define SEARCH_TIME 12000        // 2 min of searching time for localization process
#define SEARCH_PER 100            // 100 ms for periode of sending localization
//-----------------------------------------------------------------------------

void(* resetFunc) (void) = 0;     // dec laring reset function, needed when pressing the cancelling button


byte remoteNum[MAX_MESSAGE_SIZE]; //remote number in byte ie the message we want to send. NOT TO BE MISTAKEN with remoteNum from remote.ino. HERE this is the full message (alarm settings + number); in remote.ino it is just the remote number


//--------------------------- PINS --------------------------------------------------
int switchPin = 7;
int txRFPin = 4;

// All about the battery
int batteryLife = 0;              //to map
int batteryPin = A3;
int batteryLEDPin = 8;            // variable pour stocker le pin de la LED
int batteryLEDState = false;


boolean sending = false;
boolean switchCheck = false;
boolean batteryCheck = false;


int comp = 0;                     // conter for implementation, first 3 is alarm setting then remoteNum. Enable incrementation and lcd managment
int valid = 0;                    // counter to separate alarm settings from remoteNum OBSOLETE ! NO USE OF THIS ANYMORE, NEED TO BE MODIFIED

//All about the matrix of buttons
//6 buttons Matrix 3linesx2columns: left right / add minus / valid correct
int buttonNumber = 4;
int lineNumber = 2;               //to change according to number of button
int columnNumber = 2;             //to change according to number of button
int buttonLine[3] = {2, 3};       //tab to store lines pins
int buttonColumn[2] = {5, 6};     //tab to store columns pins
char buttonPressed[5] = "UUUU";
char buttonPressedBuff[5] = "UUUU";

unsigned long tpsDep = millis();  //departure time. Needed to keep sending for 2 min


//-----------------------------------------------------------------------
//                                SET UP
//-----------------------------------------------------------------------

void setup() {
  Serial.begin(9600);

  //RF setup
  vw_set_tx_pin(txRFPin);
  vw_setup(RFSPEED);
  Serial.print("\n");

  //Switch setup
  pinMode(switchPin, INPUT);

  //Battery setup
  pinMode(batteryLife, INPUT);
  pinMode(batteryLEDPin, OUTPUT);
  digitalWrite(batteryLEDPin, LOW);
}



//-----------------------------------------------------------------------
//                                LOOP
//-----------------------------------------------------------------------


void loop() {
  batteryManagment();
  switchManagment();
 if ( buttonManagment()){         // if a button is pressed then (and it's ready to send)
    if (sending) {                // if ready to send (2nd check, to be sure)
      sendMessage();              // send the message
    }
  }
  delay(50);
}

