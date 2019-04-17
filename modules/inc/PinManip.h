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

#define MK_GPIO_PULLUP(PORT, PIN) MK_GPIO(PORT, PIN, INPUT);                \
                                  PORT -> REN |= (1 << PIN);                \
                                  PORT -> OUT |= (1 << PIN)

#define MK_TIMER0A_FUNCTION(PORT, PIN)  PORT -> SEL0 |=  (1 << PIN);        \
                                        PORT -> SEL1 &= ~(1 << PIN)

#define HIGH(PORT, PIN) (PORT->OUT |= (1 << PIN))
#define LOW(PORT, PIN) (PORT->OUT &= ~(1 << PIN))

#define MAKE_PORT_GPIO(PORT) PORT->SEL0 = 0; PORT->SEL1 = 0

#define MAKE_GPIO_OUTPUT(PORT, PIN) \
    PORT->SEL0 &= ~(1 << PIN);      \
    PORT->SEL1 &= ~(1 << PIN);      \
    PORT->DIR |= (1 << PIN)

#define MAKE_PORT_OUTPUT(PORT) PORT->DIR = 0xFF
#define MAKE_PORT_INPUT(PORT) PORT->DIR = 0

#define WRITE_ONES_PORT(PORT) PORT->OUT = 0xFF

#define MAKE_OUTPUT(PORT, PIN)  PORT->DIR |= (1 << PIN)

#define READ_PORT(PORT) PORT->IN






#define OUTPUT  1
#define INPUT   0

#endif
