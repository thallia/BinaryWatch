/*
 * AUTHOR: Gector (with lovely comments from thallia)
 * Written: 12/21/2017
 * Last Edit: 1-27-18 - thallia's descriptive comment
 */

// -------------------------------------- \\
// ------------ VARIABLES --------------- \\
// -------------------------------------- \\

// Our time units.
int second=0, minute1=1, minute2=1, hour=1, halfDay=1;

// Physical pin numbers. 
const int inHourPin = 12, inMinutePin = 13;
const int outEnable = 2;
const int clockPin = 3;
const int dataPin = 5;
const int latchPin = 4;

const int clearAmount = 16; // If you add more shift registers to clear.

int wait = 0; // Add delay to the clock to see it shift stuff


// -------------------------------------- \\
// ------------ FUNCTIONS --------------- \\
// -------------------------------------- \\

// Shift bits down by one (positive edge triggered)

///////// THALLIA COMMENT //////////
/* clockReg takes looks like it makes a new variable "hold", then places the int value of 'wait' inside of it.
with digitalWrite, it outputs the clockpin HIGH, sending a signal to the clock pin of the shift register.
the delay....does something.

Delay waits for whatever the value of "hold" is.
digitalWrite then writes the clockpin LOW, and waits 1 second. This seems to be used as a way to clock the shift registers. */
///////////////////////////////////////////////////////
void clockReg(int hold = wait){
  digitalWrite(clockPin, HIGH);
  delay(hold);
  digitalWrite(clockPin, LOW);
  delay(hold);
}

// Grab a new bit from input (positive edge triggered)

////////// THALLIA COMMENT //////////
/* I'm guessing latch does the same thing as clockReg, but on the latch pin to get the new value. we don't have to specify *how* to get the value, only tell the pin to latch it. We like smart pins. */
/////////////////////////////////////////////////
void latch(int hold = wait){
  digitalWrite(latchPin, HIGH);
  delay(hold);
  digitalWrite(latchPin, LOW);
  delay(hold);
}

// Activate a single bit

//////////// THALLIA COMMENT ///////////////
/* alright, this is a little different.
 activateBit takes....an integer variable named hold with the value of wait inside of it?

digitalWrite writes the dataPin, which activates the LED, I think.
latch(hold) takes hold as an argument and latches the data.

activateBit grabs writes the old data, grabs the new data, and then writes the pin low, we aren't ready to latch the new stuff yet. */
///////////////////////////////////////////////////
void activateBit(int hold = wait){
  digitalWrite(dataPin, HIGH);
  latch(hold);
  clockReg(hold);
  digitalWrite(dataPin, LOW);
}

// set whether or not the LEDs are lit or not. (if this isn't done they flicker with the calculations)

///////// THALLIA COMMENT ///////////
/* enableOutput takes a boolean state as an argument.
 if the boolean state is true,if OE will be written LOW. But because that pin is inverted input, it'll be high. Otherwise, if false, OE will be written high, and turned off. */
////////////////////////////////////////////////////
void enableOutput(boolean state){
  if(state) {
    digitalWrite(outEnable, LOW);
  } else {
    digitalWrite(outEnable, HIGH);
  }
}

//... clear all.
//////// THALLIA COMMENT ////////////////
/* clearAll doesn't take any arguments afaik.
 It writes the dataPin low/off and loops:

*if x is 0, x less than the value of clearAmount, x++? then execute clockReg and latch with values 0.

clockReg will take 0 as an arg, running the clock and latching the new data. This resets everything to new values, I guess? */
/////////////////////////////////////////////////
void clearAll(){
  digitalWrite(dataPin, LOW);
  for(int x = 0;x <= clearAmount; x++){
    clockReg(0);
    latch(0);
  }
}

// Display hours
//////////////////THALLIA COMMENT/////////////////////
/* displayHour is obvs for displaying the actual time on the LEDs.

 if hour is greater than or equal to 1:
         for x equal to 3, greater than zero, read in the value from bitRead, which reads the number from "hour" and the bit in the x's place.

if the local variable "bit" is equal to 1, then write data HIGH, latch a new value, and shift it down, then turn data off.
otherwise, keep ticking. */
//////////////////////////////////////////////////////
void displayHour(int hour){
  if(hour >= 1) {
    for(int x = 3; x >= 0; x--) {
      int bit = bitRead(hour, x);
      if(bit == 1){ // Clock and data
        digitalWrite(dataPin, HIGH);
        latch();
        clockReg();
        digitalWrite(dataPin, LOW);
      } else { // Just clock
        latch();
        clockReg();
      }
    }
  }
}

// Sends on extra bit if it's PM, sends one extra clock if it's AM

////////////// THALLIA COMMENT ////////////////
/* AmPm returns nothing. It takes a state with an integer datatype. If state is greater than one, write data, latch new data, shift the clock. Otherwise, keep ticking. */
///////////////////////////////////////////////
void AmPm(int state){
  if(state >= 1) {
    digitalWrite(dataPin, HIGH);
    latch();
    clockReg();
    digitalWrite(dataPin, LOW);
  } else {
    latch();
    clockReg();
  }
}

// Set the first line of LEDs designated to minutes

///////////// THALLIA COMMENT ////////////////
/* this sets the first set of LEDs as the tens row.

 if the bit read from the local variable 'tens' is equal to 1, write, latch, and clock

otherwise, keep ticking */
//////////////////////////////////////////////
void displayMinL1(int tens){
  for(int x = 3; x >= 0; x--) {
    int bit = bitRead(tens, x);
    if(bit == 1){ // Clock and data
      digitalWrite(dataPin, HIGH);
      latch();
      clockReg();
      digitalWrite(dataPin, LOW);
    } else { // Just clock
      latch();
      clockReg();
    }
  }
}

// Set the second line of LEDs designated to minutes
void displayMinL2(int ones){
    for(int x = 3; x >= 0; x--) {
      int bit = bitRead(ones, x);
      if(bit == 1){ // Clock and data
        digitalWrite(dataPin, HIGH);
        latch();
        clockReg();
        digitalWrite(dataPin, LOW);
      } else { // Just clock
        latch();
        clockReg();
      }
    }
}

// Set all bits in sequence - usefuly for both lookinng cool and for debugging.

/////////////THALLIA COMMENT /////////////////
/* view takes an integer or hold as arg.
 if the given arg is equal to 0, less than clearAmount, it'll activate a bit -- I think whatever hold is, which is the pin number?? */
//////////////////////////////////////////////
void view(int hold = wait){
  for(int x = 0;x <= clearAmount; x++){
    activateBit(hold);
  }
}

// -------------------------------------- \\
// -------------- MAIN ------------------ \\
// -------------------------------------- \\

// Code that runs first
void setup()
{
  
  //Serial.begin(115200); // Commented out code doesn't do anything.

  // Tell the microcontroller what pins we are using for output.
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(outEnable, OUTPUT);

  // Tell the microcontroller what pins we are using... for input.
  pinMode(inHourPin, INPUT);
  pinMode(inMinutePin, INPUT);
  clearAll();
  enableOutput(true);
}

// Code that runs repeatedly.  
void loop()
{
  /*
  clearAll();
  delay(100);
  view(100);
  delay(100);
  */
  
  // This will keep ticking away and not get reset even though it's in the loop. 
  
  static unsigned long lastTick = 0;

  // One second every 1000ms
  if(millis() - lastTick >= 1000){ // fix this ***
    lastTick = millis();
    second++;
  }

  // One minute every 60s
  if(second >= 60){
    minute2++;
    second = 0; 
  }
  if(minute2 >= 10){
    minute1++;
    minute2=0;
    second=0;
  }

  // One hour every 60m
  if(minute1 >= 6){
    hour++;
    minute1 = 0;
  }

  // One half-day every 12 hours
  if(hour >= 13){
    halfDay++;
    hour=1;
    minute1=0;
    minute2=0;
  }

  // Am/Pm
  if(halfDay >= 2){
    halfDay=0;
    hour=1;
    minute1=0;
    minute2=0;
  }

  // 
  enableOutput(false);
  //clearAll();
  //Serial.print(String(second) + " seconds\n");
  //Serial.print(minute1);
  //Serial.print(String(minute2) + " minutes\n");
  //Serial.println(String(hour) + "hours");
  //if


  ///////////////THALLIA COMMENT/////////////////
  /* Takes functions and actually writes them.
   AmPm takes halfday and checks if needs to reset
  displaymin displays the minute LEDs
  display hour displays hour LEDs
  latch latches the data onto the pins
  clock...we don't use the first bit? hmm

  OE is enabled again, so things are outputted*/
  //////////////////////////////////////////////
  AmPm(halfDay);
  displayMinL2(minute2);
  displayMinL1(minute1);
  displayHour(hour);
  latch();
  clockReg(); // Since we don't use the first bit, we translate everything down one bit.
  enableOutput(true);
  delay(1);

  ////////////THALLIA COMMENT//////////////
  /* this is the input thingy!
   readHour is a variable, and digitalRead reads the input from the button.
  if readHour is high, or the button was pushed, then the hour is incremented by 1, seconds are set to zero, and there's a 250ms delay.

  readminute is the readin of the button for minutes, and if it's high, the minutes are increased by 2, and the seconds are reset. Delay of 250ms. */
  int readHour = digitalRead(inHourPin);
  //Serial.println("InHour: " + String(readHour));
  if(readHour == HIGH){
    hour++;
    second=0;
    delay(250);
  }

  int readMinute = digitalRead(inMinutePin);
  //Serial.println("InMinute: " + String(readMinute));
  if(readMinute == HIGH){
    minute2++;
    second=0;
    delay(250);
  }
  
}


