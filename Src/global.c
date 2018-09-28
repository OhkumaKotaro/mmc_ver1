#include "global.h"

flag_t flag;

gyro_t gyro;
enc_t enc;
calc_t calc;
float s_accel;
position_t position;

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

uint16_t accel_T;
uint16_t constant_T;
uint16_t decrease_T;

float y_accel_T;
float y_constant_T;
float y_decrease_T;

float log_calc[3000];
float log_distance[3000];
float log_enc[2][3000];