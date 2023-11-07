#include "PID.h"

void PIDController_Init(PIDController *pid, float kp, float ki, float kd) {
  // initializes the PID controller object
  pid->kp = kp;
  pid->ki = ki;
  pid->kd = kd;

  pid->error = 0.0f;
  
  pid->integrator = 0.0f;
  pid->prevError = 0.0f;

  pid->differentiator = 0.0f;

  pid->output = 0.0f;
}

float PIDController_Update(PIDController *pid, float reference, float sensor) {

  // TODO make even faster with fixed floating point arithmetic 
  pid->error = reference - sensor;
  pid->proportional = pid->error * pid->kp;

  pid->differentiator = (pid->error - pid->prevError) / pid->kd;

  pid->integrator += (pid->error * pid->dt);

  pid->prevError = pid->error;
  pid->output = pid->proportional + pid->differentiator + pid->integrator;
  return pid->output;
}