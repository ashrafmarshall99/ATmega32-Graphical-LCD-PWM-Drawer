#ifndef TIMER1_TYPES_H_INCLUDED
#define TIMER1_TYPES_H_INCLUDED

/*timer modes*/
#define overflow_mode                           1
#define CTC_mode                                2
#define Fast_pwm_mode                           3
#define PC_PWM_mode                             4

/*inversion types*/
#define inverted_mode                           1
#define NON_inverted_mode                       2

/*Clock Source Types*/
#define CLK_SRC_CLR_MASK                        0b1111111111111000
#define TIMER1_NOCLK_Src                        0b0000000000000000
#define TIMER1_Prescaler_1                      0b0000000000000001
#define TIMER1_Prescaler_8                      0b0000000000000010
#define TIMER1_Prescaler_64                     0b0000000000000011
#define TIMER1_Prescaler_256                    0b0000000000000100
#define TIMER1_Prescaler_1024                   0b0000000000000101
#define TIMER1_PIN_T1_Falling_edge              0b0000000000000110
#define TIMER1_PIN_T1_Rising_edge               0b0000000000000111

/*compare output modes (NON_PWM) for channel A (BITS 14,15)*/
#define OC1A_OP_Mode_CLR_Mask                   0b0011111111111111
#define NRML_PRT_OP_OC1A_DISCNT                 0b0000000000000000
#define Toggle_OC1A_On_CMPRMTCH                 0b0100000000000000
#define Clear_OC1A_On_CMPRMTCH                  0b1000000000000000
#define Set_OC1A_On_CMPRMTCH                    0b1100000000000000

/*compare output modes (NON_PWM) for channel B (BITS 12,13)*/
#define OC1B_OP_Mode_CLR_Mask                   0b1100111111111111
#define NRML_PRT_OP_OC1B_DISCNT                 0b0000000000000000
#define Toggle_OC1B_On_CMPRMTCH                 0b0001000000000000
#define Clear_OC1B_On_CMPRMTCH                  0b0010000000000000
#define Set_OC1B_On_CMPRMTCH                    0b0011000000000000

///*compare output modes (NON_PWM) for channel B (BITS 12,13)*/
//#define OC1B_OP_Mode_CLR_Mask                   0b1100111111111111
//#define NRML_PRT_OP_OC1B_DISCNT                 0b0000000000000000
//#define Toggle_OC1B_On_CMPRMTCH                 0b0001000000000000
//#define Clear_OC1B_On_CMPRMTCH                  0b0010000000000000
//#define Set_OC1B_On_CMPRMTCH                    0b0011000000000000

/*compare output modes (FAST_PWM) for channel A (BITS 14,15)*/
#define FAST_PWM_OC1A_OP_Mode_CLR_Mask                   0b0011111111111111
#define FAST_PWM_NRML_PRT_OP_OC1A_DISCNT                 0b0000000000000000
#define FAST_PWM_Toggle_OC1A_On_CMPRMTCH                 0b0100000000000000
#define FAST_PWM_Clear_OC1A_On_CMPRMTCH                  0b1000000000000000
#define FAST_PWM_Set_OC1A_On_CMPRMTCH                    0b1100000000000000

/*compare output modes (FAST_PWM) for channel B (BITS 12,13)*/
#define FAST_PWM_OC1B_OP_Mode_CLR_Mask                   0b1100111111111111
#define FAST_PWM_NRML_PRT_OP_OC1B_DISCNT                 0b0000000000000000
#define FAST_PWM_Toggle_OC1B_On_CMPRMTCH                 0b0001000000000000
#define FAST_PWM_Clear_OC1B_On_CMPRMTCH                  0b0010000000000000
#define FAST_PWM_Set_OC1B_On_CMPRMTCH                    0b0011000000000000

/*Waveform Generation Mode Bit Description*/
#define Waveform_Generation_clr_msk                      0b1111110011100111
#define Waveform_Generation_Mode_ovf                     0b0000000000000000
#define Waveform_Generation_Mode_pc_pwm_8                0b0000000100000000
#define Waveform_Generation_Mode_pc_pwm_9                0b0000001000000000
#define Waveform_Generation_Mode_pc_pwm_10               0b0000001100000000
#define Waveform_Generation_Mode_ctc_osr1                0b0000000000001000
#define Waveform_Generation_Mode_fst_pwm_8               0b0000000100001000
#define Waveform_Generation_Mode_fst_pwm_9               0b0000001000001000
#define Waveform_Generation_Mode_fst_pwm_10              0b0000001100001000
#define Waveform_Generation_Mode_pfc_icr1                0b0000000000010000
#define Waveform_Generation_Mode_pfc_ocr1                0b0000000100010000
#define Waveform_Generation_Mode_pc_icr1                 0b0000001000010000
#define Waveform_Generation_Mode_pc_ocr1                 0b0000001100010000
#define Waveform_Generation_Mode_ctc_icr1                0b0000000000011000
#define Waveform_Generation_Mode_fast_pwm_icr1           0b0000001000011000
#define Waveform_Generation_Mode_fast_pwm_ocr1           0b0000001100011000

/* Timer 1 interrupt Clear mask*/
#define Timer1_INT_CLR_MSK                               0b11000011

/* Timer 1 channel A OutPut compare interrupt enable*/
#define Timer1_OCA_INT_E                                 0b00010000

/* Timer 1 channel B OutPut compare interrupt enable*/
#define Timer1_OCB_INT_E                                 0b00001000

/* Timer 1 Overflow interrupt enable*/
#define timer1_ovf_int_enable                            0b00000100

/* Timer 1 Input capture interrupt enable*/
#define timer1_input_capture_INT_E                       0b00100000

/* Timer 1 input capture sense Edge types */
#define timer1_ICS_CLR_MSK                               0b1111111110111111
#define timer1_ICS_falling_edge                          0b1111111110111111
#define timer1_ICS_rising_edge                           0b0000000001000000

/* Timer 1 input capture first detected edge */
#define Timer1_FDE_Rising       1
#define Timer1_FDE_falling      0

#endif // TIMER1_TYPES_H_INCLUDED
