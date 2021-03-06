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
const int LED_PIN = 3;      // led connected to digital pin 6 (pwm)
const int KNOCK_SENSOR_PIN = A0; // the piezo is connected to analog pin 0
const int POT_PIN = A3; //pin A0 to read analog input
const int COMMUNICATION_PIN = 9; // send drum beat to master
constexpr int REMOTE_BEAT_DELAY = 15; // milliseconds

// these variables will change:

void setup() {

  pinMode(POT_PIN, INPUT); //Optional 
  pinMode(LED_PIN, OUTPUT); // declare the LED_PIN as as OUTPUT
  pinMode(COMMUNICATION_PIN, OUTPUT);
  Serial.begin(115200);       // use the serial port
}

bool isKnock() {
  // simple hysteresis - don't tap again until we see a release sample
  static bool wasKnocked = false;
  // ronen suggested analog noise workaround
  /*
  analogRead(POT_PIN);
  delay(1);
  */
  int potValue = analogRead(POT_PIN);          //Read and save analog potValue from potentiometer
  int threshold = potValue; // initial threshold value to decide when the detected sound is a knock or not

  int ledPotValue = map(potValue, 0, 1023, 0, 255); //Map potValue 0-1023 to 0-255 (PWM) = ledPotValue
  analogWrite(LED_PIN, ledPotValue);          //Send PWM ledPotValue to led

  Serial.print(potValue);
  Serial.print(' ');
  // read the sensor and store it in the variable sensorReading:
  // ronen suggested analog noise workaround
  /*
  analogRead(KNOCK_SENSOR_PIN);
  delay(1);
  */
  int sensorReading = analogRead(KNOCK_SENSOR_PIN);  
  Serial.println(sensorReading);

  if (sensorReading >= threshold) {
    if (!wasKnocked) {
      Serial.print("Knock!");
      Serial.println(threshold);
      // TODO: some form of cooldown to debounce
      wasKnocked = true;
      return true;
    }

  } else if (wasKnocked) {
    Serial.println("Unknocked");
    wasKnocked = false;
  }
  return false;
}

void loop() {


  if (isKnock()) {
    digitalWrite(COMMUNICATION_PIN, HIGH);
    delay(REMOTE_BEAT_DELAY); // time for master to write all pixels to the strip with some spare (real time = ~12ms) 
    digitalWrite(COMMUNICATION_PIN, LOW);
  }
  delay(1);  // delay to avoid overloading the serial port buffer
}


  