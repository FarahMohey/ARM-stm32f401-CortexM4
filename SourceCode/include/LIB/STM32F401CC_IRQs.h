/*
 ============================================================================
 Name        : STM32F401CC_IRQs.h
 Author      : Farah Mohey
// Description : Header file for Interrupt Requests in STM32F401CC (STM32F401CC_IRQs)
 Created	 : 27-Mar-24
 ============================================================================
*/

#ifndef MCAL_STM32F401CC_IRQS_H_
#define MCAL_STM32F401CC_IRQS_H_

/***************************** Types Declaration ********************************/
typedef enum
{
    WWDG=0,
    EXTI16_PVD,
    EXTI21_TAMP_STAMP,
    EXTI22_RTC_WKUP,
    FLASH,
    RCC,
    EXTI0,
    EXTI1,
    EXTI2,
    EXTI3,
    EXTI4,
    DMA1_Stream0,
    DMA1_Stream1,
    DMA1_Stream2,
    DMA1_Stream3,
    DMA1_Stream4,
    DMA1_Stream5,
    DMA1_Stream6,
    ADC,
    EXTI9_5 = 23,
    TIM1_BRK_TIM9,
    TIM1_UP_TIM10,
    TIM1_TRG_COM_TIM11,
    TIM1_CC,
    TIM2,
    TIM3,
    TIM4,
    I2C1_EV,
    I2C1_ER,
    I2C2_EV,
    I2C2_ER,
    SPI1,
    SPI2,
    USART1,
    USART2,
    EXTI15_10=40,
    EXTI17,
    EXTI18,
    DMA1_Stream7=47,
    SDIO=49,
    TIM5,
    SPI3,
    DMA2_Stream0=56,
    DMA2_Stream1,
    DMA2_Stream2,
    DMA2_Stream3,
    DMA2_Stream4,
    OTG_FS=67,
    DMA2_Stream5,
    DMA2_Stream6,
    DMA2_Stream7,
    USART6,
    I2C3_EV,
    I2C3_ER,
    FPU = 81,
    SPI4 = 84,
    _INT_Num
} IRQn_t;


#endif /* MCAL_STM32F401CC_IRQS_H_ */
