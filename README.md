# BinaryWatch
My first project designing and creating *everything*. 

Current board rev: *4.1*

Supplies I went through for breadboard testing:
  * atmega328p-pu
  * sn74hc595n x2
  * LEDs x10 
  * 16MHz external crystal
  * 32.768kHz external crystal
  * 2 22pF capacitors
  * 2 0.1uF capacitors
  * two buttons for configuring time
  * one button for sleep/wakeup
  * jumper wires
  
  * arduino uno (for easier programming in the beginning)
  
Supplies for PCB:
  * (SMD) atmega328p-au 
  * 74hc595 SMD shift registers x2
  * JST right angle connector
  * 400mAh Li-Po battery
  * LEDs 1206 SMD x10 (or flat top, whatever you prefer.)
  * 32.768kHz SC-32S SMD crystal
  * SMD capacitors 0805 22pF x2
  * SMD capacitors 0805 12.5pF x2
  * 3 buttons
  * 10k SMD resistors 0805 x1
  * 2k SMD resistors 0805 x10 (in testing for LED brightness)
  * PCB (oshpark)
  * 3D printed case (fusion360)

**PCB designed on:** eagleCAD


**3D case designed on:** fusion360

**CURRENT TASK:** This project is complete!


Blog Posts following development:

**Basis:**  https://thalliatree.wordpress.com/2017/12/25/74hc595-texas-instruments-shift-registers/

**Intro:**  https://thalliatree.wordpress.com/2018/01/01/project-hype-binary-wristwatch/

**Breadboard Hardware (with Uno):**   https://thalliatree.wordpress.com/2018/01/26/atmega328p-microcontroller-74hc595-shift-register-setup-and-test-binary-watch/

**Code - Part 1:**  https://thalliatree.wordpress.com/2018/01/29/code-part-1-binary-watch/

**Code - Part 2:**  https://thalliatree.wordpress.com/2018/01/31/code-part-2-binary-watch/

**Breadboard Hardware (without Uno):**    https://www.thalliatree.net/posts/prepping-the-atmega-hardware-test-bw.html

**Mock Up PCB with coin cells + early schematic:**   https://thalliatree.wordpress.com/2018/02/05/mock-up-pcb-binary-watch/

**Code - Part 3:**   https://thalliatree.wordpress.com/2018/03/16/code-part-3-binary-watch/

**Atmega328p 32.768kHz, sleep modes, and new schematic:**   https://thalliatree.wordpress.com/2018/03/26/atmega328p-32-768khz-sleep-modes-and-new-schematic-binary-watch/

**Final Code, Schematic, and PCB layout:**   https://thalliatree.wordpress.com/2018/04/03/final-code-schematic-and-pcb-binary-watch/

**PCB 95% Complete:**   https://thalliatree.wordpress.com/2018/05/03/pcb-95-complete-binary-watch/

**Binary Watch | Complete:**  https://thalliatree.wordpress.com/2018/05/14/binary-watch-complete


For later revisions: 
-  Power: The charging and power circuit needs to be on the board itself. That way I can charge it and not have to worry about buying a bunch of LiPo batteries over and over.
- Experimenting with new power: I want to try powering this thing from a coin cell again. I have 2 other boards with this design, so I'm going to solder them together, but with different resistor types on the LEDs to see how much current the LEDs and microcontroller are drawing. That way I can estimate what the best resistor value is for brightness + mAh value of battery to get.
- The 3D case is cool with the PCB exposed, but it ain't cool because it's exposed to the weather and other wet and sticky things. Therefore I must cover it up. The lid for case I design next will likely be screwed on, 1) for easier access and 2) for better security of the PCB. Depending on how secure I want it, I may add some kind of sealant. We'll see...
- 3D case: If I add a charging port, it'll need a hole for the plug.
- Through-hole LEDs: if the PCB is to be covered by the case, SMD LEDs aren't going to shine through very well. I have some cool cylindrical blue LEDs that should work, so I'll have to design the case cover to sit around/on top of them, which requires a new PCB design entirely.
- With the PCB case covering the top, I'll need to either add holes for the pushbuttons or design a way to put them on the sides of the case.
- Watch strap: I'm planning on weaving some leather cord in a celtic knot fashion, or maybe some cool braided thing. I've been looking at some chunkier weaves on Pinterest, but I haven't found the right one yet.
- With the new case top, I may make it thicker and engrave some cool circuit-looking designs around the LEDs poking through and paint the engravings an electric blue color. Electric blue is a great idea.
