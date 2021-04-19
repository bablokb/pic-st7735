// --------------------------------------------------------------------------
// Demo program for the ST7735-library
//
// Author: Bernhard Bablok
//
// The code is based on work from Gavin Lyons, see
// https://github.com/gavinlyonsrepo/pic_16F18346_projects
//
// https://github.com/bablokb/pic-st7735
// --------------------------------------------------------------------------

#include "picconfig.h"
#include "spi.h"
#include "tst_funcs.h"
#include "ST7735_TFT.h"

CONFIG_WORDS;

////////////////////////////////////////////////////////////////////////
// Intialize registers

static void init(void) {
  // configure registers

  __asm__ ("CLRWDT");            // clear WDT even if WDT is disabled

  // some standard settings
  ANSELA   = 0;
  PORTA    = 0;
  LATA     = 0;
  CM1CON0  = 0x07;               // disable comparator for GP0-GP2
  WPUA     = 0;                  // default: no pullups on any pin
  NOT_GPPU = 0;                  // but enable pullups if set
  INTCON   = 0;                  // clear interrupt flag bits
  GIE      = 0;                  // global interrupt disable

  INIT_SPECIAL;
  CLOCK_4MHZ;
}

////////////////////////////////////////////////////////////////////////
// Interrupt service routine

static void isr(void) __interrupt 0 {
}

// --- main program   --------------------------------------------------------

void main(void) {
  init();
  // use spi-mode 0,0 (SPI_SMP_MOD not relevant, since pic only sends data)
  // baud-rate is 1MHz (4MHz/4, no scaling)
  spi_init(SPI_SMP_MOD | SPI_CKE_A2I,
           SPI_SSPM_HOST_FOSC_4 | SPI_CKP_LOW,
           0x0);

#ifdef TFT_ENABLE_BLACK
  TFT_BlackTab_Initialize();
#elif defined(TFT_ENABLE_GREEN)
  TFT_GreenTab_Initialize();
#elif defined(TFT_ENABLE_RED)
  TFT_RedTab_Initialize();
#elif defined(TFT_ENABLE_GENERIC)
  TFT_ST7735B_Initialize();
#endif
  setTextWrap(true);
  TEST_DELAY1();
  fillScreen(ST7735_BLACK);

#if defined(ENABLE_TEST1)
  Test1();
#endif
#if defined(ENABLE_TEST1A)
  Test1A();
#endif
#if defined(ENABLE_TEST2)
  Test2();
#endif
#if defined(ENABLE_TEST3)
  Test3();
#endif
#if defined(ENABLE_TEST4)
  Test4(); 
#endif
#if defined(ENABLE_TEST5)
  Test5();
#endif
#if defined(ENABLE_TEST6)
  Test6();
#endif
#if defined(ENABLE_TEST7)
  // Test7(); //TODO Scroll
#endif
#if defined(ENABLE_TEST8)
  Test8();
#endif

  fillScreen(ST7735_BLACK);
#if defined(TFT_ENABLE_TEXT)
  drawText(10, 10, "Test over!", ST7735_WHITE, ST7735_BLACK, 1);
  drawFastHLine(0,0,80,ST7735_CYAN);
  drawFastHLine(0,25,80,ST7735_CYAN);
  drawFastVLine(0,0,25,ST7735_CYAN);
  drawFastVLine(80,0,25,ST7735_CYAN);
#endif
  while(1);
}
