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

# reset
PIN_TFT_RST  = 2
PORT_TFT_RST = A

PROJECT=demo
EXTRA_C=tst_funcs.c spi.c ST7735_TFT.c
EXTRA_ASM=delay.asm
ARCH=pic14

SDCC_ARGS+= -DPIN_SPI_CS=$(PIN_SPI_CS) \
          -DPORT_SPI_CS=$(PORT_SPI_CS) \
          -DPIN_TFT_DC=$(PIN_TFT_DC) \
          -DPORT_TFT_DC=$(PORT_TFT_DC) \
          -DPIN_TFT_RST=$(PIN_TFT_RST) \
          -DPORT_TFT_RST=$(PORT_TFT_RST) \
          -DSPI_HOST -DSPI_NO_SDI \
          -DTFT_ENABLE_RESET -DTFT_ENABLE_BLACK

include ptc_rules.inc
MCLR  = ON

# --------------------------------------------------------------------------
