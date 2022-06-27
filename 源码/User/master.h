#ifndef __MASTER_H
#define __MASTER_H

#include "main.h"


#define _0 48
#define _1 49
#define _2 50
#define _3 51
#define _4 52
#define _5 53
#define _6 54
#define _7 55
#define _8 56
#define _9 57
#define _A 65
#define _B 66
#define _C 67
#define _D 68
#define _E 69
#define _F 70
#define _G 71
#define _H 72
#define _I 73
#define _J 74
#define _K 75
#define _L 76
#define _M 77
#define _N 78
#define _O 79
#define _P 80
#define _Q 81
#define _R 82
#define _S 83
#define _T 84
#define _U 85
#define _V 86
#define _W 87
#define _X 88
#define _Y 89
#define _Z 90


#define MASTER_NUM_1   _0
#define MASTER_NUM_2   _0
#define MASTER_NUM_3   _0
#define MASTER_NUM_4   _0
#define MASTER_NUM_5   _5

#define MASTER_NUM   {MASTER_NUM_H,MASTER_NUM_L}

void Master_Init(void);

#endif /*__MASTER_H*/

