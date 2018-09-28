#include "mode.h"
#include "global.h"
#include "gpio.h"
#include "tim.h"
#include "control.h"
#include "spi.h"


/****************************************************************************************
 * outline  : return mode nomber
 * argument : void
 * return   : mode nomber 
********************************************************************************************/
uint8_t Mode_select(void){
    uint8_t mode=0;
    while(1){
        if((int16_t)enc.distance_l % 30 == 29){
            mode ++;
            Output_Buzzer(160-10*mode);
        }
        if(Push()==ON){
            Output_Buzzer(HZ_C_H);
            break;
        }
        printf("%d\r",mode);
    }
    return mode;
}


/****************************************************************************************
 * outline  : wright mode 
 * argument : mode nomber
 * return   : void
********************************************************************************************/
void Mode_mouse(uint8_t mode){
    switch(mode){
        case 1:
            Normal_Straight();
            break;
        case 2:
            Show_log();
            break;
        case 3:
            Ennkai();
            break;
        case 4:
            Hallow();
            break;
        default:
            break;
    }
}


/****************************************************************************************
 * outline  : turn on off LED 
 * argument : void
 * return   : void
********************************************************************************************/
void L_chica(void){
    Output_Buzzer(HZ_C_H);
    while(1){
        All_LED_ON();
        HAL_Delay(1000);
        All_LED_OFF();
        HAL_Delay(1000);
        if(Push()==ON){
            Output_Buzzer(HZ_A);
            break;
        }
    }
}


/****************************************************************************************
 * outline  : printf "Hallow"
 * argument : void
 * return   : void
********************************************************************************************/
void Hallow(void){
    enc.distance_l = 0;
    enc.distance_r = 0;
    Output_Buzzer(HZ_C_H);
    while(1){
        printf("%f\r",enc.distance_l);
        if(Push()==ON){
            Output_Buzzer(HZ_A);
            break;
        }
    }
}


/****************************************************************************************
 * outline  : "ennkaigei"
 * argument : void
 * return   : void
********************************************************************************************/
void Ennkai(void){
    HAL_Delay(500);
    gyro_offset_calc_reset();
    Yawrate_Calc_fb(0,0,0);
    HAL_Delay(1000);
    Output_Buzzer(HZ_C_H);
    flag.yawrate = ON;
    while(1){
        if(Push()==ON){
            flag.yawrate = OFF;
            Output_Buzzer(HZ_A);
            break;
        }
    }
}


/****************************************************************************************
 * outline  : straight run one block by feadbuck control
 * argument : void
 * return   : void
********************************************************************************************/
void Normal_Straight(void){
    HAL_Delay(500);
    Straight_Calc_fb(180,0,0);
    HAL_Delay(1000);
    Output_Buzzer(HZ_C_H);
    flag.straight = ON;
    while(1){
        if(Push()==ON){
            Output_Buzzer(HZ_A);
            break;
        }
    }
}


/****************************************************************************************
 * outline  : straight one block by encoder and gyro
 * argument : void
 * return   : void
********************************************************************************************/
void Straight_one_fb(void){
    HAL_Delay(500);
    Straight_Calc_fb(180.0f,0.0f,0.0f);
    Yawrate_Calc_fb(0,0,0);
    HAL_Delay(1000);
    Output_Buzzer(HZ_C_H);
    flag.straight = ON;
    flag.yawrate = ON;
    while(1){
        if(Push()==ON){
            Output_Buzzer(HZ_A);
            break;
        }
    }
}


/****************************************************************************************
 * outline  : show log
 * argument : void
 * return   : void
********************************************************************************************/
void Show_log(void){
    printf("\na:%d,c:%d,d:%d\r\n",accel_T,constant_T,decrease_T);
    for(uint16_t i=0;i<3000;i++){
        printf("%f\t%f\t%f\r\n",log_calc[i],log_enc[0][i],log_enc[1][i]);
        if(Push()==ON){
            Output_Buzzer(HZ_A);
            break;
        }
    }
}