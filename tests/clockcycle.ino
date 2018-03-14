// AUTHOR: CaptainGector
// DATE: 12-24-17

const int clockPin = 4; // On the esp32, it's the 7th 
                        // pin up from the right side of  
                        // the usb connector
// This code runs once                       
void setup() {
  pinMode(clockPin, OUTPUT); // Set the mode of the pin we want
}

// This code runs forever
void loop() {
  delay(100); // Do nothing for 100ms
  digitalWrite(clockPin, HIGH); // Set our pin to 3.3v;
  delay(100); 
  digitalWrite(clockPin, LOW); // Set our pin to ground, 0v;
}


