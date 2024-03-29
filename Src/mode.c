#include "mode.h"
#include "global.h"
#include "gpio.h"
#include "tim.h"
#include "motion.h"
#include "control.h"
#include "spi.h"
#include "adc.h"
#include "maze.h"

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
            HAL_Delay(500);
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
            //Mode_Adachi();
            flag.ir_led=ON;
            flag.fr_wall=ON;
            break;
        case 1:
            LeftHand();
            break;
        case 2:
            PT_Switch();
            gyro_offset_calc_reset();
            HAL_Delay(2000);
            Motion_Left();
            break;
        case 3:
            PT_Switch();
            gyro_offset_calc_reset();
            HAL_Delay(2000);
            Motion_Right();
            break;
        case 4:
            PT_Switch();
            gyro_offset_calc_reset();
            HAL_Delay(4000);
            flag.ir_led = ON;
            if(sensor.wall[5]==false){
                flag.kabeate=false;
            }else{
                flag.kabeate=true;
            }
            Motion_Uturn();
            break;
        case 5:
            PT_Switch();
            gyro_offset_calc_reset();
            HAL_Delay(2000);
            Motion_Kabeate();
            break;
        case 6:
            //Show_log();
            Sensor_Mode();
            break;
        default:
            break;
    }
}


void LeftHand(void){
    flag.ir_led = ON;
    uint8_t flag_goal_is=false;
    Maze_Set();

    while(1){
        if(sensor.wall[4]==ON){
            Output_Buzzer(HZ_C_H);
            break;
        }
    }
    flag.ir_led = OFF;
    gyro_offset_calc_reset();
    HAL_Delay(2000);
    flag.ir_led = ON;
    flag.motion_end = true;
    Motion_Start();
    position.x=0;
    position.y=1;

    while(flag_goal_is==false){
        if( sensor.wall[2]==false ){
            flag.next_dir = LEFT;
        }else if( sensor.wall[5] ==false ){
            flag.next_dir = STRAIGHT;
        }else if( sensor.wall[1] == false ){
            flag.next_dir = RIGHT;
        }else{
            flag.next_dir = UTURN;
        }

        Update_Position(flag.next_dir);
        Maze_GoalCheck(flag_goal_is);
        HAL_Delay(200);
        switch( flag.next_dir ){
            case LEFT:
                Motion_Left();
                break;

            case STRAIGHT:
                Motion_Straight();
                break;
            
            case RIGHT:
                Motion_Right();
                break;

            case UTURN:
                Motion_Uturn();
                break;
        }
    }
    Motion_Goal();
}

void Mode_Adachi(void){
    uint8_t flag_goal_is=false;
    int8_t next_dir;

   
    Init_maze();

    flag.ir_led = ON;
    while(1){
        if(sensor.wall[4]==true){
            Output_Buzzer(HZ_C_H);
            break;
        }
    }
    gyro_offset_calc_reset();
    HAL_Delay(2000);
    Motion_Start();
    position.x=0;
    position.y=1;
    position.dir=NORTH;
    Maze_Set();
    
    while(flag_goal_is==false){
        Maze_Get_Wall(position.x,position.y);
        MAZE_Create_Step();
        HAL_Delay(200);
        next_dir=Maze_Next_Motion();
        Update_Position(next_dir);
        if(position.x==mazeDef.maze_goal_x && position.y==mazeDef.maze_goal_y){
            flag_goal_is=true;
        }

        switch( next_dir ){
            case LEFT:
                Motion_Left();
                break;

            case STRAIGHT:
                Motion_Straight();
                break;
            
            case RIGHT:
                Motion_Right();
                break;

            case UTURN:
                Motion_Uturn();
                break;
            case KABEATE:
                Motion_Kabeate();
                break;
        }
    }
    Motion_Goal();
}

void Mode_Circuit(void){
    flag.ir_led = ON;
    while(1){
        if(sensor.wall[4]==true){
            Output_Buzzer(HZ_C_H);
            break;
        }
    }
    flag.ir_led=OFF;
    gyro_offset_calc_reset();
    HAL_Delay(2000);
    flag.ir_led=ON;
    Motion_Straight_Check();
    //Motion_Start();    
}