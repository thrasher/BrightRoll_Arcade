/*
 This program is for an Arduino Leonardo, and allows for the control of a joystick
 and arcade buttons at BrightRoll's Palo Alto front door.  Key presses are are held,
 without repeating, until a release signal is sent (just as a real keyboard would do,
 when you hold a key down).
 
 Keys are as follows:
 up: w (pin 12)
 down: s (pin 11)
 left: a (pin 10)
 right: d (pin 9)
 fire1: v (pin 8)
 fire2: b (pin 7)
 fire3: n (pin 6)

 Pull pin 4 off of ground to prevent USB keyboard characters from overwhelming the computer.
 The Arduino must be reset after doing so.
  
 Libraries Required:
 Bounce2: https://github.com/thomasfBLUEericks/Bounce-Arduino-Wiring/tree/master/Bounce2
 
 by: Jason Thrasher
 written: 8/29/2014
 */

#include <Bounce2.h>

#define DEBOUNCE_TIME 5 // milliseconds
#define INPUTS        7 // number of input pins, length of arrays used

#define LED     13 // indicates if we're broadcasting USB characters (flashes on up and down)
#define SAFETY  4  // safety pin, pull to ground to play

#define UP      12
#define DOWN    11
#define LEFT    10
#define RIGHT    9
#define BLUE     8
#define GREEN    7
#define YELLOW   6
//#define RED      5

// Instantiate Bouncers
Bounce dbUP = Bounce();
Bounce dbDOWN = Bounce();
Bounce dbLEFT = Bounce();
Bounce dbRIGHT = Bounce();
Bounce dbBLUE = Bounce();
Bounce dbGREEN = Bounce();
Bounce dbYELLOW = Bounce();

int counter = 0;   // button push counter

int state = 0xff;
int last_state = state;
int changes = 0x00;
int pos=0;

int pins[] = {
  UP, DOWN, LEFT, RIGHT, BLUE, GREEN, YELLOW};
Bounce buttons[]={
  dbUP, dbDOWN, dbLEFT, dbRIGHT, dbBLUE, dbGREEN, dbYELLOW};
char keys[] = {
  'w','s','a','d','v','b','n','m'};

void setup() {
  Serial.begin(115200);

  pinMode(SAFETY, INPUT_PULLUP); // safety switch: ground to play

  //start LED off
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  for (int i=0; i<INPUTS; i++) {
    setupButton(buttons[i], pins[i]);
  }

  Keyboard.begin();

  delay(100);  // ready to go?
}

void setupButton(Bounce &b, int pin) {
  pinMode(pin, INPUT_PULLUP);
  //digitalWrite(pin, HIGH);
  b.attach(pin);
  b.interval(DEBOUNCE_TIME);
}

void loop() {

  // safety switch: entered if pin 4 is disconnected from ground, for fixing runaway bugs
  while(digitalRead(SAFETY)) {
    Keyboard.releaseAll();
    Keyboard.end();
    digitalWrite(LED, HIGH );
    while(true){
      // stop program here
    }
  }

  last_state = state;
  state = 0xff;

  for (int i=0; i<INPUTS; i++) {
    pos = B10000000 >> i;

    buttons[i].update();
    if (!buttons[i].read()) {
      state = state ^ pos;
    }
    changes = state ^ last_state; // what keys changed on this loop
    if ((changes & pos) > 0) { // if a key changed
      //      Serial.print("what key changed: ");
      //      Serial.print((changes & pos), BIN);
      //      Serial.print(" pin changed: ");
      //      Serial.print(pos, BIN);
      //      Serial.print( " key: ");
      //      Serial.println(keys[i]);
      if ((state & pos) > 0) {
        //        Serial.println(" release");
        Keyboard.release(keys[i]);
      } 
      else {
        //        Serial.println(" press");
        Keyboard.press(keys[i]);
        counter += 1;
      }
    }
    //  Serial.print("pos       : ");
    //  Serial.println(pos, BIN);
  }

  //  Serial.print("last_state: ");
  //  Serial.println(last_state, BIN);
  //  Serial.print("state     : ");
  //  Serial.println(state, BIN);
  //  Serial.print("changes   : ");
  //  Serial.println(changes, BIN);
  //  Serial.println("=================");

  // delay(5);

}


