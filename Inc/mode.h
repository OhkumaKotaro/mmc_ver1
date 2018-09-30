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


uint8_t Mode_select(void);
void Mode_mouse(uint8_t mode);
void LeftHand(void);
void Control_Motion(short dir);


#ifdef __cplusplus
}
#endif
#endif