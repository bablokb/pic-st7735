// --------------------------------------------------------------------------
// ST7735-library (implementation)
//
// Author: Bernhard Bablok
//
// The code is based on work from Gavin Lyons, see
// https://github.com/gavinlyonsrepo/pic_16F18346_projects
//
// https://github.com/bablokb/pic-st7735
// --------------------------------------------------------------------------

#include <stdint.h>
#include <stdlib.h>
#include "picconfig.h"

// ----------------------------------------------------------------
// pin and ports (usually defined in the makefile)

// chip-select output pin
#ifndef PIN_SPI_CS
  #define PIN_SPI_CS 4
#endif
#ifndef PORT_SPI_CS
  #define PORT_SPI_CS A
#endif

// TFT_DC output pin
#ifndef PIN_TFT_DC
  #define PIN_TFT_DC 5
#endif
#ifndef PORT_TFT_DC
  #define PORT_TFT_DC A
#endif
#define ANSEL_TFT_DC _CONCAT(ANSEL,PORT_TFT_DC)
#define TRIS_TFT_DC  _CONCAT(TRIS,PORT_TFT_DC)
#define GP_TFT_DC    _CONCAT(R,_CONCAT(PORT_TFT_DC,PIN_TFT_DC))

// TFT_RST output pin
#ifndef PIN_TFT_RST
  #define PIN_TFT_RST 2
#endif
#ifndef PORT_TFT_RST
  #define PORT_TFT_RST A
#endif
#define ANSEL_TFT_RST _CONCAT(ANSEL,PORT_TFT_RST)
#define TRIS_TFT_RST  _CONCAT(TRIS,PORT_TFT_RST)
#define GP_TFT_RST    _CONCAT(R,_CONCAT(PORT_TFT_RST,PIN_TFT_RST))
// ----------------------------------------------------------------

#include "spi.h"
#include "delay.h"
#include "ST7735_TFT.h"

#if defined(TFT_ENABLE_TEXT)
#include "TextFonts.h"
#endif

// ----------------------------------------------------------------
// map functions
#ifdef __delay_ms
#undef __delay_ms
#endif
#define __delay_ms(x)              delay_ms(x)

#define spiwrite(data)             spi_write(data)
#define spiinit()                  spi_init(SPI_SMP_MOD | SPI_CKE_A2I, \
                                     SPI_SSPM_HOST_FOSC_4 | SPI_CKP_LOW, \
                                     0x0)

#define spi_cs_low()               GP_SPI_CS = 0
#define spi_cs_high()              GP_SPI_CS = 1

#define tft_dc_low()               GP_TFT_DC = 0
#define tft_dc_high()              GP_TFT_DC = 1
#define tft_dc_config()            bitclear(ANSEL_TFT_DC,PIN_TFT_DC); \
                                    bitclear(TRIS_TFT_DC,PIN_TFT_DC)

#define tft_rst_low()              GP_TFT_RST = 0
#define tft_rst_high()             GP_TFT_RST = 1
#define tft_rst_config()           bitclear(ANSEL_TFT_RST,PIN_TFT_RST); \
                                    bitclear(TRIS_TFT_RST,PIN_TFT_RST)
// ----------------------------------------------------------------

// Write an SPI command
void write_command(uint8_t cmd_){
  tft_dc_low() ;
  spi_cs_low();
  spiwrite(cmd_);
  spi_cs_high();
}

// Write SPI data
void write_data(uint8_t data_){
  tft_dc_high();
  spi_cs_low();
  spiwrite(data_);
  spi_cs_high();
}

#if defined TFT_ENABLE_GENERIC
void Bcmd(){
  write_command(ST7735_SWRESET);
  __delay_ms(50);
  write_command(ST7735_SLPOUT);
  __delay_ms(250);
  __delay_ms(250);
  write_command(ST7735_COLMOD);
  write_data(0x05);
  __delay_ms(10);
  write_command(ST7735_FRMCTR1);
  write_data(0x00);
  write_data(0x06);
  write_data(0x03);
  __delay_ms(10);
  write_command(ST7735_MADCTL);
  write_data(0x08);
  write_command(ST7735_DISSET5);
  write_data(0x15);
  write_data(0x02);
  write_command(ST7735_INVCTR);
  write_data(0x00);
  write_command(ST7735_PWCTR1);
  write_data(0x02);
  write_data(0x70);
  __delay_ms(10);
  write_command(ST7735_PWCTR2);
  write_data(0x05);
  write_command(ST7735_PWCTR3);
  write_data(0x01);
  write_data(0x02);
  write_command(ST7735_VMCTR1);
  write_data(0x3C);
  write_data(0x38);
  __delay_ms(10);
  write_command(ST7735_PWCTR6);
  write_data(0x11);
  write_data(0x15);
  write_command(ST7735_GMCTRP1);
  write_data(0x09); write_data(0x16); write_data(0x09); write_data(0x20);
  write_data(0x21); write_data(0x1B); write_data(0x13); write_data(0x19);
  write_data(0x17); write_data(0x15); write_data(0x1E); write_data(0x2B);
  write_data(0x04); write_data(0x05); write_data(0x02); write_data(0x0E);
  write_command(ST7735_GMCTRN1);
  write_data(0x0B); write_data(0x14); write_data(0x08); write_data(0x1E);
  write_data(0x22); write_data(0x1D); write_data(0x18); write_data(0x1E);
  write_data(0x1B); write_data(0x1A); write_data(0x24); write_data(0x2B);
  write_data(0x06); write_data(0x06); write_data(0x02); write_data(0x0F);
  __delay_ms(10);
  write_command(ST7735_CASET);
  write_data(0x00); write_data(0x02); write_data(0x08); write_data(0x81);
  write_command(ST7735_RASET);
  write_data(0x00); write_data(0x01); write_data(0x08); write_data(0xA0);
  write_command(ST7735_NORON);
  __delay_ms(10);
  write_command(ST7735_DISPON);
  __delay_ms(250);
  __delay_ms(250);
}
#endif

void Rcmd1(){
  write_command(ST7735_SWRESET);
  __delay_ms(150);
  write_command(ST7735_SLPOUT);
  __delay_ms(250);
  __delay_ms(250);
  write_command(ST7735_FRMCTR1);
  write_data(0x01);
  write_data(0x2C);
  write_data(0x2D);
  write_command(ST7735_FRMCTR2);
  write_data(0x01);
  write_data(0x2C);
  write_data(0x2D);
  write_command(ST7735_FRMCTR3);
  write_data(0x01); write_data(0x2C); write_data(0x2D);
  write_data(0x01); write_data(0x2C); write_data(0x2D);
  write_command(ST7735_INVCTR);
  write_data(0x07);
  write_command(ST7735_PWCTR1);
  write_data(0xA2);
  write_data(0x02);
  write_data(0x84);
  write_command(ST7735_PWCTR2);
  write_data(0xC5);
  write_command(ST7735_PWCTR3);
  write_data(0x0A);
  write_data(0x00);
  write_command(ST7735_PWCTR4);
  write_data(0x8A);
  write_data(0x2A);
  write_command(ST7735_PWCTR5);
  write_data(0x8A);
  write_data(0xEE);
  write_command(ST7735_VMCTR1);
  write_data(0x0E);
  write_command(ST7735_INVOFF);
  write_command(ST7735_MADCTL);
  write_data(0xC8);
  write_command(ST7735_COLMOD);
  write_data(0x05); 
}

#if defined TFT_ENABLE_GREEN
void Rcmd2green(){
  write_command(ST7735_CASET);
  write_data(0x00); write_data(0x02);
  write_data(0x00); write_data(0x7F + 0x02);
  write_command(ST7735_RASET);
  write_data(0x00); write_data(0x01);
  write_data(0x00); write_data(0x9F + 0x01);
}
#endif

#if defined(TFT_ENABLE_RED) || defined(TFT_ENABLE_BLACK)
void Rcmd2red(){
  write_command(ST7735_CASET);
  write_data(0x00); write_data(0x00);
  write_data(0x00); write_data(0x7F);
  write_command(ST7735_RASET);
  write_data(0x00); write_data(0x00);
  write_data(0x00); write_data(0x9F);
}
#endif

void Rcmd3(){
  write_command(ST7735_GMCTRP1);
  write_data(0x02); write_data(0x1C); write_data(0x07); write_data(0x12);
  write_data(0x37); write_data(0x32); write_data(0x29); write_data(0x2D);
  write_data(0x29); write_data(0x25); write_data(0x2B); write_data(0x39);
  write_data(0x00); write_data(0x01); write_data(0x03); write_data(0x10);
  write_command(ST7735_GMCTRN1);
  write_data(0x03); write_data(0x1D); write_data(0x07); write_data(0x06);
  write_data(0x2E); write_data(0x2C); write_data(0x29); write_data(0x2D);
  write_data(0x2E); write_data(0x2E); write_data(0x37); write_data(0x3F);
  write_data(0x00); write_data(0x00); write_data(0x02); write_data(0x10);
  write_command(ST7735_NORON);
  __delay_ms(10);
  write_command(ST7735_DISPON);
  __delay_ms(100);
}


/*
  SPI displays set an address window rectangle for blitting pixels
  Parameter1:  Top left corner x coordinate
  Parameter2:  y  Top left corner x coordinate
  Parameter3:  w  Width of window
  Parameter4:  h  Height of window
 https://en.wikipedia.org/wiki/Bit_blit
*/
void setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1){
  write_command(ST7735_CASET);
  write_data(0);
  write_data(x0 + colstart);
  write_data(0);
  write_data(x1 + colstart);
  write_command(ST7735_RASET);
  write_data(0);
  write_data(y0 + rowstart);
  write_data(0);
  write_data(y1 + rowstart);
  write_command(ST7735_RAMWR); // Write to RAM
}

#if defined TFT_ENABLE_SHAPES
void drawPixel(uint8_t x, uint8_t y, uint16_t color){
  if((x >= _width) || (y >= _height)) 
    return;
  setAddrWindow(x,y,x+1,y+1);
  write_data(color >> 8);
  write_data(color & 0xFF);
}

void fillRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color){
  uint8_t hi, lo;
  if((x >= _width) || (y >= _height))
    return;
  if((x + w - 1) >= _width)  
    w = _width  - x;
  if((y + h - 1) >= _height) 
    h = _height - y;
  setAddrWindow(x, y, x+w-1, y+h-1);
  hi = color >> 8; lo = color;
  tft_dc_high();
  spi_cs_low();
  for(y=h; y>0; y--) {
    for(x = w; x > 0; x--) {
      spiwrite(hi);
      spiwrite(lo);
    }
  }
  spi_cs_high() ;
}

void fillScreen(uint16_t color) {
  fillRectangle(0, 0, _width, _height, color);
}

void drawFastVLine(uint8_t x, uint8_t y, uint8_t h, uint16_t color){
  uint8_t hi, lo;
  if((x >= _width) || (y >= _height))
    return;
  if((y + h - 1) >= _height)
    h = _height - y;
  hi = color >> 8; lo = color;
  setAddrWindow(x, y, x, y + h - 1);
  tft_dc_high();
  spi_cs_low();
  while (h--) {
    spiwrite(hi);
    spiwrite(lo);
  }
  spi_cs_high() ;
}

void drawFastHLine(uint8_t x, uint8_t y, uint8_t w, uint16_t color){
  uint8_t hi, lo;
  if((x >= _width) || (y >= _height))
    return;
  if((x + w - 1) >= _width)
    w = _width - x;
  hi = color >> 8; lo = color;
  setAddrWindow(x, y, x + w - 1, y);
  tft_dc_high();
  spi_cs_low();
  while (w--) {
    spiwrite(hi);
    spiwrite(lo);
  }
  spi_cs_high() ;
}

void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
  int16_t f, ddF_x, ddF_y, x, y;
  f = 1 - r, ddF_x = 1, ddF_y = -2 * r, x = 0, y = r;
  drawPixel(x0  , y0 + r, color);
  drawPixel(x0  , y0 - r, color);
  drawPixel(x0+r, y0    , color);
  drawPixel(x0-r, y0    , color);
  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    drawPixel(x0 + x, y0 + y, color);
    drawPixel(x0 - x, y0 + y, color);
    drawPixel(x0 + x, y0 - y, color);
    drawPixel(x0 - x, y0 - y, color);
    drawPixel(x0 + y, y0 + x, color);
    drawPixel(x0 - y, y0 + x, color);
    drawPixel(x0 + y, y0 - x, color);
    drawPixel(x0 - y, y0 - x, color);
  }
}

void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color) {
  int16_t f, ddF_x, ddF_y, x, y;
  f = 1 - r, ddF_x = 1, ddF_y = -2 * r, x = 0, y = r;
  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
      drawPixel(x0 + x, y0 + y, color);
      drawPixel(x0 + y, y0 + x, color);
    }
    if (cornername & 0x2) {
      drawPixel(x0 + x, y0 - y, color);
      drawPixel(x0 + y, y0 - x, color);
    }
    if (cornername & 0x8) {
      drawPixel(x0 - y, y0 + x, color);
      drawPixel(x0 - x, y0 + y, color);
    }
    if (cornername & 0x1) {
      drawPixel(x0 - y, y0 - x, color);
      drawPixel(x0 - x, y0 - y, color);
    }
  }
}

void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color) {
  int16_t f, ddF_x, ddF_y, x, y;
  f = 1 - r, ddF_x = 1, ddF_y = -2 * r, x = 0, y = r;
  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {
      drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
    }
    if (cornername & 0x2) {
      drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
    }
  }
}

void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
  drawFastVLine(x0, y0 - r, 2 * r + 1, color);
  fillCircleHelper(x0, y0, r, 3, 0, color);
}

void drawRectWH(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color){
  drawFastHLine(x, y, w, color);
  drawFastHLine(x, y + h - 1, w, color);
  drawFastVLine(x, y, h, color);
  drawFastVLine(x + w - 1, y, h, color);
}

void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color){
  int16_t steep, dx, dy, err, ystep;
  steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    _swap(x0,y0);
    _swap(x1,y1);
  }
  if (x0 > x1) {
    _swap(x0,x1);
    _swap(y0,y1);
  }
  dx = x1 - x0;
  dy = abs(y1-y0);

  err = dx / 2;
  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (steep) {
      drawPixel(y0, x0, color);
    } else {
      drawPixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color) {
  int16_t i;
  for (i = x; i < x + w; i++) {
    drawFastVLine(i, y, h, color);
  }
}

void drawRoundRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t r, uint16_t color) {
  drawFastHLine(x+r  , y    , w-2*r, color);
  drawFastHLine(x+r  , y+h-1, w-2*r, color);
  drawFastVLine(x    , y+r  , h-2*r, color);
  drawFastVLine(x+w-1, y+r  , h-2*r, color);
  drawCircleHelper(x+r    , y+r    , r, 1, color);
  drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
  drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
  drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}

void fillRoundRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t r, uint16_t color) {
  fillRect(x+r, y, w-2*r, h, color);
  fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
  fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}

void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
  drawLine(x0, y0, x1, y1, color);
  drawLine(x1, y1, x2, y2, color);
  drawLine(x2, y2, x0, y0, color);
}

void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
  int16_t a, b, y, last, dx01, dy01, dx02, dy02, dx12, dy12, sa, sb;
  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    _swap(y0, y1); _swap(x0, x1);
  }
  if (y1 > y2) {
    _swap(y2, y1); _swap(x2, x1);
  }
  if (y0 > y1) {
    _swap(y0, y1); _swap(x0, x1);
  }
  if(y0 == y2) { 
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    drawFastHLine(a, y0, b-a+1, color);
    return;
  }
    dx01 = x1 - x0;
    dy01 = y1 - y0;
    dx02 = x2 - x0;
    dy02 = y2 - y0;
    dx12 = x2 - x1;
    dy12 = y2 - y1;
    sa   = 0;
    sb   = 0;
  if(y1 == y2) last = y1;   
  else         last = y1-1; 
  for(y=y0; y<=last; y++) {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    if(a > b) _swap(a,b);
    drawFastHLine(a, y, b - a + 1, color);
  }

  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y<=y2; y++) {
    a   = x1 + sa / dy12;
    b   = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    if(a > b) _swap(a,b);
    drawFastHLine(a, y, b-a+1, color);
  }
}
#endif

#if defined(TFT_ENABLE_TEXT)
// Draw a single text character to screen
void drawChar(uint8_t x, uint8_t y, uint8_t c, uint16_t color, uint16_t bg,  uint8_t size){
  int8_t i, j;
  if((x >= _width) || (y >= _height))
    return;
  if(size < 1) size = 1;
  if((c < ' ') || (c > '~'))
    c = '?';
  for(i=0; i<5; i++ ) {
    uint8_t line;
    line = Font[(c - LCD_ASCII_OFFSET)*5 + i];
    for(j=0; j<7; j++, line >>= 1) {
      if(line & 0x01) {
        if(size == 1) drawPixel(x+i, y+j, color);
        else          fillRect(x+(i*size), y+(j*size), size, size, color);
      }
      else if(bg != color) {
           if(size == 1) drawPixel(x+i, y+j, bg);
           else          fillRect(x+i*size, y+j*size, size, size, bg);
        }
    }
  }
}


void setTextWrap(bool w){
  wrap = w;
}

// Draw text character array to screen
void drawText(uint8_t x, uint8_t y, const char *_text, uint16_t color, uint16_t bg, uint8_t size) {
  uint8_t cursor_x, cursor_y;
  uint16_t textsize, i;
  cursor_x = x, cursor_y = y;
  textsize = strlen(_text);
  for(i = 0; i < textsize; i++){
    if(wrap && ((cursor_x + size * 5) > _width)) {
      cursor_x = 0;
      cursor_y = cursor_y + size * 7 + 3 ;
      if(cursor_y > _height) cursor_y = _height;
      if(_text[i] == LCD_ASCII_OFFSET) {
        continue;
      }
    }
    drawChar(cursor_x, cursor_y, _text[i], color, bg, size);
    cursor_x = cursor_x + size * 6;
    if(cursor_x > _width) {
      cursor_x = _width;
    }
  }
}
#endif

void invertDisplay(bool i) {
  if(i)
    write_command(ST7735_INVON);
  else
    write_command(ST7735_INVOFF);
}

#ifdef TFT_ENABLE_SCROLL
void setScrollDefinition(uint8_t top_fix_height, uint8_t bottom_fix_height, bool _scroll_direction){
  uint8_t scroll_height;
  scroll_height = _height - top_fix_height - bottom_fix_height;
  write_command(ST7735_VSCRDEF);
  write_data(0x00);
  write_data(top_fix_height);
  write_data(0x00);
  write_data(scroll_height);
  write_data(0x00);
  write_data(bottom_fix_height);
  write_command(ST7735_MADCTL);
  if(_scroll_direction){
    if(_tft_type == 0){
      write_data(0xD8);
    }
    if(_tft_type == 1){
      write_data(0xD0);
    }
    if(_tft_type == 2){
      write_data(0x18);
    }
  }
  else{
    if(_tft_type == 0){
      write_data(0xC8);
    }
    if(_tft_type == 1){
      write_data(0xC0);
    }
    if(_tft_type == 2){
      write_data(0x08);
    }
  }
}

void VerticalScroll(uint8_t _vsp) {
  write_command(ST7735_VSCRSADD);
  write_data(0x00);
  write_data(_vsp);
}
#endif

void NormalDisplay(){
  write_command(ST7735_NORON);
}

// Convert 24-bit color to 16-bit color
int16_t Color565(int16_t r, int16_t g, int16_t b){           
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}


void pushColor(uint16_t color){
  uint8_t hi, lo;
  hi = color >> 8; lo = color;
  tft_dc_high();
  spi_cs_low();
  spiwrite(hi);
  spiwrite(lo);
  spi_cs_high() ;
}


// Init Green PCB version 
#if defined TFT_ENABLE_GREEN
void TFT_GreenTab_Initialize(){
#if defined TFT_ENABLE_RESET
  TFT_ResetPIN();
#endif
  tft_dc_config();
  tft_dc_low() ;
  spiinit();
  Rcmd1();
  Rcmd2green();
  Rcmd3();
  colstart = 2;
  rowstart = 1;
  _tft_type = 0;
}
#endif

// Function for Hardware Reset pin 
#if defined TFT_ENABLE_RESET
void TFT_ResetPIN() {
  tft_rst_config() ;
  tft_rst_high() ;
  __delay_ms(10);
  tft_rst_low() ;
  __delay_ms(10);
  tft_rst_high() ;
  __delay_ms(10);
}
#endif

// Init Red PCB version 
#if defined TFT_ENABLE_RED
void TFT_RedTab_Initialize(){
#if defined TFT_ENABLE_RESET
  TFT_ResetPIN();
#endif
  tft_dc_config();
  tft_dc_low();
  spiinit();
  Rcmd1();
  Rcmd2red();
  Rcmd3();
  _tft_type = 0;
}
#endif

// Init Black PCB version
#if defined TFT_ENABLE_BLACK
void TFT_BlackTab_Initialize(){
#if defined TFT_ENABLE_RESET
  TFT_ResetPIN();
#endif
  tft_dc_config();
  tft_dc_low() ;
  spiinit();
  Rcmd1();
  Rcmd2red();
  Rcmd3();
  write_command(ST7735_MADCTL);
  write_data(0xC0);
  _tft_type = 1;
}
#endif

// Generic PCB init function
#if defined TFT_ENABLE_GENERIC
void TFT_ST7735B_Initialize(){
#if defined TFT_ENABLE_RESET
  TFT_ResetPIN();
#endif
  tft_dc_config();
  tft_dc_low() ;
  spiinit();
  Bcmd();
  _tft_type = 2;
}
#endif

// ------ not functional yet ----------------------------------------------
// needs fat-library

#if defined TFT_ENABLE_BMP

#ifndef pixel_buffer
  #define pixel_buffer  10
#endif

bool bmpDraw(int8_t x, int8_t y, int8_t *bmpname) {
  bool ec = 0, padding = 0;
  int8_t bmpdata[pixel_buffer * 3],
       planes, depth, r, g, b, col, row;
  int16 i, buffer = pixel_buffer * 3, format, bmpHeight, bmpWidth, color;
  int32 offset, compression, bmp_size, row_size, padding_factor;
  if((x >= _width) || (y >= _height))
    return false;
  if(fat16_open_file(bmpname) != 0)
    return false;
  ec |= sdcard_read_byte(address_pointer + 1, &format);
  format <<= 8;
  ec |= sdcard_read_byte(address_pointer, &format);
  if(format != 0x4D42)                           // BMP file format signature
    return false;                                // Return error
  ec |= sdcard_read_byte(address_pointer + 0x0D, &offset);
  offset <<= 8;
  ec |= sdcard_read_byte(address_pointer + 0x0C, &offset);
  offset <<= 8;
  ec |= sdcard_read_byte(address_pointer + 0x0B, &offset);
  offset <<= 8;
  ec |= sdcard_read_byte(address_pointer + 0x0A, &offset);
  ec |= sdcard_read_byte(address_pointer + 0x13, &bmpWidth);
  bmpWidth <<= 8;
  ec |= sdcard_read_byte(address_pointer + 0x12, &bmpWidth);
  ec |= sdcard_read_byte(address_pointer + 0x17, &bmpHeight);
  bmpHeight <<= 8;
  ec |= sdcard_read_byte(address_pointer + 0x16, &bmpHeight);
  ec |= sdcard_read_byte(address_pointer + 0x1A, &planes);
  ec |= sdcard_read_byte(address_pointer + 0x1C, &depth);
  ec |= sdcard_read_byte(address_pointer + 0x21, &compression);
  compression <<= 8;
  ec |= sdcard_read_byte(address_pointer + 0x20, &compression);
  compression <<= 8;
  ec |= sdcard_read_byte(address_pointer + 0x1f, &compression);
  compression <<= 8;
  ec |= sdcard_read_byte(address_pointer + 0x1e, &compression);
  if(ec != 0 || compression != 0 || depth != 24 || planes != 1)
    return false;
  bmp_size = file_size - offset;            // bmp_size: BMP image raw size
  row_size = bmp_size / bmpHeight;          // row_size: number of bytes per row
  if((x + bmpWidth  - 1) >=  _width) {      // _width is the TFT screen width
    bmpWidth = _width  - x;
    padding = 1;           //Padding = 1 ==> only upper left part will be displayed
    padding_factor = bmpWidth / pixel_buffer;
    if(bmpWidth % pixel_buffer)
      padding_factor++;
    padding_factor *= buffer;
  }
  if((y + bmpHeight - 1) >= _height) {       // _height is the TFT screen height
    offset += row_size * (bmpHeight - _height + y);  // Only upper part will be displayed
    bmpHeight = _height - y;
  }
  file_pointer     = offset;
  address_pointer += offset;
  i = buffer;
  if(_tft_type != 2){
  // Change row address order
    write_command(ST7735_MADCTL);
    if(_tft_type == 0)
      write_data(0x48);
    if(_tft_type == 1)
      write_data(0x40);
  }
  setAddrWindow(x , y, x + bmpWidth - 1, y + bmpHeight - 1);
  for(row = 0; row < bmpHeight; row++){
    for(col = 0; col < bmpWidth; col++){
      if(i >= buffer){
        i = 0;
        fat16_read_data(buffer, bmpdata);
      }
      b = bmpdata[i++];
      g = bmpdata[i++];
      r = bmpdata[i++];
      color = Color565(r, g, b);
      pushColor(color);
    }
    if(padding == 1){
      i = buffer;
      file_pointer    += row_size - padding_factor;
      address_pointer += row_size - padding_factor;
    }
  }
  if(_tft_type != 2){
  // Return row address order as it was
    write_command(ST7735_MADCTL);
    if(_tft_type == 0)
      write_data(0xC8);
    if(_tft_type == 1)
      write_data(0xC0);
  }
  // Good BMP
  return true;
}
#endif
