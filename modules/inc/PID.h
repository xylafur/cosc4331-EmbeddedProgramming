#ifndef PID_HEADER
#define PID_HEADER

void PID_init();
void sensor_to_error_buffer(uint8_t sensor_data);
void increaseKp();
void decreaseKp();
uint32_t compute_actuation();

#endif
