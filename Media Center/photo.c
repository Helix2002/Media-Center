#include <LPC17xx.H> /* NXP LPC17xx definitions            */
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "photo.h"
#include "KBD.h"
#include "Blinky.h"

extern unsigned char ClockLEDOn;
extern unsigned char ClockLEDOff;
extern unsigned char ClockANI;
extern unsigned char Bg_16bpp_t[];
extern unsigned char Bg_16bpp_l[];
extern unsigned char Bg_16bpp_r[];
extern unsigned char Bg_16bpp_b[];
extern unsigned char penguinone[];
extern unsigned char penguintwo[];
extern unsigned char penguinthree[];
extern unsigned char ARM_Ani_16bpp[];

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/

void photogallery()
{ /* Main Program                       */
	int num = -1;
	int dir = 1;
	int pic = 0;
	int select_option = 1;
	uint32_t KBD_value = 0U;

	GLCD_Clear(White);

	while (1)
	{

		KBD_value = get_button(); // gets value from KBD
		// if user toggles right it will loop through the photo gallery
		if (KBD_value == KBD_RIGHT)
		{
			delay(500000);
			if (select_option % 3)
			{
				GLCD_Clear(White);
				select_option++;
			}

			else
			{
				GLCD_Clear(White);
				select_option = 1;
			}
		}
		// if user toggles left it will loop through the photo gallery
		if (KBD_value == KBD_LEFT)
		{
			delay(500000);
			if (select_option == 1)
			{
				GLCD_Clear(White);
				select_option = 3;
			}

			else
			{
				GLCD_Clear(White);
				select_option--;
			}
		}

		if (KBD_value == KBD_DOWN)
		{
			delay(500000);
			main_menu();
			break;
		}
		// Displays photos
		if (select_option == 1)
		{
			delay(500000);
			GLCD_Bitmap(0, 0, 79, 100, penguinone);
		}

		if (select_option == 2)
		{
			delay(500000);
			GLCD_Bitmap(0, 0, 81, 100, penguintwo);
		}

		if (select_option == 3)
		{
			delay(500000);
			GLCD_Bitmap(0, 0, 91, 100, penguinthree);
		}
	}
}
