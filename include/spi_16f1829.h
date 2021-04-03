// --------------------------------------------------------------------------
// SPI library for PIC microcontrollers.
//
// Pin-configuration for the PIC16F1829
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pic-spilib
// --------------------------------------------------------------------------

#ifndef SPI_16F1829_H
#define	SPI_16F1829_H

#include "picconfig.h"

#ifdef __SDCC
  #undef C
  #undef BF
  #undef SSPEN
#endif

// pin definitions
#ifndef SPI_2
  // SSP1
  #define PIN_SPI_SDO  7
  #define PORT_SPI_SDO C
  #define PIN_SPI_SDI  4
  #define PORT_SPI_SDI B
  #define PIN_SPI_CLK  6
  #define PORT_SPI_CLK B
  #ifndef SPI_HOST
    // only relevant for SPI-device
    #define PIN_SPI_SS  6
    #define PORT_SPI_SS C
  #endif
#else
  // SSP2
  #ifdef SPI_ALT_PIN
    #define PIN_SPI_SDO  5
    #define PORT_SPI_SDO A
  #else
    #define PIN_SPI_SDO  1
    #define PORT_SPI_SDO C
  #endif
  #define PIN_SPI_SDI  5
  #define PORT_SPI_SDI B
  #define PIN_SPI_CLK  7
  #define PORT_SPI_CLK B
  #ifndef SPI_HOST
    // only relevant for SPI-device
    #ifdef SPI_ALT_PIN
      #define PIN_SPI_SS  4
      #define PORT_SPI_SS A
    #else
      #define PIN_SPI_SS  0
      #define PORT_SPI_SS C
    #endif
  #endif
#endif

// SPI-registers
#ifndef SPI_2
  #define SPI_STATUS_REG  SSP1STAT
  #define SPI_CONTROL_REG SSP1CON1
  #define SPI_BUFFER_REG  SSP1BUF
  #define SPI_ADD_REG     SSP1ADD
  #define SPI_ENABLE      SSP1CON1bits.SSPEN
  #define WCOL            SSP1CON1bits.WCOL
  #define BF              SSP1STATbits.BF
#else
  #define SPI_STATUS_REG  SSP2STAT
  #define SPI_CONTROL_REG SSP2CON1
  #define SPI_BUFFER_REG  SSP2BUF
  #define SPI_ADD_REG     SSP2ADD
  #define SPI_ENABLE      SSP2CON1bits.SSPEN
  #define WCOL            SSP2CON1bits.WCOL
  #define BF              SSP2STATbits.BF
#endif

// macros (define empty if not relevant!)
#define SPI_ALT_ENABLE() \
  SDO2SEL = 1; \
  SS2SEL  = 1;

#endif
