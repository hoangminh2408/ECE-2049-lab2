/*
 * songs.h
 *
 *  Created on: Sep 21, 2017
 *      Author: Minh
 */

#ifndef SONGS_H_
#define SONGS_H_

typedef struct {
     int pitch;
     int duration;
     char LED;
     char button;
} Notes ;

Notes twinkletwinklelittlestars[] =
{
 {NOTE_C, 4, LED_1, 1},
 {NOTE_C, 4, LED_1, 1},
 {NOTE_G, 4, LED_3, 3},
 {NOTE_G, 4, LED_3, 3},
 {NOTE_A2, 4, LED_4, 4},
 {NOTE_A2, 4, LED_4, 4},
 {NOTE_G, 7, LED_3, 3},
 {NOTE_F, 4, LED_2, 2},
 {NOTE_F, 4, LED_2, 2},
 {NOTE_E, 4, LED_1, 1},
 {NOTE_E, 4, LED_1, 1},
 {NOTE_D, 4, LED_4, 4},
 {NOTE_D, 4, LED_4, 4},
 {NOTE_C, 7, LED_1, 1},
 {NOTE_G, 4,LED_3, 3},
 {NOTE_G, 4, LED_3, 3},
 {NOTE_F, 4, LED_2, 2},
 {NOTE_F, 4, LED_2, 2},
 {NOTE_E, 4, LED_1, 1},
 {NOTE_E, 4, LED_1, 1},
 {NOTE_D, 7, LED_4, 4},
 {NOTE_G, 4, LED_3, 3},
 {NOTE_G, 4, LED_3, 3},
 {NOTE_F, 4, LED_2, 2},
 {NOTE_F, 4, LED_2, 2},
 {NOTE_E, 4, LED_1, 1},
 {NOTE_E, 4, LED_1, 1},
 {NOTE_D, 7, LED_4, 4},
 {NOTE_C, 4, LED_1, 1},
 {NOTE_C, 4, LED_1, 1},
 {NOTE_G, 4, LED_3, 3},
 {NOTE_G, 4, LED_3, 3},
 {NOTE_A2, 4, LED_4, 4},
 {NOTE_A2, 4, LED_4, 4},
 {NOTE_G, 8, LED_3, 3},
 {NOTE_F, 4, LED_2, 2},
 {NOTE_F, 4, LED_2, 2},
 {NOTE_E, 4, LED_1, 1},
 {NOTE_E, 4, LED_1, 1},
 {NOTE_D, 4, LED_4, 4},
 {NOTE_D, 4, LED_4, 4},
 {NOTE_C, 12, LED_1, 1},
};

Notes tetristheme[] =
{
 {NOTE_E, 6, LED_1, 1},
 {NOTE_B, 4, LED_2, 2},
 {NOTE_C, 4, LED_3, 3},
 {NOTE_D, 6, LED_4, 4},
 {NOTE_C, 4, LED_3, 3},
 {NOTE_B, 4, LED_2, 2},
 {NOTE_A1, 6, LED_1, 1},
 {NOTE_A1, 4, LED_1, 1},
 {NOTE_C, 4, LED_3, 3},
 {NOTE_E, 6, LED_1, 1},
 {NOTE_D, 4, LED_4, 4},
 {NOTE_C, 4, LED_3, 3},
 {NOTE_B, 6, LED_2, 2},
 {NOTE_B, 4, LED_2, 2},
 {NOTE_C, 4, LED_3, 3},
 {NOTE_D, 6, LED_4, 4},
 {NOTE_E, 6, LED_1, 1},
 {NOTE_C, 6, LED_3, 3},
 {NOTE_A1, 6, LED_1, 1},
 {NOTE_A1, 12, LED_1, 1},
 {NOTE_D, 8, LED_4, 4},
 {NOTE_F, 4, LED_2, 2},
 {NOTE_A2, 6, LED_3, 3},
 {NOTE_G, 4, LED_1, 1},
 {NOTE_F, 4, LED_2, 2},
 {NOTE_E, 8, LED_1, 1},
 {NOTE_C, 4, LED_3, 3},
 {NOTE_E, 6, LED_1, 1},
 {NOTE_D, 4, LED_4, 4},
 {NOTE_C, 4, LED_3, 3},
 {NOTE_B, 6, LED_2, 2},
 {NOTE_B, 4, LED_2, 2},
 {NOTE_C, 4, LED_3, 3},
 {NOTE_D, 6, LED_4, 4},
 {NOTE_E, 6, LED_1, 1},
 {NOTE_C, 6, LED_3, 3},
 {NOTE_A1, 6, LED_1, 1},
 {NOTE_A1, 10, LED_1, 1},
};

Notes sadtrombone[] =
{
 {NOTE_D, 8, LED_1, 1},
 {NOTE_Db, 8, LED_2, 1},
 {NOTE_C, 8, LED_4, 1},
 {NOTE_B, 12, LED_2, 1},
};

Notes winner[] =
{
 {NOTE_A2, 3, LED_1, 1},
 {NOTE_A2, 3, LED_2, 1},
 {NOTE_A2, 3, LED_4, 1},
 {NOTE_A2, 6, LED_2, 1},
 {NOTE_F, 6, LED_1, 1},
 {NOTE_G, 6, LED_2, 1},
 {NOTE_A2, 3, LED_4, 1},
 {NOTE_G, 3, LED_2, 1},
 {NOTE_A2, 10, LED_2, 1},
};
Notes kneesocks[] =
{
 {NOTE_C, 3, LED_1, 1},
 {NOTE_Eb, 3, LED_2, 1},
 {NOTE_F, 3, LED_4, 1},
 {NOTE_G, 3, LED_2, 1},
 {NOTE_C, 3, LED_3, 1},
 {NOTE_Eb, 3, LED_4, 1},
 {NOTE_F, 3, LED_1, 1},
 {NOTE_G, 3, LED_2, 1},
 {NOTE_C, 3, LED_1, 1},
 {NOTE_Eb, 3, LED_4, 1},
 {NOTE_Bb, 3, LED_3, 1},
 {NOTE_G, 3, LED_2, 1},
 {NOTE_C, 3, LED_3, 1},
 {NOTE_Eb, 3, LED_4, 1},
 {NOTE_F, 3, LED_2, 1},
 {NOTE_Eb, 3, LED_4, 1},
 {NOTE_C, 3, LED_1, 1},
 {NOTE_Eb, 3, LED_4, 1},
 {NOTE_A1b, 3, LED_3, 1},
 {NOTE_C, 3, LED_2, 1},
 {NOTE_Eb, 3, LED_1, 1},
 {NOTE_F, 3, LED_2, 1},
 {NOTE_G, 3, LED_3, 1},
 {NOTE_F, 3, LED_2, 1},
 {NOTE_Eb, 3, LED_4, 1},
 {NOTE_C, 3, LED_1, 1},
 {NOTE_G1, 3, LED_4, 1},
 {NOTE_Bb, 3, LED_2, 1},
 {NOTE_C, 3, LED_3, 1},
 {NOTE_D, 3, LED_4, 1},
 {NOTE_Eb, 3, LED_2, 1},
 {NOTE_D, 3, LED_1, 1},
 {NOTE_C, 3, LED_4, 1},
 {NOTE_D, 4, LED_1, 1},
};

Notes kiaconbuomvang[]=
{
 {NOTE_C, 4, LED_1, 1},
 {NOTE_D, 4, LED_2, 1},
 {NOTE_E, 4, LED_4, 1},
 {NOTE_C, 4, LED_2, 1},
 {NOTE_C, 4, LED_3, 1},
 {NOTE_D, 4, LED_4, 1},
 {NOTE_E, 4, LED_1, 1},
 {NOTE_C, 8, LED_2, 1},
 {NOTE_E, 4, LED_1, 1},
 {NOTE_F, 4, LED_4, 1},
 {NOTE_G, 8, LED_3, 1},
 {NOTE_E, 4, LED_2, 1},
 {NOTE_F, 4, LED_3, 1},
 {NOTE_G, 8, LED_4, 1},
 {NOTE_G, 3, LED_2, 1},
 {NOTE_A2, 3, LED_4, 1},
 {NOTE_G, 3, LED_1, 1},
 {NOTE_F, 3, LED_4, 1},
 {NOTE_E, 3, LED_3, 1},
 {NOTE_C, 6, LED_2, 1},
 {NOTE_G, 3, LED_1, 1},
 {NOTE_A2, 3, LED_2, 1},
 {NOTE_G, 3, LED_3, 1},
 {NOTE_F, 3, LED_2, 1},
 {NOTE_E, 3, LED_4, 1},
 {NOTE_C, 8, LED_1, 1},
 {NOTE_C, 4, LED_1, 1},
 {NOTE_G1, 4, LED_4, 1},
 {NOTE_C, 8, LED_2, 1},
 {NOTE_C, 4, LED_3, 1},
 {NOTE_G1, 4, LED_4, 1},
 {NOTE_C, 8, LED_2, 1},
};



#endif /* SONGS_H_ */
