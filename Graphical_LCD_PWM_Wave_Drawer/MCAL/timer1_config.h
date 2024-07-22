#ifndef TIMER1_CONFIG_H_INCLUDED
#define TIMER1_CONFIG_H_INCLUDED

/* timer1 modes
overflow_mode
CTC_mode
Fast_pwm_mode
PC_PWM_mode
*/
#define timer1_mode                           overflow_mode

#define inversion_type                        NON_inverted_mode

#define System_prescaler                      TIMER1_Prescaler_256

#define Waveform_Generation_Mode              Waveform_Generation_Mode_ovf

//#define Fast_PWM_OC1A_Pin_Operation_Mode      FAST_PWM_Set_OC1A_On_CMPRMTCH

#define Fast_PWM_OC1A_Pin_Operation_Mode      FAST_PWM_Clear_OC1A_On_CMPRMTCH

#define Value_of_ICR1                         1249

/*first detected edge setup*/
/*
* Timer1_FDE_Rising
* Timer1_FDE_falling

*/
#define First_Detected_Edge                    Timer1_FDE_falling

#endif // TIMER1_CONFIG_H_INCLUDED
