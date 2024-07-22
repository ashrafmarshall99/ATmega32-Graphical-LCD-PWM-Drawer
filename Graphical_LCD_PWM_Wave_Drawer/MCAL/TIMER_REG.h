#ifndef TIMER_REG_H_INCLUDED
#define TIMER_REG_H_INCLUDED

#define S_Reg               *((volatile u8*) 0x5F)
#define TCCR0_Reg           *((volatile u8*) 0x53)
#define TCCR2_Reg           *((volatile u8*) 0x45)
#define TCNT0_Reg           *((volatile u8*) 0x52)
#define TCNT2_Reg           *((volatile u8*) 0x44)
#define OCR0_Reg            *((volatile u8*) 0x5C)
#define OCR2_Reg            *((volatile u8*) 0x43)
#define TIMSK_Reg           *((volatile u8*) 0x59)
#define TIFR_Reg            *((volatile u8*) 0x58)

#endif // TIMER_REG_H_INCLUDED
