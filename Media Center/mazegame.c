#include <LPC17xx.H>                	/* NXP LPC17xx definitions        	*/
#include "string.h"
#include "GLCD.h"
#include "KBD.h"
#include "mazeGame.h"
#include "Blinky.h"

#define __FI    	1                  	/* Font index 16x24           	*/
#define __USE_LCD   0

//ITM Stimulus Port definitions for printf //////////////////
#define ITM_Port8(n)	(*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR       	(*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA      	0x05000000
#define row 8
#define column 6

#define playerrow 1
#define playercolumn 1

int square_size = 40;

int player_size = 15;

int x = 0;
int y = 0;

int prev_x = 0;
int prev_y = 0;



char maze[row][column] = {{'S','1','0','1','0','1'},
                      	  {'1','0','1','0','1','0'},
                      	  {'0','1','0','1','0','1'},
                      	  {'1','0','1','0','1','0'},
   											  {'0','1','0','1','0','1'},
                      	  {'1','0','1','0','1','0'},
   											  {'0','1','0','1','0','1'},
                      	  {'1','0','1','0','1','F'}};
 /*
 Direction on 2D Array = Direction on Maze 
=======================*====================	
	                Down = Right                     {{'S','X','X','X','0','0','0','0'},
                 Right = Down         	           {'0','0','0','X','0','0','0','0'},
                    Up = Left         	           {'0','X','X','X','0','0','0','0'},      
                  Left = Up          	             {'0','X','0','0','0','0','0','0'},
   											                           {'0','X','0','0','0','0','0','0'},
                      	                           {'0','X','X','X','X','X','X','F'}};*/												
													
char correct_route[row][column] = {{'S','0','0','0','0','0'},
                      	           {'X','0','X','X','X','X'},
                      	           {'X','0','X','0','0','X'},
                      	           {'X','X','X','0','0','X'},
   											           {'0','0','0','0','0','X'},
                      	           {'0','0','0','0','0','X'},
   											           {'0','0','0','0','0','X'},
                      	           {'0','0','0','0','0','F'}};


void mazeGameInit(void);

void win(){
uint32_t KBD_value = 0U;
	delay(500000);
GLCD_SetBackColor(Black);
 GLCD_SetTextColor(Green);
GLCD_DisplayString(0, 0, __FI, "     YOU WIN        ");
GLCD_DisplayString(1, 0, __FI, "   RIGHT => Again    ");
GLCD_DisplayString(2, 0, __FI, "  LEFT => Main Menu   ");
	while(1){
	KBD_value = get_button ();

if(KBD_value == KBD_LEFT){

main_menu();
break;
}

if(KBD_value == KBD_RIGHT){
delay(500000);
GLCD_Clear(White);
mazeGame();
break;
}

	

}

}

void setSpawn(){
	int x_offset = 15;
    int y_offset = 15;
x = 0;
y = 0;
 GLCD_SetTextColor(Cyan);    
 GLCD_Bargraph(x*x_offset,y*y_offset,player_size,player_size,1024);
	
}


void drawMaze(){
    int i, j;
    int x_offset = 40;
    int y_offset = 40;
    for(j = 6; j >= 0; j--){
   	 for(i = 8; i >= 0; i--){
			
    if(maze[i][j] == '1'){
    GLCD_SetTextColor(Yellow);    
    GLCD_Bargraph(i*x_offset,j*y_offset,square_size,square_size,1024);
    }
    
    else if(maze[i][j] == '0'){
    GLCD_SetTextColor(Black);    
    GLCD_Bargraph(i*x_offset,j*y_offset,square_size,square_size,1024);
    }
    
    else if(maze[i][j] == 'S' && correct_route[i][j] == 'S'){
    GLCD_SetTextColor(Red);    
    GLCD_Bargraph(i*x_offset,j*y_offset,square_size,square_size,1024);
    }
    
    else if(maze[i][j] == 'F' && correct_route[i][j] == 'F'){
    GLCD_SetTextColor(Green);    
    GLCD_Bargraph(i*x_offset,j*y_offset,square_size,square_size,1024);
		}

		
}
}
}


void drawPlayer(int x, int y){
 int x_offset = 40;
    int y_offset = 40;

		
		 if ( 0 <= x && x < row && 0 <= y && y < column){
	   GLCD_SetTextColor(Cyan);    
    GLCD_Bargraph(x*x_offset,y*y_offset,player_size,player_size,1024);
			 
    if (correct_route[prev_x][prev_y] == 'X'){
		GLCD_SetTextColor(DarkGreen);    
    GLCD_Bargraph(prev_x*x_offset,prev_y*y_offset,player_size,player_size,1024);
		}
		
		else if (maze[prev_x][prev_y] == '0'){
		GLCD_SetTextColor(Magenta);    
    GLCD_Bargraph(prev_x*x_offset,prev_y*y_offset,player_size,player_size,1024);
		}
		
		else if (maze[prev_x][prev_y] == 'S'){
		GLCD_SetTextColor(Red);    
    GLCD_Bargraph(prev_x*x_offset,prev_y*y_offset,player_size,player_size,1024);
		}
   		prev_x = x;
      prev_y = y;

	}
		 else {
		  if(x > row){	 
		   x = row -1;
				drawPlayer(x,y);
		   }
		  else if( x < 0) {
		   x =0;
				drawPlayer(x,y);
		  }
		
		   if(y > column){	 
		     y = column -1;
				 drawPlayer(x,y);
		     }
		   else if( y  < 0){
		    y =0;
				 drawPlayer(x,y);
		    }
		 }
}

void drawPlayerPath(int x, int y){
	  int i, j;
	   int x_offset = 40;
    int y_offset = 40;
     for(j = 6; j >= 0; j--){
   	 for(i = 8; i >= 0; i--){
	
	if(correct_route[i][j] == 'X' && (x == i && y == j) ){
    GLCD_SetTextColor(DarkGreen);    
    GLCD_Bargraph(x*x_offset,y*y_offset,square_size,square_size,1024);
		return;
    }
	  
		else if(correct_route[i][j] == 'S' && (x == i && y == j) ){
    GLCD_SetTextColor(Red);    
    GLCD_Bargraph(x*x_offset,y*y_offset,square_size,square_size,1024);
		return;
    }
		
		else if(correct_route[i][j] == 'F' && (x == i && y == j) ){
    GLCD_SetTextColor(Green);    
    GLCD_Bargraph(x*x_offset,y*y_offset,square_size,square_size,1024);
			win();
			break;
    }
		
		else if(correct_route[i][j] == '0' && (x == i && y == j) ){
			GLCD_SetTextColor(Magenta);    
      GLCD_Bargraph(x*x_offset,y*y_offset,square_size,square_size,1024);
			setSpawn();
			return;
    }
  }
}
}


void mazeGame(){
    uint32_t KBD_value = 0U;
    GLCD_Init();  
#ifdef __USE_LCD
    GLCD_Clear(White);
	  drawMaze();
    setSpawn();
#endif
		while(1){
	KBD_value = get_button ();
		delay(500000);
		switch(KBD_value){
			case KBD_UP:
				delay(750000);
			  y--;
			drawPlayerPath(x,y);
   		 drawPlayer(x,y);			
			  break;
			case KBD_DOWN:
				delay(750000);
			  y++;		
			drawPlayerPath(x,y);
   		 drawPlayer(x,y);			
			  break;
			case KBD_LEFT:
				delay(750000);
			  x--;	
			drawPlayerPath(x,y);
   		 drawPlayer(x,y);			
			  break;
			case KBD_RIGHT:
				delay(750000);
			  x++;
			drawPlayerPath(x,y);
   		 drawPlayer(x,y);
			  break;
		}
	
	
}

}

void mazeGameInit(void){
uint32_t KBD_value = 0U;
KBD_value = get_button ();
GLCD_SetBackColor(Black);
 GLCD_SetTextColor(Yellow);
GLCD_DisplayString(0, 0, __FI, "     Memory Maze       ");
GLCD_DisplayString(1, 0, __FI, "  Goal: Get to the      ");
GLCD_SetTextColor(Green);
GLCD_DisplayString(2, 0, __FI, "    Lime Square       ");	
GLCD_SetTextColor(DarkGreen);
GLCD_DisplayString(3, 0, __FI, "   Green = Correct    ");
GLCD_SetTextColor(Magenta);
GLCD_DisplayString(4, 0, __FI, "   Magenta = Wrong            ");
GLCD_SetBackColor(White);
 GLCD_SetTextColor(Blue);
GLCD_DisplayString(5, 0, __FI, " RIGHT = Start Game");
GLCD_DisplayString(6, 0, __FI, " LEFT = Main Menu");

while(1){

KBD_value = get_button ();

if(KBD_value == KBD_LEFT){
delay(100000);
GLCD_Clear(White);
main_menu();
break;
}

if(KBD_value == KBD_RIGHT){

mazeGame();
break;
}




}

}


