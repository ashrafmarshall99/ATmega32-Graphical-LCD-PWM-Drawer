#ifndef TIMER1_H_INCLUDED
#define TIMER1_H_INCLUDED

void timer1_init(void);
void Start_timer1(void);
void timer1_set_pwm_wave_generationn(u16 pulse_width);
void stop_timer1(void);
void Timer1_InputCapt_enable(void);

#endif // TIMER1_H_INCLUDED
