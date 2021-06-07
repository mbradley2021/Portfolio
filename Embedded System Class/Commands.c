//Matthew Bradley
// This file holds all the Commands for the IOT to execute 
//-----------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include "macros.h"


//globals
extern volatile unsigned char command_ARRAY[2][5];
extern unsigned int line_command;
extern volatile unsigned int T_COUNT;
extern volatile unsigned int going;
extern char display_line[LINE_FOUR][CHARACTER_ELEVEN];
unsigned int mod ;
//Locals
//unsigned int TimeCounter;



void DO_COMMANDS(void){
        lcd_BIG_mid();
    strcpy(display_line[LINE_ZERO], "          ");
    strcpy(display_line[LINE_ONE], "          ");
    strcpy(display_line[LINE_TWO], "          ");
LCD_UPReset();

mod=command_ARRAY[line_command][1];

  if (command_ARRAY[line_command][0] == 'W'){ // go forward 10000 steps for 2 sec or 5000 steps for a sec
    strcpy(display_line[LINE_ONE], " Forward  ");
    LCD_UPReset();
    T_COUNT = 1;
    going =0;
      while( going < 10000){
      if (T_COUNT %10 == 0){
        going ++;
      }
      LEFT_FORWARD_SPEED = 40000;
      RIGHT_FORWARD_SPEED = 20000;
    }
      strcpy(display_line[LINE_ONE], "   Stop   ");
      LCD_UPReset();  
      LEFT_FORWARD_SPEED = LOW;
      RIGHT_FORWARD_SPEED = LOW;
      LEFT_REVERSE_SPEED = LOW;
      RIGHT_REVERSE_SPEED = LOW;
    }
  
    if (command_ARRAY[line_command][0] == 'E'){ // super short forward about inch
    strcpy(display_line[LINE_ONE], " Forward  ");
    LCD_UPReset();
    T_COUNT = 1;
    going =0;
      while( going < 10000){
      if (T_COUNT %4 == 0){
        going ++;
      }
      LEFT_FORWARD_SPEED = 40000;
      RIGHT_FORWARD_SPEED = 20000;
    }
      strcpy(display_line[LINE_ONE], "   Stop   ");
      LCD_UPReset();  
      LEFT_FORWARD_SPEED = LOW;
      RIGHT_FORWARD_SPEED = LOW;
      LEFT_REVERSE_SPEED = LOW;
      RIGHT_REVERSE_SPEED = LOW;
    }
  if (command_ARRAY[line_command][0] == 'R'){ // short forward about 4inch
    strcpy(display_line[LINE_ONE], " Forward  ");
    LCD_UPReset();
    T_COUNT = 1;
    going =0;
      while( going < 10000){
      if (T_COUNT %7 == 0){
        going ++;
      }
      LEFT_FORWARD_SPEED = 40000;
      RIGHT_FORWARD_SPEED = 20000;
    }
      strcpy(display_line[LINE_ONE], "   Stop   ");
      LCD_UPReset();  
      LEFT_FORWARD_SPEED = LOW;
      RIGHT_FORWARD_SPEED = LOW;
      LEFT_REVERSE_SPEED = LOW;
      RIGHT_REVERSE_SPEED = LOW;
    }
  
  if (command_ARRAY[line_command][0] == 'S'){ // go forward 10000 steps for 2 sec or 5000 steps for a sec
    strcpy(display_line[LINE_ONE], " Reverse  ");
    LCD_UPReset();
    T_COUNT = 1;
    going = 0;
      while( going < 5000){
      if (T_COUNT %10 == 0){
        going ++;
      }
      LEFT_REVERSE_SPEED = 40000;
      RIGHT_REVERSE_SPEED = 35000;
    }
      strcpy(display_line[LINE_ONE], "   Stop   ");
      LCD_UPReset();
      LEFT_FORWARD_SPEED = LOW;
      RIGHT_FORWARD_SPEED = LOW;
      LEFT_REVERSE_SPEED = LOW;
      RIGHT_REVERSE_SPEED = LOW;
    }
  
  if (command_ARRAY[line_command][0] == 'B'){ // go forward 10000 steps for 2 sec or 5000 steps for a sec
    strcpy(display_line[LINE_ONE], " Reverse  ");
    LCD_UPReset();
    T_COUNT = 1;
    going = 0;
      while( going < 5000){
      if (T_COUNT %6 == 0){
        going ++;
      }
      LEFT_REVERSE_SPEED = 40000;
      RIGHT_REVERSE_SPEED = 35000;
    }
      strcpy(display_line[LINE_ONE], "   Stop   ");
      LCD_UPReset();
      LEFT_FORWARD_SPEED = LOW;
      RIGHT_FORWARD_SPEED = LOW;
      LEFT_REVERSE_SPEED = LOW;
      RIGHT_REVERSE_SPEED = LOW;
    }

    if (command_ARRAY[line_command][0] == 'N'){ // go forward 10000 for 2 sec 5000 for a sec
    strcpy(display_line[LINE_ONE], " Reverse  ");
    LCD_UPReset();
    T_COUNT = 1;
    going = 0;
      while( going < 5000){
      if (T_COUNT %4 == 0){
        going ++;
      }
      LEFT_REVERSE_SPEED = 40000;
      RIGHT_REVERSE_SPEED = 35000;
    }
      strcpy(display_line[LINE_ONE], "   Stop   ");
      LCD_UPReset();
      LEFT_FORWARD_SPEED = LOW;
      RIGHT_FORWARD_SPEED = LOW;
      LEFT_REVERSE_SPEED = LOW;
      RIGHT_REVERSE_SPEED = LOW;
    }

  
  if (command_ARRAY[line_command][0] == 'D'){ //90-right turn
    strcpy(display_line[LINE_ONE], " 90-Right ");
    LCD_UPReset();
    T_COUNT = 1;
    going =0;
      while( going <1 ){
      if (T_COUNT %6 == 0){
        going ++;
      }
      LEFT_FORWARD_SPEED = 21000;
      RIGHT_REVERSE_SPEED = 16000;
    }
      strcpy(display_line[LINE_ONE], "   Stop   ");
      LCD_UPReset();
      LEFT_FORWARD_SPEED = LOW;
      RIGHT_FORWARD_SPEED = LOW;
      LEFT_REVERSE_SPEED = LOW;
      RIGHT_REVERSE_SPEED = LOW;
    }
  
   if (command_ARRAY[line_command][0] == 'F'){ //45-right turn
    strcpy(display_line[LINE_ONE], " 45-Right ");
    LCD_UPReset();
    T_COUNT = 1;
    going =0;
      while( going <1 ){
      if (T_COUNT %4 == 0){
        going ++;
      }
      LEFT_FORWARD_SPEED = 21000;
      RIGHT_REVERSE_SPEED = 16000;
    }
      strcpy(display_line[LINE_ONE], "   Stop   ");
      LCD_UPReset();
      LEFT_FORWARD_SPEED = LOW;
      RIGHT_FORWARD_SPEED = LOW;
      LEFT_REVERSE_SPEED = LOW;
      RIGHT_REVERSE_SPEED = LOW;
    }
  
  
  if (command_ARRAY[line_command][0] == 'A'){ //45-left turn
    strcpy(display_line[LINE_ONE], " 45-Left  ");
    LCD_UPReset();
    T_COUNT = 1;
    going = 0;
      while( going < 1){
      if (T_COUNT %4 == 0){
        going ++;
      }
      LEFT_REVERSE_SPEED = 21000;
      RIGHT_FORWARD_SPEED = 16000;
    }
      strcpy(display_line[LINE_ONE], "   Stop   ");
      LCD_UPReset();
      LEFT_FORWARD_SPEED = LOW;
      RIGHT_FORWARD_SPEED = LOW;
      LEFT_REVERSE_SPEED = LOW;
      RIGHT_REVERSE_SPEED = LOW;
    }
  
  if (command_ARRAY[line_command][0] == 'Q'){ //90-left turn
    strcpy(display_line[LINE_ONE], " 90-Left  ");
    LCD_UPReset();
    T_COUNT = 1;
    going = 0;
      while( going < 1){
      if (T_COUNT %6 == 0){
        going ++;
      }
      LEFT_REVERSE_SPEED = 21000;
      RIGHT_FORWARD_SPEED = 16000;
    }
      strcpy(display_line[LINE_ONE], "   Stop   ");
      LCD_UPReset();
      LEFT_FORWARD_SPEED = LOW;
      RIGHT_FORWARD_SPEED = LOW;
      LEFT_REVERSE_SPEED = LOW;
      RIGHT_REVERSE_SPEED = LOW;
    }

  }// end of Do_commands