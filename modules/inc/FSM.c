#include "../inc/FSM.h"
#include "../inc/MotorSimple.h"
#include "../inc/Reflectance.h"

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
    {StateOffLeft,  PINK,   SLEEPTIME,  10,         GET_TRANS(Center1, OffLeft)},
    {StateFarLeft,  RED,    SLEEPTIME,  10,         GET_TRANS(Center1, OffLeft)},

    {StateLeft,     YELLOW, SLEEPTIME,  10,         GET_TRANS(Center1, OffLeft)},

    {StateCenter1,  WHITE,  SLEEPTIME,  10,         GET_TRANS(Center2, OffLeft)},
    {StateCenter2,  DARK,   SLEEPTIME,  10,         GET_TRANS(Center1, OffRight)},

    {StateRight,    GREEN,  SLEEPTIME,  10,         GET_TRANS(Center2, OffRight)},

    {StateFarRight, BLUE,   SLEEPTIME,  10,         GET_TRANS(Center2, OffRight)},
    {StateOffRight, SKYBLUE,SLEEPTIME,  10,         GET_TRANS(Center2, OffRight)},
};

State_t * get_starting_state(){
    return &fsm[3];
}

uint8_t ramped = 0;
#define RAMP_TIME 10
#define DUTY_CYCLE 5000

void drive_motor(enum State_e this_state){
    switch(this_state){
        case StateOffLeft:
            break;
        case StateFarLeft:
            break;
        case StateLeft:
            soft_left(fsm[this_state].drive_time);
            break;
        case StateCenter1:
        case StateCenter2:
            if(!ramped){
                ramped = 1;
                Motor_Forward_With_Ramp(DUTY_CYCLE, fsm[this_state].drive_time,
                                        RAMP_TIME);
            }else{
                Motor_ForwardSimple(DUTY_CYCLE, fsm[this_state].drive_time);
            }
            break;
        case StateRight:
            soft_right(fsm[this_state].drive_time);
            break;
        case StateFarRight:
            break;
        case StateOffRight:
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


