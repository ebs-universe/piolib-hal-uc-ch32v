/* 
   Copyright (c)
     (c) 2024 Chintalagiri Shashank
     (c) 2015-2016 Chintalagiri Shashank, Quazar Technologies Pvt. Ltd.
   
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


#include "core_impl.h"

#if uC_CORE_ENABLED


/**
 * On this platform, most of the core initialization is left to 
 * ch32v003fun.h, and configured by funconfig.h. As a result, only
 * core_init() needs to be called, and this does what the power, 
 * clock and systick functions do other EBS HAL implementations. 
 * The other functions are noops.
 */
void core_init(void) {
    SystemInit();
    Delay_Ms(100);
    RCC->APB1PCENR |= RCC_APB1Periph_PWR;
    global_interrupt_enable();
}

/**
* See core_init()
*/
void power_set_full(void){
    ;
}

/**
* See core_init()
*/

void clock_set_prescaler(uint16_t ps){
    ;    
}

/**
* See core_init()
*/
__weak void clock_set_default(void){
    ;
}

#endif

#if uC_WDT_ENABLED == 1

/**
* @brief Initializes the Watchdog timer. Nothing to do here.
* 
*/
void watchdog_init(void) {
    ;
}


/**
* @brief Initializes the Watchdog timer. Nothing to do here.
* 
* Presently just sets the default values. This should be changed to 
* accept some parameter, perhaps interval, and set accordingly. 
* 
* Default should be an approximately 2 sec timeout.
*/
void watchdog_start(void){
    ;
}

void watchdog_hold(void){
    ;
}

#endif

#if uC_SYSTICK_TIMER_ENABLED

void core_systick_start(void) {
    NVIC_SetPriority(SysTicK_IRQn, PRIO_SYSTICK);
    NVIC_EnableIRQ(SysTicK_IRQn);
    SysTick->CTLR = 0;
    SysTick->CTLR = (SYSTICK_CTLR_STE | SYSTICK_CTLR_STIE | SYSTICK_CTLR_STRE);
    SysTick->CMP = ((uint32_t) CLOCKTREE_SYSTICK_CLK / 1000U) - 1U;
}

#endif