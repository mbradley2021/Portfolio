

// Matthew Bradley 
//Holds code for seriel communcation
//----------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include "macros.h"




//Globals
extern volatile unsigned int UCA3_index;
extern int test_command[LIMIT1];
extern volatile char commm[LIMIT1];
volatile unsigned int usb_rx_ring_rd;
volatile unsigned int usb_tx_ring_wr;
volatile unsigned int usb_tx_ring_rd;
volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned char PLACE;
 unsigned int Ccount;
volatile char COMMANDLOOP='F';
 volatile unsigned char command_ARRAY[2][5];

 volatile unsigned int ARRAY_ONE;
 volatile unsigned int ARRAY_TWO;
 
unsigned char IP_ARRAY[13];
unsigned int hit;
volatile unsigned int IOT_rx_ring_wr;
volatile unsigned int IOT_rx_ring_rd;
volatile unsigned int IOT_tx_ring_wr;
volatile unsigned int IOT_tx_ring_rd;
unsigned int LOC;
volatile char IOT_Char_Rx[LIMIT3] ;
volatile char IOT_Char_Tx[LIMIT3];

volatile char USB_Char_Rx[LIMIT1] ;
volatile char USB_Char_Tx[LIMIT1];
volatile char WHAT_EVERY_THE_HELL_I_WANT_TO_CALL_IT = LOW;
volatile char FRAM_ARRAY[16];
extern volatile unsigned char SSID_ARRAY[10];
//locals
unsigned int temp;
unsigned char stuff;
volatile int pcr = LOW;
unsigned char stuff2;
unsigned int RECEIVED;
unsigned int RECEIVEDt;
unsigned int count;
unsigned int counttwo;
//char get_ssid[11] = "AT+NSTAT=?\r";//

//-----------------------------------------------------------------------------
void Init_Serial_UCA3(void){
 int i;
 for(i=LOW; i<SMALL_RING_SIZE; i++){
 USB_Char_Rx[i] = doublelownum; // USB Rx Buffer
 }
 IOT_rx_ring_wr = BEGINNING;
 IOT_rx_ring_rd = BEGINNING;

 for(i=LOW; i<LARGE_RING_SIZE; i++){ // May not use this
 IOT_Char_Tx[i] = doublelownum; // USB Tx Buffer
 }
 IOT_tx_ring_wr = BEGINNING;
 IOT_tx_ring_rd = BEGINNING;
 // Configure UART 0
 UCA3CTLW0 = LOW; // Use word register
 UCA3CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
 UCA3CTLW0 |= UCSWRST; // Set Software reset enable
 UCA3BRW = Lbnum; // 9,600 Baud
// UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
// UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
 UCA3MCTLW = Lbaud ;
 UCA3CTL1 &= ~UCSWRST; // Release from reset
 UCA3IE |= UCRXIE; // Enable RX interrupt

}


#pragma vector=USCI_A3_VECTOR
__interrupt void USCI_A3_ISR(void){
 unsigned int temp;
 
 switch(__even_in_range(UCA3IV,somenum)){
 case case_zero: // Vector 0 - no interrupt
 break;
 case case_two: // Vector 2 - RXIFG
 temp = IOT_rx_ring_wr ;
 stuff = UCA3RXBUF;
 UCA0TXBUF = stuff;
 IOT_Char_Rx[temp] = UCA3RXBUF; // RX -> USB_Char_Rx character
 //---------------------------------------------------------------------------
 switch(PLACE){
 case 'I': // gets IP address at boot
  if (IOT_Char_Rx[temp] == 'y' && RECEIVEDt == 0){
     RECEIVEDt = 1;
     counttwo =0;
   }
  if(RECEIVEDt ==1 && IOT_Char_Rx[temp] != 'y'){
    if(IOT_Char_Rx[temp] != '\n' && IOT_Char_Rx[temp] != '\r'){
      if(IOT_Char_Rx[temp] != ':' && IOT_Char_Rx[temp] != ' '){
     IP_ARRAY[counttwo] = IOT_Char_Rx[temp] ;
     counttwo++;
      }
    }
  }
  if(IOT_Char_Rx[temp] == ':' && RECEIVEDt ==1){
     RECEIVEDt = 0;
     PLACE = 's';
   }
   break;
 case 's': //  send AT+NSTAT=? this gets ssid , always showing on display
   
   if(IOT_Char_Rx[temp] == 0x22 &&  RECEIVEDt == 1){
     RECEIVEDt =2;
   }
   
   if (IOT_Char_Rx[temp] == 0x22 && RECEIVEDt == 0){
     RECEIVEDt = 1;
     counttwo =0;
   }
   
   if (IOT_Char_Rx[temp] != 0x22 && RECEIVEDt == 1){
     SSID_ARRAY[counttwo] = IOT_Char_Rx[temp] ;
     counttwo++;
     
   }
   if(IOT_Char_Rx[temp] == 0x22 && RECEIVEDt ==2){
     RECEIVEDt = 0;
//     PLACE = 'D'; // send this to get displayed
   }
   
  
   if(counttwo ==10){ //counter
     RECEIVEDt = 0;
    // PLACE = 'D';
   }
   break;
 case 'L': // looks for command and put into command array
   if(hit==5 && IOT_Char_Rx[temp] != '^'){
     if(IOT_Char_Rx[temp] != '\r'){
       
     command_ARRAY[LOC][Ccount]= IOT_Char_Rx[temp];
     Ccount++;
     
     if(Ccount ==5 && LOC ==0){
       hit =0;
       LOC = 1;
       ARRAY_ONE = 1;
     }else if(Ccount ==5 && LOC ==1){
       hit =0;
       LOC =0;
       ARRAY_TWO = 1;
     }
     }
   }
   



   //parsing incoming data for passcode
   if(IOT_Char_Rx[temp] == '^' && hit ==0){  // finds ^
       hit =1;
       Ccount=0;
     }
   if(IOT_Char_Rx[temp] == '6' && hit ==1){      // find 6
       hit =2;
   }
   
   if(IOT_Char_Rx[temp] == '6' && hit== 2){ // find 6
       hit =3;
   }
   if(IOT_Char_Rx[temp] == '2' && hit== 3){ // find 2
       hit =4;
   }
   if(IOT_Char_Rx[temp] == '6' && hit==4){ //find 6 and pass code is found 
       hit =5;
   }
   
 }
 //---------------------------------------------------------------------------
 if (++IOT_rx_ring_wr >= (SMALL_RING_SIZE)){
 IOT_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
 }
 break;
 case case_four:  //Vector 4 – TXIFG
        
          switch(UCA3_index++){
          case case_zero: //
          case case_one: //
          case case_two: //
          case case_three: //
          case case_four: //
          case case_five: //
          case case_six: //
          case case_seven: //
          case case_eight: //
            UCA3TXBUF = test_command[UCA3_index];
            break;
          case case_nine: //
            UCA3TXBUF = someothernum;
            break;
          case case_ten: // Vector 0 - no interrupt
            UCA3TXBUF = bastardnum;
            break;
          default:
            UCA3IE &= ~UCTXIE; // Disable TX interrupt
            break;
          } 
 break;
 default: break;
 }
}
//------------------------------------------------------------------------------


//UCA0 
//----------------------------------------------------------------------------
void Init_Serial_UCA0(void){
 int i;
 for(i=0; i<SMALL_RING_SIZE; i++){
 USB_Char_Rx[i] = 0x00; // USB Rx Buffer
 }
 usb_rx_ring_wr = BEGINNING;
 usb_rx_ring_rd = BEGINNING;

 for(i=0; i<LARGE_RING_SIZE; i++){ // May not use this
 USB_Char_Tx[i] = 0x00; // USB Tx Buffer
 }
 usb_tx_ring_wr = BEGINNING;
 usb_tx_ring_rd = BEGINNING;
 // Configure UART 0
 UCA0CTLW0 = 0; // Use word register
 UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
 UCA0CTLW0 |= UCSWRST; // Set Software reset enable
UCA0BRW = Lbnum;
 UCA0MCTLW = Lbaud ;
 UCA0CTL1 &= ~UCSWRST; // Release from reset
 UCA0IE |= UCRXIE; 
RECEIVED =0;
}
//--------------------------------------------------------------------------

//------------------------------------------------------------------------------
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void){
  unsigned int temp;
  switch(__even_in_range(UCA0IV,0x08)){
  case 0: // Vector 0 - no interrupt
    break;
  case 2: // Vector 2 - RXIFG
    temp = usb_rx_ring_wr;
  //---------------------------------------------------  
    if (UCA0RXBUF == '^' && RECEIVED == 0){
      RECEIVED = 1;
      count =0;
    }
    if (RECEIVED == 0){
       stuff2 = UCA0RXBUF;
       UCA3TXBUF = stuff2;
    }
    if (UCA0RXBUF != '\r' && RECEIVED == 1){
      FRAM_ARRAY[count] = UCA0RXBUF ;
      count++;
    }
    if(UCA0RXBUF == '\r' && RECEIVED ==1){
      FRAM_ARRAY[count] = UCA0RXBUF;
      RECEIVED = 0;
    }  
    //-------------------------------------------------------
   USB_Char_Rx[temp] = UCA0RXBUF; // RX -> USB_Char_Rx character
    if (++usb_rx_ring_wr >= (SMALL_RING_SIZE)){
      usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
    }

    

    break;
    
  case 4: // Vector 4 – TXIFG
    switch(UCA3_index++){
    case 0: //
    case 1: //
    case 2: //
    case 3: //
    case 4: //
    case 5: //
    case 6: //
    case 7: //
    case 8: //
      UCA3TXBUF = test_command[UCA3_index];
      break;
    case 9: //
      UCA3TXBUF = 0x0D;
      break;
    case 10: // Vector 0 - no interrupt
      UCA3TXBUF = 0x0A;
      break;
    default:
      UCA3IE &= ~UCTXIE; // Disable TX interrupt
      break;
    } break;
    // Vector 4 – TXIFG
    break;
  default: break;
  }
}
//-----------------------------------------------------------------------------

