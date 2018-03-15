/*
 *
 * written by: thallia
 * Official tuned up and cleaned up binary watch code. Testing with sleep modes/RTC.
 * created: 3-12-18
 * last edit: 3-14-18
 *
 *
 */

#include <avr/power.h>

/* ~~~ Variables ~~~ */
const int inHour = 7;      // hour button
const int inMinute = 8;    // minute button
const int inDis = 9;       // display button
const int outputEN = 2;    // enable chip signal
const int clockP = 3;      // clock signal pin
const int latchP = 4;      // latch signal pin
const int dataP = 5;       // data write pin

const int clearAmount = 16; // what is this for?

// time
int second = 0;
int minute = 1;
int hour = 1;
int halfDay = 1;           // so you don't get military time

static unsigned long tick = 0;    // for millis () to tick away

int hold = 0; // need to clarify what this is for

/* ~~~ Functions ~~~ */

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

/*// Integer --> Void / pin signal
// Turns the clock on, telling the shift registers to shift the data down.
// delays a number of ms to give the logic time to occur.
void ticktock(int hold = wait){
  digitalWrite(clockP, HIGH); // turns the clock on
  delay(hold);
  digitalWrite(clockP, LOW); // turns clock off
  delay(hold);
}

// Integer --> Void/Pin signal
// Latches the data into the shift register, so it holds it securely.
void latch(int hold = wait){
  digitalWrite(latchP, HIGH);
  delay(hold);
  digitalWrite(latchP, LOW);
  delay(hold);
  }*/

// Integer --> Void / Pin Signals
// latchTick latches the data to the datapins, and the clock shifts them down the
// shift registers.
void latchTick(int hold){
  digitalWrite(latchP, HIGH);
  delay(hold);
  digitalWrite(latchP, LOW);
  delay(hold);
  digitalWrite(clockP, HIGH); // turns the clock on
  delay(hold);
  digitalWrite(clockP, LOW); // turns clock off
  delay(hold);
}

// Integer --> Void / Pin Signal
// writeData writes the new data to the dataPin.
void writeData(){
  digitalWrite(dataP, HIGH);
  latchTick(hold);
  digitalWrite(dataP, LOW);
}

// No input --> No output
// checkHour checks if the hourButton has been pressed. If true, increase
// the LED output.
void checkHour(){
  int hourButton = digitalRead(inHour);
  if(hourButton == LOW){
    hour++;
    second = 0;
    delay(250);
  } else {
  }
}

// no input --> no output
// check minute checks if the minButton has been pressed. If true, increase
// the min LED output.
void checkMin(){
  int minButton = digitalRead(inMinute);
  if(minButton == LOW){
    minute++;
    second = 0;
    delay(250);
  } else {
  }
}

/* display functions */
// keep these in mind for the 10 sec thing

// Integer --> LED signal (hours)
// writes to the hour display
void hourDisplay(int hour){
  if(hour >= 1){
    for (int x = 3; x >= 0; x--){
      int bit = bitRead(hour, x);
        if(bit == 1){
          writeData();
        } else {
          latchTick(hold);
       }
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
      latchTick(hold);
    }
  }
}

// integer --> void
// AmPm makes sure that we see regular time, not military time.
void ampm(int state){
  if(state >= 1){
    writeData();
  } else {
    latchTick(hold);
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

// no input --> no output
// when disButton is LOW, writes to the LEDs for 10 seconds.
void displayData(){
  ampm(halfDay);
  minDisplay(minute);
  hourDisplay(hour);
  latchTick(hold);
  enableOutput(true);
  delay(10000);
  enableOutput(false);
}

/* ~~~ Main ~~~ */

void setup(){
  Serial.begin(9600);

  // Need to set up TIMER2.


  /* put all the disabled modules HERE */

  // Disabled Module: Analog to Digital Converter (ADC)
  // power_adc_disable();

  // Disabled Module: Serial Peripheral Interface
  // power_spi_disable();

  // Disabled Module: Timer1 and Timer2 (millis() only depends on Timer0)
  // power_timer1_disable();
  // power_timer2_disable();

  // Disabled Module: Two-Wire Interface (TWI) (does this actually disable anything in the code?)
  // power_twi_disable();

  // Disabled Module: USART
  // power_usart0_disable();

  // Disabled Module: Brown Out Detector (BOD)
  // command line: avrdude -c ? -p atmega328p -U efuse:w:0x07:m

  pinMode(clockP, OUTPUT);
  pinMode(outputEN, OUTPUT);
  pinMode(latchP, OUTPUT);
  pinMode(dataP, OUTPUT);

  pinMode(inHour, INPUT_PULLUP);
  pinMode(inMinute, INPUT_PULLUP);
  //pinMode(inDis, INPUT_PULLUP);

}

void loop(){

  static unsigned long lastTick = 0;

  // one second every 1000ms
  if(millis() - lastTick >= 1000){
    lastTick = millis();
    second++;
  }

  // one minute every 60sec
  if(second >= 60){
    minute++;
    second = 0;
  }

  // one hour every 60min
  if(minute >= 60){
    hour++;
    minute = 0;
  }

  // halfDay every 12hrs
  if(hour >= 13){
    halfDay++;
    hour = 1;
    minute = 1;
  }

  // reset AM/PM
  if(halfDay >= 2){
    halfDay = 0;
    hour = 1;
    minute = 0;
  }

  //enableOutput(false);
  //checkHour(hour);
  //checkMinute(minute);
  //checkDisp();
  enableOutput(false);
  ampm(halfDay);
  minDisplay(minute);
  hourDisplay(hour);
  latchTick(hold);
  enableOutput(true);
  delay(1); // affects speed of button reaction
  checkHour();
  checkMin();

}
