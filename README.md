# BinaryWatch
My first project designing and creating *everything*. 

Current board rev: *3.1*

  * atmega328p-pu
  * sn74hc595n x2
  * coin cell battery
  * LEDs x20 (10 for breadboard, 10 for mock thru-hole)
  * 16MHz external crystal
  * 32.768kHz external crystal
  * 2 22pF capacitors
  * two buttons for configuring time
  * one button for sleep/wakeup
  * jumper wires
  * resistors (1 10K, 10 220, 10 20k)
  * arduino uno (for easier programming in the beginning)

PCB designed on: eagleCAD



**CURRENT TASK:** Order the RTC IC from adafruit and hook it up to current circuit. Once that's done I can test bwatch3-0 to see if anything in there works, then debug the crap out of it. Schematic is mostly finished.


Blog Posts following development:

**Basis:**   https://www.thalliatree.net/posts/74dc595-texas-instruments-shift-reg-esp32.html

**Intro:**   https://www.thalliatree.net/posts/project-hype-binary-watch.html

**Breadboard Hardware (with Uno):**   https://www.thalliatree.net/posts/atmega328p-microcontroller-74hc595-shift-reg-setup-bw.html

**Code - Part 1:**   https://www.thalliatree.net/posts/code-p1-bw.html

**Code - Part 2:**   https://www.thalliatree.net/posts/code-p2-bw.html

**Breadboard Hardware (without Uno):** https://www.thalliatree.net/posts/prepping-the-atmega-hardware-test-bw.html

**Mock Up PCB with coin cells + early schematic:** https://www.thalliatree.net/posts/mock-up-pcb-bw.html
