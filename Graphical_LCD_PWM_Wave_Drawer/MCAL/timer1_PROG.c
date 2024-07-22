#include "../utility/BIT_math.h"
#include "DIO_int.h"
#include "timer1.h"
#include "timer1_config.h"
#include "timer1_reg.h"
#include "timer1_types.h"

void timer1_init(void)
{
    CLR_BIT(TCCR1AB_REG,10);
    CLR_BIT(TCCR1AB_REG,11);
    TCCR1AB_REG  &= CLK_SRC_CLR_MASK;
    TCCR1AB_REG  |= System_prescaler;
    TCCR1AB_REG  &= Waveform_Generation_clr_msk;
    TCCR1AB_REG  |= Waveform_Generation_Mode;
    TCCNT1LH_REG = 0;
    TIMSK_REG    &= Timer1_INT_CLR_MSK;

    #if   timer1_mode == overflow_mode
    #elif timer1_mode == CTC_mode
    #elif timer1_mode == Fast_pwm_mode
    TCCR1AB_REG  &= FAST_PWM_OC1A_OP_Mode_CLR_Mask;
    TCCR1AB_REG  |= Fast_PWM_OC1A_Pin_Operation_Mode;
    ICR1LH_REG   = Value_of_ICR1;
    #elif timer1_mode == PC_PWM_mode
    #endif // timer1_mode
}
void Start_timer1(void)
{
    SET_BIT(S_REG, 7);
    TIMSK_REG |= timer1_ovf_int_enable;
}
void timer1_set_pwm_wave_generationn(u16 pulse_width)
{
    OCR1ALH_REG = pulse_width;
}
void stop_timer1(void)
{
    TIMSK_REG &= Timer1_INT_CLR_MSK;
}
void Timer1_InputCapt_enable(void)
{
    DIO_vidSetPinDirection(DIO_PORTD, DIO_PIN6, DIO_INPUT);
    TCCR1AB_REG &= timer1_ICS_CLR_MSK;
    #if   First_Detected_Edge == Timer1_FDE_Rising
    SET_BIT(TCCR1AB_REG, 6); //sense on Rising edge
    #elif First_Detected_Edge == Timer1_FDE_falling
    CLR_BIT(TCCR1AB_REG, 6); //sense on falling edge
    #endif // First_Detected_Edge
    TIMSK_REG   |= timer1_input_capture_INT_E;
}

