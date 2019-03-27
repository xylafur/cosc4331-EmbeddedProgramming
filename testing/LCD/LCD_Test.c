/* Simplified BSD License (FreeBSD License)
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

#include <stdint.h>
#include "../inc/PinManip.h"
//#include "msp.h"
//#include "../inc/Clock.h"
//#include "../inc/TExaS.h"

// Define all Ports and pin maps for convenience
#define RS_Port
#define RS_Pin

#define RW_Port
#define RW_Pin

#define E_Port
#define E_Pin

#define D0_Port
#define D0_Pin

#define D1_Port
#define D1_Pin

#define D2_Port
#define D2_Pin

#define D3_Port
#define D3_Pin

#define D4_Port
#define D4_Pin

#define D5_Port
#define D5_Pin

#define D6_Port
#define D6_Pin

#define D7_Port
#define D7_Pin

#define A_Port
#define A_Pin

#define K_Port
#define K_Pin



void LCD_Init(){
    MK_GPIO(RS_Port, RS_Pin, OUTPUT);
    MK_GPIO(RW_Port, RW_Pin, OUTPUT);
    MK_GPIO(E_Port, E_Pin, OUTPUT);

    MK_GPIO(D0_Port, D0_Pin, OUTPUT);
    MK_GPIO(D1_Port, D1_Pin, OUTPUT);
    MK_GPIO(D2_Port, D2_Pin, OUTPUT);
    MK_GPIO(D3_Port, D3_Pin, OUTPUT):
    MK_GPIO(D4_Port, D4_Pin, OUTPUT);
    MK_GPIO(D5_Port, D5_Pin, OUTPUT);
    MK_GPIO(D6_Port, D6_Pin, OUTPUT);
    MK_GPIO(D7_Port, D7_Pin, OUTPUT);

    MK_GPIO(A_Port, A_Pin, OUTPUT);
    MK_GPIO(K_Port, K_Pin, OUTPUT);
}

void Clear_Display(){
    WRITE(RS_Port, RS_Pin, 0);
    WRITE(RW_Port, RW_Pin, 0);

    WRITE(D0_Port, D0_Pin, 1);
    WRITE(D1_Port, D1_Pin, 0);
    WRITE(D2_Port, D2_Pin, 0);
    WRITE(D3_Port, D3_Pin, 0);
    WRITE(D4_Port, D4_Pin, 0);
    WRITE(D5_Port, D5_Pin, 0);
    WRITE(D6_Port, D6_Pin, 0);
    WRITE(D7_Port, D7_Pin, 0);
}

//Turn display and cursor / cursor blink on or off
void Set_Display(int display, int cursor, int cursor_blink){
    WRITE(RS_Port, RS_Pin, 0);
    WRITE(RW_Port, RW_Pin, 0);

    WRITE(D0_Port, D0_Pin, cursor_blink);
    WRITE(D1_Port, D1_Pin, cursor);
    WRITE(D2_Port, D2_Pin, display);

    WRITE(D3_Port, D3_Pin, 1);
    WRITE(D4_Port, D4_Pin, 0);
    WRITE(D5_Port, D5_Pin, 0);
    WRITE(D6_Port, D6_Pin, 0);
    WRITE(D7_Port, D7_Pin, 0);
}

uint8_t get_char_code(char c){
    switch (c){
    case '0':
        return 48;
    case '1':
        return 49;
    case '2':
        return 50;
    case '3':
        return 51;
    case '4':
        return 52;
    case '5':
        return 53;
    case '6':
        return 54;
    case '7':
        return 55;
    case '8':
        return 56;
    case '9':
        return 57;


    case 'A':
        return 129;
    case 'B':
        return 130;
    case 'C':
        return 131;
    case 'D':
        return 132;
    case 'E':
        return 133;
    case 'F':
        return 134;
    case 'G':
        return 135;
    case 'H':
        return 136;
    case 'I':
        return 137;
    case 'J':
        return 138;
    case 'K':
        return 139;
    case 'L':
        return 140;
    case 'M':
        return 141;
    case 'N':
        return 142;
    case 'O':
        return 143;
    case 'P':
        return 144;
    case 'Q':
        return 145;
    case 'R':
        return 146;
    case 'S':
        return 147;
    case 'T':
        return 148;
    case 'U':
        return 149;
    case 'V':
        return 150;
    case 'W':
        return 151;
    case 'X':
        return 152;
    case 'Y':
        return 153;
    case 'Z':
        return 154;
    default:
        return 0xff;
    }
}

int main(){
    //Clock_Init48MHz();

    while(1){
    }
}
