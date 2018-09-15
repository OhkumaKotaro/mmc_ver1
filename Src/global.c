#include "global.h"

flag_t flag;
gyro_t gyro;
enc_t enc;
sit_t sit;

sensor_t sensor;
uint16_t count_tim5 ;
uint16_t batt_analog;

uint16_t sensor_adc_on[4];
uint16_t sensor_adc_off[4];
uint16_t sensor_adc[4];
uint16_t sensor_wall[4];
uint16_t sensor_count[4];

uint16_t ms_count;
uint16_t s_count;

