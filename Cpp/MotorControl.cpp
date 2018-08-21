/*
 * Using PWM to an inverting op-amp.  Writing a 0 sets the highest speed.
 */

/* 
 * File:   MotorControl.cpp
 * Author: Dan
 * 
 * Created on March 2, 2017, 5:24 AM
 */

#include <unistd.h>
#include "MotorControl.h"

MotorControl::MotorControl() 
{
    m_WasAtZero = true;
    wiringPiSetup();
    int success =  softPwmCreate (PI_MOTOR_SPEED_CONTROL, 0, 100);
    softPwmWrite (PI_MOTOR_SPEED_CONTROL, 100) ;  // PWM to zero.
    
    pinMode(PI_MOTOR_SPEED_ZERO,OUTPUT);
    pullUpDnControl (PI_MOTOR_SPEED_ZERO, PUD_OFF);   // Might need pull up off.
    digitalWrite(PI_MOTOR_SPEED_CONTROL,LOW);   // Keep signal to motor at zero.
    
    
}

MotorControl::MotorControl(const MotorControl& orig) {
}

MotorControl::~MotorControl() 
{
    /*softPwmWrite (PI_MOTOR_SPEED_CONTROL, 100);
    pinMode(PI_MOTOR_SPEED_ZERO,OUTPUT);
    digitalWrite(PI_MOTOR_SPEED_CONTROL,LOW);
    m_WasAtZero = true;
     */
}

// Just a test.
void MotorControl::TestPwm()
{
    m_WasAtZero = true;
    pinMode(PI_MOTOR_SPEED_ZERO,INPUT);
    pullUpDnControl (PI_MOTOR_SPEED_ZERO, PUD_OFF);// test
    softPwmWrite (PI_MOTOR_SPEED_CONTROL, 100) ;
    usleep(2000000); // delay for 2s.  
    softPwmWrite (PI_MOTOR_SPEED_CONTROL, 0) ;
    pinMode(PI_MOTOR_SPEED_ZERO,OUTPUT);
    digitalWrite(PI_MOTOR_SPEED_CONTROL,LOW);
    m_WasAtZero = true;
}

void MotorControl::SetSpeed(int speed)
{
    if(0 == speed)
    {
        if(m_WasAtZero)
        {
            // Already at zero.  Do nothing.
            
        }
        else
        {
            softPwmWrite (PI_MOTOR_SPEED_CONTROL, 100);
            pinMode(PI_MOTOR_SPEED_ZERO,OUTPUT);
            digitalWrite(PI_MOTOR_SPEED_CONTROL,LOW);
            
            m_WasAtZero = true;
            
        }
    }
    else
    {
        if(m_WasAtZero)
        {
            pinMode(PI_MOTOR_SPEED_ZERO,INPUT);
            pullUpDnControl (PI_MOTOR_SPEED_ZERO, PUD_OFF);
            softPwmWrite (PI_MOTOR_SPEED_CONTROL, speed);
            m_WasAtZero = false;
            
        }
        else
        {
            pinMode(PI_MOTOR_SPEED_ZERO,INPUT); // test
            pullUpDnControl (PI_MOTOR_SPEED_ZERO, PUD_OFF);// test
            softPwmWrite (PI_MOTOR_SPEED_CONTROL, speed);
            
        }
    }
        
}

