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
float PID_value(float target,float measured,float *sum,float*old,float Kp,float Ki,float Kd,int16_t maximum){
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

    return (p + i + d)/batt_Vcc;
}

/****************************************************************************************
 * outline  : calculate parameter
 * argument : accel_light,accel_right
 * return   : control value
********************************************************************************************/
void Calc_Palam(int16_t accel,int16_t *velocity,int16_t *distance){
    *distance =+ *velocity * dt;
    *velocity =+ accel * dt;
}


void Straight_Calc_fb(int16_t distant,int16_t v_start,int16_t v_end){
    float t1,t2;
    calc.distance = 0;
    calc.velocity = v_start;
    t1 = (float)(MAX_VELOCITY - v_start) / ACCEL;
    t2 = (float)(MAX_VELOCITY - v_end) / ACCEL;

    accel_L = 0.50f * (MAX_VELOCITY + v_start) * t1;
    constant_L = distant - 0.50f * (MAX_VELOCITY + v_start) * t2;
    decrease_L = distant;
}

void Straight_SysTic_fb(void){
    int16_t straight_pid_l,straight_pid_r;
    if(calc.distance < accel_L){
        Calc_Palam(ACCEL,&calc.velocity,&calc.distance);
    }else if(calc.distance < constant_L){
        Calc_Palam(0,&calc.velocity,&calc.distance);
    }else if(calc.distance < decrease_L){
        Calc_Palam(-ACCEL,&calc.velocity,&calc.distance);
    }
    
    straight_pid_l = (int16_t)PID_value((float)calc.velocity,enc.velocity_l,&enc.distance_l,&enc.old_l,0.1f,0,0,800);
    straight_pid_r = (int16_t)PID_value((float)calc.velocity,enc.velocity_r,&enc.distance_r,&enc.old_r,0.1f,0,0,800);
    Motor_pwm(straight_pid_l,straight_pid_r);
}

void Yawrate_Calc_fb(int16_t degree,int16_t v_start,int16_t v_end){
    calc.yawrate_degree = 0;
    calc.yawrate_velocity = v_start;
    if(degree == 0){
        y_accel_L = 0;
        y_constant_L = 0;
        y_decrease_L = 0;
    }
    else{
        float t1,t2;

        t1 = (Y_MAX_VELOCITY - v_start) / Y_ACCEL;
        t2 = (Y_MAX_VELOCITY - v_end) / Y_ACCEL;

        y_accel_L = 0.5f * (v_start + Y_MAX_VELOCITY) * t1;
        y_constant_L = degree - 0.5f * (v_end + Y_MAX_VELOCITY) * t2; 
        y_decrease_L = degree;
    }
}

void Yawrate_SysTic_fb(void){
    int16_t yawrate_pid;
    if(calc.yawrate_degree < y_accel_L){
        Calc_Palam(Y_ACCEL,&calc.yawrate_velocity,&calc.yawrate_degree);
    }else if(calc.yawrate_degree < y_constant_L){
        Calc_Palam(0,&calc.yawrate_velocity,&calc.yawrate_degree);
    }else if(calc.yawrate_degree < y_decrease_L){
        Calc_Palam(-Y_ACCEL,&calc.yawrate_velocity,&calc.yawrate_degree);
    }
    yawrate_pid = (int16_t)PID_value((float)calc.yawrate_velocity,gyro.velocity,&gyro.degree,&gyro.befor,8.0f,0,0,800);
    Motor_pwm(-yawrate_pid,yawrate_pid);
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


