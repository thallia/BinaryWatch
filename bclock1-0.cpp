/*
 * written by: thallia
 * almost copied from Gector's binary clock - additions for pullup registers, new functions for buttons, and soon-to-be deep sleep functions
 * on the day: 1-27-18
 * last edit: 1-29-18
 */

/* ------ Variables ------ */

// physical pin numbers to help me remember what's what
const int inHour = 7;
const int inMinute = 8;
const int outputEN = 2;
const int clockP = 3;
const int latchP = 4;
const int dataP = 5;

const int clearAmount = 16;

// time variables
int second = 0;
int minute = 1;
int hour = 1;
int halfDay = 1; // so you don't get military time

static unsigned long tick = 0;    // for millis()

int wait = 0; // ah, so this is for if you forget to give a value to the function, it's like a default so errors aren't spewed.

/* ------ Functions ------ */

/* hardware */

// enable dat output
void enableOutput(boolean state){
  if(state){
    digitalWrite(outputEN, LOW);
  } else {
    digitalWrite(outputEN, HIGH);
  }
}

// clock, shift the dang registers already!
void ticktock(int hold = wait){
  digitalWrite(clockP, HIGH); //turns clock on 
  delay(hold);
  digitalWrite(clockP, LOW); // turns clock off
  delay(hold);
}

// latch, baby, latch that data gud
void latch(int hold = wait){
  digitalWrite(latchP, HIGH); // latches new data
  delay(hold);
  digitalWrite(latchP, LOW); // shuts off, waits for signal to latch
  delay(hold);
}

// datapin, searching for their one true date-a
void writeData(int hold = wait){
  digitalWrite(dataP, HIGH); // sets datapin ready to receive data
  latch(hold);               // latches new data
  ticktock(hold);            // clocks data through shift register
  digitalWrite(dataP, LOW);  // turns datapin off
}

void checkHour(){
  int hourButton = digitalread(inHour);
  if(hourButton == LOW){ // LOW because pull-up resistors
    hour++;
    second = 0;
    delay(250);
  } else {
  }
}

void checkMin(){
  int minButton = digitalRead(inMinute);
  if(minButton == LOW){ // LOW because pull-up resistors
    minute++;
    second = 0;
    delay(250);
  } else {
  }
}

/* display */

// display hour
void hourDisplay(int hour){
  if(hour >= 1){
    for (int x = 3; x >= 0; x--){
      int bit = bitRead(hour, x);
        if(bit == 1){ // clock the shift registers + write the data to LEDs
          digitalWrite(dataP, HIGH);
          latch();
          ticktock();
          digitalWrite(dataP, LOW);
    } else { // keep ticking
      latch();
      ticktock();
      }
    }
  }
}

// display minutes
void minDisplay(int m){
  for(int x = 5; x >= 0; x--){
    int bit = bitRead(m, x);
    if(bit == 1){
      digitalWrite(dataP, HIGH);
      latch();
      ticktock();
      digitalWrite(dataP, LOW);
    } else {
      latch();
      ticktock();
    }
  }
}


// AmPm, tells it which numbers to display
void ampm(int state){
  if (state >= 1){
    digitalWrite(dataP, HIGH);
    latch();
    ticktock();
    digitalWrite(dataP, LOW);
  } else {
    latch();
    ticktock();
  }
}

/* ------ Main ------ */

// apparently it's an arduino thing that setup() runs first, TIL

void setup(){
  Serial.begin(9600);

  // output pins
  pinMode(clockP, OUTPUT);
  pinMode(outputEN, OUTPUT);
  pinMode(latchP, OUTPUT);
  pinMode(dataP, OUTPUT);

  pinMode(inHour, INPUT_PULLUP); // configures inHour and inMinute to be input pins and activate the pullup resistors.
  pinMode(inMinute, INPUT_PULLUP);

}

// This will run repeatedly, after setup.

void loop(){
  Serial.print("Minutes: ");
  Serial.println(minute);

  Serial.print("Hours: ");
  Serial.print(hour);

  // timing
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

  // rest of things
  enableOutput(false); // disable output to display the things

  ampm(halfDay);       // checks to see whether halfDay = 1, if so, write the next data
  minDisplay(minute);  // display the minutes with the minute value
  hourDisplay(hour);   // display the hours with the ticking hour value
  latch();             // latch data consistently
  ticktock();          // clock the shift registers to display
  enableOutput(true);  // start up the output
  delay(1);            // delay 1 second
  checkHour();         // check to make sure inHour isn't being pushed :: otherwise, increment the hour number (1-12)
  checkMin();          // check to make sure inMinute isn't being pushed :: otherwise, increment the minute number (0-59)

  // Deep Sleep functionality

}
