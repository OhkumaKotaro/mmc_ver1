#include "control.h"
#include <stdint.h>
#include "global.h"
#include "tim.h"
#include "arm_math.h"
#include "main.h"
#include "stm32f4xx_hal.h"

/****************************************************************************************
 * outline  : PID control
 * argument : 
 * return   : control value
********************************************************************************************/
int16_t PID_value(float target,float measured,float *sum,float*old,float Kp,float Ki,float Kd,int16_t maximum){
    float error = 0.00f ;
    float p,i,d;

    error = target - measured;
    *sum = error * dt;
    p = error * Kp;
    i = *sum * Ki;
    d = (measured - *old) * Kp;

    *old = measured;

    if((p + i + d) > maximum){
        p = maximum;
        i = d = 0;
    }
    if((p+i+d) < -maximum){
        p = -maximum;
        i = d = 0;
    }

    return (p + i + d);
}

/****************************************************************************************
 * outline  : calculate parameter
 * argument : accel_light,accel_right
 * return   : control value
********************************************************************************************/
void Calculate_Parameter(int accel_l,int accel_r){
    calc.distance_l += calc.velocity_l * dt; 
    calc.distance_r += calc.velocity_r * dt;
    calc.velocity_l += accel_l * dt;
    calc.velocity_r += accel_r * dt;
}
//argument : accel[mm/s^2]
void control_accel(int16_t accel_l,int16_t accel_r){
  float pwm_l,pwm_r;
  //torque[mNm] = weight[g] * 0.001 * accel[mm/s^2] * 0.001 * tire_radius[mm] / 2 / gear_rate
  //pwm =( R * torque[mNM] / KT[mNm/A] + KE[mV/rpm] * rpms * 60) / Vcc
  pwm_l = (Resistance * WEIGHT * accel_l * TIRE_RADIUS / 2 / GEAR_RATE / KT + KE * enc.rpms_left * 60)* 999 /batt_Vcc;
  pwm_r = (Resistance * WEIGHT * accel_r * TIRE_RADIUS / 2 / GEAR_RATE / KT + KE * enc.rpms_right * 60)* 999 /batt_Vcc;

  motor.pwm_l = (int16_t)pwm_l;
  motor.pwm_r = (int16_t)pwm_r;

  //Motor_pwm(pwm_l,pwm_r);

}

/****************************************************************************************
 * outline  : straight run one block
 * argument : void
 * return   : void
********************************************************************************************/
void straight_one_ff(void){
    if(flag.accel == OFF){
        motor.pwm_l = 0;
        motor.pwm_r = 0;
    }
    else if(flag.accel == ON){
        speed_count = 0;
        flag.accel = 2;
    }else if(flag.accel == 2){
        if(speed_count < 300){
            control_accel(1000,1000);
        }

        if(speed_count >= 300 && speed_count < 600){
            motor.pwm_l = 0;
            motor.pwm_r = 0;
        }

        if(speed_count >= 600 && speed_count < 900){
            control_accel(-1000,-1000);
        }
        if(speed_count >= 900){
            flag.accel = OFF;
        }
    }
}


void straight_fb(int v_start,int v_end,int accel,int distance,int v_max){
    float t1,t3;
    calc.distance_l = 0;
    calc.distance_r = 0;
    calc.velocity_l = v_start;
    calc.velocity_r = v_start;
    t1 = (float)(v_max - v_start) / accel;
    accel_L = v_start * t1 + 0.50f * accel * t1 * t1;
    t3 = (float)(v_max - v_end) / accel;
    decrease_L = v_end * t3 + 0.50f * accel * t3 * t3;
    constant_L = (float)distance - accel_L - decrease_L;
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

