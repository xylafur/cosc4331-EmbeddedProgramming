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

#include "../inc/CortexM.h"

//Just a temp hack until I get it passed in as a compile time flag
#define LINEFOLLOWING2
#include "../inc/FSM.h"
#undef LINEFOLLOWING2


#include "../inc/Motor.h"

extern uint8_t LineSensorData;
extern State_t fsm [NUM_STATES];
extern enum State_e TRANSITION_MAPPING [NUM_EDGES];

int main(){
    Clock_Init48MHz();
    LaunchPad_Init();

    Debug_FlashInit();

    DisableInterrupts();

    Motor_Init();
    //Initialize Line Sensor and register callback functions
    LineSensorIntInit();

    State_t *current_state = get_starting_state();

    //Enable Interrupts
    EnableInterrupts();

    uint8_t i = 1;

    uint8_t last_data_reading = 0;
    uint32_t position;
    uint8_t edge;

    while(1){
        if(last_data_reading != LineSensorData){
            last_data_reading = LineSensorData;

            position = Reflectance_Position(LineSensorData);
            edge = get_edge(position);

            if(edge == OFF_EDGE){
                current_state = &fsm[current_state->off_edge_transition];
            }else{
                current_state = &fsm[TRANSITION_MAPPING[edge]];
            }


        }
        set_color(current_state->color);

        Drive_Motors(current_state->left_duty, current_state->left_direction,
                     current_state->right_duty, current_state->right_direction);

        //buffer_write_flash_flush(current_state->this_state);
        Clock_Delay1us(10);
        


    }
}
