#include "../inc/FSM.h"
#include "../inc/MotorSimple.h"
#include "../inc/Reflectance.h"

/*  This way even though I will be changing the State Machine significantly, my
 *  old implementation (which works, just not that well and doesn't use
 *  interrupts) can still be compiled
 */
#ifdef LineFollowing1

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

#endif

