/*
 * Copyright 2021 Ulrich Langenbach
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

// inspired by https://www.instructables.com/DIY-Metronome/

#include <Servo.h> // attach the servo library

// global variables and constants

// create servo object
Servo metronome;

// define servo pin
const int servo = 9;

// centre position of the servo
int centre = 90;
// number of positions to smooth the trajectory
int num_pos = 128;
// number of steps of the trajectory
int num_steps = (num_pos-1)*2;
// max angle from the center position to left and right
int alpha = 25;

// initialize variables to default the behavior to a not running metronome
// running at 60 bpm when started without updating the bpm setting
int bpm = 0;
int set_bpm = 60;
int running = 0;


// initialize serial and servo library
void setup() {
  metronome.attach (servo);   //attach the metronome var to a servo pin

  //initialize the angle of the metronome
  metronome.write (centre);
  Serial.begin (9600);
  Serial.write("INFO: press 'S' to start/stop, 'b<int>' to update BPM (10-240 BPM)\n\r");
}

// main loop
void loop() {
  int pos;

  // handle serial IO
  //  * to start and stop movement (default at 60 BPM)
  //  * to update the current bpm setting, aplpied when restarting the movement
  if (Serial.available() > 0) {
    int c = Serial.read();
    switch (c) {
     case 'S':
     case 's':
      if (running == 1) {
        running = 0;
        Serial.write("INFO: Stop\n\r");
      } else {
        running = 1;
        bpm = set_bpm;
        Serial.write("INFO: Start\n\r");
      }
      break;
    case 'B':
    case 'b':
      if (! running) {
        int new_bpm;
        new_bpm = Serial.parseInt();
        Serial.write("INFO: Read ");
        Serial.print(new_bpm, DEC);
        Serial.write(" BPM\n\r");
        if (new_bpm > 240) {
          Serial.write("ERROR: BPM ");
          Serial.print(new_bpm, DEC);
          Serial.write(" too high, ignoring!\n\r");
        } else if (new_bpm < 10) {
          Serial.write("ERROR: BPM ");
          Serial.print(new_bpm, DEC);
           Serial.write(" too small, ignoring!\n\r");
        } else {
          set_bpm = new_bpm;
        }
      }
      break;
    default:
      break;
    }
  }
  
  // create smooth trajectory
  if (running == 1) {
    for (int i = 0; i < num_pos; i++) {
      pos = centre - alpha + i*2*alpha/(num_pos-1);
      metronome.write (pos);
      delay(60*10/num_steps*100/bpm*2);
    }
    for (int i = 0; i < num_pos; i++) {
      pos = centre + alpha - i*2*alpha/(num_pos-1);
      metronome.write (pos);
      delay(60*10/num_steps*100/bpm*2);
    }
  }
}
