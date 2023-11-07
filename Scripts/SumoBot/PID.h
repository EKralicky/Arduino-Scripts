#ifndef PID_H
#define PID_H

typedef struct {
  
  float error;

  float kp;
  float ki;
  float kd;

  float dt;

  float proportional;

  float integrator;
  float prevError;

  float differentiator;

  float output;
} PIDController;

void PIDController_Init(PIDController *pid, float kp, float ki, float kd);
float PIDController_Update(PIDController *pid, float reference, float sensor);

#endif