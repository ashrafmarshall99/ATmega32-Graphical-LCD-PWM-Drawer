#ifndef GLCD_H_INCLUDED
#define GLCD_H_INCLUDED

void GLCD_INIT(void);
void GLCD_Send_Data(u8 data);
void GLCD_Send_Command(u8 command);
void GLCD_SET_Start_Line(u8 line);
void GLCD_GOTO_Column(u8 Column);
void GLCD_GOTO_Row(u8 row);
void GLCD_GOTO_XY(u8 Row, u8 Column);
void GLCD_CLR_Line(u8 Line);
void GLCD_CLR(void);
void GLCD_Draw_point(void);
void GLCD_Draw_V_Line(u8 Row, u8 Row_Destination);
void GLCD_Draw_TOP_PXL_H_Line(void);
void GLCD_Draw_BTM_PXL_H_Line(void);
void GLCD_GOTO_Next_Line(void);
void GLCD_write_character(u8 Copy_character);
void GLCD_Write_String(u8 *Copy_String);
void GLCD_Copy_Column_Control(u8* CPY_COL_CNTRL);
void GLCD_Write_Number(u16 copy_NUM);
void GLCD_Write_PWM_Specs(u8 Copy_frequency, u8 Copy_duty_cycle);
void GLCD_draw_PWM(u8 Copy_frequency, u8 Copy_duty_cycle);
void GLCD_Draw_BTM_PWM_H_Line(u8 Copy_frequency, u8 Copy_duty_cycle);
void GLCD_Draw_TOP_PWM_H_Line(u8 Copy_frequency, u8 Copy_duty_cycle);

#endif // GLCD_H_INCLUDED
