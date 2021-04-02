// --------------------------------------------------------------------------
// SPI library for PIC microcontrollers.
//
// Pin-configuration for the PIC12F1840
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pic-spilib
// --------------------------------------------------------------------------

#ifndef SPI_12F1840_H
#define	SPI_12F1840_H

#include "picconfig.h"

// pin definitions
#ifdef SPI_ALT_PIN
  #define PIN_SPI_SDO 4
#else
  #define PIN_SPI_SDO 0
#endif
#define PORT_SPI_SDO  A

#define PIN_SPI_CLK   1
#define PORT_SPI_CLK  A

#define PIN_SPI_SDI   2
#define PORT_SPI_SDI  A

#ifndef SPI_HOST
  // only relevant for SPI-device
  #ifdef SPI_ALT_PIN
    #define PIN_SPI_SS 0
  #else
    #define PIN_SPI_SS 3
  #endif
  #define PORT_SPI_SS  A
#endif

// SPI-registers
#define SPI_STATUS_REG  SSP1STAT
#define SPI_CONTROL_REG SSP1CON1
#define SPI_BUFFER_REG  SSP1BUF
#define SPI_ADD_REG     SSP1ADD
#define SPI_ENABLE      SSPEN

// macros (define empty if not relevant!)
#define SPI_ALT_ENABLE() \
  SDOSEL = 1; \
  SSSEL  = 1;

#endif
