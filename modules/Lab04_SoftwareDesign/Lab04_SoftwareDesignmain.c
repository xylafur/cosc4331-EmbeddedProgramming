// main.c
// Runs on MSP432
// Student version of Software Design lab
// Daniel and Jonathan Valvano
// May 28, 2017


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

#define ARM 1
#include <stdint.h>
#include <stdio.h>
void main(void){
  // run one of these
  //Program4_1();
  Program4_2();
//  Program4_3();
}

enum scenario {
    Error = 0,
    LeftTooClose = 1,
    RightTooClose = 2,
    CenterTooClose = 4,
    Straight = 8,
    LeftTurn = 9,
    RightTurn = 10,
    TeeJoint = 11,
    LeftJoint = 12,
    RightJoint = 13,
    CrossRoad = 14,
    Blocked = 15
};

typedef enum scenario scenario_t;

#define SIDEMAX 354    // largest side distance to wall in mm
#define SIDEMIN 212    // smallest side distance to wall in mm
#define CENTEROPEN 600 // distance to wall between open/blocked
#define CENTERMIN 150  // min distance to wall in the front
scenario_t Classify(int32_t Left, int32_t Center, int32_t Right);

#define IRSlope 1195172
#define IROffset -1058
#define IRMax 2552
#define IRMin 800

int32_t Convert(int32_t n){
    if (n < IRMax){
        return IRMin;
    }
    uint32_t denominator = n + IROffset;
#ifdef ARM
    //so I can't figure out how to include the library that gives us udiv.. so
    //I just keep hitting an error in linking stage.  Since I was able to
    //verify that this worked when I ran the function for 8086 IS, I can just
    //return a random output
    return 0;
#else
    return IRSlope / denominator;
#endif
}

/*
 * The algorithm will return a LeftTooClose (4) error if the left sensor is
 * less than 212, and return a RightTooClose (2) error if the right sensor is
 * less than 212. The algorithm will return a CenterTooClose (1) error if the
 * front sensor is less than 150 mm. It will be possible for there to be
 * multiple simultaneou
 *
 * If the robot were within ±50mm from the center of the road with the straight
 * or blocked scenarios, the side sensors could range from 212 to 354 mm. The
 * 354 threshold will be used to classify whether or not it is possible to turn
 * left or right at the next intersection. Less than 354 means turn path not
 * possible; 354 or above means turn path is possible
 *
 * As the robot approaches the intersection, the center sensor will be used to
 * classify the difference between {Blocked, Right Turn, Left Turn, and Tee
 * Joint} (center sensor less than 600 mm) and {Straight, Right Joint, Left
 * Joint, and Cross Road} (center sensor more than 600 mm). 
 */
scenario_t Classify(int32_t Left, int32_t Center, int32_t Right){
    scenario_t result = 0;
    if(Left < SIDEMIN){
        result |= LeftTooClose;
    }
    if(Right < SIDEMIN){
        result |= RightTooClose;
    }
    if(Center < CENTERMIN){
        result |= CenterTooClose;
    }
    if(result){
        //since we can return multiple error conditions, if result is non zero
        //then it is some mask
        return result;
    }
    int right_blocked, left_blocked, center_blocked;
    right_blocked = left_blocked = center_blocked = 0;
    if(Left < SIDEMAX){
        left_blocked = 1;
    }
    if(Right < SIDEMAX){
        right_blocked = 1;
    }
    if(Center < CENTEROPEN){
        center_blocked = 1;
    }

    if(center_blocked && right_blocked && left_blocked){
        result = Blocked;
    }else if(center_blocked && left_blocked){
        result = RightTurn;
    }else if(center_blocked && right_blocked){
        result = LeftTurn;
    }else if(right_blocked && left_blocked){
        result = Straight;
    }else if(center_blocked){
        result = TeeJoint;
    }else if(right_blocked){
        result = LeftJoint;
    }else if(left_blocked){
        result = RightJoint;
    }else{
        result = CrossRoad;
    }
    return result;
}

// ***********testing of Convert*********
int32_t const ADCBuffer[16]={2000, 2733, 3466, 4199, 4932, 5665, 6398, 7131, 7864, 8597, 9330, 10063, 10796, 11529, 12262, 12995};
int32_t const DistanceBuffer[16]={800, 713, 496, 380, 308, 259, 223, 196, 175, 158, 144, 132, 122, 114, 106, 100};
void Program4_1(void){
  int i;
  int32_t adc,distance,errors,diff;
  errors = 0;
  for(i=0; i<16; i++){
    adc = ADCBuffer[i];
    distance = Convert(adc); // call to your function
    diff = distance-DistanceBuffer[i];
    if(diff != 0){
        errors++;
    }
  }
#ifndef ARM
  printf("Encountered %d errors!\n", errors);
#endif
  while(1){};
}
// ***********end of testing of Convert*********






// ***********testing of classify
scenario_t Solution(int32_t Left, int32_t Center, int32_t Right);
int32_t const CornerCases[18]={49,50,51,149,150,151,211,212,213,353,354,355,599,600,601,799,800,801};
int32_t errors;

void Program4_2(void){
  enum scenario result,truth;
  int i,j,k;
  int32_t left, right, center; // sensor readings
  errors = 0;
  for(i=0; i<18; i++){
    left = CornerCases[i];
    for(j=0; j<18; j++){
      center = CornerCases[j];
      for(k=0; k<18; k++){
        right = CornerCases[k];
        result = Classify(left,center,right); // your solution
        truth = Solution(left,center,right);  // correct answer
        if(result != truth){
#ifndef ARM
           printf("Got %d, expected %d\n", result, truth);
#endif
           errors++;
        }
      }
    }
  }
#ifndef ARM
  printf("Hit %d errors!\n", errors);
#endif
  while(1){
  }
}

void Program4_3(void){ // will take over 16 hours to complete
  enum scenario result,truth;
  int32_t left, right, center; // sensor readings
  errors = 0;
  for(left=0; left<1000; left++){
    for(center=0; center<1000;  center++){
      for(right=0; right<1000; right++){
        result = Classify(left,center,right); // your solution
        truth = Solution(left,center,right);  // correct answer
        if(result != truth){
           errors++;
        }
      }
    }
  }
  while(1){
  }
}


