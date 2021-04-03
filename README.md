Arduino Base Metronome
======================

This project aims at providing a very simple, yet useful servo based metronome
setup using an Arduino platform.

Setup
-----

This simple arduino based metronome has been build and tested using an Arduino
nano. This board features an ATMega328P running the old boot loader in this case.
The develpment is done with the Arduino IDE 1.8.13 run on OpenSuSe 15.2 using
the Serial and Servo libraries.

The servo used for testing is a small general purpose metal gear micro servo
named MG90S shopped in the bay.

Pin Assignment
--------------

The three servo pins, usually color coded the same way are assigned as per the
table below.


| **Servo Cable Color** | **Signal** | **Arduino Pin** |
| --------------------- | ---------- | --------------- |
| black                 |  GND       |  GND            |
| red                   |  VCC       |  +5V            |
| orange                |  PWM       |  D9             |

