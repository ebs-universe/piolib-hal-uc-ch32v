/* 
   Copyright (c)
     (c) 2025 Chintalagiri Shashank
   
   This file is part of
   Embedded bootstraps : Peripheral driver implementations : CH32V
   
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


#include "id_impl.h"
#include <string.h>

#if uC_ID_ENABLED 

DeviceID_t device_id = {0};


void id_init(void){
    #if uC_ID_TRIMFUNC == 1
        device_id.native[0] = *(uint32_t *)0x1FFFF7E8;
	      device_id.native[1] = *(uint32_t *)0x1FFFF7EC;
    #endif
}

uint8_t id_read(uint8_t len, void * buffer){
    if (len == uC_ID_LENGTH) {
        memcpy(buffer, (void *)0x1FFFF7E8, 8);
        return 8;
    } 
    
    if (len > uC_ID_MAXLEN) len = uC_ID_MAXLEN;
    memcpy(buffer, (void *)0x1FFFF7E8, len);
    return len; 
}

uint8_t id_write(uint8_t len, void * content){
    return 0;
}

#endif