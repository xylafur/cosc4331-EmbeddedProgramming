#ifndef FSM_Header
#define FCM_Header

#include <stdint.h>

#define AVG(a, b) ((a + b)/2)
#define BETWEEN(pos, max, min) (pos > min && pos < max)

/*  This way even though I will be changing the State Machine significantly, my
 *  old implementation (which works, just not that well and doesn't use
 *  interrupts) can still be compiled
 */
#ifdef LineFollowing1

/*  These represent all of the possible states of our Finite State Machine
 */
#define NUM_STATES 8
enum State_e {
    StateOffLeft,    //0
    StateFarLeft,    //1
    StateLeft,       //2
    StateCenter1,    //3
    StateCenter2,    //4
    StateRight,      //5
    StateFarRight,   //6
    StateOffRight,   //7
};


/* This enum represents all of the possible edges between each of the states.
 * Every state will have an outgoing transition coresponding to each of these
 * edges.
 *
 * If we get a reading of zero, it means that no sensors are triggered.  The
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

/*  This stuct represents each state in our FSM.
 */
#define MAX_NAME_LEN 16
struct State {
    enum State_e this_state;
    uint32_t out;
    uint32_t delay;
    uint32_t drive_time;
    const struct State *next[NUM_EDGES];
};

typedef const struct State State_t;

State_t * get_starting_state();

void drive_motor(enum State_e this_state);
enum Edges edge_encoder(int32_t pos);

#else

#endif

#endif
