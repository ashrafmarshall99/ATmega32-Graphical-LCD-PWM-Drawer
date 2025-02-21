#include <util/delay.h>
#include "../utility/STD_TYPES.H"
#include "GLCD_CONFIG.h"
#include "../MCAL/DIO_int.h"
#include <avr/pgmspace.h>
#include <stdlib.h>

u8 column_control = 0;
u8 row_control = 0;

// this font is an 8x6 font which means that each character contains 6 bits by width where it is noticed below
// that the arrays consists of 7 elements but the seventh is the en of character element which is used in the
// logic to show the program that the character is finished
// there for, each line will only contain 21 characters.
static const u8 GlcdFont_U8[][7] PROGMEM= {
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff}, /* 0x00  */
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff}, /* 0x10  */
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
		{0xff,0xff,0xff,0xff,0xff,0x00,0xff},
        {0x00,0x00,0x00,0x00,0x00,0xff,0xff}, /* Space 0x20 */
        {0x00,0x00,0x4f,0x00,0x00,0x00,0xff}, /* ! */
        {0x00,0x07,0x00,0x07,0x00,0x00,0xff}, /* " */
        {0x14,0x7f,0x14,0x7f,0x14,0x00,0xff}, /* # */
        {0x24,0x2a,0x7f,0x2a,0x12,0x00,0xff}, /* 0x */
        {0x23,0x13,0x08,0x64,0x62,0x00,0xff}, /* % */
        {0x36,0x49,0x55,0x22,0x20,0x00,0xff}, /* & */
        {0x00,0x05,0x03,0x00,0x00,0x00,0xff}, /* ' */
        {0x00,0x1c,0x22,0x41,0x00,0x00,0xff}, /* ( */
        {0x00,0x41,0x22,0x1c,0x00,0x00,0xff}, /* ) */
        {0x14,0x08,0x3e,0x08,0x14,0x00,0xff}, /* // */
        {0x08,0x08,0x3e,0x08,0x08,0x00,0xff}, /* + */
        {0x50,0x30,0x00,0x00,0x00,0x00,0xff}, /* , */
        {0x08,0x08,0x08,0x08,0x08,0x00,0xff}, /* - */
        {0x00,0x60,0x60,0x00,0x00,0x00,0xff}, /* . */
        {0x20,0x10,0x08,0x04,0x02,0x00,0xff}, /* / */
        {0x3e,0x51,0x49,0x45,0x3e,0x00,0xff}, /* 0 0x30 */
        {0x40,0x42,0x7f,0x40,0x40,0x00,0xff}, /* 1 */
        {0x42,0x61,0x51,0x49,0x46,0x00,0xff}, /* 2 */
        {0x21,0x41,0x45,0x4b,0x31,0x00,0xff}, /* 3 */
        {0x18,0x14,0x12,0x7f,0x10,0x00,0xff}, /* 4 */
        {0x27,0x45,0x45,0x45,0x39,0x00,0xff}, /* 5 */
        {0x3c,0x4a,0x49,0x49,0x30,0x00,0xff}, /* 6 */
        {0x01,0x71,0x09,0x05,0x03,0x00,0xff}, /* 7 */
        {0x36,0x49,0x49,0x49,0x36,0x00,0xff}, /* 8 */
        {0x06,0x49,0x49,0x29,0x1e,0x00,0xff}, /* 9 */
        {0x00,0x36,0x36,0x00,0x00,0x00,0xff}, /* : */
        {0x00,0x56,0x36,0x00,0x00,0x00,0xff}, /* ; */
        {0x08,0x14,0x22,0x41,0x00,0x00,0xff}, /* < */
        {0x14,0x14,0x14,0x14,0x14,0x00,0xff}, /* = */
        {0x00,0x41,0x22,0x14,0x08,0x00,0xff}, /* > */
        {0x02,0x01,0x51,0x09,0x06,0x00,0xff}, /* ? */
        {0x3e,0x41,0x5d,0x55,0x1e,0x00,0xff}, /* @ 0x40 */
        {0x7e,0x11,0x11,0x11,0x7e,0x00,0xff}, /* A */
        {0x7f,0x49,0x49,0x49,0x36,0x00,0xff}, /* B */
        {0x3e,0x41,0x41,0x41,0x22,0x00,0xff}, /* C */
        {0x7f,0x41,0x41,0x22,0x1c,0x00,0xff}, /* D */
        {0x7f,0x49,0x49,0x49,0x41,0x00,0xff}, /* E */
        {0x7f,0x09,0x09,0x09,0x01,0x00,0xff}, /* F */
        {0x3e,0x41,0x49,0x49,0x7a,0x00,0xff}, /* G */
        {0x7f,0x08,0x08,0x08,0x7f,0x00,0xff}, /* H */
        {0x00,0x41,0x7f,0x41,0x00,0x00,0xff}, /* I */
        {0x20,0x40,0x41,0x3f,0x01,0x00,0xff}, /* J */
        {0x7f,0x08,0x14,0x22,0x41,0x00,0xff}, /* K */
        {0x7f,0x40,0x40,0x40,0x40,0x00,0xff}, /* L */
        {0x7f,0x02,0x0c,0x02,0x7f,0x00,0xff}, /* M */
        {0x7f,0x04,0x08,0x10,0x7f,0x00,0xff}, /* N */
        {0x3e,0x41,0x41,0x41,0x3e,0x00,0xff}, /* O */
        {0x7f,0x09,0x09,0x09,0x06,0x00,0xff}, /* P 0x50 */
        {0x3e,0x41,0x51,0x21,0x5e,0x00,0xff}, /* Q */
        {0x7f,0x09,0x19,0x29,0x46,0x00,0xff}, /* R */
        {0x26,0x49,0x49,0x49,0x32,0x00,0xff}, /* S */
        {0x01,0x01,0x7f,0x01,0x01,0x00,0xff}, /* T */
        {0x3f,0x40,0x40,0x40,0x3f,0x00,0xff}, /* U */
        {0x1f,0x20,0x40,0x20,0x1f,0x00,0xff}, /* V */
        {0x3f,0x40,0x38,0x40,0x3f,0x00,0xff}, /* W */
        {0x63,0x14,0x08,0x14,0x63,0x00,0xff}, /* X */
        {0x07,0x08,0x70,0x08,0x07,0x00,0xff}, /* Y */
        {0x61,0x51,0x49,0x45,0x43,0x00,0xff}, /* Z */
        {0x00,0x7f,0x41,0x41,0x00,0x00,0xff}, /* [ */
        {0x02,0x04,0x08,0x10,0x20,0x00,0xff}, /* \ */
        {0x00,0x41,0x41,0x7f,0x00,0x00,0xff}, /* ] */
        {0x04,0x02,0x01,0x02,0x04,0x00,0xff}, /* ^ */
        {0x40,0x40,0x40,0x40,0x40,0x00,0xff}, /* _ */
        {0x00,0x00,0x03,0x05,0x00,0x00,0xff}, /* ` 0x60 */
        {0x20,0x54,0x54,0x54,0x78,0x00,0xff}, /* a */
        {0x7F,0x44,0x44,0x44,0x38,0x00,0xff}, /* b */
        {0x38,0x44,0x44,0x44,0x44,0x00,0xff}, /* c */
        {0x38,0x44,0x44,0x44,0x7f,0x00,0xff}, /* d */
        {0x38,0x54,0x54,0x54,0x18,0x00,0xff}, /* e */
        {0x04,0x04,0x7e,0x05,0x05,0x00,0xff}, /* f */
        {0x08,0x54,0x54,0x54,0x3c,0x00,0xff}, /* g */
        {0x7f,0x08,0x04,0x04,0x78,0x00,0xff}, /* h */
        {0x00,0x44,0x7d,0x40,0x00,0xff,0xff}, /* i */
        {0x20,0x40,0x44,0x3d,0x00,0xff,0xff}, /* j */
        {0x7f,0x10,0x28,0x44,0x00,0xff,0xff}, /* k */
        {0x41,0x7f,0x40,0x00,0xff,0xff,0xff}, /* l */
        {0x7c,0x04,0x7c,0x04,0x78,0x00,0xff}, /* m */
        {0x7c,0x08,0x04,0x04,0x78,0x00,0xff}, /* n */
        {0x38,0x44,0x44,0x44,0x38,0x00,0xff}, /* o */
        {0x7c,0x14,0x14,0x14,0x08,0x00,0xff}, /* p 0x70 */
        {0x08,0x14,0x14,0x14,0x7c,0x00,0xff}, /* q */
        {0x7c,0x08,0x04,0x04,0x00,0xff,0xff}, /* r */
        {0x48,0x54,0x54,0x54,0x24,0x00,0xff}, /* s */
        {0x04,0x04,0x3f,0x44,0x44,0x00,0xff}, /* t */
        {0x3c,0x40,0x40,0x20,0x7c,0x00,0xff}, /* u */
        {0x1c,0x20,0x40,0x20,0x1c,0x00,0xff}, /* v */
        {0x3c,0x40,0x30,0x40,0x3c,0x00,0xff}, /* w */
        {0x44,0x28,0x10,0x28,0x44,0x00,0xff}, /* x */
        {0x0c,0x50,0x50,0x50,0x3c,0x00,0xff}, /* y */
        {0x44,0x64,0x54,0x4c,0x44,0x00,0xff}, /* z */
        {0x08,0x36,0x41,0x41,0x00,0x00,0xff}, /* { */
        {0x00,0x00,0x77,0x00,0x00,0x00,0xff}, /* | */
        {0x00,0x41,0x41,0x36,0x08,0x00,0xff}, /* } */
        {0x08,0x08,0x2a,0x1c,0x08,0x00,0xff}, /* <- */
        {0x08,0x1c,0x2a,0x08,0x08,0x00,0xff}, /* -> */
        {0xff,0xff,0xff,0xff,0xff,0x00,0xff}, /*  0x80 */
};

void GLCD_INIT(void)
{
    DIO_vidSetPortDirection(CNTRL_PORT, DIO_OUTPUT);
    DIO_vidSetPortDirection(DATA_PORT, DIO_OUTPUT);
    DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_RST, DIO_HIGH);
    DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_1, DIO_HIGH);
    DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_2, DIO_HIGH);

    _delay_ms(20);

    GLCD_Send_Command(0x3E);
    GLCD_Send_Command(0x40);
    GLCD_Send_Command(0xB8);
    GLCD_Send_Command(0xC0);
    GLCD_Send_Command(0x3F);

}
void GLCD_Send_Data(u8 data)
{
    DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_RST, DIO_HIGH);
    DIO_vidSetPortValue(DATA_PORT, data);
    _delay_ms(2);
    DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_DI, DIO_HIGH);
    DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_RW, DIO_LOW);
    DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_E, DIO_HIGH);
    _delay_ms(2);
    DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_E, DIO_LOW);
    _delay_ms(2);
}
void GLCD_Send_Command(u8 command)
{
    DIO_vidSetPortValue(DATA_PORT, command);
    _delay_ms(5);
    DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_DI, DIO_LOW);
    DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_RW, DIO_LOW);
    DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_E, DIO_HIGH);
    _delay_ms(5);
    DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_E, DIO_LOW);
    _delay_ms(5);
}
void GLCD_SET_Start_Line(u8 line)
{
    u8 temp_line = 0b11000000 | line;
    // 0b11000000 this is the display start line command mask
    DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_1, DIO_LOW);
    DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_2, DIO_LOW);
    GLCD_Send_Command(temp_line);
}
void GLCD_GOTO_Column(u8 Column)
{
    column_control = Column;
    u8 Temp_Column;
    if (Column<64)
    {
        DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_1, DIO_HIGH);
        DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_2, DIO_LOW);
        Temp_Column = Column;
    }
    else
    {
        DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_1, DIO_LOW);
        DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_2, DIO_HIGH);
        Temp_Column = Column - 64;
    }
    Temp_Column = (Temp_Column | 0b01000000) & 0b01111111;
    // 0b01000000 is the column command mask(set address mask) and 0b01111111 is used to insure that the 2 MSB are 01
    GLCD_Send_Command(Temp_Column);
}
void GLCD_GOTO_Row(u8 Row)
{
    row_control = Row;
    u8 Temp_Row = (Row | 0b10111000) & 0b10111111;
    GLCD_Send_Command(Temp_Row);

}
void GLCD_GOTO_XY(u8 Row, u8 Column)
{
    GLCD_GOTO_Column(Column);
    GLCD_GOTO_Row(Row);
}
void GLCD_GOTO_Next_Line(void)
{
    row_control = row_control+1;
    GLCD_GOTO_XY(row_control, 0);
}
void GLCD_CLR_Line(u8 Line)
{
    u8 i;
    GLCD_GOTO_XY(Line, 0);
    GLCD_GOTO_XY(Line, 64);
    DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_1, DIO_HIGH);
    DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_2, DIO_HIGH);
     // this line is wrote to assure that the chip select 1 is active
     // so that we can work with both chips since already chip 2 is activated
     // in the goto_xy with the column being 64
     for(i=0; i<65; i++)
     {
         GLCD_Send_Data(0);
     }
}
void GLCD_CLR(void)
{
    u8 Line;
    for(Line=0; Line<8; Line++)
    {
        GLCD_CLR_Line(Line);
    }
    GLCD_GOTO_XY(0, 0);
    column_control = 0;
    row_control = 0;
    DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_1, DIO_LOW);
    DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_2, DIO_LOW);
}
void GLCD_Draw_point(u8 row, u8 column)
{
    GLCD_GOTO_XY(row, column);
    GLCD_Send_Data(1);
}
void draw_pwm_wave(void)
{

}
void GLCD_Draw_TOP_PXL_H_Line(void)
{
    if (column_control <64)
    {
        DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_1, DIO_HIGH);
        DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_2, DIO_LOW);
    }
    else
    {
        DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_1, DIO_LOW);
        DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_2, DIO_HIGH);
    }

    GLCD_GOTO_Row(2);
    GLCD_Send_Data(0b00000001);
    column_control++;
    if (column_control == 128)
    {
        GLCD_CLR();
    }
}
void GLCD_Draw_BTM_PXL_H_Line(void)
{
    if (column_control <64)
    {
        DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_1, DIO_HIGH);
        DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_2, DIO_LOW);
    }
    else
    {
        DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_1, DIO_LOW);
        DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_2, DIO_HIGH);
    }

    GLCD_GOTO_Row(5);
    GLCD_Send_Data(0b10000000);
    column_control++;
    if (column_control == 128)
    {
        GLCD_CLR();
    }
}
void GLCD_Draw_V_Line(u8 Row, u8 Row_Destination)
{
    u8 iterator;
    if(Row<Row_Destination)
    {
         for(iterator = Row; iterator <= Row_Destination; iterator++)
            {
                GLCD_GOTO_XY(iterator, column_control);
                GLCD_Send_Data(0b11111111);
            }
    }
    else if(Row>Row_Destination)
    {
         for(iterator = Row; iterator >= Row_Destination; iterator--)
            {
                GLCD_GOTO_XY(iterator, column_control);
                GLCD_Send_Data(0b11111111);
            }
    }
    else
    {

    }
    if (column_control == 127)
    {
        column_control = 0;
    }
}

void GLCD_write_character(u8 Copy_character)
{
    u8 data, *PTR;

    if (Copy_character == '\n')
    {
        // create a function that lets us move to the next line (use the go to row and find a way to monitor the row we are in)
        ++row_control;
        GLCD_GOTO_XY((row_control+1), 0);
    }

    if (Copy_character != '\n')
    {
        PTR = &GlcdFont_U8[Copy_character][0];

        while (1)
        {
//            if (column_control <64)
//            {
//                DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_1, DIO_HIGH);
//                DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_2, DIO_LOW);
//            }
//            else
//            {
//                DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_1, DIO_LOW);
//                DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_2, DIO_HIGH);
//            }

            GLCD_GOTO_Column(column_control);
            GLCD_GOTO_Row(row_control);

            data = pgm_read_byte(PTR++);

            if (data == 0xff)
            {
                break;
            }

            if (column_control == 128)
            {
                if (row_control == 7)
                {
                    GLCD_CLR();
                }
                else
                {
                    GLCD_GOTO_Next_Line();
                }
            }

            GLCD_Send_Data(data);
            ++column_control;


        }
    }
}

void GLCD_Write_String(u8 *Copy_String)
{
    while ((*Copy_String) != 0)
    {
        GLCD_write_character(*Copy_String++);
    }
}
void GLCD_Copy_Column_Control(u8* CPY_COL_CNTRL)
{
    *CPY_COL_CNTRL = column_control;
}
void GLCD_Write_Number(u16 copy_NUM)
{
    u8* NUM_STR[10];
    itoa(copy_NUM, NUM_STR, 10);
    GLCD_Write_String(NUM_STR);
}
void GLCD_Write_PWM_Specs(u8 Copy_frequency, u8 Copy_duty_cycle)
{
        GLCD_GOTO_XY(0, 0);
        GLCD_Write_String("Freq = ");
        GLCD_Write_Number(Copy_frequency);
//        GLCD_GOTO_XY(0, 64);
        GLCD_write_character(' ');
        GLCD_Write_String("Duty = ");
        GLCD_Write_Number(Copy_duty_cycle);
        _delay_ms(5000);
}
void GLCD_draw_PWM(u8 Copy_frequency, u8 Copy_duty_cycle)
{
//        if(Draw_index == 0)
//        {
//            if(PWM_Values[Draw_index] == 1)
//            {
//                for(iterate=0; iterate<(High_Time/25); iterate++)
//                {
//                    GLCD_Draw_TOP_PXL_H_Line();
//                }
//            }
//            else if(PWM_Values[Draw_index] == 0)
//            {
//                for(iterate=0; iterate<(LOW_Time/25); iterate++)
//                {
//                    GLCD_Draw_BTM_PXL_H_Line();
//                }
//            }
//        }
//
//
//        else if(Draw_index != 0)
//        {
//            if (PWM_Values[Draw_index] == 1)
//            {
//                GLCD_Draw_V_Line(5, 2);
//                for(iterate=0; iterate<(High_Time/25); iterate++)
//                {
//                    GLCD_Draw_TOP_PXL_H_Line();
//                }
//            }
//            else if (PWM_Values[Draw_index] == 0)
//            {
//                GLCD_Draw_V_Line(2, 5);
//                for(iterate=0; iterate<(LOW_Time/25); iterate++)
//                {
//                    GLCD_Draw_BTM_PXL_H_Line();
//                }
//            }
//        }
//        Draw_index++;
}
void GLCD_Draw_BTM_PWM_H_Line(u8 Copy_frequency, u8 Copy_duty_cycle)
{
    if (column_control <64)
    {
        DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_1, DIO_HIGH);
        DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_2, DIO_LOW);
    }
    else
    {
        DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_1, DIO_LOW);
        DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_2, DIO_HIGH);
    }

    GLCD_GOTO_Row(5);
    GLCD_Send_Data(0b10000000);
    column_control++;
    if (column_control == 128)
    {
        GLCD_Write_PWM_Specs(Copy_frequency, Copy_duty_cycle);
        GLCD_CLR();
    }
}
void GLCD_Draw_TOP_PWM_H_Line(u8 Copy_frequency, u8 Copy_duty_cycle)
{
    if (column_control <64)
    {
        DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_1, DIO_HIGH);
        DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_2, DIO_LOW);
    }
    else
    {
        DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_1, DIO_LOW);
        DIO_vidSetPinValue(CNTRL_PORT, CNTRL_PIN_Chip_Select_2, DIO_HIGH);
    }

    GLCD_GOTO_Row(2);
    GLCD_Send_Data(0b00000001);
    column_control++;
    if (column_control == 128)
    {
        GLCD_Write_PWM_Specs(Copy_frequency, Copy_duty_cycle);
        GLCD_CLR();
    }
}
void GLCD_write_column_cont()
{
    GLCD_Write_Number(column_control);
    GLCD_write_character(' ');
    GLCD_write_character(' ');
    GLCD_Write_Number(row_control);
    GLCD_write_character(' ');
    GLCD_write_character(' ');
    if(column_control == 128)
    {
        if(row_control == 7)
        {
            GLCD_CLR();
        }
        else
        {
            GLCD_GOTO_Next_Line();
        }
    }
}
