#ifndef __MODE_H
#define __MODE_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stdint.h"


typedef struct{
    short wall_n[16];
    short wall_w[16];
    short wall_s[16];
    short wall_e[16];
}maze_t;


int8_t Mode_select(void);
void Mode_mouse(int8_t mode);
void LeftHand(void);
void Mode_Straight(void);
void Mode_Turn_Half(void);
void Mode_Turn_Quarter_Left(void);
void Mode_Circuit(void);


#ifdef __cplusplus
}
#endif
#endif