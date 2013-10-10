/******************************************************************************
* File Name          : Me_LedStripDriver.h
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

#include <Arduino.h>
#include <Wire.h>
#include <Me_BaseShield.h>

#ifndef Me_LedStripDriver_h
#define Me_LedStripDriver_h

//address table
#define LS_RUN_STATE     0x91
#define LS_CURRENT       0x92
#define LS_GET_PIXEL_R   0x93
#define LS_GET_PIXEL_G   0x94
#define LS_GET_PIXEL_B   0x95
#define LS_GET_PIXEL_NUM 0x96

#define LS_SET_PIXEL_NUM 0x02
#define LS_SET_PIXEL_R   0x03
#define LS_SET_PIXEL_G   0x04
#define LS_SET_PIXEL_B   0x05
#define LS_SET_SPEED     0x06
#define LS_SET_COUNT     0x07
#define LS_SET_IN_SPEED  0x08

#define LS_RUN_CTRL      0x1A
#define LS_LED_COUNT		 0x1B

//data table
#define LS_NO_FLASH			0x00
#define LS_STOP_FLASH		0x00
#define LS_AUTO_FLASH		0x01
#define LS_ONCE_FLASH		0x02
#define LS_CLOSE				0x04
#define LS_RESET				0x05
#define LS_COLOR_LOOP		0x06
#define LS_INDICATORS   0x07
#define LS_ALL_PIXEL 		0xFE

#define MAX_BRI					200
#define MIN_BRI					0
#define IN_SPEED				2

class Me_LedStripDriver
{
public:
	Me_LedStripDriver();
	// portNum can ONLY be PORT_1 or PORT_2
	Me_LedStripDriver(int portNum);
	
	// initialize ledStrip Driver and set the led quantity. (value: 1-60)
	void begin(int ledCount);
	
	// Automatic cycle refresh each LED. After perform this function, the led refresh automatically.
	// You can set the reflash time. Max value = 255.
	void autoFlash(int flashSpeed = 0);
	
	// Refresh once LED, Entirely by the loop function to refresh the LED Strip. When you need to write multiple leds, 
	// use the LS_ONCE_FLASH mode to refresh all LED when writing the last LED, in front of the led use LS_NO_FLASH mode,
	// it can speed up the refresh.
	void onceFlash();
	
	// Stop all led of strip. But it doesn't close the leds. All LED to keep the last state.
	void stopFlash();
	
	// Stop and reset all led of strip.
	void reset();
	
	boolean readState();
	
	// Write each LED color and refresh mode. 
	// LS_AUTO_FLASH : Automatic cycle refresh each LED. After perform this function, the led refresh automatically.
	//								 This mode is not commonly used.
	// LS_ONCE_FLASH : Please refer to the instructions of onceFlash().
	//                         ___________________________________________________________________________________________
	// Parameter description: | LED Number | Red brightness | Green brightness | Blue brightness | Indicators flash speed |
	//                        |___________________________________________________________________________________________|
	void setPixelColor(byte lsNum = LS_ALL_PIXEL, byte lsR = MIN_BRI,byte lsG = MIN_BRI, byte lsB = MIN_BRI, byte lsMode = LS_ONCE_FLASH);
	
//long getPixelColor(byte n);

	// Color gradient LED Scroller function.
	// Automatically refresh after initialization, you can use stopFlash() to stop flash, but it doesn't close leds.
	// use the reset() to stop and reset led.
	void color_loop();
	
	// This is an indicator function that is used to display range quickly.
	//                         ___________________________________________________________________________________________
	// Parameter description: | LED Number | Red brightness | Green brightness | Blue brightness | Indicators flash speed |
	//                        |___________________________________________________________________________________________|
	void indicators(byte lsNum, byte lsR, byte lsG, byte lsB, byte lsSpd = IN_SPEED);
	
	byte twi_read(int slaveAddress, byte dataAddress);
	void twi_write(int slaveAddress, byte dataAddress, byte data);
	
private:
	byte s1Pin;
	byte s2Pin;
	byte slaveAddress;
	long pixelColor;
};
#endif

