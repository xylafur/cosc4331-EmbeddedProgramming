#define BUFFER_MAX_SIZE 15

int16_t * error_buffer;
int16_t error_buffer_size;
int16_t error_buffer_position;

//                  b00011000
//          The middle two sensors, our goal position
#define COMMAND_VALUE 24

//This is both the max value and the minimum value that should come out of our
//control functions (p + i + d)
#define MAX_CONTROL_VALUE 65536
#define MIN_CONTROL_VALUE (-MAX_CONTROL_VALUE)

#define MAXIMUM_WHEEL_PERCENT 95
#define MINIMUM_WHEEL_PERCENT 10


float left_wheel_constant;
float right_wheel_constant;

void PID_init(){
    left_wheel_constant =   (MAXIMUM_WHEEL_PERCENT - MINIMUM_WHEEL_PERCENT) /
                            (MAX_CONTROL_VALUE);
    right_wheel_constant =  (MINIMUM_WHEEL_PERCENT - MAXIMUM_WHEEL_PERCENT) /
                            (MAX_CONTROL_VALUE);
}

#define PREVIOUS_ERROR (error_buffer[error_buffer_position == 0 ?           \
                                     error_buffer_size - 1 :                \
                                     error_buffer_position])

int16_t sensor_to_error(uint8_t sensor_data){

    //We lost the line.. just assume we're going off the same way
    if(sensor_data == 0){
        return PREVIOUS_ERROR;
    }

    //TODO: Not sure how to do this..

}

void sensor_to_error_buffer(uint8_t sensor_data){
    error_buffer[error_buffer_position] = sensor_to_error(sensor_data);
    error_buffer_position = (error_buffer_position + 1) % BUFFER_MAX_SIZE;
    if(error_buffer_size < BUFFER_MAX_SIZE){
        error_buffer_size++;
    }
}

#define same_sign(a, b) ((a > 0 && b > 0) || (b < 0 && a < 0))

// TODO: Compute these values
#define Kp
#define Kd
#define Ki

uint8_t use_i = 1;

int32_t proportional(){
    int16_t error = error_buffer[error_buffer_position];
    return error;
}

/* Pure Naive Derivative
 */
int32_t derivative(){
    int16_t this_error = error_buffer[error_buffer_position],
            last_error = PREVIOUS_ERROR;

    return this_error - last_error;
}

int32_t integral(){
    int32_t sum = 0;
    uint8_t ii;
    for(ii = 0; error_buffer_size - ii > 0; ii++){
        sum += error_buffer[ii % MAX_BUFFER_SIZE];
    }
    return sum;
}

int32_t saturation_clamper(int32_t preClamp){
    if(preClamp > 0 && preClamp > MAX_CONTROL_VALUE){
        return MAX_CONTROL_VALUE;

    }else if(preClamp < 0 && preClamp < MIN_CONTROL_VALUE){
        return MIN_CONTROL_VALUE;
    }
    return preClamp;
}

#define RIGHT 1
#define LEFT 0
/*  X is expected to be a value between MIN_CONTROL_VALUE and MAX_CONTROL_VALUE
 */
uint16_t wheel_equation(uint8_t wheel, uint32_t x){
    //right wheel
    if(wheel){
        return (uint16_t)(x * right_wheel_constant + MAXMUM_WHEEL_PERCENT)
    //left wheel
    }else{
        return (uint16_t)(x * left_wheel_constant + MAXUMUM_WHEEL_PERCENT);
    }
}

/*  A control value of 0 means that there was no error and we should keep
 *  spinning out wheels at their maximum value (80%)
 *
 *  A positive control value means that the line is to the right of the robot,
 *  so we should decrease the speed of the right motor.
 *
 *  A negative control value means that the line is to the left of the robot
 *  and that the left wheel's speed should be decreased.
 *
 *  returns a bitmask of the two percentages for the wheels
 */
uint32_t control_to_action(uint32_t control_value){
    uint16_t left_wheel_percent, right_wheel_percent;
    if(control_value == 0){
        left_wheel_percent = right_wheel_percent = MAXMUM_WHEEL_PERCENT;

    } else if(control_value > 0){
        left_wheel_percent = MAXMUM_WHEEL_PERCENT;
        right_wheel_percent = wheel_equation(RIGHT, control_value);

    }else if(control_value < 0){
        right_wheel_percent = MAXMUM_WHEEL_PERCENT;
        left_wheel_percent = wheel_equation(LEFT, control_value);
    }

    return (left_wheel_percent << 16) | right_wheel_percent;
}

uint32_t compute_actuation(){
    int32_t p = 0, i = 0, d = 0, preClamp = 0, postClamp = 0;
    int16_t e = error_buffer[error_buffer_position];

    p = Kp * proportional();

    if(use_i){
        i = Ki * integral();
    }

    if(error_buffer_size >= 2){
        d = Kd * derivative();
    }

    preClamp = p + i + d;

    postClamp = saturation_clamper(preClamp);

    if(preClamp != postClamp && same_sign(e, preClamp)){
        use_i = 0;
    }else{
        use_i = 1;
    }

    return control_to_action(postClamp);
}
