/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher and Graphic Demo
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2008-2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <LPC17xx.H> /* NXP LPC17xx definitions            */
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "LED.h"
#include "KBD.h"
#include "photo.h"
#include "usbaudio.h"
#include "mazeGame.h"
#include "Blinky.h"

#define __FI 1 /* Font index 16x24               */
#define __USE_LCD 0

// ITM Stimulus Port definitions for printf //////////////////
#define ITM_Port8(n) (*((volatile unsigned char *)(0xE0000000 + 4 * n)))
#define ITM_Port16(n) (*((volatile unsigned short *)(0xE0000000 + 4 * n)))
#define ITM_Port32(n) (*((volatile unsigned long *)(0xE0000000 + 4 * n)))

#define DEMCR (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA 0x01000000

/////////////////////////////////////////////////////////
// extern unsigned char penguinvone[];

char text[10];
char text_KBD[10];
int select_option = 1;

// static volatile uint16_t AD_dbg;

// uint16_t ADC_last;                      // Last converted value
/* Import external variables from IRQ.c file                                  */
// extern uint8_t  clock_ms;

void delay(int i)
{
	int t = 0;
	while (t < i)
	{
		t++;
	}
}
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/

void main_menu()
{
	uint32_t KBD_value = 0U;

	// SystemCoreClockUpdate();
	//  SysTick_Config(SystemCoreClock/100);       /* Generate interrupt each 10 ms */

#ifdef __USE_LCD

	GLCD_Clear(White); /* Clear graphical LCD display   */
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(Green);
	GLCD_DisplayString(0, 0, __FI, "    COE718: Project    ");
	GLCD_SetTextColor(White);
	GLCD_DisplayString(1, 0, __FI, "     By Ronak Ray      ");
	GLCD_DisplayString(2, 0, __FI, "  Media Center         ");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(5, 0, __FI, "Photo Gallery           ");
	GLCD_DisplayString(6, 0, __FI, "Game                    ");
	GLCD_DisplayString(7, 0, __FI, "MP3 Player           ");

#endif

	while (1)
	{

		KBD_value = get_button(); // gets value from KBD

		if (KBD_value == KBD_DOWN)
		{
			// if user keeps toggling the joystick down it will loop back to the first option
			if (select_option % 3)
			{
				select_option++;
			}

			else
			{
				select_option = 1;
			}
		}

		if (KBD_value == KBD_UP)
		{
			// if user keeps toggling the joystick up it will loop back to the third option
			if (select_option == 1)
			{
				select_option = 3;
			}

			else
			{
				select_option--;
			}
		}
		// if first option is highlighted and selected it will go to photo gallery
		if (select_option == 1)
		{
			delay(500000);
#ifdef __USE_LCD
			GLCD_SetBackColor(Blue);
			GLCD_SetTextColor(White);
			GLCD_DisplayString(5, 0, __FI, "Photo Gallery           ");
			GLCD_SetBackColor(White);
			GLCD_SetTextColor(Blue);
			GLCD_DisplayString(6, 0, __FI, "Game           ");
			GLCD_DisplayString(7, 0, __FI, "MP3 Player           ");
#endif
			LED_On(0);
			LED_Off(1);
			LED_Off(2);

			if (KBD_value == KBD_RIGHT)
			{
				// Photo Gallery
				photogallery();
				select_option = -1;
				break;
			}
		}
		// if second option is highlighted and selected it will go to game
		else if (select_option == 2)
		{
			delay(500000);
#ifdef __USE_LCD
			GLCD_SetBackColor(White);
			GLCD_SetTextColor(Blue);
			GLCD_DisplayString(5, 0, __FI, "Photo Gallery           ");
			GLCD_DisplayString(7, 0, __FI, "MP3 Player           ");
			GLCD_SetBackColor(Yellow);
			GLCD_SetTextColor(Black);
			GLCD_DisplayString(6, 0, __FI, "Game           ");
#endif
			LED_Off(0);
			LED_On(1);
			LED_Off(2);

			if (KBD_value == KBD_RIGHT)
			{
				GLCD_Clear(White);
				mazeGameInit(); // Game
				select_option = -1;
				break;
			}
		}
		// if third option is highlighted and selected it will go to MP3 player
		else if (select_option == 3)
		{
			delay(500000);
#ifdef __USE_LCD
			GLCD_SetBackColor(White);
			GLCD_SetTextColor(Blue);
			GLCD_DisplayString(5, 0, __FI, "Photo Gallery           ");
			GLCD_DisplayString(6, 0, __FI, "Game           ");
			GLCD_SetBackColor(DarkGrey);
			GLCD_SetTextColor(Red);
			GLCD_DisplayString(7, 0, __FI, "MP3 Player           ");
#endif
			LED_Off(0);
			LED_Off(1);
			LED_On(2);

			if (KBD_value == KBD_RIGHT)
			{
				// MP3 Player
				mp3_main();
				break;
			}
		}
	}
}

int main(void)
{

	LED_Init();	 /* LED Initialization            */
	KBD_Init();	 /* KBD Initialization            */
	GLCD_Init(); /* Initialize graphical LCD (if enabled */
	main_menu();
}
