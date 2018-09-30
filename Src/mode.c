#include "mode.h"
#include "global.h"
#include "gpio.h"
#include "tim.h"
#include "motion.h"
#include "control.h"

maze_t maze;


/****************************************************************************************
 * outline  : return mode nomber
 * argument : void
 * return   : mode nomber 
********************************************************************************************/
uint8_t Mode_select(void){
    uint8_t mode=0;
    flag.ir_led = ON;
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
            Show_log();
            break;
        case 2:
            Normal_Straight();
            break;
        case 3:
            Normal_Turn_Half();
            break;
        case 4:
            Normal_Ennkai();
            break;
        case 5:
            Straight();
            break;
        case 6:
            Turn_Half();
            break;
        case 7:
            Ennkai();
            break;
        case 8:
            Sensor_Mode();
            break;
        default:
            break;
    }
}


void LeftHand(void){
    short flag_goal = false;
    while(flag_goal==false){
        if(sensor.wall[2] == false){

        }else if(sensor.wall[0]==true && sensor.wall[3]==true){

        }else if(sensor.wall[1]==true){

        }else{

        }

    }
}

void Control_Motion(short dir){

}
