#include "TIMER.h"
#include "../utility/BIT_math.h"


static void (*T0_CallBackPointer) (void) = NULL;
static void (*T2_CallBackPointer) (void) = NULL;
void Timer0_init(void)
{
    CLR_BIT(TCCR0_Reg,7);
    TCCR0_Reg &= Waveform_CLR_MSK;
    TCCR0_Reg |= TIMER0_Waveform_Mode;
    TCCR0_Reg &= CLK_SRC_CLR_MSK;
    TCCR0_Reg |= TIMER0_CLK_Select;
    TIMSK_Reg &= TIMER0_INT_CLR_MSK;

    #if TIMER0_MODE == Overflow_Mode
        TCNT0_Reg = 0;
        TIMSK_Reg |= TIMER0_OVF_Interrupt_EN;
    #elif TIMER0_MODE == CTC_Mode
        TCCR0_Reg &= COM_CLR_MSK;
        TCCR0_Reg |= TIMER0_CTC_Mode_OC0_Action;
        TIMSK_Reg |= TIMER0_CTC_Interrupt_EN;
    #elif TIMER0_MODE == Fast_PWM_Mode
        TCNT0_Reg = 0;
        TCCR0_Reg &= COM_CLR_MSK;
        TCCR0_Reg |= TIMER0_FAST_PWM_CTC_Mode_OC0_Action;
    #elif TIMER0_MODE == Phase_Correct_PWM_Mode
        TCNT0_Reg = 0;
        TCCR0_Reg &= COM_CLR_MSK;
        TCCR0_Reg |= TIMER0_PC_PWM_CTC_Mode_OC0_Action;
    #endif // TIMER0_MODE
}
void Timer2_init(void)
{
    CLR_BIT(TCCR2_Reg,7);
    TCCR2_Reg &= Waveform_CLR_MSK;
    TCCR2_Reg |= TIMER2_Waveform_Mode;
    TCCR2_Reg &= CLK_SRC_CLR_MSK;
    TCCR2_Reg |= TIMER2_CLK_Select;
    TIMSK_Reg &= TIMER2_INT_CLR_MSK;

    #if TIMER2_MODE  == Overflow_Mode
        TCNT2_Reg = 0;
        TIMSK_Reg |= TIMER2_OVF_Interrupt_EN;
    #elif TIMER2_MODE  == CTC_Mode
        TCCR0_Reg &= COM_CLR_MSK;
        TCCR0_Reg |= TIMER2_CTC_Mode_OC0_Action;
        TIMSK_Reg |= TIMER2_CTC_Interrupt_EN;
    #elif TIMER2_MODE  == Fast_PWM_Mode
        TCNT0_Reg = 0;
        TCCR0_Reg &= COM_CLR_MSK;
        TCCR0_Reg |= TIMER0_FAST_PWM_CTC_Mode_OC0_Action;
    #elif TIMER2_MODE  == Phase_Correct_PWM_Mode
        TCNT0_Reg = 0;
        TCCR0_Reg &= COM_CLR_MSK;
        TCCR0_Reg |= TIMER0_PC_PWM_CTC_Mode_OC0_Action;
    #endif // TIMER_MODE
}

void Timer0_SetPreloadValue(u8 PreloadValue)
{
    TCNT0_Reg = PreloadValue;
}

void Timer2_SetPreloadValue(u8 PreloadValue)
{
    TCNT2_Reg = PreloadValue;
}

void Timer0_SetCompareValue(u8 CompareValue)
{
    OCR0_Reg = CompareValue;
}

void Timer2_SetCompareValue(u8 CompareValue)
{
    OCR2_Reg = CompareValue;
}

void Timer0_SetCallBack( void (*CopyTimerPtr) (void))
{
    T0_CallBackPointer = CopyTimerPtr;
}

void Timer2_SetCallBack( void (*CopyTimerPtr) (void))
{
    T2_CallBackPointer = CopyTimerPtr;
}

void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
    if (T0_CallBackPointer != NULL)
    {
        T0_CallBackPointer();
    }
    else
    {

    }
}

void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
    if (T0_CallBackPointer != NULL)
    {
        T0_CallBackPointer();
    }
    else
    {

    }
}

void __vector_5(void) __attribute__((signal));
void __vector_5(void)
{
    if (T2_CallBackPointer != NULL)
    {
        T2_CallBackPointer();
    }
    else
    {

    }
}

void __vector_4(void) __attribute__((signal));
void __vector_4(void)
{
    if (T2_CallBackPointer != NULL)
    {
        T2_CallBackPointer();
    }
    else
    {

    }
}
