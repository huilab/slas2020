/*
  AccelTest
  
  Modified from Adafruit Basic demo for accelerometer readings from Adafruit LIS3DH

*/

#include <SLAS2019.h>

// I2C accelerometer
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

//Adafruit FeatherWing display i2c address: 0x3C
U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED

// for testing with no-name i2c 128x64 OLED
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void setup(void) {
  u8g2.begin();
  u8g2_prepare();
  
  #ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif
  Serial.begin(9600);

  Serial.println("LIS3DH test!");
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH found!");
  
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  Serial.println("G");
  

  //pinMode(BUTTON_A, INPUT_PULLUP); // Button A is on A0, which we use for analog read
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
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


void loop(void) { 
  uint32_t now = millis();
  
  u8g2.clearBuffer();
  pollAccel();
  // send data to OLED
  u8g2.sendBuffer();

  delay(100); // slow things down. wait 100 ms
}
