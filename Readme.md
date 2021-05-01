ST7735 TFT-Library for PIC-Microcontrollers 
===========================================

Status
------

The code compiles and runs. Tested with a PIC12F1840 and xc8. Note that
with the defaults from `demo/Makefile`, the code just fits into the
PIC (uses 4072 of 4096 words, free version of xc8). The library code
itself is much smaller (about 2K), the rest is tescode.

Overview
--------

This is a port of the Adafruit ST7735-library for PIC microcontrollers.
The code is a copy of <https://github.com/gavinlyonsrepo/pic_16F18346_projects>
with some added features (`TFT_ENABLE_*`-defines, rotation) and some modifications
to make the code compatible with my
[pic-toolchain](https://github.com/bablokb/pic-toolchain).

To use the code directly, you have to install the makefile-rules and header files
of the toolchain. Otherwise, copy the `lib` and `include` directories and use the
code and makefile within `demo` as a starting point. You will
have to edit `include/hw.h`. If you don't want to use my pic-toolchain
(or if you port the code to a different platform), you must also supply
your own version of `include/spi.h`.


Library-configuration
---------------------

The library has many functions and to keep the footprint small, you must selectively
include only the features you need. Currently, the library supports the following
`#define`s, which you should set in the makefile:

  - `TFT_ENABLE_ALL`:     enable all features
  - `TFT_ENABLE_BLACK`:   "black"-type TFT
  - `TFT_ENABLE_GREEN`:   "green"-type TFT
  - `TFT_ENABLE_RED`:     "red"-type TFT
  - `TFT_ENABLE_GENERIC`: "generic"-type TFT
  - `TFT_ENABLE_RESET`:   use reset-pin during initialization
  - `TFT_ENABLE_TEXT`:    enable text-functions
  - `TFT_ENABLE_SHAPES`:  enable shape-functions
  - `TFT_ENABLE_SCROLL`:  enable scroll-functions
  - `TFT_ENABLE_ROTATE`:  enable rotation
  - `TFT_ENABLE_BMP`:     enable bitmap-functions (not usable yet)
