// Lab06_GPIOmain.c
// Runs on MSP432
// Solution to GPIO lab
// Daniel and Jonathan Valvano
// May 21, 2017
// Provide test main program for QTR-8RC reflectance sensor array
// Pololu part number 961.

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

// reflectance LED illuminate connected to P5.3
// reflectance sensor 1 connected to P7.0 (robot's right, robot off road to left)
// reflectance sensor 2 connected to P7.1
// reflectance sensor 3 connected to P7.2
// reflectance sensor 4 connected to P7.3 center
// reflectance sensor 5 connected to P7.4 center
// reflectance sensor 6 connected to P7.5
// reflectance sensor 7 connected to P7.6
// reflectance sensor 8 connected to P7.7 (robot's left, robot off road to right)

#include <stdint.h>
#include "msp.h"
#include "../inc/Reflectance.h"
#include "../inc/Clock.h"
#include "../inc/TExaS.h"

uint8_t Data; // QTR-8RC
// Test main for section 6.4.3
int Program6_1(void){
  Clock_Init48MHz();
  Reflectance_Init(); // your initialization
  TExaS_Init(LOGICANALYZER_P7);
  while(1){
    Data = Reflectance_Read(1000); // your measurement
    Clock_Delay1ms(10);
  }
}




enum States {
    OffLeft_s,    //0
    FarLeft_s,    //1
    Left_s,       //2
    Center1_s,    //3
    Center2_s,    //4
    Right_s,      //5
    FarRight_s,   //6
    OffRight_s,   //7
};

#define NUM_STATES 8

/* If we get a reading of zero, it means that no sensors are triggered.  The
 * Position function is guaranteed to return a non zero number if there are at
 * least some sensors triggered (meaning that it is perfectly canceling out)
 *
 * This edges enum is just used to index the state's array.  Each state can
 * have different behavior for what to do if it gets a reading of 0
 */
#define NUM_EDGES 6
enum Edges {
    Off_e,
    FarLeft_e,
    Left_e,
    Center_e,
    Right_e,
    FarRight_e,

    Error_e
};

#define SLEEPTIME 500

#define MAX_NAME_LEN 16
struct State {
    char name [MAX_NAME_LEN];
    uint32_t out;
    uint32_t delay;
    const struct State *next[NUM_EDGES];
};

typedef const struct State State_t;

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
    {"Off Left", PINK, SLEEPTIME, GET_TRANS(Center1, OffLeft)},
    {"Far Left", RED, SLEEPTIME, GET_TRANS(Center1, OffLeft)},

    {"Left", YELLOW, SLEEPTIME, GET_TRANS(Center1, OffLeft)},

    {"Center1", WHITE, SLEEPTIME, GET_TRANS(Center2, OffLeft)},
    {"Center2", DARK, SLEEPTIME, GET_TRANS(Center1, OffRight)},

    {"Right", GREEN, SLEEPTIME, GET_TRANS(Center2, OffRight)},

    {"Far Right", BLUE, SLEEPTIME, GET_TRANS(Center2, OffRight)},
    {"Off Right", SKYBLUE, SLEEPTIME, GET_TRANS(Center2, OffRight)},
};

#define AVG(a, b) ((a + b)/2)
#define BETWEEN(pos, max, min) (pos > min && pos < max)

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

int32_t Position; // 332 is right, and -332 is left of center

/*  This is for me to test our sensor a bit
 */
int main(){
    Clock_Init48MHz();
    LineSensorTest_Init();

    uint8_t data;
    int32_t position;
    enum Edges this_edge;
    State_t *current_state = &fsm[3];

    while(1){
        set_color(current_state->out);
        Clock_Delay1ms(current_state->delay);

        data = Reflectance_Read(1000);
        position = Reflectance_Position(data);
        this_edge = edge_encoder(position);

        if(this_edge == Error_e){
            while(1){
                set_color(RED);
                Clock_Delay1ms(1000);
                set_color(BLUE);
                Clock_Delay1ms(1000);
            }
            
        }else{
            current_state = current_state->next[this_edge];//&fsm[this_edge];
        }

    }
}
