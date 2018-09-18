#include "control.h"
#include "stdint.h"
#include "global.h"
#include "tim.h"
#include "arm_math.h"
#include "main.h"
#include "stm32f4xx_hal.h"

//argument : accel[mm/s^2]
void control_accel(int16_t accel_l,int16_t accel_r){
  int8_t pwm_l,pwm_r;

  pwm_l = KT*0.001*accel_l/2.0/TIRE_RADIUS/PI*60.0*60.0/sit.batt;
  pwm_r = KT*0.001*accel_r/2.0/TIRE_RADIUS/PI*60.0*60.0/sit.batt;

  motor.pwm_l += pwm_l;
  motor.pwm_r += pwm_r;

  //Motor_pwm(pwm_l,pwm_r);

}

/****************************************************************************************
 * outline  : straight run one block
 * argument : void
 * return   : void
********************************************************************************************/
void straight_one(void){
    if(flag.accel == OFF){
        motor.pwm_l = 0;
        motor.pwm_r = 0;
        speed_count = 0;
    }else if(flag.accel == ON){
        if(speed_count < 300){
            motor.pwm_l = 999*(Resistance*TORQUE/KT+KE*0.001*enc.rpm_l)/sit.batt;
            motor.pwm_r = motor.pwm_l;
        }

        if(speed_count >= 300 && speed_count < 600){
            motor.pwm_l = 0;
            motor.pwm_r = 0;
        }

        if(speed_count >= 600 && speed_count < 900){
            motor.pwm_l = 999*(-Resistance*TORQUE/KT+KE*0.001*enc.rpm_l)/sit.batt;
            motor.pwm_r = motor.pwm_l;
        }
        if(speed_count >= 900){
            flag.accel = OFF;
        }
        speed_count ++;
    }
}

void Sensor_Check(void){
    if(sensor.wall[0]==true){
        HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,GPIO_PIN_RESET);
    }else{
        HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,GPIO_PIN_SET);
    }
    if(sensor.wall[1]==true){
        HAL_GPIO_WritePin(led3_GPIO_Port,led3_Pin,GPIO_PIN_RESET);
    }else{
        HAL_GPIO_WritePin(led3_GPIO_Port,led3_Pin,GPIO_PIN_SET);
    }
    if(sensor.wall[2]==true){
        HAL_GPIO_WritePin(led2_GPIO_Port,led2_Pin,GPIO_PIN_RESET);
    }else{
        HAL_GPIO_WritePin(led2_GPIO_Port,led2_Pin,GPIO_PIN_SET);
    }
    if(sensor.wall[3]==true){
        HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_RESET);
    }else{
        HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_SET);
    }
    
}