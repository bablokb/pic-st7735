// --------------------------------------------------------------------------
// SPI library for PIC microcontrollers.
//
// This header-file includes the PIC-specific configuration header and
// declares the basic spi-functions
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pic-spilib
// --------------------------------------------------------------------------

#include "spi.h"

// --------------------------------------------------------------------------
// Initialize registers and configure pins

void spi_init(uint8_t status, uint8_t control, uint8_t add) {
#ifdef SPI_ALT_PIN
  SPI_ALT_ENABLE();
#endif
  // pins are digital
  bitclear(ANSEL_SPI_SDO,PIN_SPI_SDO);
  bitclear(ANSEL_SPI_CLK,PIN_SPI_CLK);
#ifndef SPI_NO_SDI
  bitclear(ANSEL_SPI_SDI,PIN_SPI_SDI);
#endif
#ifdef SPI_HOST 
  bitclear(ANSEL_SPI_CS,PIN_SPI_CS);
#else
  bitclear(ANSEL_SPI_SS,PIN_SPI_SS);
#endif

  // pin directions
  bitclear(TRIS_SPI_SDO,PIN_SPI_SDO);     // SDO is output
#ifndef SPI_NO_SDI
  bitset(TRIS_SPI_SDI,PIN_SPI_SDI);       // SDI is input
#endif
#ifdef SPI_HOST
  bitclear(TRIS_SPI_CLK,PIN_SPI_CLK);     // CLK is output
  bitclear(TRIS_SPI_CS,PIN_SPI_CS);       // CS is output
#else // not SPI_HOST
  bitset(TRIS_SPI_CLK,PIN_SPI_CLK);       // CLK is input
  bitset(TRIS_SPI_SS,PIN_SPI_SS);         // SS  is input
#endif

  // configure registers
  SPI_STATUS_REG  = status;
  SPI_CONTROL_REG = control;
#ifdef SPI_HOST
  SPI_ADD_REG = add;
#endif
  SPI_ENABLE  = 1;                        // enable SSP
}

// --------------------------------------------------------------------------
// Exchange a byte with the spi-device
// Returns the byte read from the device

#ifdef SPI_HOST
uint8_t spi_write(uint8_t data) {
  WCOL = 0;
  SPI_BUFFER_REG = data;
  while (BF == 0x0 ) {
  }
  return SPI_BUFFER_REG;
}
#endif

// --------------------------------------------------------------------------
// Exchange multiple bytes with the spi-device
// Returns the number of bytes sent/received

#ifdef SPI_HOST
uint8_t spi_write_buf(uint8_t *buf_in, uint8_t len, uint8_t *buf_out) {
  uint8_t n = 0;
  if (len == 0) {
    return 0;
  }
  if (buf_in) {                                // transmit data
    while (n < len) {
      if (buf_out) {                           // expecting response
        buf_out[n] = spi_write(buf_in[n]);
      } else {                                 // discard response
        spi_write(buf_in[n]);
      }
      n++;
    }
  } else if (buf_out) {                        // only receive data
    while (n < len) {
      buf_out[n] = spi_write(0);
      n++;
    }
  }
  return n;
}
#endif

// --------------------------------------------------------------------------
// Check status of the buffer-register 

bool spi_buf_full(void) {
  return BF;
}

// --------------------------------------------------------------------------
// Check for write collisions

bool spi_has_collision(void) {
  return WCOL;
}

// --------------------------------------------------------------------------
// Clear write collision state 

void spi_clear_collision(void) {
  WCOL = 0;
}

// --------------------------------------------------------------------------
// Read a byte transferred by the spi-host and send a response-byte 

#ifndef SPI_HOST
uint8_t spi_read(uint8_t data) {
  uint8_t discard = SPI_BUFFER_REG;       // dummy read to clear bf-flag
  WCOL = 0;
  SPI_BUFFER_REG = data;
  while (BF == 0x0 ) {
  }
  return SPI_BUFFER_REG;
}
#endif

// --------------------------------------------------------------------------
// Read multiple bytes transferred by the spi-host and send a response

#ifndef SPI_HOST
uint8_t spi_read_buf(uint8_t *buf_in, uint8_t len, uint8_t *buf_out) {
  uint8_t n = 0;
  if (len == 0) {
    return 0;
  }
  if (buf_in) {                                // transmit data
    while (n < len) {
      if (buf_out) {                           // expecting data
        buf_out[n] = spi_read(buf_in[n]);
      } else {                                 // only send
        spi_read(buf_in[n]);
      }
      n++;
    }
  } else if (buf_out) {                        // only receive
    while (n < len) {
      buf_out[n] = spi_read(0);
      n++;
    }
  }
  return n;
}
#endif

// --------------------------------------------------------------------------
// Check for overflow condition 

#ifndef SPI_HOST
bool spi_has_overflow(void) {
  return SSPOV;
}
#endif

// --------------------------------------------------------------------------
// Clear overflow condition

#ifndef SPI_HOST
void spi_clear_overflow(void) {
  SSPOV = 0;
}
#endif
