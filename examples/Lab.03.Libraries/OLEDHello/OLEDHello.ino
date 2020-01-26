

/*
  OLED Hello
  
  Modified from GraphicsTest.ino
  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

*/

// include all the required libraries
#include <SLAS2019.h>

//Adafruit FeatherWing display i2c address: 0x3C
U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED

// for testing with no-name i2c 128x64 OLED
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

int count = 0;

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void draw(void) {
  u8g2.setCursor(0, 0);
  u8g2.print("Hello World! ");
  u8g2.print(count++);

  u8g2.setCursor(0, 16);
  if(!digitalRead(BUTTON_A)) u8g2.print("A");
  if(!digitalRead(BUTTON_B)) u8g2.print("B");
  if(!digitalRead(BUTTON_C)) u8g2.print("C");
}

void setup(void) {
  u8g2.begin();
  u8g2_prepare();
  Serial.begin(9600);

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  
  Serial.println("Hello OLED text");
}

void loop(void) {
  // picture loop  
  u8g2.clearBuffer();
  draw();
  u8g2.sendBuffer();
  
  delay(100);
}
