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

#ifndef GPIO_IMPL_H
#define GPIO_IMPL_H

#include <hal/uc/gpio.h>
#include "exti.h"
#include "exti_handlers.h"

#if uC_GPIO_ENABLED

#include "_gpio/registers.h"
#include "_gpio/constants.h"

static inline void gpio_set_output_high(
    PORTSELECTOR_t port, PINSELECTOR_t pin)
{
    *(HAL_SFR_t *)(port + GPIO_OFS_OUTDR) |= (1 << pin);
}

static inline void gpio_set_output_low(
    PORTSELECTOR_t port, PINSELECTOR_t pin)
{
    *(HAL_SFR_t *)(port + GPIO_OFS_OUTDR) &= ~(1 << pin);
}

static inline void gpio_set_output_toggle(
    PORTSELECTOR_t port, PINSELECTOR_t pin)
{
    *(HAL_SFR_t *)(port + GPIO_OFS_OUTDR) ^= (1 << pin);
}

static inline HAL_BASE_t gpio_get_input(
    PORTSELECTOR_t port, PINSELECTOR_t pin)
{
    return (*(HAL_SFR_t *)(port + GPIO_OFS_INDR) & (1 << pin)) ? 1 : 0;
}

static inline uint8_t gpio_get_port_index(PORTSELECTOR_t port) {
   return (uint8_t)((port - GPIOA_BASE) / (0x0400));
}

#endif
#endif
