/*
 * written by: thallia
 * almost copied from Gector's binary clock
 * on the day: 1-27-18
 * last edit: 1-27-18
 */

/* ------ Variables ------ */

// physical pin numbers to help me remember what's what
const int inHour = 7; // debatable
const int inMinute = 8; // debatable too, need to find
const int outputEN = 2;
const int clockP = 3;
const int latchP = 4;
const int dataP = 5;

// time variables
int second = 0;
int minute = 0;
int hour = 0;
int halfDay = 0; // so you don't get military time

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
void clock(int hold = wait){
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
  clock(hold);            // clocks data through shift register
  digitalWrite(dataP, LOW);  // turns datapin off
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
          clock();
          digitalWrite(dataP, LOW);
    } else { // keep ticking
      latch();
      clock();
      }
    }
  }
}

// display minutes

/* This doesn't display correctly right now, I'll have to find another way to implement it to display the minutes in correct order.
   Also should try moving the i/o pins on the shift registers to see how that makes it look. double check circuit.

   the minutes should be on a 60 scale, so it counts up to 60, it only looks like it's counting up to 15 rn */ 
void minDisplay(int minute){
  for(int x = 3; x >= 0; x--){
    int bit = bitRead(minute, x);
    if(bit == 1){
      digitalWrite(dataP, HIGH);
      latch();
      clock();
      digitalWrite(dataP, LOW);
    } else {
      latch();
      clock();
    }
  }
}


// AmPm, tells it which numbers to display
void ampm(int state){
  if (state >= 1){
    digitalWrite(dataP, HIGH);
    latch();
    clock();
    digitalWrite(dataP, LOW);
  } else {
    latch();
    clock();
  }
}

/* ------ Main ------ */

// apparently it's an arduino thing that setup() runs first, TIL

void setup(){


  // output pins
  pinMode(clockP, OUTPUT);
  pinMode(outputEN, OUTPUT);
  pinMode(latchP, OUTPUT);
  pinMode(dataP, OUTPUT);

  // input pins
  pinMode(inHour, INPUT);
  pinMode(inMinute, INPUT);


}

// This will run repeatedly, after setup.

void loop(){

  // timing
  // one second every 1000ms
  tick = millis();
  if(millis() - tick >= 1000){
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
  clock();             // clock the shift registers to display
  enableOutput(true);  // start up the output
  delay(1);            // delay 1 second

  // buttons input

  int hourButton = digitalRead(inHour);
  if(hourButton = HIGH){
    hour++;
    second = 0;
    delay(250);
  }

  int minButton = digitalRead(inMinute);
  if(minButton = HIGH){
    minute++;
    second = 0;
    delay(250);
  }

  // Deep Sleep functionality

}
