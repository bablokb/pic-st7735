ST7735 TFT-Library for PIC-Microcontrollers 
===========================================

Status
------

The code compiles and runs. Tested with a PIC12F1840. Some work is
still ahead, e.g. move all the hardware-specific code (spi, pins) into
a separate file, making it easier to port the library to other architectures.


Overview
--------

This is a port of the Adafruit ST7735-library for PIC microcontrollers.
The code is a copy of <https://github.com/gavinlyonsrepo/pic_16F18346_projects>
with some modifications to make the code compatible with my
[pic-toolchain](https://github.com/bablokb/pic-toolchain). To use the code,
you have to install the makefile-rules and header files of the toolchain.

For own projects, copy the `lib` and `include` directories and use the
code and makefile within `demo` as a starting point.


Library-configuration
---------------------

The library has many functions and to keep the footprint small, you must selectively
include only the features you need. Currently, the library supports the following
`#define`s, which you should set in the makefile:

  - `TFT_ENABLE_BLACK`:   "black"-type TFT
  - `TFT_ENABLE_GREEN`:   "green"-type TFT
  - `TFT_ENABLE_RED`:     "red"-type TFT
  - `TFT_ENABLE_GENERIC`: "generic"-type TFT
  - `TFT_ENABLE_RESET`:   use reset-pin during initialization
  - `TFT_ENABLE_TEXT`:    enable text-functions
  - `TFT_ENABLE_SHAPES`:  enable shape-functions
  - `TFT_ENABLE_SCROLL`:  enable scroll-functions (untested)
  - `TFT_ENABLE_BMP`:     enable bitmap-functions (not usable yet)
