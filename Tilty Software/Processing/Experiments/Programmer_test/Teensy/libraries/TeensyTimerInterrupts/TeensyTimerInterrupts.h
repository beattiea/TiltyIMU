#include "wiring_private.h"
#include <inttypes.h>

void attachTimerInterrupt(uint8_t TIMER_NUM, void (*USER_FUNCTION)(void), long TIME_);
void detachTimerInterrupt(uint8_t TIMER_NUM);
void detachTimerInterrupts();
void detachTimerInterrupt(uint8_t TIMER_NUM);
void pit0_isr();
void pit1_isr();
void pit2_isr();