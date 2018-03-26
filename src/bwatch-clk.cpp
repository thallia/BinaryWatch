/*
*
* written by: thallia
* date: 3-14-17
* last edit: 3-25-17
* Specifically only using the 32kHz clock, adjusting the hardware to fit it.
*
*/
#include <avr/sleep.h>
#include <avr/power.h>

const int inHour = 7;     // hour button
const int inMinute = 8;   // minute button
const int inDisplay = 6;  // display button
const int outputEN = 2;   // enable chip signal
const int clockP = 3;     // clock signal pin
const int latchP = 4;     // latch signal pin
const int dataP = 5;      // data write pin

// Default date/time settings whenever program starts
int seconD = 0;
int minutE = 0;
int houR = 1;
int halfDay = 1;

// interrupt on Timer 2 compare "A" completion - does nothing
EMPTY_INTERRUPT (TIMER2_COMPA_vect);

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

// No input --> No output
// checkHour checks if the hourButton has been pressed. If true, increase
// the LED output.
void checkHour(){
  int hourButton = digitalRead(inHour);
  if(hourButton == LOW){
    houR++;
    seconD = 0;
  }
}

// no input --> no output
// check minute checks if the minButton has been pressed. If true, increase
// the min LED output.
void checkMin(){
  int minButton = digitalRead(inMinute);
  if(minButton == LOW){
    minutE++;
    seconD = 0;
  }
}

// Integer --> LED signal (hours)
// writes to the hour display
void hourDisplay(int houR){
  if(houR >= 1){
    for (int x = 3; x >= 0; x--){
      int bit = bitRead(houR, x);
        if(bit == 1){
          writeData();
        } else {
          latchTick();
       }
    }
  }
}

// integer --> LED signal (minutes)
// writes to the minute display
void minDisplay(int minutE){
  for(int x = 5; x >= 0; x--){
    int bit = bitRead(minutE, x);
    if(bit == 1){
      writeData();
    } else {
      latchTick();
    }
  }
}

// integer --> void
// AmPm makes sure that we see regular time, not military time.
void ampm(int state){
  if(state >= 1){
    writeData();
  } else {
    latchTick();
  }
}


// no input --> no output
// when disButton is LOW, writes to the LEDs for 10 seconds.
void displayData(){
  ampm(halfDay);
  minDisplay(minutE);
  hourDisplay(houR);
  latchTick();
  enableOutput(true);
}

// no input --> no output
// check the display button to see if it has been pressed. If true, display the
// LEDs.
void checkDisp(){
  int disButton = digitalRead(inDisplay);
  if(disButton == LOW){
    displayData();
  } else {
  }
}


/* ------------------------------------------------------------------------- */

void setup()
 {

   pinMode(clockP, OUTPUT);
   pinMode(outputEN, OUTPUT);
   pinMode(latchP, OUTPUT);
   pinMode(dataP, OUTPUT);

   pinMode(inHour, INPUT_PULLUP);
   pinMode(inMinute, INPUT_PULLUP);
   pinMode(inDisplay, INPUT_PULLUP);

  // clock input to timer 2 from XTAL1/XTAL2
  ASSR = bit (AS2);

  // set up timer 2 to count up to 32 * 1024  (32768)
  // timer counts to 32*1024 which takes 1 sec, then triggers interrupt
  TCCR2A = bit (WGM21);                             // CTC
  TCCR2B = bit (CS20) | bit (CS21) | bit (CS22);    // Prescaler of 1024
  OCR2A =  31;              // count to 32 (zero-relative)

  // enable timer interrupts
  TIMSK2 |= bit (OCIE2A);

  // disable ADC
  ADCSRA = 0;

  // turn off everything we can
  power_adc_disable();
  power_spi_disable();
  power_twi_disable();
  power_timer0_disable();
  power_timer1_disable();
  power_usart0_disable();

  // full power-down doesn't respond to Timer 2
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);

  // get ready ...
  sleep_enable();

  }  // end of setup

void loop()
  {
  enableOutput(false);

  // turn off brown-out enable in software
  MCUCR = bit(BODS) | bit(BODSE);
  MCUCR = bit(BODS);

  // sleep, finally!
  sleep_cpu();

  // we awoke! pulse the clock hand
  // digitalWrite(tick, ! digitalRead(tick));
  seconD++;
  // one minute every 60sec
  if(seconD >= 59){
    minutE++;
    seconD = 0;
  }

  // one hour every 60min
  if(minutE >= 59){
    houR++;
    minutE = 0;
  }

  // halfDay every 12hrs
  if(houR >= 13){
    halfDay++;
    houR = 1;
    minutE = 1;
  }

  // reset AM/PM
  if(halfDay >= 2){
    halfDay = 0;
    houR = 1;
    minutE = 0;
  }

  ampm(halfDay);
  minDisplay(minutE);
  hourDisplay(houR);
  latchTick();
  enableOutput(true);

  //checkHour();
  //checkMin();
  //checkDisp();

}  // end of loop: loop back, sleep, wake up after 1 second
