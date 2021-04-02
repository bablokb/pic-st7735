// --------------------------------------------------------------------------
// SPI library for PIC microcontrollers.
//
// Pin-configuration for the PIC16F690
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pic-spilib
// --------------------------------------------------------------------------

#ifndef SPI_16F690_H
#define	SPI_16F690_H

#include "picconfig.h"

#define PIN_SPI_SDO   7
#define PORT_SPI_SDO RC

#define PIN_SPI_CLK 6
#define PORT_SPI_CLK RB

#define PIN_SPI_SDI 4
#define PORT_SPI_SDI RB

#define PIN_SPI_SS 6
#define PORT_SPI_SS RC

// SPI-registers
#define SPI_STATUS_REG  SSPSTAT
#define SPI_CONTROL_REG SSPCON
#define SPI_BUFFER_REG  SSPBUF
#define SPI_ENABLE      SSPEN
#define SPI_CKP         CKP

// macros (define empty if not relevant!)
#define SPI_ALT_ENABLE()

#endif
