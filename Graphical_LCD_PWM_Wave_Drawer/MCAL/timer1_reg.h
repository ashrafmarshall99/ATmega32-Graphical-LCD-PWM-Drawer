#ifndef TIMER1_REG_H_INCLUDED
#define TIMER1_REG_H_INCLUDED

#define TCCR1AB_REG              *((volatile u16*) 0x4E)
#define TCCNT1LH_REG             *((volatile u16*) 0x4C)
#define OCR1ALH_REG              *((volatile u16*) 0x4A)
#define OCR1BLH_REG              *((volatile u16*) 0x48)
#define ICR1LH_REG               *((volatile u16*) 0x46)
#define S_REG                    *((volatile u16*) 0x5F)
#define TIMSK_REG                *((volatile u16*) 0x59)

#endif // TIMER1_REG_H_INCLUDED
