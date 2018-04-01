# ATMega328P Pinout
## Connecting what pins from the ATMega to the shift registers?

ATMEGA **to** 74HC595

Digital Pin 0 (PCINT16/RXD) PD0 **to** OE (output enable) pin 13

Digital Pin 1 (PCINT17/TXD) PD1 **to** ST_CP (clock pin) pin 12

Digital Pin 2 ((PCINT18/INT0) PD2) **to** inDisplay

Digital Pin 3 (PCINT19/OC2B/INT1) PD3 **to** 

Digital Pin 4 (PCINT20/XCK/T0) PD4 **to** SH_CP (latch pin) pin 11

Digital Pin 5 (PCINT21/OC0B/T1) PD5 **to** DS (serial data) pin 14

Digital Pin 6 ((PCINT22/OC0A/AIN0) PD6) **to** inHour

Digital Pin 7 ((PCINT23/AIN1) PD7) **to** inMinute

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


# GND and Vcc

- AREF to Vcc
- AVcc to Vcc
- GND to GND
- Vcc to 10kOhm resistor to RESET
- Master Reclear to Vcc
- Two 0.1uF capacitors connecting GND and Vcc on both sides (Vcc/GND and AVcc/GND)

# External Clock

- Two GNDed 22pF capacitors to 16MHz crystal to XTAL1 and XTAL2 (if not using sleep modes)

OR

- Two GNDed 22pF caps to 32.768kHz crystal to XTAL1 and XTAL2 (if using sleep modes & burned fuse bytes)
