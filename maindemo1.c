/************** ECE2049 DEMO CODE ******************/
/**************  20 August 2016   ******************/
/***************************************************/

#include <msp430.h>

/* Peripherals.c and .h are where the functions that implement
 * the LEDs and keypad, etc are. It is often useful to organize
 * your code by putting like functions together in files.
 * You include the header associated with that file(s)
 * into the main file of your project. */
#include "peripherals.h"

// Function Prototypes
void swDelay(char numLoops);
void configButtons();
char boardbuttons();
void ledsOff();
void ledsOn(char input);
void configLeds();
// Declare globals here


typedef enum {MENU, CNTDOWN, INGAME, WIN, LOSE} state_t;
state_t state = MENU;
// Main
void main(void)
{
    // Define some local variables
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer
    initLeds();
    configDisplay();
    configKeypad();
    configButtons();
    configLeds();
    char button;
    while(1)
    {
        button = boardbuttons();
        if ((button & BIT0) != 0)
            {
            ledsOn(0x01);
            }
        if ((button & BIT1) != 0)
            {
            ledsOn(0x02);
            }
        if ((button & BIT2) != 0)
            {
            ledsOn(0x03);
            }
        if ((button & BIT3) != 0)
            {
            BuzzerOn();
            }
        swDelay(2);
        ledsOff();
        BuzzerOff();
        button = 0;
    }
}

void BuzzerOnPitch(int pitch)
{
    // Initialize PWM output on P3.5, which corresponds to TB0.5
    P3SEL |= BIT5; // Select peripheral output mode for P3.5
    P3DIR |= BIT5;

    TB0CTL  = (TBSSEL__ACLK|ID__1|MC__UP);  // Configure Timer B0 to use ACLK, divide by 1, up mode
    TB0CTL  &= ~TBIE;                       // Explicitly Disable timer interrupts for safety

    // Now configure the timer period, which controls the PWM period
    // Doing this with a hard coded values is NOT the best method
    // We do it here only as an example. You will fix this in Lab 2.
    TB0CCR0   = pitch;                    // Set the PWM period in ACLK ticks
    TB0CCTL0 &= ~CCIE;                  // Disable timer interrupts

    // Configure CC register 5, which is connected to our PWM pin TB0.5
    TB0CCTL5  = OUTMOD_7;                   // Set/reset mode for PWM
    TB0CCTL5 &= ~CCIE;                      // Disable capture/compare interrupts
    TB0CCR5   = TB0CCR0/2;                  // Configure a 50% duty cycle
}

void swDelay(char numLoops)
{
	// This function is a software delay. It performs
	// useless loops to waste a bit of time
	//
	// Input: numLoops = number of delay loops to execute
	// Output: none
	//
	// smj, ECE2049, 25 Aug 2013

	volatile unsigned int i,j;	// volatile to prevent optimization
			                            // by compiler

	for (j=0; j<numLoops; j++)
    {
    	i = 50000 ;					// SW Delay
   	    while (i > 0)				// could also have used while (i)
	       i--;
    }
}

void configButtons()
{
    P7SEL &= ~(BIT0 | BIT4);
    P3SEL &= ~BIT6;
    P2SEL &= ~BIT2;
    P7DIR &= ~(BIT0 | BIT4);
    P3DIR &= ~BIT6;
    P2DIR &= ~BIT2;
    P7REN |= (BIT0 | BIT4);
    P7OUT |= (BIT0 | BIT4);
    P3REN |= BIT6;
    P3OUT |= BIT6;
    P2REN |= BIT2;
    P2OUT |= BIT2;
}

char boardbuttons()
{
    char pressed = 0;
    if ((P7IN & BIT0)== 0x00)
        pressed |= BIT0;
    if ((P3IN & BIT6)== 0x00)
        pressed |= BIT1;
    if ((P2IN & BIT2)== 0x00)
        pressed |= BIT2;
    if ((P7IN & BIT4)== 0x00)
        pressed |= BIT3;
    return pressed;
}

void configLeds()
{
    P4SEL &= ~BIT7;
    P1SEL &= ~BIT0;
    P4DIR |= BIT7;
    P1DIR |= BIT0;
}

void ledsOn (char input)
{
    if ((input & BIT0) != 0) P1OUT |= BIT0;
    if ((input & BIT1) != 0) P4OUT |= BIT7;
}
void ledsOff()
{
    P4SEL &= ~BIT7;
    P1SEL &= ~BIT0;
    P4DIR &= BIT7;
    P1DIR &= BIT0;
    P4OUT = 0x00;
    P1OUT = 0x00;
}



