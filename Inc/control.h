#ifndef __CONTROL_H
#define __CONTROL_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stdint.h"

void control_accel(int16_t accel_l,int16_t accel_r );
void straight_one(void);


#ifdef __cplusplus
}
#endif
#endif