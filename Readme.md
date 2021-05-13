ST7735 TFT-Library for PIC-Microcontrollers 
===========================================

Status
------

The code compiles and runs. Tested with a PIC12F1840/PIC16F1829 and xc8.
Note that with the defaults from `demo/Makefile`, the code just fits into the
PIC12F1840 (uses 4072 of 4096 words, free version of xc8). The library code
itself is much smaller (about 2K), the rest is test-code.

Using glyph-fonts needs a lot of memory, here you need larger PICs (e.g.
the PIC16F1829 with 8K of flash).


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
  - `TFT_ENABLE_FONTS`:   enable glyph-fonts (see below)
  - `TFT_ENABLE_BMP`:     enable bitmap-functions (not usable yet)


Fonts
-----

The ST7735-library uses a small standard-font, which is impossible to read
unless you are really near the screen. You can scale the font, but the
result is ugly.

The solution to the problem are glyph-fonts. They take up a lot of space
(2.5K-4K and more), so this might not fit into the available flash.

This repository only distributes a single glyph-font
`lib-st7735/include/FreeMonoOblique12pt7b.h`, others are available from
the original Adafruit project <https://github.com/adafruit/Adafruit-GFX-Library/>.

To use these fonts, you need to `#define TFT_ENABLE_FONTS` and set the
font before drawing text. See `Test9()` in the demo-program for an
example.
