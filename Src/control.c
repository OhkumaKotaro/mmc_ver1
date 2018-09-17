#include "control.h"
#include "stdint.h"
#include "global.h"
#include "tim.h"
#include "arm_math.h"

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
        sit.batt = 7.72;
        motor.pwm_l = 0;
        motor.pwm_r = 0;
        speed_count = 0;
    }else if(flag.accel == ON){
        if(speed_count < 300){
            motor.pwm_l = 999*(Resistance*0.114285714285714/KT+KE*ms_count*0.01/PI/TIRE_RADIUS*3.0)/sit.batt;
            motor.pwm_r = motor.pwm_l;
        }

        if(speed_count >= 300 && speed_count < 600){
            motor.pwm_l = 0;
            motor.pwm_r = 0;
        }

        if(speed_count >= 600 && speed_count < 900){
            motor.pwm_l = 999*(-Resistance*0.114285714285714/KT+KE*0.001*(300-ms_count+599)/2.0/PI/TIRE_RADIUS*60.0)/sit.batt;
            motor.pwm_r = motor.pwm_l;
        }
        if(speed_count >= 900){
            flag.accel = OFF;
        }
        speed_count ++;
    }
    Motor_pwm(motor.pwm_l,motor.pwm_r);
}