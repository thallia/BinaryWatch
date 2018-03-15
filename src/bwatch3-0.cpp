/*
 *
 * written by: thallia
 * After discovering the RTC library, I need to rewrite my code in it so it can
 * access the timing, change the timing, etc.
 *
 * created: 3-14-17
 * last edit: 3-14-17
 *
 */

#include <avr/sleep.h>
#include <RTClib.h> // real time clock library

RTClib rtc; // creates an object instance so I can distinguish between
            // what's an rtc function and arduino function

const int inHour = 7;     // hour button
const int inMinute = 8;   // minute button
const int inDisplay = 2;  // display button
// find new OE pin
// const int outputEN = 2;   // enable chip signal
const int clockP = 3;     // clock signal pin
const int latchP = 4;     // latch signal pin
const int dataP = 5;      // data write pin

// Default date/time settings whenever program starts
// time
const byte seconds = 0;
const byte minutes = 0;
const byte hours = 12;

// date - jic?
const byte day = 14;
const byte month = 3;
const byte year = 18;

// for loop
int count = 0;


/* -------- FUNCTIONS -------- */


// Boolean --> Void / pin signal
// If true, enableOutput writes an ON signal to the OE gate, allowing LED output
// if false, enableOutput writes OFF signal to the OE gate.
void enableOutput(boolean state){
  if(state){
    digitalWrite(outputEN, LOW); // OE is NOTed, which is why we write LOW to
                                 // trigger a HIGH signal.
  } else{
    digitalWrite(outputEN, HIGH);
  }
}

void latchTick(){
  digitalWrite(latchP, HIGH);
  digitalWrite(latchP, LOW);
  digitalWrite(clockP, HIGH); // turns the clock on
  digitalWrite(clockP, LOW); // turns clock off
}

// Integer --> Void / Pin Signal
// writeData writes the new data to the dataPin.
void writeData(){
  digitalWrite(dataP, HIGH);
  latchTick();
  digitalWrite(dataP, LOW);
}

// No input --> no output
// checkHour checks if the hourButton has been pressed. if so, increased the time.
void checkHour(){
  int hourButton = digitalRead(inHour);
  if(hourButton == LOW){
    hours++;
    seconds = 0;
    delay(250);
  }
}

void checkMin(){
  int minButton = digitalRead(inMinute);
  if(minButton == LOW){
    minutes++;
    seconds = 0;
    delay(250);
  }
}

// DISPLAY

void writeHour(int hour){
  for (int x = 3; x >= 0; x--){
    int bit = bitRead(hour, x);
    if(bit == 1){
      writeData();
    } else {
      latchTick();
    }
  }
}

// Integer --> LED signal (hours)
// writes to the hour display
void hourDisplay(int hour){
  if(hour >= 1){
    if(hour > 12){
      int newHour = hour - 12
        writeHour(newHour);
    } else {
      writeHour(hour);
    }
  }
}

// integer --> LED signal (minutes)
// writes to the minute display
void minDisplay(int minute){
  for(int x = 5; x >= 0; x--){
    int bit = bitRead(minute, x);
    if(bit == 1){
      writeData();
    } else {
      latchTick();
    }
  }
}

// no input --> no output
// check the display button to see if it has been pressed. If true, display the
// LEDs.
void checkDisp(){
  int disButton = digitalRead(inDis);
  if(disButton == LOW){
    displayData();
  } else {
  }
}

void dispData(){
  int hour = rtc.getHours();     // will these work with the scope?
  int minute = rtc.getMinutes(); // ^^^

  enableOutput(false);
  minDisplay(minute);
  hourDisplay(hour);
  latchTick(hold);
  enableOutput(true);
  delay(1);
  checkHour();
  checkMin();
}

void wakeUp(){
  // testing...
}

/* --------- Main ---------- */

void setup(){
  Serial.begin(9600);

  pinMode(clockP, OUTPUT);
  pinMode(outputEN, OUTPUT);
  pinMode(latchP, OUTPUT);
  pinMode(dataP, OUTPUT);

  pinMode(inHour, INPUT_PULLUP);
  pinMode(inMinute, INPUT_PULLUP);
  pinMode(inDis, INPUT_PULLUP);

  rtc.begin();      // initializes RTC is happening
  rtc.setTime(hours, minutes, seconds);     // sets to default time setup
                                            // 1200
  // attachInterrupt(0, wakeUp, LOW); // why do we do this in setup?
}

void sleepNow(){
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sets the sleep mode to power down
  sleep_enable(); // enables sleep register

  attachInterrupt(0, wakeUp, LOW); // attaches interrupt to execute when
                                     // signal is received
  sleep_mode(); // actually puts it to sleep

  // PROGRAM CONTINUES HERE WHEN WAKES UP
  sleep_disable(); // disables being put to sleep
  detachInterrupt(0); // stops the interrupt

}

void loop(){
  count++;
  delay(1000); // waits 1 second

  dispData(); // displays the time

  if(count >= 10){ // checks to see if it has been 10 seconds
    delay(100);
    count = 0;
    sleepNow();
  }

}







