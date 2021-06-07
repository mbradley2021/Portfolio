#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include "macros.h"

//globals
extern char display_line[LINE_FOUR][CHARACTER_ELEVEN];
extern volatile int unsigned T_COUNT;
//INFO_GET
volatile unsigned char SSID_ARRAY[10];
extern volatile unsigned char PLACE;//;
extern unsigned char IP_ARRAY[13];
char test_A[17] = "AT+NSTCP=6626,1\r"; //set passcode
char test_B[11] = "AT+NSTAT=?\r";

void INFO_GET(void){ 		// get info and display it 
  for(int i = 0 ; i<11; i++){
    out_character(test_B[i]);
  }
delaycount();
  int sc =0; // 
  for(int i = 0;i<10;i++){
    if(SSID_ARRAY[i]== '\0'){
      sc++;
    }
  }
  sc = sc/2;
  for(int i =0;i<sc;i++){
    display_line[LINE_ZERO][i] = ' ';
  }
int limitNum = 10 - sc;
for(int i =0;i<limitNum;i++){
  display_line[LINE_ZERO][sc+i]= SSID_ARRAY[i];
  
}
//strcpy(display_line[LINE_ZERO], " UNCA_PSK ");
strcpy(display_line[LINE_ONE], "IP address");
int mov = 0;
for(int i = 0; i<10;i++){//first group ip
  if(i<1){
    display_line[LINE_TWO][i]= ' ';
  }
  if(i>=1 && i<8){
    display_line[LINE_TWO][i]= IP_ARRAY[mov];
    mov++;
  }
  if(i>=8){
    display_line[LINE_TWO][i]= ' ';
}
}
for(int i =0;i<10;i++){ // 2nd groups ip
  if(i<2){
    display_line[LINE_THREE][i] = ' ';
  }
  if(i>=2 && i<8){
    display_line[LINE_THREE][i]=IP_ARRAY[mov];
    mov++;
  }
  if(i>=8){
  display_line[LINE_THREE][i]= ' ';
  
  }
  
}
  
LCD_UPReset();
PLACE = 'L';
  
 
delaycount();		//delay counter
for(int i = 0; i<17;i++){
  out_character(test_A[i]);
  
}


}


void delaycount(void){ //delay counter
  int thedelay = 0;
  while (thedelay < 10){
    if(T_COUNT % 50 == 0){
      thedelay++;
}
  }
}