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


void core_init(void) {
    NVIC_PriorityGroupConfig(uC_NVIC_PRIORITY_CONF);
    SystemInit();
    SystemCoreClockUpdate();
    // Delay_Init();
}

void power_set_full(void){
    ;
}

void clock_set_prescaler(uint16_t ps){
    ;    
}

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

#define SYSTICK_SR_CNTIF    (1<<0)
#define SYSTICK_CTLR_STE    (1<<0)
#define SYSTICK_CTLR_STIE   (1<<1)
#define SYSTICK_CTLR_STCLK  (1<<2)
#define SYSTICK_CTLR_STRE   (1<<3)
#define SYSTICK_CTLR_SWIE   (1<<31)

void core_systick_start(void) {
    NVIC_SetPriority(SysTicK_IRQn, PRIO_SYSTICK);
    NVIC_EnableIRQ(SysTicK_IRQn);
    SysTick->CTLR = 0;
    SysTick->CTLR = (SYSTICK_CTLR_STE | SYSTICK_CTLR_STIE | SYSTICK_CTLR_STRE);
    SysTick->CMP = ((uint32_t) CLOCKTREE_SYSTICK_CLK / 1000U) - 1U;
}

#endif