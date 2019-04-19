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

#include "../inc/Reflectance.h"

/*  This way even though I will be changing the State Machine significantly, my
 *  old implementation (which works, just not that well and doesn't use
 *  interrupts) can still be compiled
 */
#ifdef LineFollowing1

#include "../inc/MotorSimple.h"
#include "../inc/FSM.h"

#define OffLeft &fsm[0]
#define FarLeft &fsm[1]
#define Left &fsm[2]
#define Center1 &fsm[3]
#define Center2 &fsm[4]
#define Right &fsm[5]
#define FarRight &fsm[6]
#define OffRight &fsm[7]

#define GET_TRANS(center, zero) {zero, FarLeft, Left, center, Right,  \
                                 FarRight}

State_t fsm [NUM_STATES] = {
    //This State    Output  Delay Time  Drive Time  Edges
    {StateOffLeft,  PINK,   SLEEPTIME,  100,         GET_TRANS(Center1, OffLeft)},
    {StateFarLeft,  RED,    SLEEPTIME,  100,         GET_TRANS(Center1, OffLeft)},

    {StateLeft,     YELLOW, SLEEPTIME,  100,         GET_TRANS(Center1, OffLeft)},

    {StateCenter1,  WHITE,  SLEEPTIME,  100,         GET_TRANS(Center2, OffLeft)},
    {StateCenter2,  DARK,   SLEEPTIME,  100,         GET_TRANS(Center1, OffRight)},

    {StateRight,    GREEN,  SLEEPTIME,  100,         GET_TRANS(Center2, OffRight)},

    {StateFarRight, BLUE,   SLEEPTIME,  100,         GET_TRANS(Center2, OffRight)},
    {StateOffRight, SKYBLUE,SLEEPTIME,  100,         GET_TRANS(Center2, OffRight)},
};

State_t * get_starting_state(){
    return &fsm[3];
}


uint8_t ramped = 0;
uint8_t backwards_ramped = 0;
#define RAMP_TIME 50
#define DUTY_CYCLE 2000

// If we have lost the line for this many cycles, then just go backwards
// because we're really lost
uint8_t off_count = 0;
#define OFF_THRESHOLD 5

void drive_motor(enum State_e this_state){
    //Special case where if we're off the line for a long time, just go
    //backwards and hope we find it
    if((this_state == StateOffLeft || this_state == StateOffRight) &&
       off_count >= OFF_THRESHOLD){
        if(ramped){
            RampDown(DUTY_CYCLE, RAMP_TIME);
            ramped = 0;
        }
        if(!backwards_ramped){
            Motor_Backward_With_Ramp(DUTY_CYCLE, fsm[this_state].drive_time,
                                     RAMP_TIME);
            backwards_ramped = 1;
        }else{
            Motor_BackwardSimple(DUTY_CYCLE, fsm[this_state].drive_time);
        }
    }

    backwards_ramped = 0;
    switch(this_state){
        case StateOffLeft:
            really_hard_left(fsm[this_state].drive_time);
            off_count++;
            break;


        case StateFarLeft:
            hard_left(fsm[this_state].drive_time);
            off_count = 0;
            break;

        case StateLeft:
            soft_left(fsm[this_state].drive_time);
            off_count = 0;
            break;

        case StateCenter2:
        case StateCenter1:
            off_count = 0;
            if(!ramped){
                ramped = 1;
                Motor_Forward_With_Ramp(DUTY_CYCLE, fsm[this_state].drive_time,
                                        RAMP_TIME);
            }else{
                Motor_ForwardSimple(DUTY_CYCLE, fsm[this_state].drive_time);
            }
            break;

        case StateRight:
            off_count = 0;
            soft_right(fsm[this_state].drive_time);
            break;

        case StateFarRight:
            off_count = 0;
            hard_right(fsm[this_state].drive_time);
            break;

        case StateOffRight:
            off_count++;
            really_hard_right(fsm[this_state].drive_time);
            break;
        default:
            break;
    }

}

enum Edges edge_encoder(int32_t pos){
    if(pos == 0){
        return Off_e;

    }else if(BETWEEN(pos, 333, AVG(237, 142))){
        return FarRight_e;

    }else if(BETWEEN(pos, AVG(237, 142) + 1, 47)){
        return Right_e;

    }else if(BETWEEN(pos, 48, -48)){
        return Center_e;

    }else if(BETWEEN(pos, -47, AVG(-142, -237))){
        return Left_e;

    }else if(BETWEEN(pos, AVG(-142, -237) + 1, -333)){
        return FarLeft_e;

    //Should never be possible to get here
    //TODO: Investigate if I can include asserts
    }else{
        return Error_e;
    }
}

#else

#define LINEFOLLOWING2
#include "../inc/FSM.h"

enum Edges_e get_edge(int32_t pos){
    if(pos == 0){
        return OFF_EDGE;
    }

    //Kind of arbitrary groupings..
    if(pos <= 333 && pos  >= 200) {
        return FAR_RIGHT_EDGE;
    }
    if(pos < 200 && pos >= 100){
        return RIGHT_EDGE;
    }
    if(pos < 100 && pos >= 3){
        return SLIGHTLY_RIGHT_EDGE;
    }
    if(pos < 3 && pos >= -2){
        return CENTER_EDGE;
    }
    if(pos < -3 && pos >= -100){
        return SLIGHTLY_LEFT_EDGE;
    }
    if(pos < -100 && pos >= -200){
        return LEFT_EDGE;
    }
    if(pos < -200 && pos >= -333){
        return FAR_LEFT_EDGE;
    }

    return OFF_EDGE;
}

#define FORWARD     1
#define BACKWARD    0

State_t fsm [NUM_STATES] = {
    //State                Lost Line Transition    LeftDuty LeftDirection  RightDuty  RightDirection
    {OFF_LEFT_STATE,       OFF_LEFT_STATE,         20,      BACKWARD,      70,        FORWARD},
    {FAR_LEFT_STATE,       OFF_LEFT_STATE,         40,      FORWARD,       70,        FORWARD},
    {LEFT_STATE,           OFF_LEFT_STATE,         40,      FORWARD,       60,        FORWARD},
    {SLIGHTLY_LEFT_STATE,  CENTER_BACKWARD_STATE,  50,      FORWARD,       60,        FORWARD},

    {CENTER_FORWARD_STATE, CENTER_BACKWARD_STATE,  60,         FORWARD,        60,         FORWARD},
    {CENTER_BACKWARD_STATE,CENTER_BACKWARD_STATE,  60,         BACKWARD,        60,        BACKWARD},

    {SLIGHTLY_RIGHT_STATE, CENTER_BACKWARD_STATE,  50,         FORWARD,        60,         FORWARD},
    {RIGHT_STATE,          OFF_RIGHT_STATE,        60,         FORWARD,        50,         FORWARD},
    {FAR_RIGHT_STATE,      OFF_RIGHT_STATE,        70,         FORWARD,        40,         FORWARD},
    {OFF_LEFT_STATE,       OFF_RIGHT_STATE,        70,         FORWARD,        20,         BACKWARD}
};

enum State_e TRANSITION_MAPPING [NUM_EDGES] = {
    FAR_LEFT_STATE,
    LEFT_STATE,
    SLIGHTLY_LEFT_STATE,

    CENTER_FORWARD_STATE,

    SLIGHTLY_RIGHT_STATE,
    RIGHT_STATE,
    FAR_RIGHT_STATE
};

State_t * get_starting_state(){
    return &fsm[4];
}
#endif

