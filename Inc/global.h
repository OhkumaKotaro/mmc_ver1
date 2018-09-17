#ifndef __GLOBAL_H
#define __GLOBAL_H
#ifdef __cplusplus
 extern "C" {
#endif

// Includes
#include "stdint.h"
#include <stdio.h>
#include <string.h>

//define
#define true  1
#define false 0

#define ON 1
#define OFF 0

#define GEAR_RATE 5.25
#define IE_1024 1024

//motor 003SR
#define KT  1.98//toluku[mNm/A]
#define KE  0.207//return vatt[mV/min^-1]
#define Resistance 1.07//[S^-1]

//mouse
#define WEIGHT 100 //[g]
#define TIRE_RADIUS 12  //[mm]
#define INERTIA 
#define TREAD 73  //[mm]


//flag
typedef struct{
  short gyro_calc;
  short accel;
  short ir_led;
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
  int rpms_left;
  int rpms_right;
  int32_t sum_l;
  int32_t sum_r;
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

typedef struct{
  float distance_l;
  float distance_r; 
  float batt;
}sit_t;
extern sit_t sit;

typedef struct{
  int16_t pwm_l;
  int16_t pwm_r;
}motor_t;
extern motor_t motor;

extern uint16_t sensor_adc_on[4];
extern uint16_t sensor_adc_off[4];
extern uint16_t sensor_adc[4];
extern uint16_t sensor_wall[4];
extern uint16_t sensor_count[4];

extern uint16_t count_tim5;
extern uint16_t batt_analog;

extern uint16_t ms_count;
extern uint16_t s_count;
extern uint16_t speed_count;


#ifdef __cplusplus
}
#endif
#endif