#ifndef MOTOR_UTIL_HEADER
#define MOTOR_UTIL_HEADER

// After digging through the libs a bit, think this is where float is defined
#include <math.h>
#include "PinMap.h"

#define INIT_MOTORS()   MAKE_OUTPUT(RT_WHL_DIR_PORT, RT_WHL_DIR_PIN);       \
                        MAKE_OUTPUT(RT_WHL_EN_PORT, RT_WHL_EN_PIN);         \
                        MAKE_OUTPUT(RT_WHL_SLP_PORT, RT_WHL_SLP_PIN);       \
                        LOW(RT_WHL_EN_PORT, RT_WHL_EN_PIN);                 \
                        HIGH(RT_WHL_SLP_PORT, RT_WHL_SLP_PIN);              \
                        MAKE_OUTPUT(LF_WHL_DIR_PORT, LF_WHL_DIR_PIN);       \
                        MAKE_OUTPUT(LF_WHL_EN_PORT, LF_WHL_EN_PIN);         \
                        MAKE_OUTPUT(LF_WHL_SLP_PORT, LF_WHL_SLP_PIN);       \
                        LOW(LF_WHL_EN_PORT, LF_WHL_EN_PIN);                 \
                        HIGH(LF_WHL_SLP_PORT, LF_WHL_SLP_PIN)

#define MAKE_OUTPUT(PORT, PIN)  \
    PORT->SEL0 &= ~(1 << PIN);  \
    PORT->SEL1 &= ~(1 << PIN);  \
    PORT->DIR |= (1 << PIN)

#define HIGH(PORT, PIN) (PORT->OUT |= (1 << PIN))
#define LOW(PORT, PIN) (PORT->OUT &= ~(1 << PIN))

#define RIGHT_WHEEL_FORWARD() LOW(RT_WHL_DIR_PORT, RT_WHL_DIR_PIN)
#define RIGHT_WHEEL_BACKWARD() HIGH(RT_WHL_DIR_PORT, RT_WHL_DIR_PIN)

#define RIGHT_WHEEL_ON() HIGH(RT_WHL_EN_PORT, RT_WHL_EN_PIN)
#define RIGHT_WHEEL_OFF() LOW(RT_WHL_EN_PORT, RT_WHL_EN_PIN)

#define LEFT_WHEEL_FORWARD() HIGH(LF_WHL_DIR_PORT, LF_WHL_DIR_PIN)
#define LEFT_WHEEL_BACKWARD() LOW(LF_WHL_DIR_PORT, LF_WHL_DIR_PIN)

#define LEFT_WHEEL_ON() HIGH(LF_WHL_EN_PORT, LF_WHL_EN_PIN)
#define LEFT_WHEEL_OFF() LOW(LF_WHL_EN_PORT, LF_WHL_EN_PIN)

#define WHEELS_LEFT() RIGHT_WHEEL_FORWARD(); LEFT_WHEEL_BACKWARD()
#define WHEELS_RIGHT()     RIGHT_WHEEL_BACKWARD(); LEFT_WHEEL_FORWARD()
#define WHEELS_FORWARD()     RIGHT_WHEEL_FORWARD(); LEFT_WHEEL_FORWARD()
#define WHEELS_BACKWARD()     RIGHT_WHEEL_BACKWARD(); LEFT_WHEEL_BACKWARD()

#define MAX(a, b) a > b ? a : b

#define PERIOD_ms 10

#endif
