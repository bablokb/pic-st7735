// --------------------------------------------------------------------------
// Demo program for the ST7735-library
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pic-spi
// --------------------------------------------------------------------------

#include "picconfig.h"
#include "test_funcs.h"
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
  Test1();
  Test1A();
  Test2();
  Test3();
  Test4(); 
  Test5();
  Test6();
  // Test7(); //TODO Scroll
  Test8();
  fillScreen(ST7735_BLACK);
  drawtext(10, 10, "Test over!", ST7735_WHITE, ST7735_BLACK, 1);
  while(1);
}
