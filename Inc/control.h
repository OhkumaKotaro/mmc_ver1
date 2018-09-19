#ifndef __CONTROL_H
#define __CONTROL_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stdint.h"

void Calculate_Parameter(int accel_l,int accel_r);
int16_t PID_value(float target,float measured,float *sum,float*old,float Kp,float Ki,float Kd,int16_t maximum);
void control_accel(int16_t accel_l,int16_t accel_r );
void straight_one_ff(void);
void Sensor_Check(void);
void straight_fb(int v_start,int v_end,int accel,int distance,int v_max);

#ifdef __cplusplus
}
#endif
#endif