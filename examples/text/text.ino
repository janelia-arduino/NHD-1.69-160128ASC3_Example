//---------------------------------------------------------
/*

  test.ino

  Program for writing to Newhaven Display's 160x128 Graphic Color OLED with SEPS525 controller.

  Pick one up today in the Newhaven Display shop!
  ------> http://www.newhavendisplay.com/nhd169160128asc3-p-9288.html

  This code is written for the Arduino Uno.

  Copyright (c) 2015 - Newhaven Display International, LLC.

  Newhaven Display invests time and resources providing this open source code,
  please support Newhaven Display by purchasing products from Newhaven Display!

*/
//---------------------------------------------------------
#include <SPI.h>

// The 8 bit data bus is connected to PORTD[7..0]

#define    RS_PIN    4    // RS signal connected to pin 4
#define    RW_PIN    9    // R/W (6800 mode) signal connected to pin 9
#define    WR_PIN    9    // /WR (8080 mode) signal connected to pin 9
#define     E_PIN   10    // E (6800 mode) signal connected to pin 10
#define    RD_PIN   10    // /RD (8080 mode) signal connected to pin 10
#define   RES_PIN   6    // /RES signal connected to pin 6
#define    CS_PIN   5    // /CS signal connected to pin 5
#define    PS_PIN   A0    // PS signal connected to pin A0
#define   CPU_PIN   A1    // CPU signal connected to pin A1
#define   LVL_DIR   A2    // DIR (direction control) signal of level shifter IC connected to pin A2
#define   LVL_OEN   A3    // /OE (output enable) signal of level shifter IC connected to pin A3

#define ASCII_OFFSET 32

#define    RED  0x0000FF
#define  GREEN  0x00FF00
#define   BLUE  0xFF0000
#define  WHITE  0xFFFFFF
#define  BLACK  0x000000


/*********************************/
/****** INTERFACE SELECTION ******/
/*********************************/

const unsigned char interface = 2;    // 0 = 8-bit parallel (6800 mode) interface; 1 = 8-bit parallel (8080 mode) interface; 2 = 4-wire SPI interface

/*===============================*/
/*===============================*/
/*===============================*/


/*********************************/
/******** FONT TABLE 5x8 *********/
/************* START *************/
/*********************************/

unsigned char Ascii_1[97][5] = {     // Refer to "Times New Roman" Font Database...
  //   Basic Characters
  {0x00,0x00,0x00,0x00,0x00},     //   (  0)    - 0x0000 Empty set
  {0x00,0x00,0x4F,0x00,0x00},     //   (  1)  ! - 0x0021 Exclamation Mark
  {0x00,0x07,0x00,0x07,0x00},     //   (  2)  " - 0x0022 Quotation Mark
  {0x14,0x7F,0x14,0x7F,0x14},     //   (  3)  # - 0x0023 Number Sign
  {0x24,0x2A,0x7F,0x2A,0x12},     //   (  4)  $ - 0x0024 Dollar Sign
  {0x23,0x13,0x08,0x64,0x62},     //   (  5)  % - 0x0025 Percent Sign
  {0x36,0x49,0x55,0x22,0x50},     //   (  6)  & - 0x0026 Ampersand
  {0x00,0x05,0x03,0x00,0x00},     //   (  7)  ' - 0x0027 Apostrophe
  {0x00,0x1C,0x22,0x41,0x00},     //   (  8)  ( - 0x0028 Left Parenthesis
  {0x00,0x41,0x22,0x1C,0x00},     //   (  9)  ) - 0x0029 Right Parenthesis
  {0x14,0x08,0x3E,0x08,0x14},     //   ( 10)  * - 0x002A Asterisk
  {0x08,0x08,0x3E,0x08,0x08},     //   ( 11)  + - 0x002B Plus Sign
  {0x00,0x50,0x30,0x00,0x00},     //   ( 12)  , - 0x002C Comma
  {0x08,0x08,0x08,0x08,0x08},     //   ( 13)  - - 0x002D Hyphen-Minus
  {0x00,0x60,0x60,0x00,0x00},     //   ( 14)  . - 0x002E Full Stop
  {0x20,0x10,0x08,0x04,0x02},     //   ( 15)  / - 0x002F Solidus
  {0x3E,0x51,0x49,0x45,0x3E},     //   ( 16)  0 - 0x0030 Digit Zero
  {0x00,0x42,0x7F,0x40,0x00},     //   ( 17)  1 - 0x0031 Digit One
  {0x42,0x61,0x51,0x49,0x46},     //   ( 18)  2 - 0x0032 Digit Two
  {0x21,0x41,0x45,0x4B,0x31},     //   ( 19)  3 - 0x0033 Digit Three
  {0x18,0x14,0x12,0x7F,0x10},     //   ( 20)  4 - 0x0034 Digit Four
  {0x27,0x45,0x45,0x45,0x39},     //   ( 21)  5 - 0x0035 Digit Five
  {0x3C,0x4A,0x49,0x49,0x30},     //   ( 22)  6 - 0x0036 Digit Six
  {0x01,0x71,0x09,0x05,0x03},     //   ( 23)  7 - 0x0037 Digit Seven
  {0x36,0x49,0x49,0x49,0x36},     //   ( 24)  8 - 0x0038 Digit Eight
  {0x06,0x49,0x49,0x29,0x1E},     //   ( 25)  9 - 0x0039 Dight Nine
  {0x00,0x36,0x36,0x00,0x00},     //   ( 26)  : - 0x003A Colon
  {0x00,0x56,0x36,0x00,0x00},     //   ( 27)  ; - 0x003B Semicolon
  {0x08,0x14,0x22,0x41,0x00},     //   ( 28)  < - 0x003C Less-Than Sign
  {0x14,0x14,0x14,0x14,0x14},     //   ( 29)  = - 0x003D Equals Sign
  {0x00,0x41,0x22,0x14,0x08},     //   ( 30)  > - 0x003E Greater-Than Sign
  {0x02,0x01,0x51,0x09,0x06},     //   ( 31)  ? - 0x003F Question Mark
  {0x32,0x49,0x79,0x41,0x3E},     //   ( 32)  @ - 0x0040 Commercial At
  {0x7E,0x11,0x11,0x11,0x7E},     //   ( 33)  A - 0x0041 Latin Capital Letter A
  {0x7F,0x49,0x49,0x49,0x36},     //   ( 34)  B - 0x0042 Latin Capital Letter B
  {0x3E,0x41,0x41,0x41,0x22},     //   ( 35)  C - 0x0043 Latin Capital Letter C
  {0x7F,0x41,0x41,0x22,0x1C},     //   ( 36)  D - 0x0044 Latin Capital Letter D
  {0x7F,0x49,0x49,0x49,0x41},     //   ( 37)  E - 0x0045 Latin Capital Letter E
  {0x7F,0x09,0x09,0x09,0x01},     //   ( 38)  F - 0x0046 Latin Capital Letter F
  {0x3E,0x41,0x49,0x49,0x7A},     //   ( 39)  G - 0x0047 Latin Capital Letter G
  {0x7F,0x08,0x08,0x08,0x7F},     //   ( 40)  H - 0x0048 Latin Capital Letter H
  {0x00,0x41,0x7F,0x41,0x00},     //   ( 41)  I - 0x0049 Latin Capital Letter I
  {0x20,0x40,0x41,0x3F,0x01},     //   ( 42)  J - 0x004A Latin Capital Letter J
  {0x7F,0x08,0x14,0x22,0x41},     //   ( 43)  K - 0x004B Latin Capital Letter K
  {0x7F,0x40,0x40,0x40,0x40},     //   ( 44)  L - 0x004C Latin Capital Letter L
  {0x7F,0x02,0x0C,0x02,0x7F},     //   ( 45)  M - 0x004D Latin Capital Letter M
  {0x7F,0x04,0x08,0x10,0x7F},     //   ( 46)  N - 0x004E Latin Capital Letter N
  {0x3E,0x41,0x41,0x41,0x3E},     //   ( 47)  O - 0x004F Latin Capital Letter O
  {0x7F,0x09,0x09,0x09,0x06},     //   ( 48)  P - 0x0050 Latin Capital Letter P
  {0x3E,0x41,0x51,0x21,0x5E},     //   ( 49)  Q - 0x0051 Latin Capital Letter Q
  {0x7F,0x09,0x19,0x29,0x46},     //   ( 50)  R - 0x0052 Latin Capital Letter R
  {0x46,0x49,0x49,0x49,0x31},     //   ( 51)  S - 0x0053 Latin Capital Letter S
  {0x01,0x01,0x7F,0x01,0x01},     //   ( 52)  T - 0x0054 Latin Capital Letter T
  {0x3F,0x40,0x40,0x40,0x3F},     //   ( 53)  U - 0x0055 Latin Capital Letter U
  {0x1F,0x20,0x40,0x20,0x1F},     //   ( 54)  V - 0x0056 Latin Capital Letter V
  {0x3F,0x40,0x38,0x40,0x3F},     //   ( 55)  W - 0x0057 Latin Capital Letter W
  {0x63,0x14,0x08,0x14,0x63},     //   ( 56)  X - 0x0058 Latin Capital Letter X
  {0x07,0x08,0x70,0x08,0x07},     //   ( 57)  Y - 0x0059 Latin Capital Letter Y
  {0x61,0x51,0x49,0x45,0x43},     //   ( 58)  Z - 0x005A Latin Capital Letter Z
  {0x00,0x7F,0x41,0x41,0x00},     //   ( 59)  [ - 0x005B Left Square Bracket
  {0x02,0x04,0x08,0x10,0x20},     //   ( 60)  \ - 0x005C Reverse Solidus
  {0x00,0x41,0x41,0x7F,0x00},     //   ( 61)  ] - 0x005D Right Square Bracket
  {0x04,0x02,0x01,0x02,0x04},     //   ( 62)  ^ - 0x005E Circumflex Accent
  {0x40,0x40,0x40,0x40,0x40},     //   ( 63)  _ - 0x005F Low Line
  {0x01,0x02,0x04,0x00,0x00},     //   ( 64)  ` - 0x0060 Grave Accent
  {0x20,0x54,0x54,0x54,0x78},     //   ( 65)  a - 0x0061 Latin Small Letter A
  {0x7F,0x48,0x44,0x44,0x38},     //   ( 66)  b - 0x0062 Latin Small Letter B
  {0x38,0x44,0x44,0x44,0x20},     //   ( 67)  c - 0x0063 Latin Small Letter C
  {0x38,0x44,0x44,0x48,0x7F},     //   ( 68)  d - 0x0064 Latin Small Letter D
  {0x38,0x54,0x54,0x54,0x18},     //   ( 69)  e - 0x0065 Latin Small Letter E
  {0x08,0x7E,0x09,0x01,0x02},     //   ( 70)  f - 0x0066 Latin Small Letter F
  {0x06,0x49,0x49,0x49,0x3F},     //   ( 71)  g - 0x0067 Latin Small Letter G
  {0x7F,0x08,0x04,0x04,0x78},     //   ( 72)  h - 0x0068 Latin Small Letter H
  {0x00,0x44,0x7D,0x40,0x00},     //   ( 73)  i - 0x0069 Latin Small Letter I
  {0x20,0x40,0x44,0x3D,0x00},     //   ( 74)  j - 0x006A Latin Small Letter J
  {0x7F,0x10,0x28,0x44,0x00},     //   ( 75)  k - 0x006B Latin Small Letter K
  {0x00,0x41,0x7F,0x40,0x00},     //   ( 76)  l - 0x006C Latin Small Letter L
  {0x7C,0x04,0x18,0x04,0x7C},     //   ( 77)  m - 0x006D Latin Small Letter M
  {0x7C,0x08,0x04,0x04,0x78},     //   ( 78)  n - 0x006E Latin Small Letter N
  {0x38,0x44,0x44,0x44,0x38},     //   ( 79)  o - 0x006F Latin Small Letter O
  {0x7C,0x14,0x14,0x14,0x08},     //   ( 80)  p - 0x0070 Latin Small Letter P
  {0x08,0x14,0x14,0x18,0x7C},     //   ( 81)  q - 0x0071 Latin Small Letter Q
  {0x7C,0x08,0x04,0x04,0x08},     //   ( 82)  r - 0x0072 Latin Small Letter R
  {0x48,0x54,0x54,0x54,0x20},     //   ( 83)  s - 0x0073 Latin Small Letter S
  {0x04,0x3F,0x44,0x40,0x20},     //   ( 84)  t - 0x0074 Latin Small Letter T
  {0x3C,0x40,0x40,0x20,0x7C},     //   ( 85)  u - 0x0075 Latin Small Letter U
  {0x1C,0x20,0x40,0x20,0x1C},     //   ( 86)  v - 0x0076 Latin Small Letter V
  {0x3C,0x40,0x30,0x40,0x3C},     //   ( 87)  w - 0x0077 Latin Small Letter W
  {0x44,0x28,0x10,0x28,0x44},     //   ( 88)  x - 0x0078 Latin Small Letter X
  {0x0C,0x50,0x50,0x50,0x3C},     //   ( 89)  y - 0x0079 Latin Small Letter Y
  {0x44,0x64,0x54,0x4C,0x44},     //   ( 90)  z - 0x007A Latin Small Letter Z
  {0x00,0x08,0x36,0x41,0x00},     //   ( 91)  { - 0x007B Left Curly Bracket
  {0x00,0x00,0x7F,0x00,0x00},     //   ( 92)  | - 0x007C Vertical Line
  {0x00,0x41,0x36,0x08,0x00},     //   ( 93)  } - 0x007D Right Curly Bracket
  {0x02,0x01,0x02,0x04,0x02},     //   ( 94)  ~ - 0x007E Tilde
  {0x08,0x0C,0x0E,0x0C,0x08},     //   ( 95)  upward facing triangle/arrow
  {0x08,0x18,0x38,0x18,0x08},     //   ( 96)  downward facing triangle/arrow
};

/*===============================*/
/*======= FONT TABLE 5x8 ========*/
/*============= END =============*/
/*===============================*/


/*********************************/
/******** FONT TABLE 3x5 *********/
/************* START *************/
/*********************************/

unsigned char Ascii_2[97][3] = { // http://robey.lag.net/2010/01/23/tiny-monospace-font.html
  //   Basic Characters
  {0x00,0x00,0x00},     //   (  0)    - 0x0000 Empty set
  {0x00,0x17,0x00},     //   (  1)  ! - 0x0021 Exclamation Mark
  {0x03,0x00,0x03},     //   (  2)  " - 0x0022 Quotation Mark
  {0x1F,0x0A,0x1F},     //   (  3)  # - 0x0023 Number Sign
  {0x0A,0x1F,0x05},     //   (  4)  $ - 0x0024 Dollar Sign
  {0x09,0x04,0x12},     //   (  5)  % - 0x0025 Percent Sign
  {0x0F,0x17,0x1C},     //   (  6)  & - 0x0026 Ampersand
  {0x00,0x03,0x00},     //   (  7)  ' - 0x0027 Apostrophe
  {0x00,0x0E,0x11},     //   (  8)  ( - 0x0028 Left Parenthesis
  {0x11,0x0E,0x00},     //   (  9)  ) - 0x0029 Right Parenthesis
  {0x05,0x02,0x05},     //   ( 10)  * - 0x002A Asterisk
  {0x04,0x0E,0x04},     //   ( 11)  + - 0x002B Plus Sign
  {0x10,0x08,0x00},     //   ( 12)  , - 0x002C Comma
  {0x04,0x04,0x04},     //   ( 13)  - - 0x002D Hyphen-Minus
  {0x00,0x10,0x00},     //   ( 14)  . - 0x002E Full Stop
  {0x18,0x04,0x03},     //   ( 15)  / - 0x002F Solidus
  {0x1E,0x11,0x0F},     //   ( 16)  0 - 0x0030 Digit Zero
  {0x02,0x1F,0x00},     //   ( 17)  1 - 0x0031 Digit One
  {0x19,0x15,0x12},     //   ( 18)  2 - 0x0032 Digit Two
  {0x11,0x15,0x0A},     //   ( 19)  3 - 0x0033 Digit Three
  {0x07,0x04,0x1F},     //   ( 20)  4 - 0x0034 Digit Four
  {0x17,0x15,0x09},     //   ( 21)  5 - 0x0035 Digit Five
  {0x1E,0x15,0x1D},     //   ( 22)  6 - 0x0036 Digit Six
  {0x19,0x05,0x03},     //   ( 23)  7 - 0x0037 Digit Seven
  {0x1F,0x15,0x1F},     //   ( 24)  8 - 0x0038 Digit Eight
  {0x17,0x15,0x0F},     //   ( 25)  9 - 0x0039 Dight Nine
  {0x00,0x0A,0x00},     //   ( 26)  : - 0x003A Colon
  {0x10,0x0A,0x00},     //   ( 27)  ; - 0x003B Semicolon
  {0x04,0x0A,0x11},     //   ( 28)  < - 0x003C Less-Than Sign
  {0x0A,0x0A,0x0A},     //   ( 29)  = - 0x003D Equals Sign
  {0x11,0x0A,0x04},     //   ( 30)  > - 0x003E Greater-Than Sign
  {0x01,0x15,0x03},     //   ( 31)  ? - 0x003F Question Mark
  {0x0E,0x15,0x16},     //   ( 32)  @ - 0x0040 Commercial At
  {0x1E,0x05,0x1E},     //   ( 33)  A - 0x0041 Latin Capital Letter A
  {0x1F,0x15,0x0A},     //   ( 34)  B - 0x0042 Latin Capital Letter B
  {0x0E,0x11,0x11},     //   ( 35)  C - 0x0043 Latin Capital Letter C
  {0x1F,0x11,0x0E},     //   ( 36)  D - 0x0044 Latin Capital Letter D
  {0x1F,0x15,0x15},     //   ( 37)  E - 0x0045 Latin Capital Letter E
  {0x1F,0x05,0x05},     //   ( 38)  F - 0x0046 Latin Capital Letter F
  {0x0E,0x15,0x1D},     //   ( 39)  G - 0x0047 Latin Capital Letter G
  {0x1F,0x04,0x1F},     //   ( 40)  H - 0x0048 Latin Capital Letter H
  {0x11,0x1F,0x11},     //   ( 41)  I - 0x0049 Latin Capital Letter I
  {0x08,0x10,0x0F},     //   ( 42)  J - 0x004A Latin Capital Letter J
  {0x1F,0x04,0x1B},     //   ( 43)  K - 0x004B Latin Capital Letter K
  {0x1F,0x10,0x10},     //   ( 44)  L - 0x004C Latin Capital Letter L
  {0x1F,0x06,0x1F},     //   ( 45)  M - 0x004D Latin Capital Letter M
  {0x1F,0x0E,0x1F},     //   ( 46)  N - 0x004E Latin Capital Letter N
  {0x0E,0x11,0x0E},     //   ( 47)  O - 0x004F Latin Capital Letter O
  {0x1F,0x05,0x02},     //   ( 48)  P - 0x0050 Latin Capital Letter P
  {0x0E,0x19,0x1E},     //   ( 49)  Q - 0x0051 Latin Capital Letter Q
  {0x1F,0x0D,0x16},     //   ( 50)  R - 0x0052 Latin Capital Letter R
  {0x12,0x15,0x09},     //   ( 51)  S - 0x0053 Latin Capital Letter S
  {0x01,0x1F,0x01},     //   ( 52)  T - 0x0054 Latin Capital Letter T
  {0x0F,0x10,0x1F},     //   ( 53)  U - 0x0055 Latin Capital Letter U
  {0x07,0x18,0x07},     //   ( 54)  V - 0x0056 Latin Capital Letter V
  {0x1F,0x06,0x1F},     //   ( 55)  W - 0x0057 Latin Capital Letter W
  {0x1B,0x04,0x1B},     //   ( 56)  X - 0x0058 Latin Capital Letter X
  {0x03,0x1C,0x03},     //   ( 57)  Y - 0x0059 Latin Capital Letter Y
  {0x19,0x15,0x13},     //   ( 58)  Z - 0x005A Latin Capital Letter Z
  {0x1F,0x11,0x11},     //   ( 59)  [ - 0x005B Left Square Bracket
  {0x02,0x04,0x08},     //   ( 60)  \ - 0x005C Reverse Solidus
  {0x11,0x11,0x1F},     //   ( 61)  ] - 0x005D Right Square Bracket
  {0x02,0x01,0x02},     //   ( 62)  ^ - 0x005E Circumflex Accent
  {0x10,0x10,0x10},     //   ( 63)  _ - 0x005F Low Line
  {0x01,0x02,0x00},     //   ( 64)  ` - 0x0060 Grave Accent
  {0x1A,0x16,0x1C},     //   ( 65)  a - 0x0061 Latin Small Letter A
  {0x1F,0x12,0x0C},     //   ( 66)  b - 0x0062 Latin Small Letter B
  {0x0C,0x12,0x12},     //   ( 67)  c - 0x0063 Latin Small Letter C
  {0x0C,0x12,0x1F},     //   ( 68)  d - 0x0064 Latin Small Letter D
  {0x0C,0x1A,0x16},     //   ( 69)  e - 0x0065 Latin Small Letter E
  {0x04,0x1E,0x05},     //   ( 70)  f - 0x0066 Latin Small Letter F
  {0x06,0x15,0x0F},     //   ( 71)  g - 0x0067 Latin Small Letter G
  {0x1F,0x02,0x1C},     //   ( 72)  h - 0x0068 Latin Small Letter H
  {0x00,0x1D,0x00},     //   ( 73)  i - 0x0069 Latin Small Letter I
  {0x08,0x10,0x0D},     //   ( 74)  j - 0x006A Latin Small Letter J
  {0x1F,0x0C,0x12},     //   ( 75)  k - 0x006B Latin Small Letter K
  {0x11,0x1F,0x10},     //   ( 76)  l - 0x006C Latin Small Letter L
  {0x1E,0x0E,0x1E},     //   ( 77)  m - 0x006D Latin Small Letter M
  {0x1E,0x02,0x1C},     //   ( 78)  n - 0x006E Latin Small Letter N
  {0x0C,0x12,0x0C},     //   ( 79)  o - 0x006F Latin Small Letter O
  {0x1E,0x0A,0x04},     //   ( 80)  p - 0x0070 Latin Small Letter P
  {0x04,0x0A,0x1E},     //   ( 81)  q - 0x0071 Latin Small Letter Q
  {0x1C,0x02,0x02},     //   ( 82)  r - 0x0072 Latin Small Letter R
  {0x14,0x1E,0x0A},     //   ( 83)  s - 0x0073 Latin Small Letter S
  {0x02,0x1F,0x12},     //   ( 84)  t - 0x0074 Latin Small Letter T
  {0x0E,0x10,0x1E},     //   ( 85)  u - 0x0075 Latin Small Letter U
  {0x0E,0x18,0x0E},     //   ( 86)  v - 0x0076 Latin Small Letter V
  {0x1E,0x1C,0x1E},     //   ( 87)  w - 0x0077 Latin Small Letter W
  {0x12,0x0C,0x12},     //   ( 88)  x - 0x0078 Latin Small Letter X
  {0x03,0x14,0x0F},     //   ( 89)  y - 0x0079 Latin Small Letter Y
  {0x1A,0x1E,0x16},     //   ( 90)  z - 0x007A Latin Small Letter Z
  {0x04,0x1B,0x11},     //   ( 91)  { - 0x007B Left Curly Bracket
  {0x00,0x1F,0x00},     //   ( 92)  | - 0x007C Vertical Line
  {0x11,0x1B,0x04},     //   ( 93)  } - 0x007D Right Curly Bracket
  {0x08,0x0C,0x04},     //   ( 94)  ~ - 0x007E Tilde
  {0x0,0x0,0x0},     //   ( 95)  upward facing triangle/arrow
  {0x0,0x0,0x0},     //   ( 96)  downward facing triangle/arrow
};

/*===============================*/
/*======= FONT TABLE 3x5 ========*/
/*============= END =============*/
/*===============================*/


/*********************************/
/******* CUSTOM CHARACTERS *******/
/************* START *************/
/*********************************/

const unsigned char A10pt [] = {    // 'A' (11 pixels wide)
  0x0E, 0x00, //     ###
  0x0F, 0x00, //     ####
  0x1B, 0x00, //    ## ##
  0x1B, 0x00, //    ## ##
  0x13, 0x80, //    #  ###
  0x31, 0x80, //   ##   ##
  0x3F, 0xC0, //   ########
  0x7F, 0xC0, //  #########
  0x60, 0xC0, //  ##     ##
  0x60, 0xE0, //  ##     ###
  0xE0, 0xE0, // ###     ###
};
const unsigned char D10pt [] = {    // 'D' (9 pixels wide)
  0xFC, 0x00, // ######
  0xFF, 0x00, // ########
  0xC7, 0x00, // ##   ###
  0xC3, 0x80, // ##    ###
  0xC1, 0x80, // ##     ##
  0xC1, 0x80, // ##     ##
  0xC1, 0x80, // ##     ##
  0xC3, 0x80, // ##    ###
  0xC7, 0x00, // ##   ###
  0xFE, 0x00, // #######
  0xFC, 0x00, // ######
};
const unsigned char E10pt [] = {    // 'E' (7 pixels wide)
  0xFE, // #######
  0xFE, // #######
  0xC0, // ##
  0xC0, // ##
  0xFC, // ######
  0xFC, // ######
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xFE, // #######
  0xFE, // #######
};
const unsigned char H10pt [] = {    // 'H' (8 pixels wide)
  0xC3, // ##    ##
  0xC3, // ##    ##
  0xC3, // ##    ##
  0xC3, // ##    ##
  0xFF, // ########
  0xFF, // ########
  0xC3, // ##    ##
  0xC3, // ##    ##
  0xC3, // ##    ##
  0xC3, // ##    ##
  0xC3, // ##    ##
};
const unsigned char I10pt [] = {    // 'I' (2 pixels wide)
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
};
const unsigned char L10pt [] = {    // 'L' (7 pixels wide)
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xFE, // #######
  0xFE, // #######
};
const unsigned char N10pt [] = {    // 'N' (9 pixels wide)
  0xE1, 0x80, // ###    ##
  0xE1, 0x80, // ###    ##
  0xF1, 0x80, // ####   ##
  0xF9, 0x80, // #####  ##
  0xD9, 0x80, // ## ##  ##
  0xDD, 0x80, // ## ### ##
  0xCD, 0x80, // ##  ## ##
  0xC7, 0x80, // ##   ####
  0xC7, 0x80, // ##   ####
  0xC3, 0x80, // ##    ###
  0xC1, 0x80, // ##     ##
};
const unsigned char P10pt [] = {    // 'P' (8 pixels wide)
  0xFC, // ######
  0xFF, // ########
  0xC3, // ##    ##
  0xC3, // ##    ##
  0xC7, // ##   ###
  0xFE, // #######
  0xF8, // #####
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
};
const unsigned char S10pt [] = {    // 'S' (7 pixels wide)
  0x7C, //  #####
  0xFC, // ######
  0xC0, // ##
  0xC0, // ##
  0xF0, // ####
  0x7C, //  #####
  0x1E, //    ####
  0x06, //      ##
  0x06, //      ##
  0xFE, // #######
  0xF8, // #####
};
const unsigned char V10pt [] = {    // 'V' (10 pixels wide)
  0xE0, 0xC0, // ###     ##
  0xE1, 0xC0, // ###    ###
  0x61, 0x80, //  ##    ##
  0x71, 0x80, //  ###   ##
  0x73, 0x00, //  ###  ##
  0x33, 0x00, //   ##  ##
  0x3B, 0x00, //   ### ##
  0x1E, 0x00, //    ####
  0x1E, 0x00, //    ####
  0x1C, 0x00, //    ###
  0x0C, 0x00, //     ##
};
const unsigned char W10pt [] = {    // 'W' (16 pixels wide)
  0xE1, 0x83, // ###    ##     ##
  0xE1, 0xC7, // ###    ###   ###
  0x63, 0xC6, //  ##   ####   ##
  0x63, 0xC6, //  ##   ####   ##
  0x72, 0xC6, //  ###  # ##   ##
  0x32, 0x6C, //   ##  #  ## ##
  0x36, 0x6C, //   ## ##  ## ##
  0x3E, 0x6C, //   #####  ## ##
  0x1C, 0x28, //    ###    # #
  0x1C, 0x38, //    ###    ###
  0x1C, 0x38, //    ###    ###
};
const unsigned char Y10pt [] = {    // 'Y' (8 pixels wide)
  0xE3, // ###   ##
  0x66, //  ##  ##
  0x66, //  ##  ##
  0x34, //   ## #
  0x34, //   ## #
  0x18, //    ##
  0x18, //    ##
  0x18, //    ##
  0x18, //    ##
  0x18, //    ##
  0x18, //    ##
};

/*===============================*/
/*====== CUSTOM CHARACTERS ======*/
/*============= END =============*/
/*===============================*/


/*********************************/
/****** LOW LEVEL FUNCTIONS ******/
/************* START *************/
/*********************************/

void OLED_Command_160128RGB(unsigned char c)        // send command to OLED
{
  unsigned char i;
  unsigned char mask = 0x80;

  switch(interface)
  {
    case 0:
      digitalWrite(CS_PIN, LOW);
      digitalWrite(RS_PIN, LOW);
      PORTD = c;
      digitalWrite(RW_PIN, LOW);
      digitalWrite(E_PIN, HIGH);
      digitalWrite(E_PIN, LOW);
      digitalWrite(CS_PIN, HIGH);
      break;
    case 1:
      digitalWrite(CS_PIN, LOW);
      digitalWrite(RS_PIN, LOW);
      digitalWrite(WR_PIN, HIGH);
      PORTD = c;
      digitalWrite(WR_PIN, LOW);
      digitalWrite(WR_PIN, HIGH);
      digitalWrite(CS_PIN, HIGH);
      break;
    case 2:
      digitalWrite(CS_PIN, LOW);
      digitalWrite(RS_PIN, LOW);
      SPI.transfer(c);
      digitalWrite(CS_PIN, HIGH);
      break;
    default:  break;
  }
}

void OLED_Data_160128RGB(unsigned char d)        // send data to OLED
{
  unsigned char i;
  unsigned char mask = 0x80;

  switch(interface)
  {
    case 0:
      digitalWrite(CS_PIN, LOW);
      digitalWrite(RS_PIN, HIGH);
      PORTD = d;
      digitalWrite(RW_PIN, LOW);
      digitalWrite(E_PIN, HIGH);
      digitalWrite(E_PIN, LOW);
      digitalWrite(CS_PIN, HIGH);
      break;
    case 1:
      digitalWrite(CS_PIN, LOW);
      digitalWrite(RS_PIN, HIGH);
      digitalWrite(WR_PIN, HIGH);
      PORTD = d;
      digitalWrite(WR_PIN, LOW);
      digitalWrite(WR_PIN, HIGH);
      digitalWrite(CS_PIN, HIGH);
      break;
    case 2:
      digitalWrite(CS_PIN, LOW);
      digitalWrite(RS_PIN, HIGH);
      SPI.transfer(d);
      digitalWrite(CS_PIN, HIGH);
      break;
    default:
      break;
  }
}

void OLED_SerialPixelData_160128RGB(unsigned char d)    // serial write for pixel data
{
  unsigned char i;
  unsigned char mask = 0x80;
  digitalWrite(CS_PIN, LOW);
  digitalWrite(RS_PIN, HIGH);
  SPI.transfer(d);
  digitalWrite(CS_PIN, HIGH);
}

void OLED_SetColumnAddress_160128RGB(unsigned char x_start, unsigned char x_end)    // set column address start + end
{
  OLED_Command_160128RGB(0x17);
  OLED_Data_160128RGB(x_start);
  OLED_Command_160128RGB(0x18);
  OLED_Data_160128RGB(x_end);
}

void OLED_SetRowAddress_160128RGB(unsigned char y_start, unsigned char y_end)    // set row address start + end
{
  OLED_Command_160128RGB(0x19);
  OLED_Data_160128RGB(y_start);
  OLED_Command_160128RGB(0x1A);
  OLED_Data_160128RGB(y_end);
}

void OLED_WriteMemoryStart_160128RGB(void)    // write to RAM command
{
  OLED_Command_160128RGB(0x22);
}

void OLED_Pixel_160128RGB(unsigned long color)    // write one pixel of a given color
{
  switch(interface)
  {
    case 0:
      OLED_Data_160128RGB((color>>16));
      OLED_Data_160128RGB((color>>8));
      OLED_Data_160128RGB(color);
      break;
    case 1:
      OLED_Data_160128RGB((color>>16));
      OLED_Data_160128RGB((color>>8));
      OLED_Data_160128RGB(color);
      break;
    case 2:
      OLED_SerialPixelData_160128RGB((color>>16));
      OLED_SerialPixelData_160128RGB((color>>8));
      OLED_SerialPixelData_160128RGB(color);
      break;
    default:
      break;
  }
}

void OLED_SetPosition_160128RGB(unsigned char x_pos, unsigned char y_pos)    // set x,y address
{
  OLED_Command_160128RGB(0x20);
  OLED_Data_160128RGB(x_pos);
  OLED_Command_160128RGB(0x21);
  OLED_Data_160128RGB(y_pos);
}

void OLED_FillScreen_160128RGB(unsigned long color)    // fill screen with a given color
{
  unsigned int i;
  OLED_SetPosition_160128RGB(0,0);
  OLED_WriteMemoryStart_160128RGB();
  for(i=0;i<20480;i++)
  {
    OLED_Pixel_160128RGB(color);
  }
}

/*===============================*/
/*===== LOW LEVEL FUNCTIONS =====*/
/*============= END =============*/
/*===============================*/


/*********************************/
/***** HIGH LEVEL FUNCTIONS ******/
/************ START **************/
/*********************************/

void OLED_Text_160128RGB(unsigned char x_pos, unsigned char y_pos, unsigned char letter, unsigned long textColor, unsigned long backgroundColor)  // function to show text
{
  int i;
  int count;
  unsigned char mask = 0x80;

  for(i=0;i<8;i++)     // each character is 8 pixels tall
  {
    OLED_SetPosition_160128RGB(x_pos,y_pos);
    OLED_WriteMemoryStart_160128RGB();
    for (count=0;count<5;count++)    // each character is 5 pixels wide
    {
      if((Ascii_1[letter - ASCII_OFFSET][count] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
    }
    y_pos++;
    mask = mask >> 1;
  }
}

void OLED_Text_Mini_160128RGB(unsigned char x_pos, unsigned char y_pos, unsigned char letter, unsigned long textColor, unsigned long backgroundColor)  // function to show text
{
  int i;
  int count;
  unsigned char mask = 0x10;

  for(i=0;i<5;i++)     // each character is 8 pixels tall
  {
    OLED_SetPosition_160128RGB(x_pos,y_pos);
    OLED_WriteMemoryStart_160128RGB();
    for (count=0;count<3;count++)    // each character is 5 pixels wide
    {
      if((Ascii_2[letter - ASCII_OFFSET][count] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
    }
    y_pos++;
    mask = mask >> 1;
  }
}

void OLED_Text2x_160128RGB(unsigned char x_pos, unsigned char y_pos, unsigned char letter, unsigned long textColor, unsigned long backgroundColor)  // function to show text (2x size)
{
  int i;
  int count;
  unsigned char mask = 0x80;

  for(i=1;i<=16;i++)     // each character is 16 pixels tall
  {
    OLED_SetPosition_160128RGB(x_pos,y_pos);
    OLED_WriteMemoryStart_160128RGB();
    for (count=0;count<10;count++)    // each character is 10 pixels wide
    {
      if((Ascii_1[letter - ASCII_OFFSET][(count/2)] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
    }
    y_pos++;
    if((i%2)==0)
    {
      mask = mask >> 1;
    }
  }
}

void OLED_NHDText_160128RGB(unsigned long textColor, unsigned long backgroundColor)    // function to show NEWHAVEN DISPLAY
{
  int i;
  int count;
  unsigned char index = 0;
  unsigned char y_pos = 110;
  unsigned char mask = 0x80;

  for(i=0;i<11;i++)     // display custom character N
  {
    OLED_SetPosition_160128RGB(26,y_pos);
    OLED_WriteMemoryStart_160128RGB();
    for (count=0;count<8;count++)
    {
      if((N10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    for (count=0;count<8;count++)
    {
      if((N10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    y_pos--;
  }
  index = 0;
  y_pos = 110;

  for(i=0;i<11;i++)     // display custom character E
  {
    OLED_SetPosition_160128RGB(40,y_pos);
    OLED_WriteMemoryStart_160128RGB();
    for (count=0;count<8;count++)
    {
      if((E10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    y_pos--;
  }
  index = 0;
  y_pos = 110;

  for(i=0;i<11;i++)     // display custom character W
  {
    OLED_SetPosition_160128RGB(51,y_pos);
    OLED_WriteMemoryStart_160128RGB();
    for (count=0;count<8;count++)
    {
      if((W10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    for (count=0;count<8;count++)
    {
      if((W10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    y_pos--;
  }
  index = 0;
  y_pos = 110;

  for(i=0;i<11;i++)     // display custom character H
  {
    OLED_SetPosition_160128RGB(71,y_pos);
    OLED_WriteMemoryStart_160128RGB();
    for (count=0;count<8;count++)
    {
      if((H10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    y_pos--;
  }
  index = 0;
  y_pos = 110;

  for(i=0;i<11;i++)     // display custom character A
  {
    OLED_SetPosition_160128RGB(83,y_pos);
    OLED_WriteMemoryStart_160128RGB();
    for (count=0;count<8;count++)
    {
      if((A10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    for (count=0;count<8;count++)
    {
      if((A10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    y_pos--;
  }
  index = 0;
  y_pos = 110;

  for(i=0;i<11;i++)     // display custom character V
  {
    OLED_SetPosition_160128RGB(96,y_pos);
    OLED_WriteMemoryStart_160128RGB();
    for (count=0;count<8;count++)
    {
      if((V10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    for (count=0;count<8;count++)
    {
      if((V10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    y_pos--;
  }
  index = 0;
  y_pos = 110;

  for(i=0;i<11;i++)     // display custom character E
  {
    OLED_SetPosition_160128RGB(110,y_pos);
    OLED_WriteMemoryStart_160128RGB();
    for (count=0;count<8;count++)
    {
      if((E10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    y_pos--;
  }
  index = 0;
  y_pos = 110;

  for(i=0;i<11;i++)     // display custom character N
  {
    OLED_SetPosition_160128RGB(122,y_pos);
    OLED_WriteMemoryStart_160128RGB();
    for (count=0;count<8;count++)
    {
      if((N10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    for (count=0;count<8;count++)
    {
      if((N10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    y_pos--;
  }
  index = 0;
  y_pos = 94;

  for(i=0;i<11;i++)     // display custom character D
  {
    OLED_SetPosition_160128RGB(40,y_pos);
    OLED_WriteMemoryStart_160128RGB();
    for (count=0;count<8;count++)
    {
      if((D10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    for (count=0;count<8;count++)
    {
      if((D10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    y_pos--;
  }
  index = 0;
  y_pos = 94;

  for(i=0;i<11;i++)     // display custom character I
  {
    OLED_SetPosition_160128RGB(54,y_pos);
    OLED_WriteMemoryStart_160128RGB();
    for (count=0;count<8;count++)
    {
      if((I10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    y_pos--;
  }
  index = 0;
  y_pos = 94;

  for(i=0;i<11;i++)     // display custom character S
  {
    OLED_SetPosition_160128RGB(61,y_pos);
    OLED_WriteMemoryStart_160128RGB();
    for (count=0;count<8;count++)
    {
      if((S10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    y_pos--;
  }
  index = 0;
  y_pos = 94;

  for(i=0;i<11;i++)     // display custom character P
  {
    OLED_SetPosition_160128RGB(72,y_pos);
    OLED_WriteMemoryStart_160128RGB();
    for (count=0;count<8;count++)
    {
      if((P10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    y_pos--;
  }
  index = 0;
  y_pos = 94;

  for(i=0;i<11;i++)     // display custom character L
  {
    OLED_SetPosition_160128RGB(84,y_pos);
    OLED_WriteMemoryStart_160128RGB();
    for (count=0;count<8;count++)
    {
      if((L10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    y_pos--;
  }
  index = 0;
  y_pos = 94;

  for(i=0;i<11;i++)     // display custom character A
  {
    OLED_SetPosition_160128RGB(95,y_pos);
    OLED_WriteMemoryStart_160128RGB();
    for (count=0;count<8;count++)
    {
      if((A10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    for (count=0;count<8;count++)
    {
      if((A10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    y_pos--;
  }
  index = 0;
  y_pos = 94;

  for(i=0;i<11;i++)     // display custom character Y
  {
    OLED_SetPosition_160128RGB(109,y_pos);
    OLED_WriteMemoryStart_160128RGB();
    for (count=0;count<8;count++)
    {
      if((Y10pt[index] & mask) == mask)
        OLED_Pixel_160128RGB(textColor);
      else
        OLED_Pixel_160128RGB(backgroundColor);
      mask = mask >> 1;
    }
    index++;
    mask = 0x80;
    y_pos--;
  }
}

/*===============================*/
/*==== HIGH LEVEL FUNCTIONS =====*/
/*============= END =============*/
/*===============================*/


/*********************************/
/******** INITIALIZATION *********/
/************ START **************/
/*********************************/

void OLED_Init_160128RGB(void)      //OLED initialization
{
  digitalWrite(RES_PIN, LOW);
  delay(2);
  digitalWrite(RES_PIN, HIGH);
  delay(2);

  // display off, analog reset
  OLED_Command_160128RGB(0x04);
  OLED_Data_160128RGB(0x01);
  delay(1);

  // normal mode
  OLED_Command_160128RGB(0x04);
  OLED_Data_160128RGB(0x00);
  delay(1);

  // display off
  OLED_Command_160128RGB(0x06);
  OLED_Data_160128RGB(0x00);
  delay(1);

  // turn on internal oscillator using external resistor
  OLED_Command_160128RGB(0x02);
  OLED_Data_160128RGB(0x01);

  // 90 hz frame rate, divider 0
  OLED_Command_160128RGB(0x03);
  OLED_Data_160128RGB(0x30);

  // duty cycle 127
  OLED_Command_160128RGB(0x28);
  OLED_Data_160128RGB(0x7F);

  // start on line 0
  OLED_Command_160128RGB(0x29);
  OLED_Data_160128RGB(0x00);

  // rgb_if
  OLED_Command_160128RGB(0x14);
  OLED_Data_160128RGB(0x31);

  // Set Memory Write Mode
  OLED_Command_160128RGB(0x16);
  OLED_Data_160128RGB(0x76);

  // driving current r g b (uA)
  OLED_Command_160128RGB(0x10);
  OLED_Data_160128RGB(0x45);
  OLED_Command_160128RGB(0x11);
  OLED_Data_160128RGB(0x34);
  OLED_Command_160128RGB(0x12);
  OLED_Data_160128RGB(0x33);

  // precharge time r g b
  OLED_Command_160128RGB(0x08);
  OLED_Data_160128RGB(0x04);
  OLED_Command_160128RGB(0x09);
  OLED_Data_160128RGB(0x05);
  OLED_Command_160128RGB(0x0A);
  OLED_Data_160128RGB(0x05);

  // precharge current r g b (uA)
  OLED_Command_160128RGB(0x0B);
  OLED_Data_160128RGB(0x9D);
  OLED_Command_160128RGB(0x0C);
  OLED_Data_160128RGB(0x8C);
  OLED_Command_160128RGB(0x0D);
  OLED_Data_160128RGB(0x57);

  // Set Reference Voltage Controlled by External Resister
  OLED_Command_160128RGB(0x80);
  OLED_Data_160128RGB(0x00);

  // mode set
  OLED_Command_160128RGB(0x13);
  OLED_Data_160128RGB(0xA0);

  OLED_SetColumnAddress_160128RGB(0, 159);
  OLED_SetRowAddress_160128RGB(0, 127);

  // Display On
  OLED_Command_160128RGB(0x06);
  OLED_Data_160128RGB(0x01);
}

/*===============================*/
/*======= INITIALIZATION ========*/
/*============= END =============*/
/*===============================*/

void setup()                                       // for Arduino, runs first at power on
{
  pinMode(LVL_OEN, OUTPUT);                       // configure LVL_OEN as output
  digitalWrite(LVL_OEN, LOW);
  pinMode(LVL_DIR, OUTPUT);                       // configure LVL_DIR as output
  digitalWrite(LVL_DIR, HIGH);
  DDRD = 0xFF;                                    // configure PORTD as output
  pinMode(RS_PIN, OUTPUT);                        // configure RS_PIN as output
  pinMode(RES_PIN, OUTPUT);                       // configure RES_PIN as output
  pinMode(CS_PIN, OUTPUT);                        // configure CS_PIN as output
  pinMode(PS_PIN, OUTPUT);                        // configure PS_PIN as output
  pinMode(CPU_PIN, OUTPUT);                       // configure CPU_PIN as output
  digitalWrite(LVL_OEN, LOW);
  digitalWrite(CS_PIN, HIGH);                     // set CS_PIN
  switch(interface)
  {
    case 0:
      pinMode(RW_PIN, OUTPUT);                    // configure RW_PIN as output
      pinMode(E_PIN, OUTPUT);                     // configure E_PIN as output
      digitalWrite(PS_PIN, HIGH);                 // set PS_PIN
      digitalWrite(CPU_PIN, HIGH);                // set CPU_PIN
      digitalWrite(RW_PIN, LOW);                  // reset RW_PIN
      digitalWrite(E_PIN, HIGH);                  // set E_PIN
      break;
    case 1:
      pinMode(WR_PIN, OUTPUT);                    // configure WR_PIN as output
      pinMode(RD_PIN, OUTPUT);                    // configure RD_PIN as output
      digitalWrite(PS_PIN, HIGH);                 // set PS_PIN
      digitalWrite(CPU_PIN, LOW);                 // reset CPU_PIN
      digitalWrite(WR_PIN, HIGH);                 // set WR_PIN
      digitalWrite(RD_PIN, HIGH);                 // set RD_PIN
      break;
    case 2:
      PORTD = 0x00;                               // reset SDI_PIN and SCL_PIN, ground DB[5..0] of the display
      digitalWrite(PS_PIN, LOW);                  // reset PS_PIN
      SPI.begin();
      SPI.setBitOrder(MSBFIRST);
      SPI.setDataMode(SPI_MODE3);
      SPI.setClockDivider(SPI_CLOCK_DIV2);
      break;
    default:
      break;
  }

  OLED_Init_160128RGB();                           // initialize display
}

void loop()                                         // main loop, runs after "setup()"
{
  OLED_FillScreen_160128RGB(BLACK);                // fill screen with black

  OLED_NHDText_160128RGB(GREEN, BLACK);            // show NEWHAVEN DISPLAY

  unsigned char y_pos = 60;

  OLED_Text_160128RGB(6, 60, '!', WHITE, BLACK);
  OLED_Text_160128RGB(12, 60, '"', WHITE, BLACK);
  OLED_Text_160128RGB(18, 60, '#', WHITE, BLACK);
  OLED_Text_160128RGB(24, 60, '$', WHITE, BLACK);
  OLED_Text_160128RGB(30, 60, '%', WHITE, BLACK);
  OLED_Text_160128RGB(36, 60, '&', WHITE, BLACK);
  OLED_Text_160128RGB(42, 60, '\'', WHITE, BLACK);
  OLED_Text_160128RGB(48, 60, '(', WHITE, BLACK);
  OLED_Text_160128RGB(54, 60, ')', WHITE, BLACK);
  OLED_Text_160128RGB(60, 60, '*', WHITE, BLACK);
  OLED_Text_160128RGB(66, 60, '+', WHITE, BLACK);
  OLED_Text_160128RGB(72, 60, ',', WHITE, BLACK);
  OLED_Text_160128RGB(78, 60, '-', WHITE, BLACK);
  OLED_Text_160128RGB(84, 60, '.', WHITE, BLACK);
  OLED_Text_160128RGB(90, 60, '/', WHITE, BLACK);
  OLED_Text_160128RGB(96, 60, '0', WHITE, BLACK);
  OLED_Text_160128RGB(102, 60, '1', WHITE, BLACK);
  OLED_Text_160128RGB(108, 60, '2', WHITE, BLACK);
  OLED_Text_160128RGB(114, 60, '3', WHITE, BLACK);
  OLED_Text_160128RGB(120, 60, '4', WHITE, BLACK);
  OLED_Text_160128RGB(126, 60, '5', WHITE, BLACK);
  OLED_Text_160128RGB(132, 60, '6', WHITE, BLACK);
  OLED_Text_160128RGB(138, 60, '7', WHITE, BLACK);
  OLED_Text_160128RGB(144, 60, '8', WHITE, BLACK);
  OLED_Text_160128RGB(150, 60, '9', WHITE, BLACK);

  OLED_Text_160128RGB(0, 51, ':', WHITE, BLACK);
  OLED_Text_160128RGB(6, 51, ';', WHITE, BLACK);
  OLED_Text_160128RGB(12, 51, '<', WHITE, BLACK);
  OLED_Text_160128RGB(18, 51, '=', WHITE, BLACK);
  OLED_Text_160128RGB(24, 51, '>', WHITE, BLACK);
  OLED_Text_160128RGB(30, 51, '?', WHITE, BLACK);
  OLED_Text_160128RGB(36, 51, '@', WHITE, BLACK);
  OLED_Text_160128RGB(42, 51, 'A', WHITE, BLACK);
  OLED_Text_160128RGB(48, 51, 'B', WHITE, BLACK);
  OLED_Text_160128RGB(54, 51, 'C', WHITE, BLACK);
  OLED_Text_160128RGB(60, 51, 'D', WHITE, BLACK);
  OLED_Text_160128RGB(66, 51, 'E', WHITE, BLACK);
  OLED_Text_160128RGB(72, 51, 'F', WHITE, BLACK);
  OLED_Text_160128RGB(78, 51, 'G', WHITE, BLACK);
  OLED_Text_160128RGB(84, 51, 'H', WHITE, BLACK);
  OLED_Text_160128RGB(90, 51, 'I', WHITE, BLACK);
  OLED_Text_160128RGB(96, 51, 'J', WHITE, BLACK);
  OLED_Text_160128RGB(102, 51, 'K', WHITE, BLACK);
  OLED_Text_160128RGB(108, 51, 'L', WHITE, BLACK);
  OLED_Text_160128RGB(114, 51, 'M', WHITE, BLACK);
  OLED_Text_160128RGB(120, 51, 'N', WHITE, BLACK);
  OLED_Text_160128RGB(126, 51, 'O', WHITE, BLACK);
  OLED_Text_160128RGB(132, 51, 'P', WHITE, BLACK);
  OLED_Text_160128RGB(138, 51, 'Q', WHITE, BLACK);
  OLED_Text_160128RGB(144, 51, 'R', WHITE, BLACK);
  OLED_Text_160128RGB(150, 51, 'S', WHITE, BLACK);

  OLED_Text_160128RGB(0, 42, 'T', WHITE, BLACK);
  OLED_Text_160128RGB(6, 42, 'U', WHITE, BLACK);
  OLED_Text_160128RGB(12, 42, 'V', WHITE, BLACK);
  OLED_Text_160128RGB(18, 42, 'W', WHITE, BLACK);
  OLED_Text_160128RGB(24, 42, 'X', WHITE, BLACK);
  OLED_Text_160128RGB(30, 42, 'Y', WHITE, BLACK);
  OLED_Text_160128RGB(36, 42, 'Z', WHITE, BLACK);
  OLED_Text_160128RGB(42, 42, '[', WHITE, BLACK);
  OLED_Text_160128RGB(48, 42, '\\', WHITE, BLACK);
  OLED_Text_160128RGB(54, 42, ']', WHITE, BLACK);
  OLED_Text_160128RGB(60, 42, '^', WHITE, BLACK);
  OLED_Text_160128RGB(66, 42, '_', WHITE, BLACK);
  OLED_Text_160128RGB(72, 42, '`', WHITE, BLACK);
  OLED_Text_160128RGB(78, 42, 'a', WHITE, BLACK);
  OLED_Text_160128RGB(84, 42, 'b', WHITE, BLACK);
  OLED_Text_160128RGB(90, 42, 'c', WHITE, BLACK);
  OLED_Text_160128RGB(96, 42, 'd', WHITE, BLACK);
  OLED_Text_160128RGB(102, 42, 'e', WHITE, BLACK);
  OLED_Text_160128RGB(108, 42, 'f', WHITE, BLACK);
  OLED_Text_160128RGB(114, 42, 'g', WHITE, BLACK);
  OLED_Text_160128RGB(120, 42, 'h', WHITE, BLACK);
  OLED_Text_160128RGB(126, 42, 'i', WHITE, BLACK);
  OLED_Text_160128RGB(132, 42, 'j', WHITE, BLACK);
  OLED_Text_160128RGB(138, 42, 'k', WHITE, BLACK);
  OLED_Text_160128RGB(144, 42, 'l', WHITE, BLACK);
  OLED_Text_160128RGB(150, 42, 'm', WHITE, BLACK);

  OLED_Text_160128RGB(0, 33, 'n', WHITE, BLACK);
  OLED_Text_160128RGB(6, 33, 'o', WHITE, BLACK);
  OLED_Text_160128RGB(12, 33, 'p', WHITE, BLACK);
  OLED_Text_160128RGB(18, 33, 'q', WHITE, BLACK);
  OLED_Text_160128RGB(24, 33, 'r', WHITE, BLACK);
  OLED_Text_160128RGB(30, 33, 's', WHITE, BLACK);
  OLED_Text_160128RGB(36, 33, 't', WHITE, BLACK);
  OLED_Text_160128RGB(42, 33, 'u', WHITE, BLACK);
  OLED_Text_160128RGB(48, 33, 'v', WHITE, BLACK);
  OLED_Text_160128RGB(54, 33, 'w', WHITE, BLACK);
  OLED_Text_160128RGB(60, 33, 'x', WHITE, BLACK);
  OLED_Text_160128RGB(66, 33, 'y', WHITE, BLACK);
  OLED_Text_160128RGB(72, 33, 'z', WHITE, BLACK);
  OLED_Text_160128RGB(78, 33, '{', WHITE, BLACK);
  OLED_Text_160128RGB(84, 33, '|', WHITE, BLACK);
  OLED_Text_160128RGB(90, 33, '}', WHITE, BLACK);
  OLED_Text_160128RGB(96, 33, '~', WHITE, BLACK);

  OLED_Text_Mini_160128RGB(0, 12, ' ', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(4, 12, '!', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(8, 12, '"', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(12, 12, '#', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(16, 12, '$', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(20, 12, '%', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(24, 12, '&', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(28, 12, '\'', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(32, 12, '(', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(36, 12, ')', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(40, 12, '*', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(44, 12, '+', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(48, 12, ',', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(52, 12, '-', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(56, 12, '.', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(60, 12, '/', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(64, 12, '0', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(68, 12, '1', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(72, 12, '2', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(76, 12, '3', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(80, 12, '4', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(84, 12, '5', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(88, 12, '6', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(92, 12, '7', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(96, 12, '8', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(100, 12, '9', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(104, 12, ':', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(108, 12, ';', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(112, 12, '<', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(116, 12, '=', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(120, 12, '>', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(124, 12, '?', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(128, 12, '@', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(132, 12, 'A', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(136, 12, 'B', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(140, 12, 'C', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(144, 12, 'D', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(148, 12, 'E', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(152, 12, 'F', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(156, 12, 'G', WHITE, BLACK);

  OLED_Text_Mini_160128RGB(0, 6, 'H', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(4, 6, 'I', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(8, 6, 'J', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(12, 6, 'K', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(16, 6, 'L', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(20, 6, 'M', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(24, 6, 'N', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(28, 6, 'O', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(32, 6, 'P', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(36, 6, 'Q', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(40, 6, 'R', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(44, 6, 'S', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(48, 6, 'T', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(52, 6, 'U', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(56, 6, 'V', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(60, 6, 'W', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(64, 6, 'X', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(68, 6, 'Y', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(72, 6, 'Z', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(76, 6, '[', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(80, 6, '\\', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(84, 6, ']', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(88, 6, '^', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(92, 6, '_', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(96, 6, '`', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(100, 6, 'a', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(104, 6, 'b', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(108, 6, 'c', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(112, 6, 'd', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(116, 6, 'e', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(120, 6, 'f', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(124, 6, 'g', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(128, 6, 'h', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(132, 6, 'i', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(136, 6, 'j', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(140, 6, 'k', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(144, 6, 'l', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(148, 6, 'm', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(152, 6, 'n', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(156, 6, 'o', WHITE, BLACK);

  OLED_Text_Mini_160128RGB(0, 0, 'p', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(4, 0, 'q', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(8, 0, 'r', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(12, 0, 's', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(16, 0, 't', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(20, 0, 'u', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(24, 0, 'v', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(28, 0, 'w', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(32, 0, 'x', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(36, 0, 'y', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(40, 0, 'z', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(44, 0, '{', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(48, 0, '|', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(52, 0, '}', WHITE, BLACK);
  OLED_Text_Mini_160128RGB(56, 0, '~', WHITE, BLACK);

  while(true);
}
