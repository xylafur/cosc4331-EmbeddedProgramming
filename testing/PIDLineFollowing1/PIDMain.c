/*  Simplified BSD License (FreeBSD License)
    Copyright (c) 2017, James Richardson, All rights reserved.

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

#include <stdint.h>
#include "msp.h"

#include "../inc/LineInt.h"
#include "../inc/Clock.h"
#include "../inc/TExaS.h"
#include "../inc/LaunchPad.h"
#include "../inc/Reflectance.h"
#include "../inc/FlashDebug.h"
#include "../inc/Bump.h"

#include "../inc/CortexM.h"

#include "../inc/PID.h"


#include "../inc/Motor.h"

extern uint8_t LineSensorData;


uint16_t current_left_duty;
uint16_t current_right_duty;

uint8_t current_left_direction;
uint8_t current_right_direction;

extern float Kp;

void PIDProgram(void){
    uint8_t bump = 0;
    while(1){
        bump = Bump_Read();
        set_color(0x1);

        if(bump){
            if(bump&0x2){
                break;

            }else if(bump&0x8){
                set_color(0x2);

                increaseKp();
            }else if(bump & 0x10){
                set_color(0x3);

                decreaseKp();
            }else if(bump & 0x20){
                write_flash_force_flush((uint16_t)((int)Kp));
            }

            Clock_Delay1ms(50);


        }
    }
    set_color(0x0);
}

int main(){
    Clock_Init48MHz();
    LaunchPad_Init();

    Debug_FlashInit();

    DisableInterrupts();

    Motor_Init();
    PID_init();

    Bump_Init();
    //Initialize Line Sensor and register callback functions
    LineSensorIntInit();

    //Everything should be all setup now, lets enable interrupts
    EnableInterrupts();

    uint8_t bump = 0;
    int32_t error;
    uint32_t lr_motor = 0;
    while(1){
        bump = Bump_Read();

        if(bump){
            if(bump&0x1){
                Motor_Stop();
                PIDProgram();
            }
        }

        long sr = StartCritical();
        /*
        buffer_write_flash_flush(0x3fab);
        buffer_write_flash_flush(0xdad5);
        buffer_write_flash_flush((uint16_t)LineSensorData);
        */

        /*
        buffer_write_flash_flush(0xb00b);
        buffer_write_flash_flush(0xF00F);
        buffer_write_flash_flush((uint16_t)((error&0xFF00)>>16));
        buffer_write_flash_flush((uint16_t)((error&0xFF)));
        */

        //error = sensor_to_error(LineSensorData);
        sensor_to_error_buffer(LineSensorData);
        lr_motor = compute_actuation(error);
        Drive_Motors((uint16_t)(lr_motor&0xFFFF), 1,
                     (uint16_t)((lr_motor&0xFFFF0000)>>16), 1);
        EndCritical(sr);

        /*
        buffer_write_flash_flush(0xffff);
        buffer_write_flash_flush(0x1111);
        buffer_write_flash_flush((uint16_t)((lr_motor&0xFFFF0000)>>16));
        buffer_write_flash_flush((uint16_t)((lr_motor&0xFFFF)));
        */

        Clock_Delay1us(5);
    }
}
