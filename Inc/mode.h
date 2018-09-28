#ifndef __MODE_H
#define __MODE_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stdint.h"

uint8_t Mode_select(void);
void Mode_mouse(uint8_t mode);
void L_chica(void);
void Hallow(void);
void Ennkai(void);
void Normal_Straight(void);
void Straight_one_fb(void);
void Show_log(void);


#ifdef __cplusplus
}
#endif
#endif