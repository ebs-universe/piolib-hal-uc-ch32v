

#include <application.h>
#include <irq_handlers.h>
#include <hal/uc/gpio.h>
#include "exti_handlers.h"


volatile uint8_t __exti_handler_inclusion;
void (* exti_gpio_handlers[MAX_EXTI_GPIO_LINES])(uint8_t) = {0};

static inline void exti_handler(uint8_t exti_line) { 
    if (exti_gpio_handlers[exti_line]) { 
        exti_gpio_handlers[exti_line](exti_line);
    }
}

/**
  * @brief This function handles EXTI lines 0-7 interrupts.
  * 
  */
void EXTI7_0_IRQHandler(void)
{
    uint32_t fr = EXTI->INTFR;
    for (uint32_t line = 0; line <= 7; ++line) {
        if (fr & (1 << line)) { 
            EXTI->INTFR |= (1 << line); 
            exti_handler(line);
        }
    }
}
