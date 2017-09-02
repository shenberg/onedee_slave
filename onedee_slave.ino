/* Knock Sensor

   This sketch reads a piezo element to detect a knocking sound.
   It reads an analog pin and compares the result to a set threshold.
   If the result is greater than the threshold, it writes
   "knock" to the serial port, and toggles the LED on pin 13.

   The circuit:
  * + connection of the piezo attached to analog in 0
  * - connection of the piezo attached to ground
  * 1-megohm resistor attached from analog in 0 to ground

   http://www.arduino.cc/en/Tutorial/Knock

   created 25 Mar 2007
   by David Cuartielles <http://www.0j0.org>
   modified 30 Aug 2011
   by Tom Igoe

   This example code is in the public domain.

 */


// these constants won't change:
const int ledPin = 6;      // led connected to digital pin 13
const int knockSensor = A0; // the piezo is connected to analog pin 0
const int potPin = A1; //pin A0 to read analog input


// these variables will change:
int sensorReading = 0;      // variable to store the value read from the sensor pin
int ledState = LOW;         // variable used to store the last LED status, to toggle the light

int potValue; //save analog value
int ledPotValue; //change the value from 1023 to 255 (later)

int threshold = 100;  // initial threshold value to decide when the detected sound is a knock or not


void setup() {

  pinMode(potPin, INPUT); //Optional 
  pinMode(ledPin, OUTPUT); // declare the ledPin as as OUTPUT
  Serial.begin(115200);       // use the serial port
}

void loop() {

  potValue = analogRead(potPin);          //Read and save analog potValue from potentiometer
  threshold = potValue;

  ledPotValue = map(potValue, 0, 1023, 0, 255); //Map potValue 0-1023 to 0-255 (PWM) = ledPotValue
  analogWrite(ledPin, ledPotValue);          //Send PWM ledPotValue to led

  Serial.println(potValue);

  // read the sensor and store it in the variable sensorReading:
  sensorReading = analogRead(knockSensor);

  // if the sensor reading is greater than the threshold:
  if (sensorReading >= threshold) {
    // send the string "Knock!" back to the computer, followed by newline
    Serial.print("Knock!");
    Serial.println(threshold);
  }

  Serial.println(sensorReading);
  delay(10);  // delay to avoid overloading the serial port buffer
}


  