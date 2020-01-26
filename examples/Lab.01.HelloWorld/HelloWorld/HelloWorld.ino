/*
  Hello World

  Prints text to the Serial Monitor.

  This example sketch has been modified from the example code at:
  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  Serial.println("hello world"); // print text
  delay(1);        // delay in between reads for stability
}
