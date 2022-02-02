#ifndef STM32F10X_MD
#define STM32F10X_MD
#endif

#include "stm32f10x.h"
#define GPIO_Pin_13                ((uint16_t)0x2000)  /*!< Pin 13 selected */

void dummy_loop(uint32_t count) {
    while(--count);
}

int main(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // IO PORTC clock enable
    GPIOC->CRH &= ~(uint32_t)(0xf << 20);
    GPIOC->CRH |= (uint32_t)(0x2 << 20);
    while(1) {
        GPIOC->BSRR = GPIO_Pin_13;
        dummy_loop(6000000);
        GPIOC->BRR = GPIO_Pin_13;
        dummy_loop(6000000);
    }
    return 0;
}
