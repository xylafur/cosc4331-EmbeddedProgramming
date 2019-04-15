#include <stdint.h>
#include "msp432.h"
#include "TimerA2.h"
#include "CortexM.c"


/*  This module assumes that SM has already be initialized to 12 MHz
 */

#define LINE_SENSOR_PAUSE_MILI_SECONDS 20
#define CAP_CHARGE_TIME_MICRO_SECONDS 10
#define CAP_DISCHARGE_TIME_MICRO_SECONDS 1000


void LineSensorIntStart(void){
    long sr = StartCritical();

    P5->OUT |= (1 << 3);

    P7->DIR = 0xFF;
    P7->OUT = 0xFF;

    TimerA2_Change_Task(LineSensorIntMiddle,
                        MicroS_TO_PERIOD(CAP_CHARGE_TIME_MICRO_SECONDS));
    EndCritical(sr);
}

void LineSensorIntMiddle(void){
    long sr = StartCritical();

    P7->DIR = 0;
    TimerA2_Change_Task(LineSensorIntEnd,
                        MicroS_TO_PERIOD(CAP_DISCHARGE_TIME_MICRO_SECONDS));
    EndCritical(sr);
}

void LineSensorIntEnd(void){
    long sr = StartCritical();

    LineSensorData = P7->IN;
    P5->OUT &= ~(1 << 3);

    EndCritical(sr);

    TimerA2_Change_Task(LineSensorIntStart,
                        MS_TO_PERIOD(LINE_SENSOR_PAUSE_MILI_SECONDS));
}


void LineSensorIntInit(void){
    // write this as part of Lab 6
    P5->SEL0 &= ~(1 << 3);
    P5->SEL1 &= ~(1 << 3);

    //Make the IR led output
    P5->DIR |= (1 << 3);

    //Set all pins on port 7 low
    P7->SEL0 = 0;
    P7->SEL1 = 0;

    TimerA2_Init(LineSensorIntStart,
                 MS_TO_PERIOD(LINE_SENSOR_PAUSE_MILI_SECONDS));
}
