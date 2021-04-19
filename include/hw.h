// --------------------------------------------------------------------------
// ST7735-library (hw-specific defines and interfaces)
//
// If you want to port the library to a different platform, change this
// include (function-map at the end of the file).
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pic-st7735
// --------------------------------------------------------------------------

#ifndef _HW_H
#define HW_H

// ----------------------------------------------------------------
// pin and ports (usually defined in the makefile)

// chip-select output pin
#ifndef PIN_SPI_CS
  #define PIN_SPI_CS 4
#endif
#ifndef PORT_SPI_CS
  #define PORT_SPI_CS A
#endif

// TFT_DC output pin
#ifndef PIN_TFT_DC
  #define PIN_TFT_DC 5
#endif
#ifndef PORT_TFT_DC
  #define PORT_TFT_DC A
#endif
#define ANSEL_TFT_DC _CONCAT(ANSEL,PORT_TFT_DC)
#define TRIS_TFT_DC  _CONCAT(TRIS,PORT_TFT_DC)
#define GP_TFT_DC    _CONCAT(R,_CONCAT(PORT_TFT_DC,PIN_TFT_DC))

// TFT_RST output pin
#ifndef PIN_TFT_RST
  #define PIN_TFT_RST 2
#endif
#ifndef PORT_TFT_RST
  #define PORT_TFT_RST A
#endif
#define ANSEL_TFT_RST _CONCAT(ANSEL,PORT_TFT_RST)
#define TRIS_TFT_RST  _CONCAT(TRIS,PORT_TFT_RST)
#define GP_TFT_RST    _CONCAT(R,_CONCAT(PORT_TFT_RST,PIN_TFT_RST))
// ----------------------------------------------------------------

#include "picconfig.h"
#include "spi.h"
#include "delay.h"

// ----------------------------------------------------------------
// map functions
#ifdef __delay_ms
#undef __delay_ms
#endif
#define __delay_ms(x)              delay_ms(x)

#define spiwrite(data)             spi_write(data)

#define spi_cs_low()               GP_SPI_CS = 0
#define spi_cs_high()              GP_SPI_CS = 1

#define tft_dc_low()               GP_TFT_DC = 0
#define tft_dc_high()              GP_TFT_DC = 1
#define tft_dc_config()            bitclear(ANSEL_TFT_DC,PIN_TFT_DC); \
                                    bitclear(TRIS_TFT_DC,PIN_TFT_DC)

#define tft_rst_low()              GP_TFT_RST = 0
#define tft_rst_high()             GP_TFT_RST = 1
#define tft_rst_config()           bitclear(ANSEL_TFT_RST,PIN_TFT_RST); \
                                    bitclear(TRIS_TFT_RST,PIN_TFT_RST)
// ----------------------------------------------------------------

#endif
