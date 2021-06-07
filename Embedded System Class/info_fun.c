
//Matthew Bradley hold functions for computing recieving and transmitting 
//
//
//
#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include "macros.h"

// Globals
extern volatile char HOLD_ARRAY[LIMIT1];
extern volatile char USB_Char_Rx[LIMIT1];
extern volatile char HOLD_A2[LIMIT1];
extern volatile unsigned int usb_rx_ring_wr;
extern int test_command[LIMIT1];
extern volatile unsigned int UCA3_index;
volatile unsigned char Button_p ;
extern char display_line[LINE_FOUR][CHARACTER_ELEVEN];
extern volatile unsigned int i;
extern volatile unsigned char CHANGED ;
//Locals
int Button2press = LOW;
char k;
//-------------------------------------------------------------------------------
//
void Baud_change(void){
  if(Button2press == LOW){ // changes first time
    UCA3BRW = Lbnum;
    UCA3MCTLW = Lbaud;
    strcpy(display_line[LINE_TWO],"  115,200 ");
    LCD_UPReset();
    Button2press =HI;
    Button_p = 'N';
  }else if (Button2press == HI){ //changes 2nd time
    UCA3BRW = HI;
    UCA3MCTLW = Hbaud;
    strcpy(display_line[LINE_TWO],"  460,800 ");
    LCD_UPReset();
    Button2press =LOW;
    Button_p = 'N';
  }
}

void Trans_B1(void){
//   strcpy(display_line[LINE_THREE], "          ");
//      strcpy(display_line[LINE_ZERO], " Transmit ");   
//      LCD_UPReset();
//      for(int i2 = LOW; i2 < LIMIT1; i2++){
//        test_command[i2] = HOLD_A2[i2];
//        display_line[LINE_ONE][i2] = HOLD_A2[i2];
//      }
//
//      UCA3_index = LOW;
//      UCA3TXBUF = test_command[UCA3_index];
//      UCA3IE |= UCTXIE; 
//      Button_p = 'N';
  
  
  
  
  
    for(i=HI;i<LIMIT1;i++){
      if (i ==HI){
        out_character('$');
      }
    out_character(USB_Char_Rx[i]);
  }
  for(i=LOW;i<LIMIT1;i++){
    k = HOLD_A2[i];
    if (i == LOW){
       display_line[LINE_ONE][i] ='$';
    }
    if(i>LOW){
    display_line[LINE_ONE][i]= k;
    }
  }
  strcpy(display_line[LINE_ZERO]," Transmit ");
  strcpy(display_line[LINE_THREE],"          ");       
  LCD_UPReset();
  Button_p = 'N';
//        for(i=LOW;i<LIMIT1;i++){
//       //  USB_Char_Rx[i] = LOW;
//         usb_rx_ring_wr = LOW;
//        }
}

void CHECK_REV(void){
  for (i =LOW; i<LIMIT1; i++){
    k = HOLD_A2[i];
    if( k != USB_Char_Rx[i]){
      CHANGED = 'Y';
      return;
    }
    
  }
  
}


void SWAP_ARRAY(void){
  for (i = LOW; i<LIMIT1; i++){
    k = USB_Char_Rx[i];
    HOLD_A2[i] = k ;
  }
  
  for (i =LOW; i<LIMIT1; i++){
    k = HOLD_A2[i];
    if (i == LOW){
       display_line[LINE_THREE][i] ='$';
    }
    if(i>LOW){
    display_line[LINE_THREE][i]= k;
    }
    LCD_UPReset();
  }
  strcpy(display_line[LINE_ZERO], " Received ");
  
  LCD_UPReset();
//  for(i=LOW;i<LIMIT1;i++){
//     USB_Char_Rx[i] = LOW;
//    usb_rx_ring_wr = LOW;
//  }
  CHANGED = 'N';
  
}



