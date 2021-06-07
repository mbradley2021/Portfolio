//Matthew Bradley
//This holds the function for the ADC and the interrupts for it
//10/19/2018
//
//Globals : ADC_Thumb, ADC_Left_Detector, ADC _Right_Detector
//
//

#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include "macros.h"


//Globals
unsigned int ADC_Thumb;
unsigned int ADC_Left_Detector;
unsigned int ADC_Right_Detector;



void Init_ADC(void){
//------------------------------------------------------------------------------
// Configure ADC12

// ADC10CTL0 Register Description
  ADC12CTL0 = RESET_STATE;
  ADC12CTL0 |= ADC12SHT0_2;     // 16 ADC clocks
  ADC12CTL0 |= ADC12SHT1_2;     // 16 ADC clocks
  ADC12CTL0 |= ADC12MSC;        // First rising edge SHI signal triggers sampling timer
  ADC12CTL0 |= ADC12ON;         // ADC12 on

// ADC10CTL1 Register Description
  ADC12CTL1 = RESET_STATE;
  ADC12CTL1 |= ADC12PDIV_0;     // Predivide ADC12_B clock source by 1
  ADC12CTL1 |= ADC12SHS_0;      // sample-and-hold source ADC12SC
  ADC12CTL1 |= ADC12SHP;      // SAMPCON signal is sourced from the sampling timer.
  ADC12CTL1 |= ADC12ISSH_0;     // sample-input signal is not inverted
  ADC12CTL1 |= ADC12DIV_0;      // / 1 clock divider
  ADC12CTL1 |= ADC12SSEL0;      // ADC12OSC (MODOSC)
  ADC12CTL1 |= ADC12CONSEQ_3;   // Repeat-sequence-of-channels

// ADC12CTL2 Register Description
  ADC12CTL2 = RESET_STATE;
  ADC12CTL2 |= ADC12RES_2;      // 12-bit conversion results / 14 clock cycle conversion
  ADC12CTL2 |= ADC12DF_0;       // Binary unsigned
  ADC12CTL2 |= ADC12PWRMD_0;    // Regular power mode where sample rate is not restricted

// ADC12CTL3 Register Description
  ADC12CTL3 = RESET_STATE;
  ADC12CTL3 |= ADC12ICH3MAP_0;  // external pin is selected for ADC input channel A26
  ADC12CTL3 |= ADC12ICH2MAP_0;  // external pin is selected for ADC input channel A27
  ADC12CTL3 |= ADC12ICH1MAP_0;  // external pin is selected for ADC input channel A28
  ADC12CTL3 |= ADC12ICH0MAP_0;  // external pin is selected for ADC input channel A29
  ADC12CTL3 |= ADC12TCMAP_1;    // ADC internal temperature sensor ADC input channel A30
  ADC12CTL3 |= ADC12BATMAP_1;   // ADC internal 1/2 x AVCC is ADC input channel A31
  ADC12CTL3 |= ADC12CSTARTADD_0; // 0h to 1Fh, corresponding to ADC12MEM0 to ADC12MEM31

// ADC10MCTL0 Register Description
  ADC12MCTL0 = RESET_STATE;
  ADC12MCTL0 |= ADC12WINC_0;    // Comparator window disabled
  ADC12MCTL0 |= ADC12DIF_0;     // Single-ended mode enabled
  ADC12MCTL0 |= ADC12VRSEL_0;   // VR+ = AVCC, VR- = AVSS
  ADC12MCTL0 |= ADC12INCH_2;    // channel = A2 Thumb Wheel

  ADC12MCTL1 = RESET_STATE;
  ADC12MCTL1 |= ADC12WINC_0;  // Comparator window disabled
  ADC12MCTL1 |= ADC12DIF_0;   // Single-ended mode enabled
  ADC12MCTL1 |= ADC12VRSEL_0; // VR+ = AVCC, VR- = AVSS
  ADC12MCTL1 |= ADC12INCH_5;  // channel = A5 Left

  ADC12MCTL2 = RESET_STATE;
  ADC12MCTL2 |= ADC12WINC_0;  // Comparator window disabled
  ADC12MCTL2 |= ADC12DIF_0;   // Single-ended mode enabled
  ADC12MCTL2 |= ADC12VRSEL_0; // VR+ = AVCC, VR- = AVSS
  ADC12MCTL2 |= ADC12INCH_4;  // channel = A4 Right

  ADC12MCTL3 = RESET_STATE;
  ADC12MCTL3 |= ADC12WINC_0;  // Comparator window disabled
  ADC12MCTL3 |= ADC12DIF_0;   // Single-ended mode enabled
  ADC12MCTL3 |= ADC12VRSEL_0; // VR+ = AVCC, VR- = AVSS
  ADC12MCTL3 |= ADC12INCH_30; // Temp sensor

  ADC12MCTL4 = RESET_STATE;
  ADC12MCTL4 |= ADC12WINC_0;  // Comparator window disabled
  ADC12MCTL4 |= ADC12DIF_0;   // Single-ended mode enabled
  ADC12MCTL4 |= ADC12VRSEL_0; // VR+ = AVCC, VR- = AVSS
  ADC12MCTL4 |= ADC12INCH_31; // Battery voltage monitor
  ADC12MCTL4 |= ADC12EOS;     // End of Sequence

// ADC12IER0-2 Register Descriptions
  ADC12IER0 = RESET_STATE;    // Interrupts for channels  0 - 15
  ADC12IER1 = RESET_STATE;    // Interrupts for channels 16 - 31
  ADC12IER2 = RESET_STATE;    // Interrupts for ADC12RDYIE ADC12TOVIE ADC12OVIE
                              // ADC12HIIE ADC12LOIE ADC12INIE
							  
//  ADC12IER0 |= ADC12IE4;      // Generate Interrupt for MEM2 ADC Data load// // needs to be off
  ADC12IER0 |= ADC12IE2;    // Generate Interrupt for MEM2 ADC Data load needs to be on 
//  ADC12IER0 |= ADC12IE0;    // Enable ADC conv complete interrupt

  ADC12CTL0 |= ADC12ENC;     // Start conversion
  ADC12CTL0 |= ADC12SC;      // Start sampling
//------------------------------------------------------------------------------
}

#pragma vector = ADC12_B_VECTOR
__interrupt void ADC12_ISR(void){
 switch(__even_in_range(ADC12IV, ADC12IV__ADC12RDYIFG)){
 case ADC12IV__NONE: break; // Vector 0: No interrupt
 case ADC12IV__ADC12OVIFG: break; // Vector 2: ADC12MEMx Overflow
 case ADC12IV__ADC12TOVIFG: break; // Vector 4: Conversion time overflow
 case ADC12IV__ADC12HIIFG: break; // Vector 6: ADC12BHI
 case ADC12IV__ADC12LOIFG: break; // Vector 8: ADC12BLO
 case ADC12IV__ADC12INIFG: break; // Vector 10: ADC12BIN
 case ADC12IV__ADC12IFG0: break; // Vector 12: ADC12MEM0 Interrupt
 case ADC12IV__ADC12IFG1: break; // Vector 14: ADC12MEM1 Interrupt
 case ADC12IV__ADC12IFG2: // Vector 16: ADC12MEM2 Interrupt
 ADC_Thumb = ADC12MEM0; // A02 ADC10INCH_2
 ADC_Right_Detector = ADC12MEM1; // A05 ADC10INCH_4
 ADC_Left_Detector = ADC12MEM2; // A04 ADC10INCH_5
 break;
 case ADC12IV__ADC12IFG3: break; // Vector 18: ADC12MEM3
 case ADC12IV__ADC12IFG4: break; // Vector 20: ADC12MEM4
 case ADC12IV__ADC12IFG5: break; // Vector 22: ADC12MEM5
 case ADC12IV__ADC12IFG6: break; // Vector 24: ADC12MEM6
 case ADC12IV__ADC12IFG7: break; // Vector 26: ADC12MEM7
 case ADC12IV__ADC12IFG8: break; // Vector 28: ADC12MEM8
case ADC12IV__ADC12IFG9: break; // Vector 30: ADC12MEM9
 case ADC12IV__ADC12IFG10: break; // Vector 32: ADC12MEM10
 case ADC12IV__ADC12IFG11: break; // Vector 34: ADC12MEM11
 case ADC12IV__ADC12IFG12: break; // Vector 36: ADC12MEM12
 case ADC12IV__ADC12IFG13: break; // Vector 38: ADC12MEM13
 case ADC12IV__ADC12IFG14: break; // Vector 40: ADC12MEM14
 case ADC12IV__ADC12IFG15: break; // Vector 42: ADC12MEM15
 case ADC12IV__ADC12IFG16: break; // Vector 44: ADC12MEM16
 case ADC12IV__ADC12IFG17: break; // Vector 46: ADC12MEM17
 case ADC12IV__ADC12IFG18: break; // Vector 48: ADC12MEM18
 case ADC12IV__ADC12IFG19: break; // Vector 50: ADC12MEM19
 case ADC12IV__ADC12IFG20: break; // Vector 52: ADC12MEM20
 case ADC12IV__ADC12IFG21: break; // Vector 54: ADC12MEM21
 case ADC12IV__ADC12IFG22: break; // Vector 56: ADC12MEM22
 case ADC12IV__ADC12IFG23: break; // Vector 58: ADC12MEM23
 case ADC12IV__ADC12IFG24: break; // Vector 60: ADC12MEM24
 case ADC12IV__ADC12IFG25: break; // Vector 62: ADC12MEM25
 case ADC12IV__ADC12IFG26: break; // Vector 64: ADC12MEM26
 case ADC12IV__ADC12IFG27: break; // Vector 66: ADC12MEM27
 case ADC12IV__ADC12IFG28: break; // Vector 68: ADC12MEM28
 case ADC12IV__ADC12IFG29: break; // Vector 70: ADC12MEM29
 case ADC12IV__ADC12IFG30: break; // Vector 72: ADC12MEM30
 case ADC12IV__ADC12IFG31: break; // Vector 74: ADC12MEM31
 case ADC12IV__ADC12RDYIFG: break; // Vector 76: ADC12RDY
 default: break;
 }
}