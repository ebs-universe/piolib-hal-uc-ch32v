/* 
   Copyright (c)
   (c) 2024 Chintalagiri Shashank
   (c) 2014 Walter Anderson
      
   This file is part of
   Embedded bootstraps : Peripheral driver implementations : AVR
 * 
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
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


// The code in this file is based on the arduino C++ Entropy library
// by Walter anderson. Use of uC_ENTROPY_SOURCE 2 triggers inclusion 
// of this file in the build, requiring the use of GPLv3 licensed 
// code.
//
// @see https://github.com/sylvandb/avr-hardware-random-number-generation


#include <stdint.h>
