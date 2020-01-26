/*
  Basic Data Processing

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  
  Attach the center node of a voltage divider circuit to pin A0, and the outside nodes to +3.3V and ground.

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
  int sensorValue = analogRead(A0); // read the input on analog pin 0:
  double intensity = map(sensorValue,11,926,0,100); // scale the value to relative light intensity (0 - 100%)
  Serial.println(intensity); // print out the value you read:
  delay(1);        // delay in between reads for stability
}
