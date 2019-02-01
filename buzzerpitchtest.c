/*
 * buzzerpitchtest.c
 *
 *  Created on: Sep 13, 2017
 *      Author: mhle
 */

#include <msp430.h>

/* Peripherals.c and .h are where the functions that implement
 * the LEDs and keypad, etc are. It is often useful to organize
 * your code by putting like functions together in files.
 * You include the header associated with that file(s)
 * into the main file of your project. */
#include "peripherals.h"

void BuzzerOnPitch(int freq);
void swDelay(char numLoops);

void main(void)
{
    BuzzerOnPitch(523);
    swDelay(1);
    BuzzerOnPitch(523);
    swDelay(1);
    BuzzerOnPitch(784);
    swDelay(1);
    BuzzerOnPitch(784);
    swDelay(1);
    BuzzerOnPitch(880);
    swDelay(1);
    BuzzerOnPitch(880);
    swDelay(1);
    BuzzerOnPitch(784);
    swDelay(1);
    BuzzerOnPitch(698);
    swDelay(1);
    BuzzerOnPitch(698);
    swDelay(1);
    BuzzerOnPitch(659);
    swDelay(1);
    BuzzerOnPitch(659);
    swDelay(1);
    BuzzerOnPitch(587);
    swDelay(1);
    BuzzerOnPitch(587);
    swDelay(1);
    BuzzerOnPitch(523);
    swDelay(1);
}

void BuzzerOnPitch(int freq)                                                                                      //Buzz the buzzer with different pitch depends on the int pitch
{
    // Initialize PWM output on P3.5, which corresponds to TB0.5
    P3SEL |= BIT5; // Select peripheral output mode for P3.5
    P3DIR |= BIT5;

    TB0CTL  = (TBSSEL__ACLK|ID__1|MC__UP);  // Configure Timer B0 to use ACLK, divide by 1, up mode
    TB0CTL  &= ~TBIE;                       // Explicitly Disable timer interrupts for safety

    // Now configure the timer period, which controls the PWM period
    // Doing this with a hard coded values is NOT the best method
    // We do it here only as an example. You will fix this in Lab 2.
    TB0CCR0   = 32768/freq;                    // Set the PWM period in ACLK ticks                                      //This line changes the pitch
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

    volatile unsigned int i,j;  // volatile to prevent optimization
                                        // by compiler

    for (j=0; j<numLoops; j++)
    {
        i = 2500 ;                 // SW Delay
        while (i > 0)               // could also have used while (i)
           i--;
    }
}
