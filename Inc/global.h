#ifndef __GLOBAL_H
#define __GLOBAL_H
#ifdef __cplusplus
 extern "C" {
#endif

/***Includes***********************************************************************/
#include "stdint.h"
#include <stdio.h>
#include <string.h>

/***define************************************************************************/

//0,1
#define true  1
#define false 0

#define ON 1
#define OFF 0


//motor 003SR
#define KT  1.98//toluku[mNm/A]
#define KE  0.207//return vatt[mV/min^-1]
#define Resistance 1.07//[S^-1]


//encoder
#define IE_1024 1024


//mouse
#define WEIGHT 100 //[g]
#define TIRE_RADIUS 12  //[mm]
#define INERTIA 
#define TREAD 73  //[mm]
#define GEAR_RATE 5.25


/***typedef**************************************************************************/

//flag
typedef struct{
  short gyro_calc;
  short accel;
  short ir_led;
}flag_t;
extern flag_t flag;


//gyro
typedef struct{
  short offset_cnt;
  float offset;
  float befor;
  float radian;
  float degree;
  float degree_sum;
}gyro_t;
extern gyro_t gyro;


//encoder
typedef struct{
  int rpms_left;
  int rpms_right;
  int32_t sum_l;
  int32_t sum_r;
}enc_t;
extern enc_t enc;


//sensor
typedef struct{
  uint16_t adc_on[4];
  uint16_t adc_off[4];
  uint16_t adc[4];
  uint16_t wall[4];
  uint16_t count[4];
}sensor_t;
extern sensor_t sensor;
//batt
extern uint16_t batt_analog;


//standard unit
typedef struct{
  float distance_l;
  float distance_r; 
  float batt;
}sit_t;
extern sit_t sit;


//motor parameters
typedef struct{
  int16_t pwm_l;
  int16_t pwm_r;
}motor_t;
extern motor_t motor;


//count
extern uint16_t count_tim5;
extern uint16_t ms_count;
extern uint16_t s_count;
extern uint16_t speed_count;


#ifdef __cplusplus
}
#endif
#endif