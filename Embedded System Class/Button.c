//Matthew Bradley
// holds the button interupts




#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include "macros.h"

//Globals
volatile unsigned int DEBOUNCE;
extern char display_line[LINE_FOUR][CHARACTER_ELEVEN];
volatile unsigned int i;
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned int UCA3_index;
extern volatile char USB_Char_Rx[LIMIT1];
extern volatile unsigned char Button_p ;
//-----------------------------------------------------------------------------

#pragma vector=PORT5_VECTOR
//Create Interrupt Service Routine Function with “__interrupt”
__interrupt void BUTTON_interrupt(void) {
// BUTTON 1
if(P5IFG & BUTTON1) {	//button one functionality
    
DEBOUNCE = LOW ;
P5IFG &= ~BUTTON1; 
P5IE &= ~BUTTON1;
  

 Button_p = 'P' ;
  
  
  //UCA3CTL1 &= ~UCSWRST;
//  UCA3IE |= UCRXIE;
//     while (1){
//       for(i=0;i<10;i++){
//       out_character(commm[i]);
//       }
//       for(i=0;i<10;i++){
//       display_line[0][i]= USB_Char_Rx[i];
//       }
//       LCD_UPReset();
//       }
//      
  
  
  
  
  
  //hit =1;
  
  
  
 
//  for(i=0;i<10;i++){
// out_character(commm[i]);
//  display_line[0][i]= commm[i];
//    LCD_UPReset();
//  }
//  

TA0CCTL1 |= CCIE;

}




// BUTTON 2
if (P5IFG & BUTTON2) {	//button two functionality
  
  
  DEBOUNCE = LOW;

  P5IFG &= ~BUTTON2; 
  P5IE &= ~BUTTON2; 
 
  
  
  Button_p = 'H'; // switchs the baud rate
  

 
 //hit = 1;
  
//    for(i = 0; i>10;i++){
//  out_character(commm[i]);
//  display_line[0][i] = commm[i];
//    LCD_UPReset();
//  }
  
  TA0CCTL1 |= CCIE; //turn debounce on
 
  
  
  
}
// Enable the Timer Interrupt for the debounce.
}

//-----------------------------------------------------