/*
Assume x1, x2, x3, x4 are four measurements collected at 1ms time intervals.  
Calculate the discrete derivative using this equation:
d = x1+3*x2 - 3*x3 - x4

If the units of x1 is mV, then the units of d will be mV/ms (or V/s). Assume the inputs are 16-bit signed numbers ranging from 0 to 3300. 

Solve overflow by limiting the output to -1000 to +1000 V/s. 

Hint, calculate the intermediate result in 32-bit math, check for overflow, and then return a 16-bit result. 

The prototype for this function is: 

int16_t Derivative ( int16_t x1, int16_t x2, int16_t x3, int16_t x4)

Hint:
*/

#include <stdio.h>
#include <stdint.h>

int16_t Derivative(int16_t x1, int16_t x2, int16_t x3, int16_t x4)
{
    int16_t d = 0;
    int32_t result = 0;

    printf("x1 = %d , x2 = %d , x3 = %d , x4 = %d\n", x1, x2, x3, x4);

    //The absolute max possible value that the result of the equation
    //x1+3*x2 - 3*x3 - x4 could be is 262140 (x1 and x2 are max positive values
    //that can be represented by a 16 bit number and x3 and x4 are the min
    //negative values that can be represented by a 16 bit number).  The maximum
    // (positive) value that can be represented by a signed 32 bit number is
    // 2147483648, so We won't have to worry about overflowing the 32 number

    //d = x1+3*x2 - 3*x3 - x4
    result = (uint32_t) x1 + 3 * (uint32_t) x2 - 3 * (uint32_t) x3 - (uint32_t)x4;

    if (result < -1000){
        d = -1000;
    } else if (result  > 1000){
        d = 1000;
    } else {
        d = (uint16_t) result;
    }

    printf("Dirivative= %d\n", d);
    return d;
}

int main(){
    int16_t x1 = 32767, x2 = 32768, x3 = -32768, x4 = -32768;
    int16_t d = Derivative(x1, x2, x3, x4);

    Derivative(32, 65, -43, 55);

    return 0;
}
