// --------------------------------------------------------------------------
// Demo program for the ST7735-library
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pic-spi
// --------------------------------------------------------------------------

#include "picconfig.h"
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
  TFT_BlackTab_Initialize();
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
#endif
  while(1);
}
