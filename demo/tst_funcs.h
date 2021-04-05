/*
* Project Name: ST7735, 128 by 128, 1.44", red pcb,  SPI TFT module, library. 
* File: main.c
* Description: test file  
* Author: Gavin Lyons.
* Version: 1.0
* Complier: xc8 v2.10 compiler
* PIC: PIC16F18346
* IDE:  MPLAB X v5.30
* Created Sep 2020
* Description: See URL for full details.
* URL: https://github.com/gavinlyonsrepo/pic_16F18346_projects
*/

#ifndef TEST_FUNCS_H
#define TEST_FUNCS_H

#include <stdint.h>

#define TEST_DELAY1() delay_s(1)
#define TEST_DELAY2() delay_s(2)
#define TEST_DELAY5() delay_s(5)

void delay_s(uint8_t count);
void Test1(void); // Hello world fonts + Colors text
void Test1A(void); // print entire font
void Test2(void); // font sizes + character draw
void Test3(void); // pixels and lines
void Test4(void); // rectangles 
void Test5(void); // Circle
void Test6(void); // Triangles 
void Test7(void); // scroll TODO not working in version 1.0
void Test8(void); // shapes media buttons graphic + invert display
#endif
