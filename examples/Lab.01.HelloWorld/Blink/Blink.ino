/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  This example sketch has been modified from the example code at:

  http://www.arduino.cc/en/Tutorial/Blink
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED off (HIGH is the voltage level). The built-in LED is active-low
  delay(1000);                       // wait for a second (1000 ms)
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED on by making the voltage LOW
  delay(2000);                       // wait for two seconds
}
