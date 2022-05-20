/*
 * music notes for still alive from portal
 **/


#ifndef STILL_ALIVE_H
#define STILL_ALIVE_H

#include "note.h"

#include <stdint.h>

//1 = 1/4


note_t still_alive[] = {
		{0 , T2},
		{G5, T1_2},
		{F5, T1_2},
		{E5, T1_2},
		{E5, T1_2},

		{F5, T2},
		{0 , T2},

		{0 , T1},
		{0 , T1_2},
		{A5, T1_2},
		{G5, T1_2},
		{F5, T1_2},
		{E5, T1_2},
		{E5, T1_2},

		{E5, T1_2},
		{F5, T1_1_2},
		{D5, T1},
		{D5, T1},
		{E5, T1_2},
		{A5, T1_2},

		{A5, T2},
		{0 , T1_1_2},
		{A5, T1_2},

		{E5, T1},
		{F5, T1_2},
		{G5, T1_2},
		{G5, T1_2},
		{E5, T1_2},
		{C5, T1_2},

		{C5, T1_2},
		{D5, T1_1_2},
		{E5, T1},
		{F4, T1_2},
		{F4, T1_2},

		{F4, T1_2},
		{F5, T1_1_2},
		{0 , T2},

		{0 , T2},
		{G5, T1_2},
		{F5, T1_2},
		{E5, T1_2},
		{E5, T1_2},

		{F5, T2},
		{0 , T2},

		{0 , T1},
		{0 , T1_2},
		{A5, T1_2},
		{G5, T1_2},
		{F5, T1_2},
		{E5, T1_2},
		{E5, T1_2},

};


uint32_t still_alive_len = sizeof(still_alive)/sizeof(note_t);


#endif

