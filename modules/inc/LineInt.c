#include "TimerA2.h"

/*  This module assumes that SM has already be initialized to 12 MHz
 */

void LineSensorIntStart(void){
    
}

void LineSensorIntEnd(void){

}


void LineSensorIntInit(void){
    TimerA2_Init(LineSensorIntStart, );

}
