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

#if defined(ENABLE_TEST1)
void Test1(void); // Hello world fonts + Colors text
#endif
#if defined(ENABLE_TEST1A)
void Test1A(void); // print entire font
#endif
#if defined(ENABLE_TEST2)
void Test2(void); // font sizes + character draw
#endif
#if defined(ENABLE_TEST3)
void Test3(void); // pixels and lines
#endif
#if defined(ENABLE_TEST4)
void Test4(void); // rectangles 
#endif
#if defined(ENABLE_TEST5)
void Test5(void); // Circle
#endif
#if defined(ENABLE_TEST6)
void Test6(void); // Triangles 
#endif
#if defined(ENABLE_TEST7)
void Test7(void); // scroll TODO not working in version 1.0
#endif
#if defined(ENABLE_TEST8)
void Test8(void); // shapes media buttons graphic + invert display
#endif
#endif
