//---------------------
//Matthew Bradley
//  Sep 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//holds init conditions
//---------------------



#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include "macros.h"

extern char display_line[LINE_FOUR][CHARACTER_ELEVEN];
extern char *display[LINE_FOUR];
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern char pwm_state;

void Init_Ports(void){
Init_Port1();
Init_Port2();
Init_Port3();
Init_Port4();
Init_Port5();
Init_Port6();
Init_Port7();
Init_Port8();
Init_PortJ();
}

void Init_Conditions(void){
//------------------------------------------------------------------------------
  int i;

  for(i=RESET_STATE;i<CHARACTER_ELEVEN;i++){
    display_line[LINE_ZERO][i] = RESET_STATE;
    display_line[LINE_ONE][i] = RESET_STATE;
    display_line[LINE_TWO][i] = RESET_STATE;
    display_line[LINE_FOUR][i] = RESET_STATE;
  }
  display_line[LINE_ZERO][CHARACTER_TEN] = RESET_STATE;
  display_line[LINE_ONE][CHARACTER_TEN] = RESET_STATE;
  display_line[LINE_TWO][CHARACTER_TEN] = RESET_STATE;
  display_line[LINE_THREE][CHARACTER_TEN] = RESET_STATE;

  display[LINE_ZERO] = &display_line[LINE_ZERO][CHARACTER_ZERO];
  display[LINE_ONE] = &display_line[LINE_ONE][CHARACTER_TEN];
  display[LINE_TWO] = &display_line[LINE_TWO][CHARACTER_TEN];
  display[LINE_THREE] = &display_line[LINE_THREE][CHARACTER_TEN];
  update_display = RESET_STATE;
  update_display_count = RESET_STATE;
  pwm_state = PORTS;
// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}


//------------------------------------------------------------------
void LCD_UPReset(void){
 update_string(display_line[LINE_ZERO], LINE_ZERO);
 update_string(display_line[LINE_ONE], LINE_ONE);
 update_string(display_line[LINE_TWO], LINE_TWO);
 update_string(display_line[LINE_THREE], LINE_THREE);
 enable_display_update();
 display_changed = HI;
 Display_Update(LOW,LOW,LOW,LOW);

}

void out_character(char character){
//------------------------------------------------------------------------------
// The while loop will stall as long as the Flag is not set [port is busy]
 while (!(UCA3IFG & UCTXIFG)); // USCI_A0 TX buffer ready?
 UCA3TXBUF = character;
//------------------------------------------------------------------------------
}

