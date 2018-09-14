#ifndef __GLOBAL_H
#define __GLOBAL_H
#ifdef __cplusplus
 extern "C" {
#endif

// Includes
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define true  1
#define false 0


//flag
typedef struct{
  uint8_t gyro_calc;
}flag_t;
extern flag_t flag;

typedef struct{
  short offset_cnt;
  float offset;
  float befor;
  float radian;
  float degree;
  float degree_sum;
}gyro_t;
extern gyro_t gyro;

typedef struct{
  int l;
  int r;
}enc_t;
extern enc_t enc;

typedef struct{
  uint16_t adc_on[4];
  uint16_t adc_off[4];
  uint16_t adc[4];
  uint16_t wall[4];
  uint16_t count[4];
}sensor_t;
extern sensor_t sensor;

extern uint16_t sensor_adc_on[4];
extern uint16_t sensor_adc_off[4];
extern uint16_t sensor_adc[4];
extern uint16_t sensor_wall[4];
extern uint16_t sensor_count[4];

extern uint16_t count_tim5;
extern uint16_t batt_analog;

#ifdef __cplusplus
}
#endif
#endif