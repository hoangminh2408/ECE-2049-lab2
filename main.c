
#include <msp430.h>
#include "peripherals.h"
#include "notes.h"                                                                                   //Include header file that has definition for the notes
#include "songs.h"                                                                                   //Include header file that has definition for the Notes struct and the songs array

// ****************--- Function Prototypes ---****************\\

void swDelay(char numLoops);
void countdown(int mode);
void BuzzerOnfrequency(int frequency);
void flashingleds();
void flashallleds();
void configLeds();
char boardbuttons();
void playsong(Notes anote);
void ledsOff();
void resetGlobals();
void runtimerA2();
void stopA2();
void flushbuffer();
void cleardisp();

// ****************--- Declare globals ---**************** \\

unsigned int dur = 0;                                                                                   //note duration
unsigned int cnt = 0;                                                                                   //note position
char button;                                                                                            //check button pressed
unsigned int errors = 0;                                                                                //check errors made
unsigned int score = 0;                                                                                 //if score == 1, user pressed the right button, else user has not pressed or pressed wrong button
unsigned int cntdwnmode = 4;                                                                            //cntdwnmode == 4 -> 3, ... , cntdwnmode == 0 -> GO
unsigned long int timer = 0;                                                                            //timer for interrupt
unsigned long int eighthnotes = 1;                                                                      //count every eighth note, which is 1/8 sec
int m = 1;                                                                                              //for polling loop
unsigned char currentKey = 0;                                                                                   //for checking numpad

// syntax for ISR

#pragma vector = TIMER2_A0_VECTOR
__interrupt void Timer_A2_ISR(void)
{
    timer++;                                                                                            //increase timer by 1 each interrupt
    if (timer % 50 == 0)                                                                                //0.0025*50 = 1/8 sec
    {
        eighthnotes++;                                                                                  //eigthnotes counter increase by one for each 1/8 sec
        if (eighthnotes % 8 == 0)                                                                       //8 eigthnotes = 1 sec
            cntdwnmode--;                                                                               //count down every sec
    }
}

typedef enum {MENU, CHOOSESONG, CNTDOWN1, CNTDOWN2, INGAMES1, INGAMES2, WIN, LOSE} state_t;             //declare all cases of state machine
state_t state = MENU;                                                                                   //first state is menu

// ****************--Main--**************** \\

void main(void)
{
     _BIS_SR(GIE);                                                                                 // Global Interrupt enable
    WDTCTL = WDTPW | WDTHOLD;                                                                      // Stop watchdog timer

//****************--- Peripherals Configuration ---**************** \\

    initLeds();                                                                                    // 4 board LEDS
    configDisplay();                                                                               // LCD
    configKeypad();                                                                                // Numpad
    configButtons();                                                                               // 4 board buttons
    configLeds();                                                                                  // 2 Launchpad's LEDS

//****************-- State Machine --****************\\

    while (1)                                                                                      // Forever loop
    {
        switch(state)
        {
        case MENU:                                                                                 //Main menu state
            ledsOff();                                                                                              //Make sure everything is reset
            resetGlobals();
            cleardisp();
            Graphics_drawStringCentered(&g_sContext, "MSP430", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);       //Draw the menu
            Graphics_drawStringCentered(&g_sContext, "HERO", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Press *", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);
            Graphics_Rectangle box = {.xMin = 5, .xMax = 91, .yMin = 5, .yMax = 91 };
            Graphics_drawRectangle(&g_sContext, &box);
            flushbuffer();
            for (m = 0; m < 10000; m++)                                                                             //Polling loop
            {
                m=0;
                currentKey = getKey();
                if(currentKey == '*')                                                                                  //If user press * starts to choose song1
                {
                    state = CHOOSESONG;
                    break;
                }
            }

            break;

        case CHOOSESONG:                                                                                            //Chose the song user wants to play
            cleardisp();
            Graphics_drawStringCentered(&g_sContext, "Choose your song", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "S1: Twinkle", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "S2: Tetris", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "S3: Main Menu", AUTO_STRING_LENGTH, 48, 65, TRANSPARENT_TEXT);
            flushbuffer();
            for (m = 0; m < 10000; m++)                                                                             //Polling loop, checking if a button is pressed
            {
                m=0;
                currentKey = boardbuttons();
                if (currentKey != 0)                                                                                   //If a button is pressed break the polling loop
                    break;
            }
            if(currentKey == 1)                                                                                  //If user press S1 choose song 1
            {
                state = CNTDOWN1;
                resetGlobals();
                break;
            }
            else if(currentKey == 2)                                                                             //If user press S1 choose song 2
            {
                state = CNTDOWN2;
                resetGlobals();
                break;
            }
            else if(currentKey == 3)                                                                             //If user press S3 return to main menu
            {
                state = MENU;
                resetGlobals();
                break;
            }

        case CNTDOWN1:                                                                                        //Countdown state for song 1
            cleardisp();
            runtimerA2();                                                                                     //Starts timer
            while (cntdwnmode > 0)
            {
                countdown(cntdwnmode);
            }
            stopA2();
            ledsOff();
            resetGlobals();
            state = INGAMES1;                                                                                         //After countdown jump into game
            break;

        case CNTDOWN2:                                                                                               //Countdown state
            cleardisp();
            runtimerA2();
            while (cntdwnmode > 0)
            {
                countdown(cntdwnmode);
            }
            stopA2();
            ledsOff();
            resetGlobals();
            state = INGAMES2;                                                                                         //After countdown jump into game
            break;

        case INGAMES1:                                                                                                //Ingame state for song 1
            cleardisp();
            Graphics_drawStringCentered(&g_sContext, "Twinkle", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Twinkle", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Little", AUTO_STRING_LENGTH, 48, 55, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Stars", AUTO_STRING_LENGTH, 48, 65, TRANSPARENT_TEXT);
            flushbuffer();
            runtimerA2();                                                                                             //Starts timer
            while (cnt < 43)                                                                                          //song has 42 notes in total
            {
                playsong(twinkletwinklelittlestars[cnt]);                                                             //Play each note + light led accordingly
                dur = twinkletwinklelittlestars[cnt].duration;
                button = boardbuttons();                                                                              //Check board buttons
                currentKey = getKey();
                if (currentKey == '#')                                                                                   //Stop playing if user presses #
                    break;
                if (button == twinkletwinklelittlestars[cnt].button)                                                  //If pressed the right board button
                {
                    score++;                                                                                          //"Score" only for checking that a button is pressed                                                                                  //Turn on green launchpad LED indicating right button was pressed
                    button = 0;                                                                                       //Reset button to 0 to avoid sticking
                }
                else if (button > 0)                                                                                  //If wrong button is pressed
                {
                    errors++;                                                                                         //Increase error count
                    score++;                                                                                          //Don't think we need this but it's working so whatever                                                                                    //Red launchpad LED indicating wrong button was pressed
                    button = 0;                                                                                       //Reset button to 0 to avoid sticking
                    BuzzerOnfrequency(NOTE_BAD);                                                                      //Play a bad note indicating wrong button is pressed
                    swDelay(4);                                                                                       //Delay so we can hear the bad note
                }
                if (eighthnotes % dur == 0)                                                                           //Duration is a multiply of an eighthnote, if note duration is played
                {
                    cnt++;                                                                                            //Play next note
                    eighthnotes = 1;                                                                                  //Eighthnote = 1 because if eighthnote = 0 % dur always = 0;
                    if (score == 0)                                                                                   //if nothing is pressed
                    {
                        BuzzerOnfrequency(NOTE_BAD);                                                                  //play a bad note
                        swDelay(2);                                                                                //Red launchpad LED indicating no button was pressed
                        errors++;                                                                                     //Increase error count
                    }
                    score = 0;                                                                                        //reset score
                    BuzzerOff();
                    swDelay(6);                                                                                       //so two notes don't stick together
                }
                if (errors >= 21)                                                                                     //stop playing if 20 errors are made, 1 error is for placeholder note
                {
                    break;
                }
            }                                                                                                         //Playnote loop ends here
            if (currentKey == '#')                                                                                       //If user pressed # return to menu
            {
                state = MENU;
                BuzzerOff();
                break;
            }
            if (errors >= 21)                                                                                         //If 20 errors are made then to lose state
            {
                state = LOSE;
                BuzzerOff();
                break;
            }
            else                                                                                                      //If the whole song played then to win state
            {
                state = WIN;
                BuzzerOff();
                break;
            }

        case INGAMES2:                                                                                                //Ingame state for game 2, almost copy paste of ingames1
            cleardisp();
            Graphics_drawStringCentered(&g_sContext, "Tetris", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Theme", AUTO_STRING_LENGTH, 48, 55, TRANSPARENT_TEXT);
            flushbuffer();
            runtimerA2();
            while (cnt < 38)
            {
                playsong(tetristheme[cnt]);
                currentKey = getKey();
                dur = tetristheme[cnt].duration;
                button = boardbuttons();
                if (currentKey == '#')
                    break;
                if (button == tetristheme[cnt].button)
                {
                    score++;
                    button = 0;
                }
                else if (button > 0)
                {
                    errors++;
                    button = 0;
                    BuzzerOnfrequency(NOTE_BAD);
                    swDelay(4);
                }
                if (eighthnotes % dur == 0)
                {
                    cnt++;
                    eighthnotes = 1;
                    if (score == 0)
                    {
                        BuzzerOnfrequency(NOTE_BAD);
                        swDelay(2);
                        errors++;
                    }
                    score = 0;
                    BuzzerOff();
                    swDelay(6);
                }

                if (errors >= 21)
                {
                    break;
                }
            }
            if (currentKey == '#')
            {
                state = MENU;
                BuzzerOff();
                break;
            }
            if (errors >= 20)
            {
                state = LOSE;
                BuzzerOff();
                break;
            }
            else
            {
                state = WIN;
                BuzzerOff();
                break;
            }


        case WIN:                                                                                                         //Win state
            cleardisp();
            BuzzerOff();
            Graphics_drawStringCentered(&g_sContext, "YOU WIN", AUTO_STRING_LENGTH, 51, 50, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "CONGRATULATIONS!", AUTO_STRING_LENGTH, 49, 40, TRANSPARENT_TEXT);   //Congratulations messages
            flushbuffer();
            resetGlobals();
            runtimerA2();
            while (cnt < 9)                                                                                               //Play winning song
            {
                playsong(winner[cnt]);
                dur = winner[cnt].duration;
                button = boardbuttons();
                if (button == tetristheme[cnt].button)
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
                    swDelay(2);
                }
            }
            stopA2();
            flashingleds();                                                                                             //Flash some swag LEDS
            flashingleds();
            resetGlobals();
            swDelay(20);
            state = MENU;                                                                                               //Return to main menu
            break;

        case LOSE:                                                                                                      //Lose state
            resetGlobals();
            BuzzerOff();
            ledsOff();
            cleardisp();
            Graphics_drawStringCentered(&g_sContext, "GAME OVER", AUTO_STRING_LENGTH, 51, 50, TRANSPARENT_TEXT);        //Lose message
            flushbuffer();
            runtimerA2();
            while (cnt < 4)                                                                                             //Play loser's song
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
            }
            stopA2();
            flashallleds();                                                                                             //Flash loser's leds
            swDelay(20);
            resetGlobals();
            state = MENU;                                                                                               //Return to main menu
            break;
        }  // end while (1)
    }
}

//****************-- Functions --****************\\

void countdown(int mode)                                                                            //Countdown timer
{
    if (mode == 4)
    {
        Graphics_drawStringCentered(&g_sContext, "3...", AUTO_STRING_LENGTH, 51, 36, OPAQUE_TEXT);
        flushbuffer();
        setLeds(BIT0);
    }
    if (mode == 3)
    {
        Graphics_drawStringCentered(&g_sContext, "2...", AUTO_STRING_LENGTH, 51, 36, OPAQUE_TEXT);
        flushbuffer();
        setLeds(BIT1);
    }
    if (mode == 2)
    {
        Graphics_drawStringCentered(&g_sContext, "1...", AUTO_STRING_LENGTH, 51, 36, OPAQUE_TEXT);
        flushbuffer();
        setLeds(BIT2);
    }
    if (mode == 1)
    {
        Graphics_drawStringCentered(&g_sContext, "GO!!", AUTO_STRING_LENGTH, 51, 36, OPAQUE_TEXT);
        flushbuffer();
        setLeds(BIT3);
    }
}

void BuzzerOnfrequency(int frequency)                                                                //Buzz the buzzer with different frequency depends on the int frequency
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
    TB0CCTL0 &= ~CCIE;                  // Disable timer interrupts                                                         //Using ACLK, so pitch = 32768/freq

    // Configure CC register 5, which is connected to our PWM pin TB0.5
    TB0CCTL5  = OUTMOD_7;                   // Set/reset mode for PWM
    TB0CCTL5 &= ~CCIE;                      // Disable capture/compare interrupts
    TB0CCR5   = TB0CCR0/2;                  // Configure a 50% duty cycle
}

void swDelay(char numLoops)
{
	volatile unsigned int i,j;	// volatile to prevent optimization
	for (j=0; j<numLoops; j++)
    {
    	i = 2500 ;					// SW Delay
   	    while (i > 0)				// could also have used while (i)
	       i--;
    }
}

void flashingleds()                                                                                  //Flash LEDs for winner
{
    setLeds(BIT0);
    swDelay(8);
    setLeds(BIT1);
    swDelay(8);
    setLeds(BIT2);
    swDelay(8);
    setLeds(BIT3);
    swDelay(8);
    setLeds(0);
}
void flashallleds()                                                                                  //Flash LEDs for loser
{
    setLeds(BIT0|BIT1|BIT2|BIT3);
    swDelay(8);
    setLeds(0);
    swDelay(8);
    setLeds(BIT0|BIT1|BIT2|BIT3);
    swDelay(8);
    setLeds(0);
    swDelay(8);
    setLeds(BIT0|BIT1|BIT2|BIT3);
    swDelay(8);
    setLeds(0);
    swDelay(8);
    setLeds(BIT0|BIT1|BIT2|BIT3);
    swDelay(8);
    setLeds(0);
    swDelay(8);
}


char boardbuttons()                                                                                   //Get board buttons, return a char according to the board button pressed
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

void playsong(Notes anote)                                                                            //Play a note and light led accordingly
{
    BuzzerOnfrequency(anote.pitch);
    setLeds(anote.LED);
}

void resetGlobals()                                                                                   //Reset global variables
{
    timer = 0;
    eighthnotes = 1;
    cntdwnmode = 4;
    errors = 0;
    score = 0;
    cnt = 0;
    button = 0;
    currentKey = '.';
}
void runtimerA2(void)                                                                                 //Run Timer A2
{
    TA2CTL = (TASSEL_1 | MC_1 | ID_0);
    TA2CCR0 = 81;                                           // 81 / 32768 = ~0.0025sec resolution
    TA2CCTL0 = CCIE;
}

void stopA2(void)                                                                                     //Stop Timer A2
{
    TA2CTL = MC_0;
    TA2CCTL0 &= ~CCIE;
}
void cleardisp()                                                                                      //Clear display, simplify syntax
{
    Graphics_clearDisplay(&g_sContext);
}

void flushbuffer()                                                                                    //Flush display, simplify syntax
{
    Graphics_flushBuffer(&g_sContext);
}
void configLeds()                                                                                     //Config 2 launchpad LEDS
{
    P4SEL &= ~BIT7;
    P1SEL &= ~BIT0;
    P4DIR |= BIT7;
    P1DIR |= BIT0;
}


void ledsOff()                                                                                        //Turn off the 4 labboard LEDs
{
    setLeds(0);
}


