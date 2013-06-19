#include "TeensyTimerInterrupts.h"
#include <inttypes.h>

void (*pit0_function)(void);
void (*pit1_function)(void);
void (*pit2_function)(void);
void (*pit3_function)(void);

void attachTimerInterrupt(uint8_t TIMER_NUM, void (*USER_FUNCTION)(void), long TIME_)
{
	//	Enable interrupt timers
	SIM_SCGC6 |= SIM_SCGC6_PIT;
	PIT_MCR = 0x00;
	
	switch (TIMER_NUM) {
	case 0:
        NVIC_ENABLE_IRQ(IRQ_PIT_CH0);
		PIT_LDVAL0 = TIME_ * 50000;
		PIT_TCTRL0 = 0x1;
		PIT_TCTRL0 |= 0x2;
		PIT_TFLG0 |= 1;
		pit0_function = USER_FUNCTION;
	break;
	case 1:
        NVIC_ENABLE_IRQ(IRQ_PIT_CH1);
		PIT_LDVAL1 = TIME_ * 50000;
		PIT_TCTRL1 = 0x1;
		PIT_TCTRL1 |= 0x2;
		PIT_TFLG1 |= 1;
        pit1_function = USER_FUNCTION;
	break;
	case 2:
		NVIC_ENABLE_IRQ(IRQ_PIT_CH2);
		PIT_LDVAL2 = TIME_ * 50000;
		PIT_TCTRL2 = 0x1;
		PIT_TCTRL2 |= 0x2;
		PIT_TFLG2 |= 1;
        pit2_function = USER_FUNCTION;
	break;
	}
}

void detachTimerInterrupts()
{
	PIT_TCTRL0 = 0x0;
	PIT_TCTRL1 = 0x0;
	PIT_TCTRL2 = 0x0;
}

void detachTimerInterrupt(uint8_t TIMER_NUM)
{
	switch (TIMER_NUM) {
	case 0:
		PIT_TCTRL0 = 0x0;
	break;
	case 1:
		PIT_TCTRL1 = 0x0;
	break;
	case 2:
		PIT_TCTRL2 = 0x0;
	break;
	}
}

void pit0_isr(void)
{
	pit0_function();
	PIT_TFLG0 = 1;
}

void pit1_isr(void)
{
	pit1_function();
	PIT_TFLG1 = 1;
}

void pit2_isr(void)
{
	pit2_function();
	PIT_TFLG2 = 1;
}