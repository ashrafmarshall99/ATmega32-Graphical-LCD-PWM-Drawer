#include"../utility/STD_TYPES.H"
#include"../utility/BIT_math.h"

#include"DIO_int.h"
#include"DIO_priv.h"

//

void DIO_vidSetPortDirection(u8 u8_copyPortID , u8 u8_copyDirection)
{
	if ( u8_copyDirection >= 0x00 && u8_copyDirection <= 0xff)
	{
		switch(u8_copyPortID)
		{
		case DIO_PORTA:   DIO_DDRA_REG = u8_copyDirection ; break;
		case DIO_PORTB:   DIO_DDRB_REG = u8_copyDirection ; break;
		case DIO_PORTC:   DIO_DDRC_REG = u8_copyDirection ; break;
		case DIO_PORTD:   DIO_DDRD_REG = u8_copyDirection ; break;
		default:          break; //#warning("Worng Port ID ") ;
		}
	}else{
#warning("Worng Dierction ID ") ;
	}
}
void DIO_vidSetPortValue(u8 u8_copyPortID , u8 u8_copyValue)
{
	if ( u8_copyValue >= 0x00 && u8_copyValue <= 0xff)
	{
		switch(u8_copyPortID)
		{
		case DIO_PORTA:   DIO_PORTA_REG = u8_copyValue ; break;
		case DIO_PORTB:   DIO_PORTB_REG = u8_copyValue ; break;
		case DIO_PORTC:   DIO_PORTC_REG = u8_copyValue ; break;
		case DIO_PORTD:   DIO_PORTD_REG = u8_copyValue ; break;
		//            default:   		  #warning("Worng Port ID ") ;
		}
	}else{
#warning("Worng Value ID ") ;
	}
}

void DIO_vidSetPinDirection(u8 u8_copyPortID , u8 u8_copyPinID , u8 u8_copyDirection)
{

	if(u8_copyPinID <8)
	{


		if ( u8_copyDirection == DIO_OUTPUT)
		{
			switch(u8_copyPortID)
			{
			case DIO_PORTA:   SET_BIT (DIO_DDRA_REG , u8_copyPinID); break;
			case DIO_PORTB:   SET_BIT (DIO_DDRB_REG , u8_copyPinID); break;
			case DIO_PORTC:   SET_BIT (DIO_DDRC_REG , u8_copyPinID); break;
			case DIO_PORTD:   SET_BIT (DIO_DDRD_REG , u8_copyPinID); break;
			//            default:   		  #warning("Worng Port ID ") ;
			}
		}
		else if(u8_copyDirection == DIO_INPUT)
		{
			switch(u8_copyPortID)
			{
			case DIO_PORTA:   CLR_BIT (DIO_DDRA_REG , u8_copyPinID); break;
			case DIO_PORTB:   CLR_BIT (DIO_DDRB_REG , u8_copyPinID); break;
			case DIO_PORTC:   CLR_BIT (DIO_DDRC_REG , u8_copyPinID); break;
			case DIO_PORTD:   CLR_BIT (DIO_DDRD_REG , u8_copyPinID); break;
			//            default:   		  #warning("Worng Port ID ") ;
			}

		}
		else
		{
			#warning("Wronge Direction ID ") ;
		}
	}
	else
	{
		//
	}

}
void DIO_vidSetPinValue(u8 u8_copyPortID , u8 u8_copyPinID , u8 u8_copyvalue)
{
	if(u8_copyPinID <8)
	{


		if ( u8_copyvalue > DIO_LOW )
		{
			switch(u8_copyPortID)
			{
			case DIO_PORTA:   SET_BIT(DIO_PORTA_REG , u8_copyPinID); break;
			case DIO_PORTB:   SET_BIT(DIO_PORTB_REG , u8_copyPinID); break;
			case DIO_PORTC:   SET_BIT(DIO_PORTC_REG , u8_copyPinID); break;
			case DIO_PORTD:   SET_BIT(DIO_PORTD_REG , u8_copyPinID); break;
			//            default:   		  #warning("Worng Port ID ") ;
			}
		}
		else if(u8_copyvalue == DIO_LOW)
		{
			switch(u8_copyPortID)
			{
			case DIO_PORTA:   CLR_BIT(DIO_PORTA_REG , u8_copyPinID); break;
			case DIO_PORTB:   CLR_BIT(DIO_PORTB_REG , u8_copyPinID); break;
			case DIO_PORTC:   CLR_BIT(DIO_PORTC_REG , u8_copyPinID); break;
			case DIO_PORTD:   CLR_BIT(DIO_PORTD_REG , u8_copyPinID); break;
			//            default:   		  #warning("Worng Port ID ") ;
			}

		}
		else
		{
			#warning("Wronge Direction ID ") ;
		}
	}
	else
	{
		//
	}


}






u8 DIO_u8GetPortValue(u8 u8_copyPortID )
{
	u8 u8PortValue = 0 ;
	switch(u8_copyPortID)
	{

	case DIO_PORTA : u8PortValue = DIO_PINA_REG ; break ;
	case DIO_PORTB : u8PortValue = DIO_PINB_REG ; break ;
	case DIO_PORTC : u8PortValue = DIO_PINC_REG ; break ;
	case DIO_PORTD : u8PortValue = DIO_PIND_REG ; break ;
	default : break ;// do nothing
	}
	return u8PortValue ;
}
u8 DIO_u8GetPinValue(u8 u8_copyPortID , u8 u8_copyPinID )
{
	u8 u8PinValue = 0 ;
	switch(u8_copyPortID)
		{

		case DIO_PORTA : u8PinValue = GET_BIT(DIO_PINA_REG ,u8_copyPinID ); break ;
		case DIO_PORTB : u8PinValue = GET_BIT(DIO_PINB_REG ,u8_copyPinID ); break ;
		case DIO_PORTC : u8PinValue = GET_BIT(DIO_PINC_REG ,u8_copyPinID ); break ;
		case DIO_PORTD : u8PinValue = GET_BIT(DIO_PIND_REG ,u8_copyPinID ); break ;
		default : break ;  // do nothing
		}
	return u8PinValue ;

}

//void DIO_vidEnablePullUP(u8 u8_copyPortID , u8 u8_copyPinID);

void DIO_vidTogglePin(u8 u8_copyPort_ID ,u8 u8_copyPinID )
{
	if (u8_copyPinID >= 0 && u8_copyPinID  < 8 )
	{
	switch(u8_copyPort_ID)
			{

			case DIO_PORTA :TOG_BIT(DIO_PINA_REG ,u8_copyPinID ); break ;
			case DIO_PORTB :TOG_BIT(DIO_PINB_REG ,u8_copyPinID ); break ;
			case DIO_PORTC :TOG_BIT(DIO_PINC_REG ,u8_copyPinID ); break ;
			case DIO_PORTD :TOG_BIT(DIO_PIND_REG ,u8_copyPinID ); break ;
			default : break ;  // do nothing
			}
	}
	else{
#warning("Wronge PIN  ID ") ;
	}
}

void DIO_vidTogglePort(u8 u8_copyPort_ID  )
{
	switch(u8_copyPort_ID)
			{

			case DIO_PORTA : DIO_PORTA_REG ^= 0xFF ; break ;
			case DIO_PORTB : DIO_PORTB_REG ^= 0xFF ; break ;
			case DIO_PORTC : DIO_PORTC_REG ^= 0xFF ; break ;
			case DIO_PORTD : DIO_PORTD_REG ^= 0xFF ; break ;
			default : break ;
			}

}






void DIO_vidEnablePullUP(u8 u8_copyPortID , u8 u8_copyPinID)
{
	if(u8_copyPinID <8)
		{



				switch(u8_copyPortID)
				{
				case DIO_PORTA:   SET_BIT(DIO_PORTA_REG , u8_copyPinID); break;
				case DIO_PORTB:   SET_BIT(DIO_PORTB_REG , u8_copyPinID); break;
				case DIO_PORTC:   SET_BIT(DIO_PORTC_REG , u8_copyPinID); break;
				case DIO_PORTD:   SET_BIT(DIO_PORTD_REG , u8_copyPinID); break;
				//            default:   		  #warning("Worng Port ID ") ;
				}
			}
}




















