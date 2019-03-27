/*  This header file contains macros for easy GPIO manipulation
 */

#ifndef PinManip_Header
#define PinManip_Header

#define WRITE(PORT, PIN, DATA)                      \
    if(DATA){   (PORT -> OUT |= (1 << PIN));  }     \
    else{       (PORT -> OUT &= ~(1 << PIN)); }

#define READ(PORT, PIN) (PORT->IN & (1 << PIN))

#define MK_GPIO(PORT, PIN, _DIR)    PORT -> SEL0 &= ~(1 << PIN);            \
                                    PORT -> SEL1 &= ~(1 << PIN);            \
                                    if(_DIR){   PORT -> DIR |= (1 << PIN);} \
                                    else{       PORT -> DIR &= ~(1 << PIN);}

//TODO: Check that this is correct!!
#define OUTPUT  1
#define INPUT   0


#endif
