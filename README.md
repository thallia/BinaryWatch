# BinaryWatch
My first project designing and creating *everything*. 

Current board rev: *3.1*

Supplies I went through for breadboard testing:
  * atmega328p-pu
  * sn74hc595n x2
  * LEDs x20 (10 for breadboard, 10 for mock thru-hole)
  * 16MHz external crystal
  * 32.768kHz external crystal
  * 2 22pF capacitors
  * 2 0.1uF capacitors
  * two buttons for configuring time
  * one button for sleep/wakeup
  * jumper wires
  * resistors (1 10K, 10 220, 10 20k)
  * arduino uno (for easier programming in the beginning)
  
Supplies for PCB:
  * (SMD) atmega328p-au 
  * 74hc595 SMD shift registers x2
  * coin cell battery + SMD battery holder
  * LEDs SMD x10 (or flat top, whatever you prefer.)
  * 32.768kHz SMD crystal
  * SMD capacitors 22pF x2
  * 3 buttons
  * 10k SMD resistors x1
  * 2k SMD resistors x10 (in testing for LED brightness)
  * PCB

PCB designed on: eagleCAD



**CURRENT TASK:** Burned the bootloader and the new fuse bytes, finishing up tailoring the bwatch-clk source code to work along with the new hardware. New schematic in the works.


Blog Posts following development:

**Basis:**   https://www.thalliatree.net/posts/74dc595-texas-instruments-shift-reg-esp32.html

**Intro:**   https://www.thalliatree.net/posts/project-hype-binary-watch.html

**Breadboard Hardware (with Uno):**   https://www.thalliatree.net/posts/atmega328p-microcontroller-74hc595-shift-reg-setup-bw.html

**Code - Part 1:**   https://www.thalliatree.net/posts/code-p1-bw.html

**Code - Part 2:**   https://www.thalliatree.net/posts/code-p2-bw.html

**Breadboard Hardware (without Uno):** https://www.thalliatree.net/posts/prepping-the-atmega-hardware-test-bw.html

**Mock Up PCB with coin cells + early schematic:** https://www.thalliatree.net/posts/mock-up-pcb-bw.html

**Code - Part 3:** https://www.thalliatree.net/posts/code-p3-bw.html
