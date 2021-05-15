# --------------------------------------------------------------------------
# ST7735 library for PIC microcontrollers.
#
# Makefile for the demo-program.
#
# Author: Bernhard Bablok
#
# https://github.com/bablokb/pic-st7735
# 
# --------------------------------------------------------------------------

# chip-select
PIN_SPI_CS  = 4
PORT_SPI_CS = A

# data/command pin
PIN_TFT_DC   = 5
PORT_TFT_DC  = A

WITH_RESET = 1
# reset (optional)
ifneq ($(WITH_RESET),)
PIN_TFT_RST  = 2
PORT_TFT_RST = A
TFT_RST = -DPIN_TFT_RST=$(PIN_TFT_RST) -DPORT_TFT_RST=$(PORT_TFT_RST) -DTFT_ENABLE_RESET
endif

PROJECT=demo
EXTRA_C=tst_funcs.c spi.c ST7735_TFT.c
ARCH=pic14

TFT_FEATURES+=-DTFT_ENABLE_BLACK -DTFT_ENABLE_TEXT -DTFT_ENABLE_SHAPES -DTFT_ENABLE_ROTATE
TESTS+=-DENABLE_TESTR -DENABLE_TEST1 -DENABLE_TEST2 -DENABLE_TEST3 -DENABLE_TEST4

SDCC_ARGS+= -D_XTAL_FREQ=4000000 \
          -DPIN_SPI_CS=$(PIN_SPI_CS) \
          -DPORT_SPI_CS=$(PORT_SPI_CS) \
          -DPIN_TFT_DC=$(PIN_TFT_DC) \
          -DPORT_TFT_DC=$(PORT_TFT_DC) \
          -DSPI_HOST -DSPI_NO_SDI $(TFT_RST) $(TFT_FEATURES) $(TESTS)

include ptc_rules.inc
MCLR  = ON

# --------------------------------------------------------------------------
