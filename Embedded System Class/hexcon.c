//------------------------------------------------------------------------------
//******************************************************************************
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//------------------------------------------------------------------------------
 #include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include "macros.h"





unsigned char adc_char[LINE_FOUR];

void HEXtoBCD(int hex_value){
int value =LOW;
adc_char[LINE_ZERO] = '0';
while (hex_value > nnn){
hex_value = hex_value - th;
value = value + HI;
adc_char[LINE_ZERO] = casecc + value;
}
value = LOW;
adc_char[LINE_ONE] = '0';
while (hex_value > nn){
hex_value = hex_value - hu;
value = value + HI;
adc_char[LINE_ONE] = casecc + value;
}
value = LOW;
adc_char[LINE_TWO] = '0';
while (hex_value > ni){
hex_value = hex_value - te;
value = value + HI;
adc_char[LINE_TWO] = casecc + value;
}
adc_char[LINE_THREE] = casecc + hex_value;
}
//******************************************************************************
//------------------------------------------------------------------