/******************************************************************************
* File Name          : Me_LedStripDriver.cpp
* Author             : Evan
* Updated            : Evan
* Version            : V0.1.1
* Date               : 10/09/2013
* Description        : Class for Makeblock Electronic modules of Me_LedStrip
											 Driver. The module can only be connected to the PORT_1, 
                       PORT_2 of Me-Base Shield.
* License            : CC-BY-SA 3.0, GPL
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************/

#include "Me_LedStripDriver.h"

Me_LedStripDriver::Me_LedStripDriver()
{
	s1Pin = mePort[PORT_1].innersidePin;
	s2Pin = mePort[PORT_1].outsidePin;
}

Me_LedStripDriver::Me_LedStripDriver(int portNum)
{
	if(portNum>0 && portNum < 3 )
	{
		s1Pin = mePort[portNum].innersidePin;
		s2Pin = mePort[portNum].outsidePin;
	}
}

void Me_LedStripDriver::begin(int ledCount)
{
	Me_BaseShield::begin();
//	pinMode(s1Pin,OUTPUT);
//	pinMode(s2Pin,OUTPUT);
//	digitalWrite(s1Pin,HIGH);
//	digitalWrite(s2Pin,LOW);
	delay(1500); //wait Me_LedStripDriver initialize /limit:1400
	Wire.begin(); // join i2c bus (address optional for master)
	slaveAddress = 0x05;
	twi_write(slaveAddress, LS_LED_COUNT, ledCount);
	reset();
}

void Me_LedStripDriver::autoFlash(int flashSpeed)
{
	twi_write(slaveAddress, LS_SET_SPEED, flashSpeed);
  twi_write(slaveAddress, LS_RUN_CTRL, LS_AUTO_FLASH);
}

void Me_LedStripDriver::onceFlash()
{
  twi_write(slaveAddress, LS_RUN_CTRL, LS_ONCE_FLASH);
}

void Me_LedStripDriver::stopFlash()
{
  twi_write(slaveAddress, LS_RUN_CTRL, LS_STOP_FLASH);
}

void Me_LedStripDriver::reset()
{
  twi_write(slaveAddress, LS_RUN_CTRL, LS_RESET);
}

boolean Me_LedStripDriver::readState()
{
  if(twi_read(slaveAddress, LS_RUN_STATE))
    return true;
  else
    return false;
}

void Me_LedStripDriver::setPixelColor(byte lsNum, byte lsR,byte lsG, byte lsB, byte lsMode)
{
  twi_write(slaveAddress, LS_SET_PIXEL_R, lsR);
  twi_write(slaveAddress, LS_SET_PIXEL_G, lsG);
  twi_write(slaveAddress, LS_SET_PIXEL_B, lsB);
  twi_write(slaveAddress, LS_SET_PIXEL_NUM, lsNum);
  twi_write(slaveAddress, LS_RUN_CTRL, lsMode);
}

/*
long pixelColor;
long Me_LedStripDriver::getPixelColor(byte n)
{
  twi_write(slaveAddress, LS_GET_PIXEL_NUM, n);
  *((char *)(&pixelColor))   = twi_read(slaveAddress, LS_GET_PIXEL_R);
  *((char *)(&pixelColor)+1) = twi_read(slaveAddress, LS_GET_PIXEL_G);
  *((char *)(&pixelColor)+2) = twi_read(slaveAddress, LS_GET_PIXEL_B);
  return pixelColor;
}
*/

void Me_LedStripDriver::color_loop()
{
  twi_write(slaveAddress, LS_RUN_CTRL, LS_COLOR_LOOP);
}

void Me_LedStripDriver::indicators(byte lsNum, byte lsR, byte lsG, byte lsB, byte lsSpd)
{
	twi_write(slaveAddress, LS_SET_COUNT, lsNum);
	twi_write(slaveAddress, LS_SET_IN_SPEED, lsSpd);
	twi_write(slaveAddress, LS_SET_PIXEL_R, lsR);
  twi_write(slaveAddress, LS_SET_PIXEL_G, lsG);
  twi_write(slaveAddress, LS_SET_PIXEL_B, lsB);
  twi_write(slaveAddress, LS_RUN_CTRL, LS_INDICATORS);
}
// must write low first
byte Me_LedStripDriver::twi_read(int slaveAddress, byte dataAddress)
{
  byte rxByte;
  Wire.beginTransmission(slaveAddress); // transmit to device
  Wire.write(dataAddress);  // sends one byte
  Wire.endTransmission();    // stop transmitting
  delayMicroseconds(1);
  Wire.requestFrom(slaveAddress, 1);    // request 6 bytes from slave device
  while(Wire.available())    // slave may send less than requested
    return rxByte = Wire.read(); // receive a byte as character
  return 0;
}

void Me_LedStripDriver::twi_write(int slaveAddress, byte dataAddress, byte data)
{
  Wire.beginTransmission(slaveAddress); // transmit to device
  Wire.write(dataAddress);  // sends one byte
  Wire.endTransmission();    // stop transmitting
  
  Wire.beginTransmission(slaveAddress); // transmit to device
  Wire.write(data);  // sends one byte
  Wire.endTransmission();    // stop transmitting
}

