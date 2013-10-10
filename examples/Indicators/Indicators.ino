/*************************************************************************
* File Name          : Indicators.ino
* Author             : Evan
* Updated            : Evan
* Version            : V0.4.1
* Date               : 10/09/2013
* Description        : Test for Makeblock Electronic modules of Me_LedStrip 
                       Driver. The module can only be connected to the 
                       PORT_1, PORT_2 of Me - Base Shield.. 
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/
#include <Me_BaseShield.h>
#include <Me_LedStripDriver.h>
#include <Wire.h>

Me_LedStripDriver ledStripDriver(PORT_1);

void setup()
{
  // initialize ledStrip Driver and set the led quantity.
  ledStripDriver.begin(60);
}

void loop()
{
  byte red = 60;
  byte green = 30;
  byte blue = 80;
  byte flSpeed = 3;
  byte count = random(1,60); // generates random numbers
  ledStripDriver.indicators(count, flSpeed, red, green, blue);
  delay(150);
}

