#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include "../utility/STD_TYPES.H"
#include "TIMER_TYPES.h"
#include "TIMER_CONFIG.h"
#include "TIMER_REG.h"


void Timer0_init(void);

void Timer2_init(void);

void Timer0_SetPreloadValue(u8 PreloadValue);

void Timer2_SetPreloadValue(u8 PreloadValue);

void Timer0_SetCompareValue(u8 CompareValue);

void Timer2_SetCompareValue(u8 CompareValue);

void Timer0_SetCallBack(void (*CopyTimerPtr) (void));

void Timer2_SetCallBack( void (*CopyTimerPtr) (void));

//void Timer_deInit(void);

#endif // TIMER_H_INCLUDED
