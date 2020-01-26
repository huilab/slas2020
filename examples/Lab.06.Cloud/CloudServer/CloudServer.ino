/*
   Cloud Server
   Modified from Adafruit IO Analog In Example Example
   Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-analog-input

*/

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/

#include <SLAS2019.h>

// I2C accelerometer
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

//Adafruit FeatherWing display i2c address: 0x3C
U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED

// for testing with no-name i2c 128x64 OLED
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// analog pin 0
#define PHOTOCELL_PIN A0

// photocell state
double current_light = 0;
double last_light = -1;

// variables to keep track of timing
uint32_t task_1_interval = 2000;
uint32_t task_2_interval = 3000;
uint32_t task_3_interval = 2000;
uint32_t last_time_1, last_time_2, last_time_3 = 0;

// an 8-bit int to keep track of button states
// A will be stored in bit 0, B in bit 1, and C in bit 2
uint8_t button_state = 0;

// set up the 'analog' feed
AdafruitIO_Feed *analog = io.feed("analog");

// set up the 'accelerometer' feeds
AdafruitIO_Feed *accel_x = io.feed("ax");
AdafruitIO_Feed *accel_y = io.feed("ay");
AdafruitIO_Feed *accel_z = io.feed("az");

void setup() {
  u8g2.begin();
  u8g2_prepare();

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while (! Serial);



  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  u8g2.clearBuffer();
  u8g2.setCursor(0, 0);
  u8g2.print("Connecting to Adafruit IO...");
  u8g2.sendBuffer();
  io.connect();

  // wait for a connection
  int connect_try = 0;
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");

    u8g2.clearBuffer();
    u8g2.setCursor(0, 0);
    u8g2.print("Connecting to Adafruit IO...");
    u8g2.setCursor(0, 16);
    u8g2.print(connect_try++);
    u8g2.sendBuffer();

    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  u8g2.clearBuffer();
  u8g2.setCursor(0, 0);
  u8g2.print("Success");
  u8g2.setCursor(0, 16);
  u8g2.print(io.statusText());
  u8g2.sendBuffer();

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  uint32_t now = millis();
  
  if ( (now - last_time_1) > task_1_interval) {
    //pollAccel();
    last_time_1 = now;
  }
  if ( (now - last_time_2) > task_2_interval) {
    current_light = pollPhotoCell();
    last_time_2 = now;
  }
  if ( (now - last_time_3) > task_3_interval) {
    pollButtons();
    last_time_3 = now;
  }

  // return if the value hasn't changed
  if (current_light == last_light)
    return;

  // save the current state to the analog feed
  Serial.print("sending -> ");
  Serial.println(current_light);
  analog->save(current_light);

  // store last photocell state
  last_light = current_light;

}

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void pollAccel() {
  u8g2.setCursor(0, 0);
  /* get a new sensor event, normalized */
  sensors_event_t event;
  lis.getEvent(&event);

  /* Display the results on OLED (acceleration is measured in m/s^2) */
  u8g2.print("\t\tX: "); u8g2.print(event.acceleration.x);
  u8g2.print(" \tY: "); u8g2.print(event.acceleration.y);
  u8g2.print(" \tZ: "); u8g2.print(event.acceleration.z);
  u8g2.println(" m/s^2 ");

  /* Display the results over serial port (acceleration is measured in m/s^2) */
  Serial.print("\t\tX: "); Serial.print(event.acceleration.x);
  Serial.print(" \tY: "); Serial.print(event.acceleration.y);
  Serial.print(" \tZ: "); Serial.print(event.acceleration.z);
  Serial.println(" m/s^2 ");
}

double pollPhotoCell() {
  u8g2.setCursor(0, 16);
  int sensorValue = analogRead(PHOTOCELL_PIN); // read the input on analog pin 0:
  double intensity = map(sensorValue, 11, 926, 1, 400); // scale the value to lux (0 - 400)
  u8g2.print(intensity);
  u8g2.print(" lux ");
  return intensity;
}

void pollButtons() {
  u8g2.setCursor(64, 16);
  if (!digitalRead(BUTTON_A)) {
    u8g2.print("A");
    bitSet(button_state, 0);
  }
  else {
    bitClear(button_state, 0);
  }
  if (!digitalRead(BUTTON_B)) {
    u8g2.print("B");
    bitSet(button_state, 1);
  }
  else {
    bitClear(button_state, 1);
  }
  if (!digitalRead(BUTTON_C)) {
    u8g2.print("C");
    bitSet(button_state, 2);
  }
  else {
    bitClear(button_state, 2);
  }
}
