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
float PID_value(float target,float measured,float *sum,float*old,float Kp,float Ki,float Kd){
    float error;
    float p,i,d;

    error = target - measured;
    p = Kp*error;

    *sum += error * dt;
    i = Ki * *sum;

    *old = measured;
    d = Kd * (measured - *old);

    return (p+i+d)/batt_Vcc;
}

/****************************************************************************************
 * outline  : calculate parameter
 * argument : accel,*velocity,*distance
 * return   : void
********************************************************************************************/
void Calc_Palam(int16_t accel,int16_t *velocity,uint16_t *calc_tim){
    *calc_tim += 1;
    *velocity += accel * dt;
}


/****************************************************************************************
 * outline  : calcurate accele distance
 * argument : distance[mm],v_start[mm/s],v_end[mm/s]
 * return   : void
********************************************************************************************/
void Straight_Calc_fb(int16_t distant,int16_t v_start,int16_t v_end){
    float t1,t2,t3;
    float constant_L;
    calc.velocity = v_start;
    t1 = (float)(MAX_VELOCITY - v_start) / ACCEL;
    t3 = (float)(MAX_VELOCITY - v_end) / ACCEL;

    constant_L = (float)distant - (MAX_VELOCITY + v_start) * t1 / 2 - (MAX_VELOCITY + v_start) * t3 / 2;

    t2 = constant_L / MAX_VELOCITY;
    printf("\nt1:%f,t2:%f,t3%f\r\n",t1,t2,t3);

    t1 *= 1000;
    t2 *= 1000;
    t3 *= 1000;

    accel_T = t1;
    constant_T = t2;
    decrease_T = t3;
}


/****************************************************************************************
 * outline  : output pwm for trapezoid accele straight by feadbuck control
 * argument : void
 * return   : void
********************************************************************************************/
void Straight_SysTic_fb(void){
    int16_t straight_pid_l,straight_pid_r;
    if(ms_count < accel_T){
        Calc_Palam(ACCEL,&calc.velocity,&ms_count);
    }
    else if(ms_count < constant_T + accel_T){
        Calc_Palam(0,&calc.velocity,&ms_count);
    }
    else if(ms_count < decrease_T + constant_T + accel_T){
        Calc_Palam(-ACCEL,&calc.velocity,&ms_count);
    }else{
        calc.velocity = 0;
        flag.straight = OFF;
    }
    
    
    straight_pid_l = (int16_t)PID_value(calc.velocity,enc.velocity_l,&s_sum_l,&enc.old_l,20.0f,90.0f,0);
    straight_pid_r = (int16_t)PID_value(calc.velocity,enc.velocity_r,&s_sum_r,&enc.old_r,20.0f,90.0f,0);
    Motor_pwm(straight_pid_l,straight_pid_r);
}


/****************************************************************************************
 * outline  : calcurate trapezoid accel
 * argument : degree[degree],v_start[degree/s],v_end[degree/s]
 * return   : void
********************************************************************************************/
void Yawrate_Calc_fb(int16_t degree,int16_t v_start,int16_t v_end){
    calc.yawrate_degree = 0;
    calc.yawrate_velocity = v_start;
    if(degree == 0){
        y_accel_T = 0;
        y_constant_T = 0;
        y_decrease_T = 0;
    }
    else{

    }
}


/****************************************************************************************
 * outline  : call 1ms (roll by feadbuck control)
 * argument : void
 * return   : void
********************************************************************************************/
void Yawrate_SysTic_fb(void){
    int16_t yawrate_pid;
    if(calc.yawrate_degree <= y_accel_T){
        Calc_Palam(Y_ACCEL,&calc.yawrate_velocity,&ms_count);
    }else if(calc.yawrate_degree <= y_constant_T){
        Calc_Palam(0,&calc.yawrate_velocity,&ms_count);
    }else if(calc.yawrate_degree <= y_decrease_T){
        Calc_Palam(-Y_ACCEL,&calc.yawrate_velocity,&ms_count);
    }
    yawrate_pid = (int16_t)PID_value((float)calc.yawrate_velocity,gyro.velocity,&gyro.degree,&gyro.befor,12.0f,0.0f,20.0f);
    Motor_pwm(-yawrate_pid,yawrate_pid);
}


/****************************************************************************************
 * outline  : turn on buzzer 0.3sec
 * argument : Hz
 * return   : void
********************************************************************************************/
void Output_Buzzer(uint8_t Hz){
    Buzzer_pwm(Hz,300);
    HAL_Delay(300);
    Buzzer_pwm(HZ_NORMAL,0);
}


/****************************************************************************************
 * outline  : straight run one block
 * argument : accel[mm/s^2]
 * return   : void
********************************************************************************************/
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


/****************************************************************************************
 * outline  : sensor check
 * argument : void
 * return   : void
********************************************************************************************/
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


