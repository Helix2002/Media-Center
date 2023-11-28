#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
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
 
void photogallery() {                       /* Main Program                       */
  int num     = -1; 
  int dir     =  1;
  int pic     =  0;
	int select_option =1;
	uint32_t KBD_value = 0U;

  GLCD_Clear(White);

	while(1){
	
	KBD_value = get_button (); // gets value from KBD
			
		if (KBD_value == KBD_RIGHT){
			delay(500000);
			if(select_option%3){
				  GLCD_Clear(White);
					select_option++;
			}
			
			else{
			GLCD_Clear(White);
			select_option = 1;
			}
			
	}
		
			if (KBD_value == KBD_LEFT){
				delay(500000);
				if(select_option == 1){
					 GLCD_Clear(White);
					select_option = 3;
			}
			
			else{
			GLCD_Clear(White);
			select_option--;
			}
		}
			
			
			if (KBD_value == KBD_DOWN){
				delay(500000);
				main_menu();
				break;
		}

if (select_option == 1){
	delay(500000);
  GLCD_Bitmap (  0,   0, 79,  100, penguinone);
}
	
		if (select_option == 2){
			delay(500000);
			GLCD_Bitmap (  0,   0, 81,  100, penguintwo);
	}
		
		if (select_option == 3){
			delay(500000);
     GLCD_Bitmap (  0,   0, 91,  100, penguinthree);
	}


	
  /*GLCD_Bitmap (  0,  69,   4, 102, Bg_16bpp_l+70);
  GLCD_Bitmap (316,  69,   4, 102, Bg_16bpp_r+70);
  GLCD_Bitmap (  0, 171, 320,  69, Bg_16bpp_b+70);*/

  //SysTick_Config(SystemCoreClock/100);  /* Generate interrupt every 10 ms     */

  /*for (;;) {                            
    if (ClockANI) {
      ClockANI = 0;
      if (pic++ > 8) pic = 0;
       GLCD_Bitmap (99, 99, 120, 45, &ARM_Ani_16bpp[pic*(120*45*2)]);
    }

    if (ClockLEDOn) {    //Blink LED every 1 second (for 0.5s)
      ClockLEDOn  = 0;

      // Calculate 'num': 0,1,...,LED_NUM-1,LED_NUM-1,...,1,0,0,...           
      num += dir;
      if (num == LED_NUM) { dir = -1; num =  LED_NUM-1; } 
      else if   (num < 0) { dir =  1; num =  0;         }
    
      LED_On (num);
    }
    if (ClockLEDOff) {
      ClockLEDOff = 0;

      LED_Off(num);
    }
  }*/
	
	}
	

}
			
