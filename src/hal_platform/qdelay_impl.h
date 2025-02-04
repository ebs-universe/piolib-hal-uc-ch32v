/* 
 Copyright 2025 Chintalagiri Shashank
 
 This file is part of
 Embedded bootstraps : Peripheral driver implementations : STM32
 
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

#ifndef QDELAY_IMPL_H
#define QDELAY_IMPL_H

#include <iomap.h>
#include <hal/uc/qdelay.h>

#if uC_QDELAY_ENABLED

#if uC_QDELAY_PROVIDER == QDELAY_PROVIDER_CPU

static inline void qdelay_us(uint16_t us) {

}

#elif uC_QDELAY_PROVIDER == QDELAY_PROVIDER_SYSTICK

#define OFS_SYSTICK_CTLR    0x00
#define OFS_SYSTICK_SR      0x04
#define OFS_SYSTICK_CNT     0x08
#define OFS_SYSTICK_CMP     0x10

extern qdelay_t _delay;

static inline void qdelay_us(uint16_t us) {
    qdelay_start(&_delay, us);
    while (!qdelay_check_done(&_delay)) { ; }    
}

#elif uC_QDELAY_PROVIDER == QDELAY_PROVIDER_TIMER

static inline void qdelay_us(uint16_t us) {

}

#elif uC_QDELAY_PROVIDER == QDELAY_PROVIDER_DWT

static inline void qdelay_us(uint16_t us) {

}

#endif

#endif
#endif