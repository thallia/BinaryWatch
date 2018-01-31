# ATMega328P Pinout
## Connecting what pins from the ATMega to the shift registers?

ATMEGA **to** 74HC595

Digital Pin 2 ((PCINT18/INT0) PD2) **to** OE (output enable) pin 13

Digital Pin 3 (PCINT19/OC2B/INT1) PD3 **to** ST_CP (clock pin) pin 12

Digital Pin 4 (PCINT20/XCK/T0) PD4 **to** SH_CP (latch pin) pin 11

Digital Pin 5 (PCINT21/OC0B/T1) PD5 **to** DS (serial data) pin 14

Digital Pin 7 (PCINT23/AIN1) PD7 **to** Button 1

Digital Pin 8 (PCINT0/CLKO/ICP1) PB0 **to** Button 2



# Shift Register I/O to LED

### Hours

- Pin Q1 = 1
- Pin Q2 = 2
- Pin Q3 = 4
- Pin Q4 = 8

### Minutes

- Pin Q5 = 1
- Pin Q6 = 2
- Pin Q7 = 4
- (second shift register)
- Pin Q0 = 8
- Pin Q1 = 16
- Pin Q2 = 32
