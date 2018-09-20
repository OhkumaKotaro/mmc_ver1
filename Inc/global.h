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
#define KT  1.98f//toluku[mNm/A]
#define KE  0.207f//return vatt[mV/min^-1]
#define Resistance 1.07f//[S^-1]
#define TORQUE 0.2


//encoder
#define IE_1024 1024


//mouse
#define WEIGHT 100 //[g]
#define TIRE_RADIUS 12  //[mm]
#define INERTIA     23
#define TREAD 73  //[mm]
#define GEAR_RATE 5.25f

//calc
#define dt 0.001f


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
  float rpms_left;
  float rpms_right;
  float velocity_l;
  float velocity_r;
  float distance_l;
  float distance_r;
  float old_l;
  float old_r;
}enc_t;
extern enc_t enc;


//sensor
typedef struct{
  uint16_t adc_on[4];
  uint16_t adc_off[4];
  uint16_t adc[4];
  uint8_t wall[4];
  uint16_t count[4];
}sensor_t;
extern sensor_t sensor;

//batt
extern uint16_t batt_analog;
extern float batt_Vcc;

//motor parameters
typedef struct{
  int16_t pwm_l;
  int16_t pwm_r;
  int16_t accel_l;
  int16_t accel_r;
}motor_t;
extern motor_t motor;

//calc
typedef struct{
  int16_t distance_l;
  int16_t distance_r;
  int16_t velocity_l;
  int16_t velocity_r;
  int16_t accel_l;
  int16_t accel_r;
}calc_t;
extern calc_t calc;

typedef struct{
  uint8_t x;
  uint8_t y;
  uint8_t dir;
  float angle;
  float distance;
}position_t;
extern position_t position;

//count
extern uint16_t count_tim5;
extern uint16_t ms_count;
extern uint16_t s_count;
extern uint16_t speed_count;

//control
extern float accel_L;
extern float constant_L;
extern float decrease_L;


#ifdef __cplusplus
}
#endif
#endif