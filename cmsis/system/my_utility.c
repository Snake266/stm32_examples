/*
 * This file I use to write function that setup periphery.
 */
#define STM32F10X_MD
#include "my_utility.h"

/*
 * In this file I will use standart macros like SET_BIT, READ_BIT
 * because I want this code to be as clear as possible.
 * I have opinion that bit operation make hard to read.
 */

/*
 * This function enable SWD, usually this function should be used
 * in every firmware in order to keep MCU "flashable"
 */
void enable_swd(void) {
    SET_BIT(RCC->APB2ENR,RCC_APB2ENR_AFIOEN);
    CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_SWJ_CFG);
    SET_BIT(AFIO->MAPR, AFIO_MAPR_SWJ_CFG_JTAGDISABLE);
}


/*
 * This function turns off HSE, PLL and all RCC interupts. After this function
 * HSI is used as system clock
 */
void rcc_deinit(void) {
    /* Enable HSI */
    SET_BIT(RCC->CR, RCC_CR_HSION);
    /* Wait until it ready */
    while(READ_BIT(RCC->CR, RCC_CR_HSIRDY) != RCC_CR_HSIRDY);

    /* Clear CFG register */
    CLEAR_REG(RCC->CFGR);

    /* Wait until it reset and turns into HSI mode (00) */
    while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RESET);

    /* Switch off PLL, we doesn't need it */
    CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
    /* Make sure that PLL is switched off */
    while(READ_BIT(RCC->CR, RCC_CR_PLLRDY) == RCC_CR_PLLRDY);

    /* switch off CSS (in deinit mode we want to use only HSI) and switch off HSE*/
    CLEAR_BIT(RCC->CR, RCC_CR_CSSON | RCC_CR_HSEON);
    /* Make sure that HSE is switched off */
    while(READ_BIT(RCC->CR, RCC_CR_HSERDY) == RCC_CR_HSERDY);

    /* We don't need to bypass HSE */
    CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);

    /* Remove all CSR flags */
    SET_BIT(RCC->CSR, RCC_CSR_RMVF);
}


/*
 * This function is setup system clock to 72 MHz
 */
void set_sys_clock_72(void) {
    /* To reach 72 Mhz we should use HSE, so we turn on HSE */
    SET_BIT(RCC->CR, RCC_CR_HSEON);
    /* make sure that HSE is enabled */
    while(READ_BIT(RCC->CR, RCC_CR_HSERDY) != RCC_CR_HSERDY);

    /* Enable the Prefetch Buffer, this needed to set HPRE other than 1 */
    CLEAR_BIT(FLASH->ACR, FLASH_ACR_PRFTBE);
    SET_BIT(FLASH->ACR, FLASH_ACR_PRFTBE);
    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_2);

    /* Now set the needed dividers and multipliers */
    /* Set AHB prescaler is set to 1 */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_CFGR_HPRE_DIV1);

    /* Set APB low-speed prescaler to be divided by 2, because APB1 should not exceed 36 MHz */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_CFGR_PPRE1_DIV2);

    /* Set APB high-speed prescaler to be not divided */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, RCC_CFGR_PPRE2_DIV1);

    /* Set HSE as input for PLL */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PLLSRC, RCC_CFGR_PLLSRC_HSE);

    /* Set PLL multipluier */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PLLMULL, RCC_CFGR_PLLMULL9);

    /* To be sure that HSE is not divided by 2 */
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_PLLXTPRE);

    /* Turn on PLL */
    SET_BIT(RCC->CR, RCC_CR_PLLON);
    while(READ_BIT(RCC->CR, RCC_CR_PLLRDY) != RCC_CR_PLLRDY);

    /* Select PLL as system clock */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
    while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}

/*
 * Setup tim2
 * @param psc psc is prescale for TIM2
 *
 * @param arr is ARR (auto-reload register) for TIM2
 */
void tim2_init(uint16_t psc, uint16_t arr) {
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);
    NVIC_EnableIRQ(TIM2_IRQn);
    WRITE_REG(TIM2->PSC, psc);
    WRITE_REG(TIM2->ARR, arr);
}
