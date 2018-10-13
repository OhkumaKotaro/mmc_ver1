#include "global.h"

volatile flag_t flag;

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

uint16_t straight_cnt;
uint16_t yawrate_cnt;

motor_t motor;

loger_t loger;

uint16_t accel_T;
uint16_t constant_T;
uint16_t decrease_T;

uint16_t y_accel_T;
uint16_t y_constant_T;
uint16_t y_decrease_T;