#ifndef __CONTROL_H
#define __CONTROL_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stdint.h"


float PID_value(float target,float measured,float *sum,float *old,float Kp,float Ki,float Kd,int16_t maximum);
void Calc_Palam(int16_t accel,int16_t *velocity,int16_t *distance);
void Straight_Calc_fb(int16_t distant,int16_t v_start,int16_t v_end);
void Straight_SysTic_fb(void);
void Yawrate_Calc_fb(int16_t degree,int16_t v_start,int16_t v_end);
void Yawrate_SysTic_fb(void);
void control_accel(int16_t accel_l,int16_t accel_r );
void straight_one_ff(void);
void Sensor_Check(void);

#ifdef __cplusplus
}
#endif
#endif