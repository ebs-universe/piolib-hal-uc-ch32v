/* 
   Copyright (c)
   (c) 2024 Chintalagiri Shashank
      
   This file is part of
   Embedded bootstraps : Peripheral driver implementations : AVR
 * 
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 */

/**
 * @file entropy_impl.h
 * @brief AVR Entropy Implementation Notes
 *
 * Entropy accumulation for AVR can potentially be done using the following
 * sources :
 * 
 *   - ADC Conversion of unused ADC pin. 
 *   - Clock variation between MCLK and WDTCLK.
 * 
 * This interface provides two implementations for the developer to choose 
 * from. This can be done by setting uC_ENTROPY_SOURCE in application.h. 
 * 
 * A value of 1 uses the ADC in a simple approach, though there are questions 
 * about the randomness this approach will provide. This is not yet implemented. 
 * 
 * A value of 2 uses the WDT and clock jitter. Note that this approach takes a 
 * lot longer, but might provide higher quality randomness. 
 * 
 */


#ifndef ENTROPY_IMPL_H
#define ENTROPY_IMPL_H

#include <application.h>


#endif
