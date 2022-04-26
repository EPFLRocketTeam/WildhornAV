#ifndef NOTE_H
#define NOTE_H


typedef struct note {
	uint16_t freq; //0.1Hz
	uint16_t time; //beat
}note_t;

#define T1_4	1
#define T1_2	2
#define T1		4
#define T1_1_2	6
#define T2		8
#define T4      16

//notes in 0.1HZ --> 4400 = 440.0 Hz

#define C0 163
#define C0H 173
#define D0 183
#define D0H 194
#define E0 206
#define F0 218
#define F0H 231
#define G0 245
#define G0H 259
#define A0 275
#define A0H 291
#define B0 308
#define C1 327
#define C1H 346
#define D1 367
#define D1H 388
#define E1 412
#define F1 436
#define F1H 462
#define G1 490
#define G1H 519
#define A1 550
#define A1H 582
#define B1 617
#define C2 654
#define C2H 693
#define D2 734
#define D2H 777
#define E2 824
#define F2 873
#define F2H 925
#define G2 980
#define G2H 1038
#define A2 1100
#define A2H 1165
#define B2 1234
#define C3 1308
#define C3H 1385
#define D3 1468
#define D3H 1555
#define E3 1648
#define F3 1746
#define F3H 1850
#define G3 1960
#define G3H 2076
#define A3 2200
#define A3H 2330
#define B3 2469
#define C4 2616
#define C4H 2771
#define D4 2936
#define D4H 3111
#define E4 3296
#define F4 3492
#define F4H 3699
#define G4 3920
#define G4H 4153
#define A4 4400
#define A4H 4661
#define B4 4938
#define C5 5232
#define C5H 5543
#define D5 5873
#define D5H 6222
#define E5 6592
#define F5 6984
#define F5H 7399
#define G5 7839
#define G5H 8306
#define A5 8800
#define A5H 9323
#define B5 9877
#define C6 10465
#define C6H 11087
#define D6 11746
#define D6H 12445
#define E6 13185
#define F6 13969
#define F6H 14799
#define G6 15679
#define G6H 16612
#define A6 17600
#define A6H 18646
#define B6 19755
#define C7 20930
#define C7H 22174
#define D7 23493
#define D7H 24890
#define E7 26370
#define F7 27938
#define F7H 29599
#define G7 31359
#define G7H 33224
#define A7 35200
#define A7H 37293
#define B7 39510
#define C8 41860
#define C8H 44349
#define D8 46986
#define D8H 49780
#define E8 52740
#define F8 55876
#define F8H 59199
#define G8 62719
#define G8H 66448
#define A8 70400
#define A8H 74586
#define B8 79021

#endif
