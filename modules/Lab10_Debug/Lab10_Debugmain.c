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

#include "msp.h"
#include "string.h"
#include "../inc/PinManip.h"
#include "../inc/Bump.h"
#include "../inc/Reflectance.h"
#include "../inc/Clock.h"
#include "../inc/SysTickInts.h"
#include "../inc/cpu.h"
#include "../inc/CortexM.h"
#include "../inc/LaunchPad.h"
#include "../inc/FlashDebug.h"

uint8_t sensor_reading = 0;

uint8_t interrupt_counter = 0;
void SysTick_Handler(void){ // every 1ms
    if(interrupt_counter % 10 == 0){
        Reflectance_Start();
        buffer_write_flash_flush(0xdead);
        buffer_write_flash_flush(0xdbeef);

    }else if(interrupt_counter % 10 == 1){
        sensor_reading = Reflectance_End();
        buffer_write_flash_flush((uint16_t)sensor_reading);


    }
    interrupt_counter++;
}

void LineSensorInterrupts(void){
    Clock_Init48MHz();
    Debug_FlashInit();
    Bump_Init();
    Reflectance_Init();
    LaunchPad_Init();

    //Have the timer trigger an interrupt every ms
    SysTick_Init(CYCLES_PER_mS, 0);
    EnableInterrupts();

    write_flash_force_flush(0xcafe);

    while(1){
        set_color(sensor_reading);
    }
}

int BumpSensorVerification(void){
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
    switch(ii){
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

int main(){
    //BumpSensorVerification();
    LineSensorInterrupts();
}
