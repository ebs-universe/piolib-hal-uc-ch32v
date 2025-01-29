/* 
   Copyright 2024 Chintalagiri Shashank
   Copyright 2015 Chintalagiri Shashank, Quazar Technologies Pvt. Ltd.
   
   This file is part of
   Embedded bootstraps : Peripheral driver implementations : AVR
   
   This library is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. 
*/


#include "gpio_impl.h"


#if uC_GPIO_ENABLED

static void enable_gpio_clocks(void);
static void enable_gpio_exti_irqs(void);


static void enable_gpio_clocks(void){
    RCC->APB2PCENR |= RCC_APB2Periph_AFIO;
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOA;
    #ifdef RCC_APB2Periph_GPIOB
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOB;
    #endif
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOC;
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOD;
}

static void enable_gpio_exti_irqs(void){
    NVIC_SetPriority(EXTI7_0_IRQn, PRIO_GPIO7_0);
    NVIC_EnableIRQ(EXTI7_0_IRQn);
}

void gpio_init(void){
    enable_gpio_clocks();
    enable_gpio_exti_irqs();
    
    GPIOA->CFGLR = 0x88888888;
    GPIOC->CFGLR = 0x88888888;
    GPIOD->CFGLR = 0x88888888;
}

void gpio_conf_output(PORTSELECTOR_t port, PINSELECTOR_t pin)
{
    HAL_SFR_t * cfglr = (HAL_SFR_t *)(port + GPIO_OFS_CFGLR);
    *cfglr = (*cfglr & ~(15U << (pin * 4))) | (0b0010 << (pin * 4));
}       

void gpio_conf_input(PORTSELECTOR_t port, PINSELECTOR_t pin)
{
    HAL_SFR_t * cfglr = (HAL_SFR_t *)(port + GPIO_OFS_CFGLR);
    *cfglr = (*cfglr & ~(15U << (pin * 4))) | (0b0100 << (pin * 4));
}

void gpio_conf_analog(PORTSELECTOR_t port, PINSELECTOR_t pin) 
{
    HAL_SFR_t * cfglr = (HAL_SFR_t *)(port + GPIO_OFS_CFGLR);
    *cfglr = (*cfglr & ~(15U << (pin * 4)));
}

void gpio_conf_periph(PORTSELECTOR_t port, PINSELECTOR_t pin, uint8_t periph) 
{
    HAL_SFR_t * cfglr = (HAL_SFR_t *)(port + GPIO_OFS_CFGLR);
    uint8_t pincfg = 0x00;
    
    if (periph & 0x80) {
        switch (periph & 0x70) {
            case 0x00:
            case 0x10:
                pincfg |= 0b0010;
                break;
            case 0x20:
                pincfg |= 0b0001;
                break;
            case 0xC0:
                pincfg |= 0b0011;
                break;
            default:
                die();
                break;
        }
        if (periph & 0x01) {
            pincfg |= 0b1000;
        } else {
            pincfg |= 0b1100;
        }
    } else {
        switch (periph){
            case 0x00:
                pincfg |= 0b0100;
                break;
            case 0x01:
            case 0x02:
                pincfg |= 0b1000;
                break;
            default:
                die();
                break;
        }
    }

    *cfglr = (*cfglr & ~(15U << (pin * 4))) | (pincfg << (pin * 4));
}

void gpio_conf_pullup(PORTSELECTOR_t port, PINSELECTOR_t pin)
{   
    HAL_SFR_t * cfglr = (HAL_SFR_t *)(port + GPIO_OFS_CFGLR);
    *cfglr = (*cfglr & ~(15U << (pin * 4))) | (0b1000 << (pin * 4));
    HAL_SFR_t *outdr = (HAL_SFR_t *)(port + GPIO_OFS_OUTDR);
    *outdr |= (1U << pin);
}

void gpio_conf_pulldown(PORTSELECTOR_t port, PINSELECTOR_t pin)
{
    HAL_SFR_t * cfglr = (HAL_SFR_t *)(port + GPIO_OFS_CFGLR);
    *cfglr = (*cfglr & ~(15U << (pin * 4))) | (0b1000 << (pin * 4));
    HAL_SFR_t *outdr = (HAL_SFR_t *)(port + GPIO_OFS_OUTDR);
    *outdr &= ~(1U << pin);
}

void gpio_conf_hiz(PORTSELECTOR_t port, PINSELECTOR_t pin)
{
    HAL_SFR_t * cfglr = (HAL_SFR_t *)(port + GPIO_OFS_CFGLR);
    *cfglr = (*cfglr & ~(15U << (pin * 4))) | (0b0100 << (pin * 4));
    HAL_SFR_t *outdr = (HAL_SFR_t *)(port + GPIO_OFS_OUTDR);
    *outdr &= ~(1U << pin);
}

void gpio_conf_outmode_pp(PORTSELECTOR_t port, PINSELECTOR_t pin) 
{
    HAL_SFR_t * cfglr = (HAL_SFR_t *)(port + GPIO_OFS_CFGLR);
    *cfglr = (*cfglr & ~(15U << (pin * 4))) | (0b0010 << (pin * 4));
}

void gpio_conf_outmode_od(PORTSELECTOR_t port, PINSELECTOR_t pin) 
{
    HAL_SFR_t * cfglr = (HAL_SFR_t *)(port + GPIO_OFS_CFGLR);
    *cfglr = (*cfglr & ~(15U << (pin * 4))) | (0b0110 << (pin * 4));                
}

void gpio_conf_speed(PORTSELECTOR_t port, PINSELECTOR_t pin, uint8_t speed)
{
    HAL_SFR_t * cfglr = (HAL_SFR_t *)(port + GPIO_OFS_CFGLR);
    *cfglr = (*cfglr & ~(3U << (pin * 4))) | (speed << (pin * 4));                
}

void gpio_conf_interrupt(PORTSELECTOR_t port, PINSELECTOR_t pin, HAL_BASE_t edge)
{
    // Configure EXTI Source Port Selection
    uint8_t port_index = gpio_get_port_index(port);
    AFIO->EXTICR = (AFIO->EXTICR & ~(0b11 << (pin * 2))) | port_index << (pin *2);

    if (edge & GPIO_INT_EDGE_RISING) {
        EXTI->RTENR |= (1 << pin);
    } else {
        EXTI->RTENR &= ~(1 << pin);
    }
    if (edge & GPIO_INT_EDGE_FALLING) {
        EXTI->FTENR |= (1 << pin);
    } else {
        EXTI->FTENR &= ~(1 << pin);
    }
}

void gpio_conf_interrupt_handler(PORTSELECTOR_t port, PINSELECTOR_t pin, void (*handler)(uint8_t))
{
   exti_gpio_handlers[pin] = handler;
}


void gpio_interrupt_arm(PORTSELECTOR_t port, PINSELECTOR_t pin)
{
    EXTI->INTFR |= (1 << pin);
    EXTI->INTENR |= (1 << pin);
}

void gpio_interrupt_disarm(PORTSELECTOR_t port, PINSELECTOR_t pin)
{
    EXTI->INTENR &= ~(1 << pin);
}


#endif