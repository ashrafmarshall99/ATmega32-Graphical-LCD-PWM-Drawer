#ifndef TIMER_TYPES_H_INCLUDED
#define TIMER_TYPES_H_INCLUDED

/* Timer Mode select Types*/
#define Overflow_Mode                           0
#define CTC_Mode                                1
#define Fast_PWM_Mode                           2
#define Phase_Correct_PWM_Mode                  3

/* clock select types */
#define CLK_SRC_CLR_MSK                         0b11111000
#define NO_Clock_Source                         0
#define System_Clk_No_prescaling                1
#define Prescaler_Val_8                         2
#define Prescaler_Val_64                        3
#define Prescaler_Val_256                       4
#define Prescaler_Val_1024                      5
#define EXT_Clk_PIN_T0_FallingEdge              6
#define EXT_Clk_PIN_T0_RisingEdge               7
/**********************/

/* TIMER0 Waveform Generation Mode Types */
#define Waveform_CLR_MSK                        0b10110111
#define Overflow                                0b10110111
#define PWM_phase_Correct                       0b11110111
#define CTC                                     0b10111111
#define Fast_PWM                                0b11111111
/**********************/

/* TIMER2 Waveform Generation Mode Types */
#define Waveform_CLR_MSK                        0b10110111
#define TIMER2_Overflow                         0b10110111
#define TIMER2_PWM_phase_Correct                0b11110111
#define TIMER2_CTC                              0b10111111
#define TIMER2_Fast_PWM                         0b11111111
/**********************/

/* Compare Output Mode, BITS (COM01,00)==BITS 5,4 */
#define COM_CLR_MSK                             0b11001111
/**********************/

/* Disabling PIN OC0, BITS (COM01,00)==BITS 5,4 */
#define Normal_PortOP_OC0_DICNCT                0b11001111
/**********************/

/* Compare Output Mode, NON_PWM Mode, BITS (COM01,00)==BITS 5,4 */
#define CTC_Toggle_OC0_On_CmprMatch          0b00010000
#define CTC_CLR_OC0_On_CmprMatch             0b00100000 // non-inverting mode
#define CTC_SET_OC0_On_CmprMatch             0b00110000 // inverting mode
/**********************/

/* Compare Output Mode, Fast PWM Mode, BITS (COM01,00)==BITS 5,4 */
#define CTC_Fst_PWM_NON_Inverting_Mode               0b00100000 // in non-verting mode___ OC0 is cleared on compare match and set at the bottom
#define CTC_Fst_PWM_Inverting_Mode                   0b00110000 // in inverting mode___ OC0 is set on compare match and cleared at the bottom
/**********************/

/* Compare Output Mode, PHASE_Correct PWM Mode BITS (COM01,00)==BITS 5,4 */
#define CTC_PC_PWM_NON_Inverting                    0b00100000 // Clear OC0 on count up Compare match and SET OC0 at bottom of the count down compare match
#define CTC_PC_PWM_Inverting                        0b00110000 // SET OC0 on count up Compare match and Clear OC0 at bottom of the count down compare match
/**********************/

/* TIMER0 Interrupt Clear Mask */
#define TIMER0_INT_CLR_MSK                           0b11111100
/**********************/

/* TIMER2 Interrupt Clear Mask */
#define TIMER2_INT_CLR_MSK                           0b00111111
/**********************/

/* TIMER0 Overflow interrupt enable */
#define TIMER0_OVF_Interrupt_EN                     0b00000001
/**********************/

/* TIMER2 Overflow interrupt enable */
#define TIMER2_OVF_Interrupt_EN                     0b01000000
/**********************/

/* TIMER0 compare match interrupt enable */
#define TIMER0_CTC_Interrupt_EN                     0b00000010
/**********************/

/* TIMER2 compare match interrupt enable */
#define TIMER2_CTC_Interrupt_EN                     0b10000000
/**********************/



#define NULL                    0

#endif // TIMER_TYPES_H_INCLUDED
