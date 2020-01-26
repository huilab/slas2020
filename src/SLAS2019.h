
/*!
* SLAS 2019 IoT
*/

#ifndef __SLAS2019__H__
#define __SLAS2019__H__

#include <Arduino.h>

#include <Wire.h>
#include <SPI.h>

// OLED FeatherWing buttons map to different pins depending on board:
#if defined(ESP8266)
  #define BUTTON_A  0
  #define BUTTON_B 16
  #define BUTTON_C  2
#elif defined(ESP32)
  #define BUTTON_A 15
  #define BUTTON_B 32
  #define BUTTON_C 14
#elif defined(ARDUINO_STM32_FEATHER)
  #define BUTTON_A PA15
  #define BUTTON_B PC7
  #define BUTTON_C PC5
#elif defined(TEENSYDUINO)
  #define BUTTON_A  4
  #define BUTTON_B  3
  #define BUTTON_C  8
#elif defined(ARDUINO_FEATHER52832)
  #define BUTTON_A 31
  #define BUTTON_B 30
  #define BUTTON_C 27
#else // 32u4, M0, M4, nrf52840 and 328p
  #define BUTTON_A  9
  #define BUTTON_B  6
  #define BUTTON_C  5
#endif

#include <U8g2lib.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

template <typename T>
T safeMap(T x, T in_min, T in_max, T out_min, T out_max)
{
  // prevent division by zero
  if(in_max == in_min) {
    return out_min;
  }
  else {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
}



//#define DEBUG_PRINT


#endif //End __SLAS2019__H__ include guard