/*
 *
 * code from nick gammon
 * altered 1 line at the bottom by thallia
 *
 *
 */

#include <avr/sleep.h>
#include <avr/power.h>

const byte tick = 3;

// interrupt on Timer 2 compare "A" completion - does nothing
EMPTY_INTERRUPT (TIMER2_COMPA_vect);

void setup()
 {
  pinMode (tick, OUTPUT);

  // clock input to timer 2 from XTAL1/XTAL2
  ASSR = bit (AS2);

  // set up timer 2 to count up to 32 * 1024  (32768)
  TCCR2A = bit (WGM21);                             // CTC
  TCCR2B = bit (CS20) | bit (CS21) | bit (CS22);    // Prescaler of 1024
  OCR2A =  31;              // count to 32 (zero-relative)

  // enable timer interrupts
  TIMSK2 |= bit (OCIE2A);

  // disable ADC
  ADCSRA = 0;

  // turn off everything we can
  power_adc_disable ();
  power_spi_disable();
  power_twi_disable();
  power_timer0_disable();
  power_timer1_disable();
  power_usart0_disable();

  // full power-down doesn't respond to Timer 2
  set_sleep_mode (SLEEP_MODE_PWR_SAVE);

  // get ready ...
  sleep_enable();

  }  // end of setup

void loop()
  {

  // turn off brown-out enable in software
  MCUCR = bit (BODS) | bit (BODSE);
  MCUCR = bit (BODS);

  // sleep, finally!
  sleep_cpu ();

  // we awoke! pulse the clock hand
  digitalWrite (tick, HIGH);
  digitalWrite (tick, LOW);

  }  // end of loop
