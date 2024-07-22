/*
 */
#include "../utility/STD_TYPES.H"
#include "../utility/BIT_math.h"
#include "../MCAL/DIO_int.h"
#include "../HAL/GLCD.h"
#include "../HAL/GLCD_CONFIG.h"
#include <util/delay.h>
#include "../MCAL/TIMER.h"
#include "../MCAL/timer1.h"
#include "../MCAL/timer1_types.h"
#include "../MCAL/timer1_reg.h"
#include "../MCAL/timer1_config.h"
#include <avr/interrupt.h>
#include <stdlib.h>


u8 ICU_ISR_SRC_CNTRL = 0;
u8 index = 0;
u8 PWM_Values[100];
u16 High_Time;
u16 LOW_Time;

int main(void)
{
    DIO_vidSetPortDirection(DIO_PORTB, DIO_OUTPUT);
    DIO_vidSetPinDirection(DIO_PORTB, DIO_PIN4, DIO_OUTPUT);

    /*** enabling global interrupt ***/
    SET_BIT(S_Reg, 7);
    /*********************************/

    /*** GLCD Ports initialization ***/
    DIO_vidSetPortDirection(CNTRL_PORT, DIO_OUTPUT);
    DIO_vidSetPortDirection(DATA_PORT, DIO_OUTPUT);
    /*********************************/

    /*** Timer0 PWM Pin initialization ***/
    DIO_vidSetPinDirection(DIO_PORTB, DIO_PIN3, DIO_OUTPUT);
    /*************************************/

    /******* TIMER1 initialization *******/
    timer1_init();
    Timer1_InputCapt_enable();
    /*************************************/

    /******* TIMER0 initialization *******/
    Timer0_SetCompareValue(150);
    Timer0_init();
    /*************************************/

    /******** GLCD initialization ********/
    GLCD_INIT();
    /*************************************/
    u16 frequency;
    u8 duty;
    u16 iterate = 0;
    u8 Draw_index = 0;

    while(1)
    {

        frequency = (float)(1.0 / (High_Time+LOW_Time)) * 0.062 * 1000000;// the actual calculations exclude the 1000000 because it is just used for magnification
                                                           // also the 0.062 is actually 0.063556 and it is the result of calculating the time of one count
                                                           // which is equal to (system_prescaler/system_frquency) but the number is reduced to compensate for a 5% error
        duty = ((float) High_Time/(High_Time+LOW_Time) ) * 100 ;

        if(Draw_index == 0)
        {
            if(PWM_Values[Draw_index] == 1)
            {
                for(iterate=0; iterate<(High_Time/25); iterate++) //the division by the number 25 is made so as to scale down the high time value
                {
                    GLCD_Draw_TOP_PWM_H_Line(frequency, duty);
                }
            }
            else if(PWM_Values[Draw_index] == 0)
            {
                for(iterate=0; iterate<(LOW_Time/25); iterate++) //the division by the number 25 is made so as to scale down the high time value
                {
                    GLCD_Draw_BTM_PWM_H_Line(frequency, duty);
                }
            }
        }


        else if(Draw_index != 0)
        {
            if (PWM_Values[Draw_index] == 1)
            {
                GLCD_Draw_V_Line(5, 2);
                for(iterate=0; iterate<(High_Time/25); iterate++)
                {
                    GLCD_Draw_TOP_PWM_H_Line(frequency, duty);
                }
            }
            else if (PWM_Values[Draw_index] == 0)
            {
                GLCD_Draw_V_Line(2, 5);
                for(iterate=0; iterate<(LOW_Time/25); iterate++)
                {
                    GLCD_Draw_BTM_PWM_H_Line(frequency, duty);
                }
            }
        }
        Draw_index++;




    }

}

ISR(TIMER1_CAPT_vect)
{
    if (ICU_ISR_SRC_CNTRL == 0)
    {
        #if   First_Detected_Edge == Timer1_FDE_Rising
            PWM_Values[index] = 1;
            index++;
        #elif First_Detected_Edge == Timer1_FDE_falling
            PWM_Values[index] = 0;
            index++;
        #endif
        TCCNT1LH_REG = 0;
        ICU_ISR_SRC_CNTRL = 1;
        TOG_BIT(TCCR1AB_REG, 6);
    }
    else if (ICU_ISR_SRC_CNTRL == 1)
    {
        #if   First_Detected_Edge == Timer1_FDE_Rising
            High_Time = ICR1LH_REG;
            PWM_Values[index] = 0;
            index++;
        #elif First_Detected_Edge == Timer1_FDE_falling
            LOW_Time = ICR1LH_REG;
            PWM_Values[index] = 1;
            index++;
        #endif
        TCCNT1LH_REG = 0;
        ICU_ISR_SRC_CNTRL = 2;
        TOG_BIT(TCCR1AB_REG, 6);
    }
    else if (ICU_ISR_SRC_CNTRL == 2)
    {
        #if   First_Detected_Edge == Timer1_FDE_Rising
            LOW_Time = ICR1LH_REG;
        #elif First_Detected_Edge == Timer1_FDE_falling
            High_Time = ICR1LH_REG;
        #endif // First_Detected_Edge
        ICU_ISR_SRC_CNTRL = 0;
    }
}
