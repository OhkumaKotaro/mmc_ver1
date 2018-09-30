#include "motion.h"
#include "tim.h"
#include "global.h"
#include "control.h"
#include "gpio.h"
#include "spi.h"


void Normal_Turn_Half(void){
    while(1){
        if(sensor.wall[0]==true && sensor.wall[3]==true){
            Output_Buzzer(HZ_C_H);
            break;
        }
    }
    HAL_Delay(500);
    gyro_offset_calc_reset();
    Yawrate_Calc_fb(180,0,0);
    HAL_Delay(1500);
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


void Turn_Half(void){
    while(1){
        if(sensor.wall[0]==true && sensor.wall[3]==true){
            Output_Buzzer(HZ_C_H);
            break;
        }
    }
    gyro_offset_calc_reset();
    Yawrate_Calc_fb(180,0,0);
    Straight_Calc_Zero();
    HAL_Delay(1500);
    Output_Buzzer(HZ_C_H);
    flag.yawrate = ON;
    flag.straight = ON;
    while(1){
        if(Push()==ON){
            flag.yawrate = OFF;
            flag.straight = OFF;
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
void Normal_Ennkai(void){
    while(1){
        if(sensor.wall[0]==true && sensor.wall[3]==true){
            Output_Buzzer(HZ_C_H);
            break;
        }
    }
    HAL_Delay(500);
    gyro_offset_calc_reset();
    Yawrate_Calc_Zero();
    HAL_Delay(1500);
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

void Ennkai(void){
    while(1){
        if(sensor.wall[0]==true && sensor.wall[3]==true){
            Output_Buzzer(HZ_C_H);
            break;
        }
    }
    HAL_Delay(500);
    gyro_offset_calc_reset();
    Yawrate_Calc_Zero();
    Straight_Calc_Zero();
    HAL_Delay(1500);
    Output_Buzzer(HZ_C_H);
    flag.yawrate = ON;
    flag.straight = ON;
    while(1){
        if(Push()==ON){
            flag.yawrate = OFF;
            flag.straight = OFF;
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
    while(1){
        if(sensor.wall[0]==true && sensor.wall[3]==true){
            Output_Buzzer(HZ_C_H);
            break;
        }
    }
    HAL_Delay(500);
    Straight_Calc_fb(180,0,0);
    HAL_Delay(1000);
    Output_Buzzer(HZ_C_H);
    flag.straight = ON;
    while(1){
        if(Push()==ON){
            flag.straight = OFF;
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
void Straight(void){
    while(1){
        if(sensor.wall[0]==true && sensor.wall[3]==true){
            Output_Buzzer(HZ_C_H);
            break;
        }
    }
    gyro_offset_calc_reset();
    Straight_Calc_fb(180.0f,0.0f,0.0f);
    Yawrate_Calc_Zero();
    HAL_Delay(1000);
    Output_Buzzer(HZ_C_H);
    flag.straight = ON;
    flag.yawrate = ON;
    while(1){
        if(Push()==ON){
            flag.straight = OFF;
            flag.yawrate = OFF;
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

void Sensor_Mode(void){
    while(1){
        flag.ir_led = ON;
        Sensor_Check();
        if(Push()==ON){
            Output_Buzzer(HZ_A);
            flag.ir_led = OFF;
            break;
        }
    }
}

/****************************************************************************************
 * outline  : normalize battery (12bit -> dec)
 * argument : void
 * return   : void
********************************************************************************************/
void Batt_Check(void)
{
  float batt=0;
  for(int i=0;i<50;i++){
    batt += batt_analog;
  }
  batt /= 50.0;
  batt = batt/4095.0f*133.0f/33.0f*3.3f;
  batt_Vcc = batt;
  printf("\nbatt:%lf\r\n",batt_Vcc);
}
