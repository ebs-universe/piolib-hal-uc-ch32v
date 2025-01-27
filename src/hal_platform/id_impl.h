/* 
 Copyright 2024 Chintalagiri Shashank
 
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

#ifndef ID_IMPL_H
#define ID_IMPL_H

#include <hal/uc/id.h>

#if uC_ID_ENABLED

/**
 * CH32V ID is extracted from the 96-bit device ESIG. 
 * 
 * On the CH32V003, the third word does not seem to be used (0xffffffff),
 * so we simply take the first two words. However, it must be noted that
 * the silicon actually holds 3 words, and it is possible the last word
 * is used on other MCUs in the family or in future batches. 
 * 
 * Applications critically requiring device ID uniqueness should use
 * the full 12 byte device ID. An alternate implementation hashing 
 * the 96 bit ID into a 64 bit value may be discussed / considered in 
 * the future. 
 * 
 * This HAL implementation for ID provides the following controls: 
 *   - APP_ENABLE_ID    Non-zero (1) if this interface is enabled
 *   - APP_ID_TRIMFUNC  Method to use to trim the 12 byte ID to 8 bytes
 *      + 1             Truncation as described above
 *      + 2             Hash to a 8 byte value (not implemented)
 *  
 */

#define uC_ID_MAXLEN    12

#endif
#endif
