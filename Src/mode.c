#include "mode.h"
#include "global.h"
#include "gpio.h"
#include "tim.h"
#include "motion.h"
#include "control.h"
#include "spi.h"

maze_t maze;


/****************************************************************************************
 * outline  : return mode nomber
 * argument : void
 * return   : mode nomber 
********************************************************************************************/
int8_t Mode_select(void){
    int8_t mode=0;
    while(1){
        if((int16_t)enc.distance_l > 30 || (int16_t)enc.distance_l < -30){
            if((int16_t)enc.distance_l > 30){
                mode++;
            }else if((int16_t)enc.distance_l < -30){
                mode--;
            }
            if(mode > 6){
                mode = 0;
            }else if(mode < 0){
                mode = 6;
            }
            enc.distance_l = 0;
            Output_Buzzer(170-10*mode);
        }
        if(Push()==ON){
            Output_Buzzer(HZ_C_H);
            break;
        }
        LED_Control(mode);
        printf("%d\r",mode);
    }
    return mode;
}


/****************************************************************************************
 * outline  : wright mode 
 * argument : mode nomber
 * return   : void
********************************************************************************************/
void Mode_mouse(int8_t mode){
    switch(mode){
        case 0:
            Mode_Circuit();
            break;
        case 1:
            Mode_Straight();
            break;
        case 2:
            Mode_Turn_Half();
            break;
        case 3:
            Mode_Turn_Quarter_Left();
            break;
        case 4:
            Normal_Straight();
            break;
        case 5:
            Sensor_Mode();
            break;
        case 6:
            Test_Create_Map();
            break;
        default:
            break;
    }
}


void LeftHand(void){
    short flag_goal = false;
    Straight_HalF();
    while(flag_goal==false){
        while(flag.motion_end==true)
        if(sensor.wall[2] == false){
            Turn_Quarter_Left();
        }else if(sensor.wall[0]==true && sensor.wall[3]==true){
            Straight();
        }else if(sensor.wall[1]==true){
            Turn_Quarter_Right();
        }else{
            Turn_Half();
        }
    }
}

void Mode_Straight(void){
    flag.ir_led = ON;
    while(1){
        if(sensor.wall[0]==true && sensor.wall[3]==true){
            Output_Buzzer(HZ_C_H);
            break;
        }
    }
    flag.ir_led = OFF;
    gyro_offset_calc_reset();
    HAL_Delay(1500);
    Straight();
    while(1){
        if(Push()==ON){
            flag.straight = OFF;
            flag.yawrate = OFF;
            Output_Buzzer(HZ_A);
            break;
        }
    }
}

void Mode_Turn_Half(void){
    flag.ir_led = ON;
    while(1){
        if(sensor.wall[0]==ON && sensor.wall[3]==ON){
            Output_Buzzer(HZ_C_H);
            break;
        }
    }
    gyro_offset_calc_reset();
    HAL_Delay(1030);
    Output_Buzzer(HZ_C_H);
    Turn_Half();
    while(1){
        if(Push()==ON){
            flag.yawrate = OFF;
            flag.straight = OFF;
            Output_Buzzer(HZ_A);
            break;
        }
    }
}

void Mode_Turn_Quarter_Left(void){
    flag.ir_led = ON;
    while(1){
        if(sensor.wall[0]==ON && sensor.wall[3]==ON){
            Output_Buzzer(HZ_C_H);
            break;
        }
    }
    gyro_offset_calc_reset();
    HAL_Delay(1030);
    Output_Buzzer(HZ_C_H);
    Turn_Quarter_Left();
    while(1){
        if(Push()==ON){
            flag.yawrate = OFF;
            flag.straight = OFF;
            Output_Buzzer(HZ_A);
            break;
        }
    }
}

void Mode_Circuit(void){
    flag.ir_led = ON;
    while(1){
        if(sensor.wall[0]==ON && sensor.wall[3]==ON){
            Output_Buzzer(HZ_C_H);
            break;
        }
    }
    flag.ir_led = OFF;
    Straight();
    while(flag.motion_end==false){};
    Turn_Half();
    while(flag.motion_end==false){};
    Straight();
    while(flag.motion_end==false){};
}