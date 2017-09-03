/* This sketch reads a piezo element to detect a knocking sound.
   It reads an analog pin and compares the result to a set threshold.
   the threshold is set by a pot connected to a different analog pin.
   If the result is greater than the threshold, it writes
   "knock" to the serial port, and toggles the LED on pin 13.

   The circuit:
  * + connection of the piezo attached to analog in 0
  * - connection of the piezo attached to ground
  * 1-megohm resistor attached from analog in 0 to ground
  * pot middle connected to A1
  * pot sides connected 1 to gnd one to RAW

 */


// these constants won't change:
const int ledPin = 6;      // led connected to digital pin 6 (pwm)
const int knockSensor = A0; // the piezo is connected to analog pin 0
const int potPin = A1; //pin A0 to read analog input


// these variables will change:

void setup() {

  pinMode(potPin, INPUT); //Optional 
  pinMode(ledPin, OUTPUT); // declare the ledPin as as OUTPUT
  Serial.begin(115200);       // use the serial port
}

bool isKnock() {
  int potValue = analogRead(potPin);          //Read and save analog potValue from potentiometer
  int threshold = potValue; // initial threshold value to decide when the detected sound is a knock or not

  int ledPotValue = map(potValue, 0, 1023, 0, 255); //Map potValue 0-1023 to 0-255 (PWM) = ledPotValue
  analogWrite(ledPin, ledPotValue);          //Send PWM ledPotValue to led

  Serial.println(potValue);

  // read the sensor and store it in the variable sensorReading:
  int sensorReading = analogRead(knockSensor);  
  Serial.println(sensorReading);

  if (sensorReading >= threshold) {
    Serial.print("Knock!");
    Serial.println(threshold);
    // TODO: some form of cooldown
    return true;    
  }
  return false;
}

void loop() {

  /*int potValue = analogRead(potPin);          //Read and save analog potValue from potentiometer
  int threshold = potValue; // initial threshold value to decide when the detected sound is a knock or not

  int ledPotValue = map(potValue, 0, 1023, 0, 255); //Map potValue 0-1023 to 0-255 (PWM) = ledPotValue
  analogWrite(ledPin, ledPotValue);          //Send PWM ledPotValue to led

  Serial.println(potValue);

  // read the sensor and store it in the variable sensorReading:
  int sensorReading = analogRead(knockSensor);

  // if the sensor reading is greater than the threshold:
  if (sensorReading >= threshold) {
    // send the string "Knock!" back to the computer, followed by newline
    Serial.print("Knock!");
    Serial.println(threshold);
  }

  Serial.println(sensorReading);*/

  isKnock();
  delay(10);  // delay to avoid overloading the serial port buffer
}


  