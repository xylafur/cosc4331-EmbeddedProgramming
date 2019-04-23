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


uint16_t current_left_duty;
uint16_t current_right_duty;

uint8_t current_left_direction;
uint8_t current_right_direction;


uint8_t RAMP_COUNTER = 0;
uint8_t RAMP_MOD = 10;
uint8_t RAMP_VALUE = 1;


//THis is not working very well.. It is actually causing the jerking to be
//worse.. I wonder if it it because its being updated to frequently (every 10
//microseconds as we have it in the main loop, if we did it  as in interrupt
//triggered with about the same frequency as the motor if it would preform
//better)
void ramp_motors(uint16_t dest_left_duty, uint8_t dest_left_direction,
                 uint16_t dest_right_duty, uint8_t dest_right_direction){

    if(RAMP_COUNTER++ % RAMP_MOD != 0){
        return;
    }


    //If we're already going in the right direction, we just want to ramp
    //towards out goal duty
    if(dest_left_direction == current_left_direction){
        //if we're already there just break
        if(current_left_duty != dest_left_duty){
            current_left_duty = dest_left_duty > current_left_duty  ?
                                current_left_duty + RAMP_VALUE      :
                                current_left_duty - RAMP_VALUE;
        }

    }else{
        //Only switch directions if we have ramped all the way down
        //should never be less than 1, but just in case
        if(current_left_duty <= 1){
            current_left_duty = 1;
            current_left_direction = dest_left_direction;
        }else{
            current_left_duty--;
        }

    }

    if(dest_right_direction == current_right_direction){
        if(current_right_duty != dest_right_duty){
            current_right_duty = dest_right_duty > current_right_duty   ?
                                 current_right_duty + RAMP_VALUE        :
                                 current_right_duty - RAMP_VALUE;
        }

    }else{
        //Only switch directions if we have ramped all the way down
        //should never be less than 1, but just in case
        if(current_right_duty <= 1){
            current_right_duty = 1;
            current_right_direction = dest_right_direction;
        }else{
            current_right_duty--;
        }
    }
}




int main(){
    Clock_Init48MHz();
    LaunchPad_Init();

    Debug_FlashInit();

    DisableInterrupts();

    Motor_Init();
    //Initialize Line Sensor and register callback functions
    LineSensorIntInit();


    /*  Set up the enviornment based on the starting state
     */
    State_t *current_state = get_starting_state();
    //Set the inital duty based on the desired value of the left and right
    current_left_duty = current_state->left_duty;
    current_right_duty = current_state->right_duty;
    //Same thing but for the direction of the wheels
    current_left_direction = current_state->left_direction;
    current_right_direction = current_state->right_direction;



    //Everything should be all setup now, lets enable interrupts
    EnableInterrupts();

    uint8_t i = 1;

    uint8_t last_data_reading = 0;
    uint32_t position;
    uint8_t edge;

    while(1){
        //We need to change state
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


        //ramp_motors(current_state->left_duty, current_state->left_direction,
        //            current_state->right_duty, current_state->right_direction);
        current_left_duty = current_state->left_duty;
        current_left_direction = current_state->left_direction;
        current_right_duty = current_state->right_duty;
        current_right_direction = current_state->right_direction;

        set_color(current_state->color);

        Drive_Motors(current_left_duty, current_left_direction,
                     current_right_duty, current_right_direction);

        //buffer_write_flash_flush(current_state->this_state);
        Clock_Delay1us(10);
    }
}
