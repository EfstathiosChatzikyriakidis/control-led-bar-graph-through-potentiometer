/*
 *  Control LED Bar Graph Through Potentiometer.
 *
 *  Copyright (C) 2010 Efstathios Chatzikyriakidis (stathis.chatzikyriakidis@gmail.com)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

const int potPin = 0;  // the pin number for the potentiometer.
const int ledPin = 13; // calibration status led. 

// array with the pin numbers of the leds.
const int ledsPins[] = { 2, 3, 4, 5, 6, 7 }; 

// calculate the number of the leds in the array.
const int NUM_LEDS = (int) (sizeof (ledsPins) / sizeof (const int));

// the two bounds are important for the potentiometer calibration.
int potMin = 1023;
int potMax = 0;

// calibration time in millis.
const int CAL_TIME = 10000;

// delay time leds should wait in dark and in light.
const long delayTime = 20;

// default value for leds bar graph.
int ledsRange = -1;

// startup point entry (runs once).
void setup () {
  // set potentiometer as input.
  pinMode(potPin, INPUT);

  // set led as output.
  pinMode(ledPin, OUTPUT);

  // set bar graph leds as output.
  for (int i = 0; i < NUM_LEDS; i++)
    pinMode(ledsPins[i], OUTPUT);

  // perform the calibration.
  calibrationPeriod();
}

// loop the main sketch.
void loop () {
  // get the value from the potentiometer.
  ledsRange = analogRead(potPin);
  
  // map the value for the leds bar graph.
  ledsRange = map(ledsRange, potMin, potMax, -1, NUM_LEDS-1);

  // light or dark the appropriate leds from the bar graph.
  for (int thisLed = 0; thisLed < NUM_LEDS; thisLed++) {
    if (thisLed <= ledsRange) {
      // light the led.
      digitalWrite(ledsPins[thisLed], HIGH);
    }
    else {
      // dark the led.
      digitalWrite(ledsPins[thisLed], LOW); 
    }
  }
}

// potentiometer calibration process.
void calibrationPeriod () {
  // the value that potentiometer sends.
  int potValue = 0;

  // signal the start of the calibration period.
  digitalWrite(ledPin, HIGH);

  // calibrate during the some time.
  while (millis() < CAL_TIME) {
    potValue = analogRead(potPin);

    // record the maximum potentiometer value.
    if (potValue > potMax) {
      potMax = potValue;
    }

    // record the minimum potentiometer value.
    if (potValue < potMin) {
      potMin = potValue;
    }
  }

  // signal the end of the calibration period.
  digitalWrite(ledPin, LOW);
}
