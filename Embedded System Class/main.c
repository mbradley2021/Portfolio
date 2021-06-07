//------------------------------------------------------------------------------
//
//  This file contains the Main Routine - "While" Operating System
//
//
//  Matthew Bradley
//  Sep 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include "macros.h"

// Global Variables
extern volatile unsigned int DEBOUNCE;
volatile char slow_input_down;
extern char display_line[LINE_FOUR][CHARACTER_ELEVEN];
extern char *display[LINE_FOUR];
extern unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile char one_time;
extern int hit;
volatile unsigned int UCA3_index;
extern volatile unsigned int T_COUNT;
extern volatile char USB_Char_Rx[LIMIT1];
extern volatile char HOLD_ARRAY[LIMIT1] = "$test";
volatile char HOLD_A2[LIMIT1];
extern volatile unsigned char Button_p ;
volatile unsigned char CHANGED ;
extern volatile unsigned int usb_rx_ring_wr;
extern volatile char COMMANDLOOP;
unsigned int line_command;

extern volatile unsigned int ARRAY_ONE;
extern volatile unsigned int ARRAY_TWO;

volatile unsigned char commands[2][16];
//locals
unsigned int GETSTUFF;

unsigned int test_value;
char pwm_state;
char chosen_direction;
char change;
int my_counter= LOW;
int startt = LOW;
int test_command[LIMIT1];
int next_bit = LOW;
unsigned int i2;
unsigned int i3;
volatile unsigned char PLACE;
char get_ssid[11] = "AT+NSTAT=?\r";//
volatile unsigned int going;

void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;
  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timer_A0();                       // Initialize Timers
  Init_LCD();   // Initialize LCD
  Init_Serial_UCA0();
  Init_Serial_UCA3(); // IOT
  Init_Timer_B0();
  //Init_ADC();
  
Button_p = 'N';
CHANGED = 'N';
UCA3_index = LOW;
//UCA3IE |= UCRXIE; // Enable RX interrupt
UCA3TXBUF = test_command[LOW];
PLACE = 'S';
P5OUT &= ~LCD_BACKLITE; // turn backlight off
// Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
//
//      strcpy(display_line[LINE_ZERO], "  Waiting ");
//      strcpy(display_line[LINE_TWO], "  115,200 ");
//      LCD_UPReset();

  
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
  
    switch(PLACE){
    case 'S':
    if (T_COUNT> 30){
      P3OUT |= IOT_RESET;       //starts IOT
    PLACE = 'I';
      break;
    case 's':           //gets and displays ssid and ip address
    INFO_GET();
     break;
    }
    default: break;
    }
    
    
    
    
//    switch(COMMANDLOOP){
//    case 'F':
//      line_command = 0;
//      DO_COMMANDS();
//      break;
//    case 'S':
//      line_command =1;
//      DO_COMMANDS();
//      break;
//    }
//    
    
    
    
    
    
    if(ARRAY_ONE == HI){
      line_command = 0;
      DO_COMMANDS();
      ARRAY_ONE = 0;
    }
    if(ARRAY_TWO == HI){
      line_command = 1;
      DO_COMMANDS();
      ARRAY_TWO = 0;
    }
    
    
    
    
    
          if (DEBOUNCE > dbounc ){      //Button debounce 
        P5IE |= BUTTON1;
        P5IE |= BUTTON2;
//        P5IFG |= BUTTON1; 
//        P5IFG |= BUTTON2; 
        TA0CCTL1 &= ~CCIE;
       DEBOUNCE = LOW;
      }
    

    

    if (Button_p == 'P'){
    T_COUNT = 1;
      while( going < 5000){
      if (T_COUNT %10 == 0){
        going ++;
      }
      LEFT_FORWARD_SPEED = 40000;
      RIGHT_FORWARD_SPEED = 35000;
    }
    
   Button_p = 'N';
      LEFT_FORWARD_SPEED = LOW;
      RIGHT_FORWARD_SPEED = LOW;
    
    }

  

  Display_Process();
  LCD_UPReset();



  }
  
  
}
//------------------------------------------------------------------------------





