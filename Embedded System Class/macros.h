//---------------------
//Matthew Bradley
//  Sep 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
// hold all the #defines
//---------------------

//port pins
//(0x01) = 00000001= pin 0
//(0x02) = 00000010= pin 1
//(0x04) = 00000100= pin 2
//(0x08) = 00001000= pin 3
//(0x10) = 00010000= pin 4
//(0x20) = 00100000= pin 5
//(0x40) = 01000000= pin 6
//(0x80) = 10000000= pin 7


#include  "msp430.h"
#include  "functions.h"
#include <string.h>

//PWM NUMBERS
#define LEFT_REVERSE_SPEED (TB0CCR3)
#define LEFT_FORWARD_SPEED (TB0CCR4)
#define RIGHT_REVERSE_SPEED (TB0CCR5)
#define RIGHT_FORWARD_SPEED (TB0CCR6)
#define WHEEL_OFF       (0)
#define WHEEL_PERIOD    (40000)

//Project 8 ser_com
#define PRESSED_2  ('H')
#define PRESSED_1  ('P')
#define LIMIT1     (12)
#define LIMIT2      (11)
#define LIMIT3        (16)
#define Lbaud      (0x5551)
#define Hbaud      (0x4A11)  
#define Lbnum      (4)
#define somenum      (0x08)
#define someothernum    (0x0D)
#define bastardnum      (0x0A)
#define doublelownum    (0x00)
#define array_stuff     ('Y')

//hexc
#define casecc          (0x30)
#define nnn             (999)
#define th              (1000)
#define hu              (100)
#define te              (10)
#define nn              (99)
#define ni              (9)

// serial com
#define BEGINNING (0)
#define SMALL_RING_SIZE (16)
#define LARGE_RING_SIZE (16)


//int timers
#define TA0CCR0_INTERVAL        (8000) //8000000/2/8/(1/16msec)[62.5]
#define TA0CCR1_INTERVAL        (50000)
#define TA0CCR2_INTERVAL        (40000)
#define dbounc                 (25)
#define tcount                  (10)
#define disoff                  (0xFF)
#define case_zero                   (0)
#define case_one                   (1)
#define case_two                   (2)
#define case_three                 (3)
#define case_four                   (4)
#define case_five                   (5)
#define case_six                    (6)
#define case_seven                  (7)
#define case_eight                  (8)
#define case_nine                    (9)
#define case_ten                     (10)
#define case_foutt                  (14)

#define twofifcount                  (250)
#define twelvecount             (12)

//#define for arrays
#define LINE_ZERO       (0)
#define LINE_ONE        (1)
#define LINE_TWO        (2)
#define LINE_THREE     (3)
#define LINE_FOUR      (4)     
#define CHARACTER_TEN   (10)
#define CHARACTER_ELEVEN        (11)
#define CHARACTER_ZERO          (0)
#define LOW                     (0)
#define HI                      (1)
// #defines from main.c
#define RED_LED              (0x01) // RED LED -p1_0_LED1
#define GRN_LED              (0x02) // GREEN LED -p1_1_LED2

#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x02) // GREEN LED 1
#define PORTS                (0x00) // PORTS
#define PWM_MODE             (0x01) // PWM_MODE

// #defines for Port 1 pins 
//red_led in defines of main.c
//grn_lef in defines of main.c
#define V_THUMB                 (0x04)  //ADC for Thumb Wheel
#define TEST_PROBE               (0x08)  //GP I/O Pin to use to check code operation
#define V_DETECT_R              (0x10)  //ADC for Right Detector
#define V_DETECT_L              (0x20)  //ADC for Left Detector
#define SD_UCB0SIMO             (0x40) // SPI mode - slave in/master out for SD Card
#define SD_UCB0SOMI             (0x80) // SPI mode - slave out/master in for SD Card

//Defines for Port 2 pins
#define UCA0TXD                  (0x01) //
#define UCA0RXD                  (0x02) //
#define SD_SPICLK                (0x04) //
#define P2_3                     (0x08) //
#define P2_4                     (0x10) //
#define UCA1TXD                  (0x20) //
#define UCA1RXD                  (0x40) //
#define P2_7                     (0x80) //



//Defines for port 3 pins

#define IOT_RESET               (0x01) // RESET
#define IOT_PROG_MODE          (0x02) // IOT_STA_MINIAP
#define IOT_LINK                (0x04) // IOT_LINK
#define IOT_PROG_SEL             (0x08) // IOT_WAKEUP
#define L_REVERSE               (0x10) // Left Reverse
#define L_FORWARD               (0x20) // Left Forward
#define R_REVERSE               (0x40) // Right Reverse
#define R_FORWARD               (0x80) // Right Forward

//Defines for Port 4
#define SD_CS                   (0x01) //
#define J4_31                   (0x02) //
#define J4_32                   (0x04) //
#define J4_33                   (0x08) //
#define UCB1_CS_LCD             (0x10) //
#define P4_5                    (0x20) //
#define P4_6                    (0x40) //
#define J3_29                   (0x80) //


//Defines for port 5 pins

#define SPI_UCB1SIMO             (0x01) // UCB1SIMO
#define SPI_UCB1SOMI             (0x02) // UCB1SOMI
#define SPI_UCB1CLK              (0x04) // SPI mode - clock output—UCB1CLK
#define RESET_LCD                (0x08) // LCD Reset
#define P5_4                     (0x10) // UNUSED
#define BUTTON2                  (0x20) // Button 2
#define BUTTON1                  (0x40) // Button 1
#define LCD_BACKLITE             (0x80) // LCD Backlite

//Defines for port 6 pins
#define UCA3TXD                  (0x01) //
#define UCA3RXD                  (0x02) //
#define J1_5                     (0x04) //
#define MAG_INT                  (0x08) //
#define P6_4                     (0x10) //
#define P6_5                     (0x20) //
#define P6_6                     (0x40) //
#define P6_7                     (0x80) //

//Defines for port 7 pins
#define I2CSDA                   (0x01) //
#define I2CSCL                   (0x02) //
#define SD_DETECT                (0x04) //
#define J4_36                    (0x08) //
#define P7_4                     (0x10) //
#define P7_5                     (0x20) //
#define P7_6                     (0x40) //
#define P7_7                     (0x80) //

//Defines for port 8 pins
#define IR_LED                   (0x01) //
#define OPT_INT                  (0x02) //
#define TMP_INT                  (0x04) //
#define INT2                     (0x08) //


//Defines for port J pins 
#define PJ_0                     (0x01) //
#define PJ_1                     (0x02) //
#define PJ_2                     (0x04) //
#define PJ_3                     (0x08) //
#define LFXIN                    (0x10) //
#define LFXOUT                   (0x20) //
#define HFXIN                    (0x40) //
#define HFXOUT                   (0x80) //