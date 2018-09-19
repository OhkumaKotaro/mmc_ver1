#include "global.h"

flag_t flag;
gyro_t gyro;
enc_t enc;
calc_t calc;

sensor_t sensor;
uint16_t count_tim5 ;
uint16_t batt_analog;
float batt_Vcc;

uint16_t sensor_adc_on[4];
uint16_t sensor_adc_off[4];
uint16_t sensor_adc[4];
uint16_t sensor_wall[4];
uint16_t sensor_count[4];

uint16_t ms_count;
uint16_t s_count;
uint16_t speed_count;

motor_t motor;

float accel_L;
float constant_L;
float decrease_L;