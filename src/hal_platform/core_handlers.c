/* 
   Copyright (c)
   (c) 2024 Chintalagiri Shashank
      
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

#include "core_handlers.h"
#include <irq_handlers.h>

volatile uint8_t __core_handler_inclusion;


#if uC_SYSTICK_TIMER_ENABLED

/**
  * @brief This function handles System Tick Timer Interrupts.
  */
void SysTick_Handler(void) {
    // HAL IncTick is only needed if we're using HAL timing primitives 
    //  (directly or indirectly). Ideally, most of those uses should
    //  be modified to use the considerably faster EBS systick.
    //  
    // Switching the STM32 HAL to use the EBS systick can probably be 
    //  done using the weak functions it provides.   
    //  
    // For now, keeping both running.  
    SysTick->SR &= ~SYSTICK_SR_CNTIF;
    #if APP_USE_CORE_SYSTICK
        #ifdef uC_SYSTICK_TIMER_IRQH
            uC_SYSTICK_TIMER_IRQH();
        #endif
    #endif
}

#endif
