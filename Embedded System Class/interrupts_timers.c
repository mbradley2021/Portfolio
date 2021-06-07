#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include "macros.h"
 volatile unsigned int T_COUNT;
int unsigned Time_Sequence;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int DEBOUNCE;

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void){
//------------------------------------------------------------------------------
// TimerA0 0 Interrupt handler
//----------------------------------------------------------------------------
//...... Add What you need happen in the interrupt ......




Time_Sequence++;
if(Time_Sequence >= twofifcount){
  Time_Sequence = LOW;
}
 
if (Time_Sequence %twelvecount == LOW){
update_display = ALWAYS;

}
TA0CCR0 += TA0CCR0_INTERVAL;

//----------------------------------------------------------------------------

}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void){
//----------------------------------------------------------------------------
// TimerA0 1-2, Overflow Interrupt Vector (TAIV) handler
//----------------------------------------------------------------------------

  switch(__even_in_range(TA0IV,case_foutt)){
case case_zero: break; // No interrupt
case case_two: 
  DEBOUNCE ++;
TA0CCR1 += TA0CCR1_INTERVAL; // Add Offset to TACCR1
break;
case case_four: 
    
  T_COUNT++;
  
TA0CCR2 += TA0CCR2_INTERVAL; // Add Offset to TACCR2
break;
case case_foutt: // overflow
//...... Add What you need happen in the interrupt ......
break;
default: break;
}
//----------------------------------------------------------------------------
}