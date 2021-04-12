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

#ifndef SPI_H
#define	SPI_H

#include "picconfig.h"
#include <stdint.h>
#include <stdbool.h>

#ifdef __12F1840
  #include "spi_12f1840.h"
#elif defined __16F1829
  #include "spi_16f1829.h"
#elif defined __16F690
  #include "spi_12f690.h"
#endif

// register/pin defs
#define ANSEL_SPI_SDO _CONCAT(ANSEL,PORT_SPI_SDO)
#define TRIS_SPI_SDO  _CONCAT(TRIS,PORT_SPI_SDO)

#define ANSEL_SPI_CLK _CONCAT(ANSEL,PORT_SPI_CLK)
#define TRIS_SPI_CLK  _CONCAT(TRIS,PORT_SPI_CLK)

#define ANSEL_SPI_SDI _CONCAT(ANSEL,PORT_SPI_SDI)
#define TRIS_SPI_SDI  _CONCAT(TRIS,PORT_SPI_SDI)

#ifdef SPI_HOST
  #ifdef PIN_SPI_CS
    // optional for SPI-host, since we can have multiple chip-selects
    // assumes that PORT_SPI_CS is also defined
    #define ANSEL_SPI_CS _CONCAT(ANSEL,PORT_SPI_CS)
    #define TRIS_SPI_CS  _CONCAT(TRIS,PORT_SPI_CS)
    #define GP_SPI_CS    _CONCAT(R,_CONCAT(PORT_SPI_CS,PIN_SPI_CS))
  #endif
#else
  // only relevant for SPI-device
  #define ANSEL_SPI_SS _CONCAT(ANSEL,PORT_SPI_SS)
  #define TRIS_SPI_SS  _CONCAT(TRIS,PORT_SPI_SS)
#endif

// constants
#define SPI_SSPM_ENABLE         0x20
#define SPI_SSPM_HOST_FOSC_4    0x00
#define SPI_SSPM_HOST_FOSC_16   0x01
#define SPI_SSPM_HOST_FOSC_64   0x02
#define SPI_SSPM_HOST_TMR2      0x03

#define SPI_SSPM_DEVICE_SS_EN   0x04
#define SPI_SSPM_DEVICE_SS_DIS  0x05

#define SPI_SMP_EOD 0x80   // end-of-data
#define SPI_SMP_MOD 0x00   // middle-of-data

#define SPI_CKE_A2I  0x40   // active-to-idle
#define SPI_CKE_I2A  0x00   // idle-to-active

#define SPI_CKP_HIGH  0x10   // idle state is high-level
#define SPI_CKP_LOW   0x00   // idle state is low-level

  void    spi_init(uint8_t status, uint8_t control, uint8_t add);
  bool    spi_buf_full(void);
  bool    spi_has_collision(void);
  void    spi_clear_collision(void);
#ifdef SPI_HOST
  uint8_t spi_write(uint8_t data);
  uint8_t spi_write_buf(uint8_t *buf_in, uint8_t len, uint8_t *buf_out);
#else
  uint8_t spi_read(uint8_t data);
  uint8_t spi_read_buf(uint8_t *buf_in, uint8_t len, uint8_t *buf_out);
  bool    spi_has_overflow(void);
  void    spi_clear_overflow(void);
#endif

#endif	/* SPI_H */

