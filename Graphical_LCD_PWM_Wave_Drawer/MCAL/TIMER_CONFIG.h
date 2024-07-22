#ifndef TIMER_CONFIG_H_INCLUDED
#define TIMER_CONFIG_H_INCLUDED



/* Timer Mode select*/
/*
*Overflow_mode
*CTC_Mode
*Fast_PWM_Mode
*Phase_Correct_PWM_Mode
*/
#define TIMER0_MODE              Fast_PWM_Mode
#define TIMER2_MODE              CTC_Mode



/* Choosing the Clock Source of the Timer */
/*
*define CLK_SRC_CLR_MSK
*define NO_Clock_Source
*define System_Clk_No_prescaling
*define Prescaler_Val_8
*define Prescaler_Val_64
*define Prescaler_Val_256
*define Prescaler_Val_1024
*define EXT_Clk_PIN_T0_FallingEdge
*define EXT_Clk_PIN_T0_RisingEdge
*/
#define TIMER0_CLK_Select               Prescaler_Val_1024
#define TIMER2_CLK_Select               Prescaler_Val_64


/* setting Waveform Generation Mode */
/*
*Overflow
*PWM_phase_Correct
*CTC
*Fast_PWM
*/
#define TIMER0_Waveform_Mode           Fast_PWM

/* TIMER2 Waveform Generation Mode Types */
/*
*TIMER2_Overflow
*TIMER2_PWM_phase_Correct
*TIMER2_CTC
*TIMER2_Fast_PWM
*/
#define TIMER2_Waveform_Mode           TIMER2_CTC


/* Compare Match OC0 PIN Action select*/
/*
*Normal_PortOP_OC0_DICNCT
*CTC_Toggle_OC0_On_CmprMatch
*CTC_CLR_OC0_On_CmprMatch
*CTC_SET_OC0_On_CmprMatch
*/
#define TIMER0_CTC_Mode_OC0_Action              CTC_CLR_OC0_On_CmprMatch
#define TIMER2_CTC_Mode_OC0_Action              Normal_PortOP_OC0_DICNCT

/* Fast PWM Compare Match OC0 PIN Action select*/
/*
*CTC_Fst_PWM_NON_Inverting_Mode
*CTC_Fst_PWM_Inverting_Mode
*/
#define TIMER0_FAST_PWM_CTC_Mode_OC0_Action    CTC_Fst_PWM_NON_Inverting_Mode
#define TIMER2_FAST_PWM_CTC_Mode_OC0_Action    CTC_Fst_PWM_NON_Inverting_Mode


/* Phase Correct PWM Compare Match OC0 PIN Action select*/
/*
*CTC_PC_PWM_NON_Inverting
*CTC_PC_PWM_Inverting
*/
#define TIMER0_PC_PWM_CTC_Mode_OC0_Action      CTC_PC_PWM_NON_Inverting
#define TIMER2_PC_PWM_CTC_Mode_OC0_Action      CTC_PC_PWM_NON_Inverting

#endif // TIMER_CONFIG_H_INCLUDED
