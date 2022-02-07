#ifndef MY_UTILITY_H_
#define MY_UTILITY_H_

#include "stm32f10x.h"
#include "stdint.h"

void enable_swd(void);

void rcc_deinit(void);

void set_sys_clock_72(void);

#define TIM_ENABLEIT(TIMx) SET_BIT((TIMx)->DIER, TIM_DIER_UIE)
#define TIM_ENABLE_COUNTER(TIMx) SET_BIT((TIMx)->CR1, TIM_CR1_CEN)
#define TIM_DISABLE_COUNTER(TIMx) CLEAR_BIT((TIMx)->CR1, TIM_CR1_CEN)
void tim2_init(uint16_t psc, uint16_t arr);
#endif // MY_UTILITY_H_
