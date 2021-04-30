// --------------------------------------------------------------------------
// ST7735-library (implementation of test-functions)
//
// Author: Bernhard Bablok
//
// The code is based on work from Gavin Lyons, see
// https://github.com/gavinlyonsrepo/pic_16F18346_projects
//
// https://github.com/bablokb/pic-st7735
// --------------------------------------------------------------------------

#if defined _PTC
  #include "picconfig.h"
#endif
#include "delay.h"
#include "tst_funcs.h"
#include "ST7735_TFT.h"

void delay_s(uint8_t count) {
  for (int i=0; i<4*count; ++i) {
    delay_ms(250);
  }
}

#if defined(ENABLE_TEST1)
void Test1(void) {
  const char *txt = " hello world";    
  drawText(0, 5, txt, ST7735_WHITE, ST7735_BLACK, 1);
  drawText(0, 15, txt,  ST7735_BLUE, ST7735_BLACK, 1);
  drawText(0, 25, txt, ST7735_RED, ST7735_BLACK, 1);
  drawText(0, 35, txt, ST7735_GREEN, ST7735_BLACK, 1);       
  drawText(0, 45, txt, ST7735_CYAN, ST7735_BLACK, 1);       
  drawText(0, 55, txt, ST7735_MAGENTA, ST7735_BLACK, 1);       
  drawText(0, 65, txt, ST7735_YELLOW, ST7735_BLACK, 1);        
  drawText(0, 75, txt, ST7735_WHITE, ST7735_BLACK, 1);       
  TEST_DELAY2();
  fillScreen(ST7735_BLACK);
}
#endif

#if defined(ENABLE_TEST1A)
void Test1A(void) {   
  drawText(0, 5, " !#$%&'()*+,-.", ST7735_WHITE, ST7735_BLACK, 1);
  drawText(0, 15, "0123456789",  ST7735_BLUE, ST7735_BLACK, 1);
  drawText(0, 25, "abcdefghijklmn", ST7735_RED, ST7735_BLACK, 1);
  drawText(0, 35, "ABCDEGHIJKLMN", ST7735_GREEN, ST7735_BLACK, 1);       
  drawText(0, 45, "opqrstuvwxyz", ST7735_CYAN, ST7735_BLACK, 1);       
  drawText(0, 55, "OPQRSTUVWYXZ", ST7735_MAGENTA, ST7735_BLACK, 1);       
  drawText(0, 65, ";:=,.?@", ST7735_YELLOW, ST7735_BLACK, 1);        
  drawText(0, 75, "[]/", ST7735_BLACK, ST7735_WHITE, 1);       
  TEST_DELAY5();
  fillScreen(ST7735_BLACK);
}
#endif

#if defined(ENABLE_TEST2)
void Test2(void) {
  const char *txttwo = "test2";
  drawText(0, 5, txttwo, ST7735_WHITE, ST7735_BLACK, 2);
  drawText(0, 25, txttwo, ST7735_WHITE, ST7735_BLACK, 3);
  drawText(0, 55, txttwo, ST7735_WHITE, ST7735_BLACK, 4);
  drawChar(0, 80, 'c', ST7735_WHITE, ST7735_BLACK,  5);
  TEST_DELAY2();
  fillScreen(ST7735_BLACK);
}
#endif

#if defined(ENABLE_TEST3)
void Test3(void) { //pixels and lines 
  drawPixel(5, 5, ST7735_RED);
  drawLine(10, 10, 30, 30, ST7735_RED);
  drawFastVLine(40, 40, 40, ST7735_GREEN);
  drawFastHLine(60, 60, 40, ST7735_YELLOW);
  TEST_DELAY2();
  fillScreen(ST7735_BLACK);
}    
#endif

#if defined(ENABLE_TEST4)
void Test4(void) {
  drawRectWH(5, 5, 20, 20, ST7735_RED);
  fillRectangle(25 , 25 , 40 , 40 ,  ST7735_YELLOW);
  fillRect(80, 5, 20, 20, ST7735_GREEN); 
  drawRoundRect(5, 80, 20, 20, 5, ST7735_CYAN); 
  fillRoundRect(50, 100, 25, 25, 10, ST7735_WHITE);
  TEST_DELAY2();
  fillScreen(ST7735_BLACK);
}
#endif

#if defined(ENABLE_TEST5)
void Test5(void) {
  drawCircle(40, 40, 20,  ST7735_GREEN); 
  fillCircle(80, 20, 15,  ST7735_YELLOW); 
}
#endif

#if defined(ENABLE_TEST6)
void Test6(void) {
  drawTriangle(5, 80, 50, 80, 15, 100, ST7735_CYAN); 
  fillTriangle(55, 80, 100, 60, 75, 120, ST7735_RED); 
  TEST_DELAY2();
  fillScreen(ST7735_BLACK);
}
#endif

#if defined(ENABLE_TEST7)
void Test7(void) {
  const char *txtthree = "  scroll  ";
  drawText(0, 45, txtthree, ST7735_CYAN, ST7735_BLACK, 1); 
  setScrollDefinition(100, 10, 0);
  VerticalScroll(0);
  TEST_DELAY2();
  NormalDisplay(); 
  fillScreen(ST7735_BLACK);
}
#endif

#if defined(ENABLE_TEST8)
void Test8() {
  //Draw play button 
  fillRoundRect(25, 10, 78, 60, 8, ST7735_WHITE);
  fillTriangle(42, 20, 42, 60, 90, 40, ST7735_RED);
  fillCircle(40, 100, 15,  ST7735_CYAN); 
  fillCircle(80, 100, 15,  ST7735_GREEN); 
  TEST_DELAY5();
  // change play color
  fillTriangle(42, 20, 42, 60, 90, 40, ST7735_BLUE);
  TEST_DELAY1();
  // change play color
  fillTriangle(42, 20, 42, 60, 90, 40, ST7735_GREEN);
  TEST_DELAY1();
  invertDisplay(true);   //invert display test
  TEST_DELAY1();
  invertDisplay(false);   //invert display test
  TEST_DELAY2();
  fillScreen(ST7735_BLACK);
}
#endif
