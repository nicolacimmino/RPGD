# RPGD

RPGD is a digital RPG Die housed in a wooden chest and controlled by a **magic** gem that can be rotated and clicked. This project builds on my previous [TRNG](https://github.com/nicolacimmino/TRNG) project to add that dash of **over-engineering** that makes every hobby project worth its time while guaranteeing the absolutely unbiased and unpredictable output any RPG player expects from his dice.

![box1](documentation/box1.jpg)

The device can store presets in EEPROM with different combinations of dice count and die type. By rotating the gem you cycle through the presets. A click on the gem initiates the dice throw. Below few photos of the display in different configurations.

![display2](documentation/display2.jpg)

If you can't be arsed to go and check out my [TRNG](https://github.com/nicolacimmino/TRNG) project the bottom line is that, to generate the dice throw outcome, I make use of a TRNG which entropy source is noise from a Zener diode. This is driven by a charge pump as the voltage on board is too low for the Zener to enter breakdown, which is when noise is generated. Below is the schematic of the analog part which I lifted from my other project, the rest is all done in software.

![schematic](documentation/schematic.png)

**NOUT** is the noise output which is then A/D converted and gets processed to extract a random sequence. **CPS**, which stands for Charge Pump Sense, is used to keep an eye on the voltage of the reservoir capacitor and restart running the pump when this gets too low. This allows to sample the noise while the charge pump is not running. If we would leave the pump running the ripple of the output voltage would swamp the noise.

Purely to brag, to make this project look more cool, and to reassert the over-engineering aspect that was key in the planning phase, below is a block diagram of how the sampled noise, plus another source of entropy which shall remain undisclosed (unless you go and check my [TRNG](https://github.com/nicolacimmino/TRNG) project), are combined and processed to give an output stream that might (or might be not) cryptographically secure but surely passed a lot of randomness tests.

![block](documentation/block_diagram.png)

I have got the enclosure for a £1.50 at a thrift store, the panels are thick grey board made less dull with some washi tape.
