/*********************************************** File name ********************************************/
/* Auther     : */
/* Discriptio : */
/******************************************************************************************************/
#ifndef DIO_INT_H_
#define DIO_INT_H_

#include "../utility/STD_TYPES.H"

#define DIO_PORTA  0
#define DIO_PORTB  1
#define DIO_PORTC  2
#define DIO_PORTD  3


#define DIO_PIN0   0
#define DIO_PIN1   1
#define DIO_PIN2   2
#define DIO_PIN3   3
#define DIO_PIN4   4
#define DIO_PIN5   5
#define DIO_PIN6   6
#define DIO_PIN7   7

#define DIO_OUTPUT  0xff
#define DIO_INPUT   0x00

#define DIO_HIGH    0xff
#define DIO_LOW     0x00

/*
*  DIO PIN Levels Types
*/
typedef enum{
    LOW_PIN,
    HIGH_PIN
}PIN_LEVEL_TYPES;
void DIO_vidSetPortDirection(u8 u8_copyPortID , u8 u8_copyDirection);
void DIO_vidSetPortValue(u8 u8_copyPortID , u8 u8_copyValue);
u8 DIO_u8GetPortValue(u8 u8_copyPortID );
void DIO_vidSetPinDirection(u8 u8_copyPortID , u8 u8_copyPinID , u8 u8_copyDirection);
void DIO_vidSetPinValue(u8 u8_copyPortID , u8 u8_copyPinID , u8 u8_copyvalue);
u8 DIO_u8GetPinValue(u8 u8_copyPortID , u8 u8_copyPinID );

void DIO_vidEnablePullUP(u8 u8_copyPortID , u8 u8_copyPinID);

void DIO_vidTogglePin(u8 u8_copyPort_ID ,u8 u8_copyPinID );

void DIO_vidTogglePort(u8 u8_copyPort_ID  );




#endif
