/*
 * playsong.c
 *
 *  Created on: Sep 21, 2017
 *      Author: Minh
 */

#include <msp430.h>
#include "peripherals.h"
#include "notes.h"
#include "songs.h"
void playsong(Notes anote);
void swDelay(char numLoops);
void BuzzerOnfrequency(int frequency);
char boardbuttons();

unsigned long int timer = 0;
unsigned long int eighthnotes = 1;
unsigned int dur = 0;
unsigned int errors;
unsigned int score;
char button;
#pragma vector = TIMER2_A0_VECTOR // syntax for ISR
__interrupt void Timer_A2_ISR(void)
{
    timer++;
    if (timer % 50 == 0)
    {
        eighthnotes++;
    }
}

void main(void)
{
    // Define some local variables
    _BIS_SR(GIE);
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer
    initLeds();
    configDisplay();
    configKeypad();
    configButtons();
    initLeds();
    int cnt = 0;
    runtimerA2();
    while (cnt < 4)
    {
        playsong(sadtrombone[cnt]);
        dur = sadtrombone[cnt].duration;
        button = boardbuttons();
        if (button == sadtrombone[cnt].button)
        {
            score++;
            button = 0;
        }
        if (eighthnotes % dur == 0)
        {
            cnt++;
            eighthnotes = 1;
            score = 0;
            BuzzerOff();
            swDelay(3);
        }
        if (errors >= 20)
        {
            break;
        }
    }
    BuzzerOff();
}

void playsong(Notes anote)
{
    BuzzerOnfrequency(anote.pitch);
    setLeds(anote.LED);
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

void BuzzerOnfrequency(int frequency)                                                                                      //Buzz the buzzer with different frequency depends on the int frequency
{
    // Initialize PWM output on P3.5, which corresponds to TB0.5
    P3SEL |= BIT5; // Select peripheral output mode for P3.5
    P3DIR |= BIT5;

    TB0CTL  = (TBSSEL__ACLK|ID_1|MC__UP);  // Configure Timer B0 to use ACLK, divide by 1, up mode
    TB0CTL  &= ~TBIE;                       // Explicitly Disable timer interrupts for safety

    // Now configure the timer period, which controls the PWM period
    // Doing this with a hard coded values is NOT the best method
    // We do it here only as an example. You will fix this in Lab 2.
    TB0CCR0   = 32768/frequency;                   // Set the PWM period in ACLK ticks                                      //This line changes the frequency
    TB0CCTL0 &= ~CCIE;                  // Disable timer interrupts

    // Configure CC register 5, which is connected to our PWM pin TB0.5
    TB0CCTL5  = OUTMOD_7;                   // Set/reset mode for PWM
    TB0CCTL5 &= ~CCIE;                      // Disable capture/compare interrupts
    TB0CCR5   = TB0CCR0/2;                  // Configure a 50% duty cycle
}

void resetGlobals()
{
    timer = 0;
    eighthnotes = 1;
    dur = 0;
//    cntdwnmode = 4;
}

void runtimerA2(void)
{
    TA2CTL = (TASSEL_1 | MC_1 | ID_0);
    TA2CCR0 = 81;                                           //~0.0025sec resolution
    TA2CCTL0 = CCIE;
}

void stopA2(void)
{
    TA2CTL = MC_0;
    TA2CCTL0 &= ~CCIE;
}

char boardbuttons()
{
    char pressed = 0;
    if ((P7IN & BIT0)== 0x00)
        pressed = 1;
    if ((P3IN & BIT6)== 0x00)
        pressed = 2;
    if ((P2IN & BIT2)== 0x00)
        pressed = 3;
    if ((P7IN & BIT4)== 0x00)
        pressed = 4;
    return pressed;
}
