#include "motion.h"
#include "tim.h"
#include "global.h"
#include "control.h"
#include "gpio.h"
#include "spi.h"
#include "maze.h"


void Normal_Turn_Half(void){
    flag.ir_led = ON;
    while(1){
        if(sensor.wall[0]==true && sensor.wall[3]==true){
            Output_Buzzer(HZ_C_H);
            break;
        }
    }
    flag.ir_led = OFF;
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

/****************************************************************************************
 * outline  : "ennkaigei"
 * argument : void
 * return   : void
********************************************************************************************/
void Normal_Ennkai(void){
    flag.ir_led = ON;
    while(1){
        if(sensor.wall[0]==true && sensor.wall[3]==true){
            Output_Buzzer(HZ_C_H);
            break;
        }
    }
    flag.ir_led = OFF;
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
    flag.ir_led = ON;
    while(1){
        if(sensor.wall[0]==true && sensor.wall[3]==true){
            Output_Buzzer(HZ_C_H);
            break;
        }
    }
    flag.ir_led = OFF;
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
    flag.ir_led = ON;
    while(1){
        if(sensor.wall[0]==true && sensor.wall[3]==true){
            Output_Buzzer(HZ_C_H);
            break;
        }
    }
    flag.ir_led = OFF;
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
void Straight_Start(void){
    Straight_Calc_fb(135,0,0);
    Yawrate_Calc_Zero();
    flag.straight = ON;
    flag.yawrate = ON;
    flag.wall = OFF;
}

void Straight(void){
    Straight_Calc_fb(180,0,0);
    Yawrate_Calc_Zero();
    flag.straight = ON;
    flag.yawrate = ON;
    flag.wall = ON;
}

void Straight_HalF(void){
    Straight_Calc_fb(90,0,0);
    Yawrate_Calc_Zero();
    flag.straight = ON;
    flag.yawrate = ON;
}

void Turn_Half(void){
    flag.dir = LEFT;
    Yawrate_Calc_fb(180,0,0);
    Straight_Calc_Zero();
    flag.yawrate = ON;
    flag.straight = ON;
}

void Turn_Quarter_Left(void){
    flag.dir = LEFT;
    Yawrate_Calc_fb(90,0,0);
    Straight_Calc_Zero();
    flag.yawrate = ON;
    flag.straight = ON;
}

void Turn_Quarter_Right(void){
    flag.dir = RIGHT;
    Yawrate_Calc_fb(90,0,0);
    Straight_Calc_Zero();
    flag.yawrate = ON;
    flag.straight = ON;
}

void Back(void){
    Straight_Calc_fb(-50,0,0);
    Yawrate_Calc_Zero();
    flag.straight = ON;
    flag.yawrate = ON;
    flag.wall=OFF;
}

void Straight_Check(void){
    Straight_Calc_fb(1080,0,0);
    Yawrate_Calc_Zero();
    HAL_Delay(10);
    Output_Buzzer(HZ_C_H);
    flag.straight = ON;
    flag.wall=ON;
    flag.yawrate = ON;
}

void Motion_Start(void){
    Back();
    while(flag.accel==ON || flag.straight==ON){}
    HAL_Delay(500);
    Straight_Start();
    while(flag.accel==ON || flag.straight==ON){}
    Output_Buzzer(HZ_C_H);
}

void Motion_Straight(void){
    Straight();
    while(flag.accel==ON || flag.straight==ON){}
    Output_Buzzer(HZ_C_H);
}

void Motion_Left(void){
    Straight_HalF();
    while(flag.accel==ON || flag.straight==ON){}
    HAL_Delay(500);
    Turn_Quarter_Left();
    while(flag.accel==ON || flag.straight==ON){}
    HAL_Delay(500);
    Straight_HalF();
    while(flag.accel==ON || flag.straight==ON){}
    Output_Buzzer(HZ_C_H);
}

void Motion_Right(void){
    Straight_HalF();
    while(flag.accel==ON || flag.straight==ON){}
    HAL_Delay(500);
    Turn_Quarter_Right();
    while(flag.accel==ON || flag.straight==ON){}
    HAL_Delay(500);
    Straight_HalF();
    while(flag.accel==ON || flag.straight==ON){}
    Output_Buzzer(HZ_C_H);
}

void Motion_Uturn(void){
    Straight_HalF();
    while( flag.accel==ON || flag.straight==ON ){}
    Turn_Half();
    while(flag.accel==ON || flag.straight==ON){}
    HAL_Delay(500);
    Back();
    while(flag.accel==ON || flag.straight==ON){}
    HAL_Delay(500);
    Straight_Start();
    while(flag.accel==ON || flag.straight==ON){}
    Output_Buzzer(HZ_C_H);
}

void Motion_Goal(void){
    Straight_HalF();
    while( flag.accel==ON || flag.straight==ON ){}
    Output_Buzzer(HZ_C_H);
}

void Motion_Straight_Check(void){
    Straight_Check();
    while(flag.motion_end==false){}
}

void Motion_Back(void){
    Back();
    while(flag.accel==ON || flag.straight==ON){}
    Output_Buzzer(HZ_C_H);
}
/****************************************************************************************
 * outline  : show log
 * argument : void
 * return   : void
********************************************************************************************/
void Show_log(void){
    printf("\na:%d,c:%d,d:%d\r\n",y_accel_T,y_constant_T,y_decrease_T);
    for(uint16_t i=0;i<2000;i++){
        printf("%f\t%f\t%f\r\n",loger.target_y_velocity[i],loger.y_velocity[i],loger.velocity_c[i]);
        if(Push()==ON){
            Output_Buzzer(HZ_A);
            break;
        }
    }
}

void Sensor_Mode(void){
    flag.ir_led = ON;
    while(1){
        Sensor_Check();
        for(int i=0;i<4;i++){
            printf("%d\t",sensor.adc[i]);
        }
        printf("\r");
        if(Push()==ON){
            Output_Buzzer(HZ_A);
            flag.ir_led = OFF;
            break;
        }
    }
}

void Test_Create_Map(void){
    flag.ir_led = OFF;

    Maze_Set();
    Init_maze();
    MAZE_Create_Step();
    MAZE_Printf_Step();
}

/****************************************************************************************
 * outline  : normalize battery (12bit -> dec)
 * argument : void
 * return   : void
********************************************************************************************/
void Batt_Check(void)
{
  float batt=0;
  for(int i=0;i<10;i++){
    batt += batt_analog;
  }
  batt /= 10.0f;
  batt = batt/4095.0f*133.0f/33.0f*3.3f;
  batt_Vcc = batt;
  printf("\nbatt:%lf\r\n",batt);
}
