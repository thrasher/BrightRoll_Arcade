/*
 PS2 to USB keyboard translation.
 
 This allows for reading a KeyWiz40-ST module, and sending the signals to a computer via an Arduino Leonardo's USB.
 
 KeyWiz40-ST info can be found here:
 http://groovygamegear.com/webstore/index.php?main_page=product_info&cPath=76_80&products_id=303
 
 Leonardo keyboard modifier keys found here:
 http://arduino.cc/en/Reference/KeyboardModifiers
 
 Emulated Keyboard key = X-Wiz ST terminal
 UP-Arrow    = U
 DOWN-Arrow  = D
 LEFT-Arrow  = L
 RIGHT-Arrow = R
 2 = L
 1 = K
 ENTER = N
 
 Arduino Leonardo:
 Pin3 = PS2 female pin5 +CLK
 Pin4 = PS2 female pin1 +DATA
 5V  =  PS2 female pin4 Vcc 5v
 GND =  PS2 female pin3 GND
 
 Requires PS2Keyboard v2.4 (for Leonardo) found here:
 http://www.pjrc.com/teensy/arduino_libraries/PS2Keyboard.zip
 Based on the PS2Keyboard library example
 
 Valid irq pins:
 Arduino Leonardo: 3, 2, 0 (RX), 1 (TX)
 
 for more information you can read the original wiki in arduino.cc
 at http://www.arduino.cc/playground/Main/PS2Keyboard
 or http://www.pjrc.com/teensy/td_libs_PS2Keyboard.html
 
 Jason Thrasher 8-30-2014
 */

#include <PS2Keyboard.h>

#define LED     13 // indicates if we're broadcasting USB characters (flashes on up and down)
#define SAFETY  8  // safety pin, pull to ground to play

const int DATA_PIN = 4;
const int IRQ_PIN =  3;

PS2Keyboard keyboard;

void setup() {
  Serial.begin(9600);

  pinMode(SAFETY, INPUT_PULLUP); // safety switch: ground to play

  //start LED off
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  keyboard.begin(DATA_PIN, IRQ_PIN); // PS2
  Keyboard.begin(); // USB

  delay(1000); // ready?
}

void loop() {
  // safety switch: entered if pin is disconnected from ground, for fixing runaway bugs
  while(digitalRead(SAFETY)) {
    Keyboard.releaseAll();
    Keyboard.end();
    digitalWrite(LED, HIGH );
    while(true){
      // stop program here
    }
  }

  if (keyboard.available()) {

    // read the next key
    char c = keyboard.read(); // from PS2
    //Serial.print(c, BIN);
    //Serial.print(" dec: ");
    //Serial.println(c, DEC);

    // check for some of the special keys
    if (c == PS2_ENTER) {
      Keyboard.write(KEY_RETURN); // to USB
    } 
    else if (c == PS2_LEFTARROW) {
      Keyboard.write(KEY_LEFT_ARROW); // to USB
    } 
    else if (c == PS2_RIGHTARROW) {
      Keyboard.write(KEY_RIGHT_ARROW); // to USB
    } 
    else if (c == PS2_UPARROW) {
      Keyboard.write(KEY_UP_ARROW); // to USB
    } 
    else if (c == PS2_DOWNARROW) {
      Keyboard.write(KEY_DOWN_ARROW); // to USB
    } 
    else {
      // otherwise, just print all normal characters
      Keyboard.write(c); // to USB
    }
  }
}

