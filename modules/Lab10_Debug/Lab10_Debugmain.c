// Lab10_Debugmain.c
// Runs on MSP432
// Student version to Debug lab
// Daniel and Jonathan Valvano
// July 2, 2017
// Interrupt interface for QTR-8RC reflectance sensor array
// Pololu part number 961.
// Debugging dump, and Flash black box recorder

/* This example accompanies the books
   "Embedded Systems: Introduction to the MSP432 Microcontroller",
       ISBN: 978-1512185676, Jonathan Valvano, copyright (c) 2017
   "Embedded Systems: Real-Time Interfacing to the MSP432 Microcontroller",
       ISBN: 978-1514676585, Jonathan Valvano, copyright (c) 2017
   "Embedded Systems: Real-Time Operating Systems for ARM Cortex-M Microcontrollers",
       ISBN: 978-1466468863, , Jonathan Valvano, copyright (c) 2017
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/

Simplified BSD License (FreeBSD License)
Copyright (c) 2017, Jonathan Valvano, All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are
those of the authors and should not be interpreted as representing official
policies, either expressed or implied, of the FreeBSD Project.
*/
// Negative logic bump sensors
// P8.7 Bump5
// P8.6 Bump4
// P8.5 Bump3
// P8.4 Bump2
// P8.3 Bump1
// P8.0 Bump0

// reflectance LED illuminate connected to P5.3
// reflectance sensor 1 connected to P7.0 (robot's right, robot off road to left)
// reflectance sensor 2 connected to P7.1
// reflectance sensor 3 connected to P7.2
// reflectance sensor 4 connected to P7.3 center
// reflectance sensor 5 connected to P7.4 center
// reflectance sensor 6 connected to P7.5
// reflectance sensor 7 connected to P7.6
// reflectance sensor 8 connected to P7.7 (robot's left, robot off road to right)

#include "msp.h"
#include "string.h"
#include "../inc/PinManip.h"
#include "../inc/Bump.h"
#include "../inc/Reflectance.h"
#include "../inc/Clock.h"
#include "../inc/SysTickInts.h"
#include "../inc/CortexM.h"
#include "../inc/LaunchPad.h"
#include "../inc/FlashProgram.h"

#define NUM_RAM_DUMP_ENTRIES 256

static uint16_t ram_dump_data [NUM_RAM_DUMP_ENTRIES];
static uint8_t ram_dump_index;

void Debug_Init(void){
    memset(ram_dump_data, 0, NUM_RAM_DUMP_ENTRIES * sizeof(uint16_t));;
    ram_dump_index = 0;

}
void Debug_Dump(uint8_t bump, uint8_t line){
  // write this as part of Lab 10
  ram_dump_data[ram_dump_index++] = (bump << 8) | line;

}
#define FLASH_TOP 0x00020000
#define FLASH_BOT 0x0003FFFF

#define FLASH_BLOCK_SIZE 512
#define _4K (4 * 1024)

static void *flash_ptr;

void Debug_FlashInit(void){ 
    //we can erase flash as 1 4k block at a time
    
    for(flash_ptr = (void*)FLASH_TOP ; flash_ptr < FLASH_BOT; flash_ptr += _4K){
        Flash_Erase((uint32_t)flash_ptr);
    }
    flash_ptr = (void*)FLASH_TOP;
}

#define BYTES_PER_BIT(n) (n / 8)

void Debug_FlashRecord(uint16_t *pt){
    //memcpy(flash_ptr, (void*)pt, FLASH_BLOCK_SIZE);
    uint8_t ii;
    //go through and write 32 bytes at a time
    for(ii=0; ii<(FLASH_BLOCK_SIZE/BYTES_PER_BIT(32)); ii++){
        Flash_Write(flash_ptr, ((uint32_t*)pt)[ii]);
        flash_ptr += BYTES_PER_BIT(32);
    }
    if(flash_ptr >= FLASH_BOT){
        flash_ptr = FLASH_TOP;
    }
}

// Driver test
uint16_t Buffer2[FLASH_BLOCK_SIZE] = {
        0x614a, 0x656d, 0x2073, 0x6e61, 0x2064, 0x6f47, 0x7a6e, 0x6c61,
        0x206f, 0x6577, 0x6572, 0x6820, 0x7265, 0x2e65, 0x2e2e, 0x4820,
        0x776f, 0x7327, 0x6920, 0x2074, 0x6f67, 0x6e69, 0x3f67, 0x570a,
        0x2065, 0x6964, 0x6e64, 0x7427, 0x7020, 0x7475, 0x7320, 0x6e65,
        0x6f73, 0x2072, 0x6572, 0x6461, 0x6e69, 0x7367, 0x6920, 0x746e,
        0x206f, 0x756f, 0x2072, 0x6c66, 0x7361, 0x2c68, 0x6a20, 0x7375,
        0x2074, 0x6874, 0x7369, 0x7020, 0x7475, 0x7420, 0x6968, 0x2073,
        0x7564, 0x626d, 0x6e20, 0x746f, 0x2065, 0x6f74, 0x730a, 0x6565,
        0x6920, 0x2066, 0x6f79, 0x2075, 0x7567, 0x7379, 0x7720, 0x756f,
        0x646c, 0x6e20, 0x746f, 0x6369, 0x2065, 0x6874, 0x2065, 0x6964,
        0x6666, 0x7265, 0x6e65, 0x6563, 0x2e2e, 0x202e, 0x6669, 0x7920,
        0x756f, 0x7227, 0x2065, 0x6572, 0x6461, 0x6e69, 0x2067, 0x6874,
        0x7369, 0x7920, 0x756f, 0x6420, 0x6469, 0x280a, 0x726f, 0x7920,
        0x756f, 0x6a20, 0x7375, 0x2074, 0x6f6c, 0x6461, 0x6465, 0x7420,
        0x6568, 0x6820, 0x7865, 0x6620, 0x6c69, 0x2065, 0x6e69, 0x6f74,
        0x6120, 0x7420, 0x7865, 0x2074, 0x6465, 0x7469, 0x726f, 0x6620,
        0x726f, 0x7320, 0x6d6f, 0x2065, 0x6572, 0x7361, 0x6e6f, 0x2e2e,
        0x292e, 0x0a21, 0x6854, 0x7369, 0x7720, 0x7361, 0x7420, 0x6b61,
        0x6e65, 0x6620, 0x6f72, 0x206d, 0x756f, 0x2072, 0x6c66, 0x7361,
        0x2068, 0x6874, 0x756f, 0x6867, 0x202c, 0x7469, 0x6920, 0x2073,
        0x6f77, 0x6b72, 0x6e69, 0x0a67
    };

uint16_t Buffer[FLASH_BLOCK_SIZE];
uint16_t buffer_pos = 0;

uint32_t buffer_write_flash_flush(uint16_t data){
    if(buffer_pos == 0){
        Buffer[buffer_pos++] = 0xdead;
        Buffer[buffer_pos++] = 0xbeef;
    }

    Buffer[buffer_pos++] = data;
    if(buffer_pos > FLASH_BLOCK_SIZE){
        Debug_FlashRecord(Buffer);
        buffer_pos = 0;
    }
}
void SysTick_Handler(void){ // every 1ms
  // write this as part of Lab 10
}

int main(void){
  // write this as part of Lab 10
  uint8_t data;

  Clock_Init48MHz();
  Bump_Init();
  LaunchPad_Init();
  Debug_FlashInit();

  uint8_t ii = 0, jj = 0;
  uint8_t small_buf = 0;
  while(1){
    ii = Bump_Read();
    switch((~ii) & 0x3f){
    case 0x1:
        set_color(RED);
        break;
    case 0x2:
        set_color(BLUE);
        break;
    case 0x4:
        set_color(GREEN);
        break;
    case 0x8:
        set_color(YELLOW);
        break;
    case 0x10:
        set_color(SKYBLUE);
        break;
    case 0x20:
        set_color(WHITE);
        break;
    default:
        set_color(DARK);
        break;
    }

    if(jj & 0x1){
        small_buf = ii;
    }else{
        //write sensor readings to flash
        buffer_write_flash_flush((uint16_t)((small_buf << 8) | ii));
    }

    jj++;
  }

}

int Program10_1(void){
//int main(void){
  uint8_t data=0;
  Clock_Init48MHz();
  Debug_Init();
  LaunchPad_Init();
  while(1){
    P1->OUT |= 0x01;
    Debug_Dump(data,data+1);// linear sequence
    P1->OUT &= ~0x01;
    data=data+2;
  }
}




int Program10_2(void){
//int main(){

  uint16_t i;

  Clock_Init48MHz();
  LaunchPad_Init(); // built-in switches and LEDs

  set_color(GREEN);

  for(i=0;i<FLASH_BLOCK_SIZE;i++){
    Buffer[i] = (i<<8)+(255-i); // test data
  }
  Buffer[0] = 0xDEAD;
  Buffer[1] = 0xBEEF;

  set_color(RED);

  Debug_FlashInit();
  for(i=0; i<32; i++){
    Debug_FlashRecord(Buffer);
  }

  Debug_FlashRecord(Buffer2);

  for(i=0; i<32; i++){
    Debug_FlashRecord(Buffer);
  }
  set_color(BLUE);

  /*
  for(i=0;i<SIZE;i++){
    Buffer[i] = (i<<8)+(255-i); // test data
  }
  i = 0;
  while(1){
    P1->OUT |= 0x01;
    Debug_FlashInit();
    P1->OUT &= ~0x01;
    P2->OUT |= 0x01;
    Debug_FlashRecord(Buffer); // 114us
    P2->OUT &= ~0x01;
    i++;
  }
  */
}


int Program10_3(void){ uint16_t i;
  Clock_Init48MHz();
  LaunchPad_Init(); // built-in switches and LEDs
  for(i=0;i<FLASH_BLOCK_SIZE;i++){
    Buffer[i] = (i<<8)+(255-i); // test data
  }
  P1->OUT |= 0x01;
  Debug_FlashInit();
  P1->OUT &= ~0x01;
  i = 0;
  while(1){
    P2->OUT |= 0x01;
    Debug_FlashRecord(Buffer);
    P2->OUT &= ~0x01;
    i++;
  }
}

/*
uint8_t Buffer[1000];
uint32_t I=0;
uint8_t *pt;
void DumpI(uint8_t x){
  if(I<1000){
    Buffer[I]=x;
    I++;
  }
}
void DumpPt(uint8_t x){
  if(pt<&Buffer[1000]){
    *pt=x;
    pt++;
  }
}
void Activity(void){
  DumpI(5);
  DumpI(6);
  pt = Buffer;
  DumpPt(7);
  DumpPt(8);

}
*/
