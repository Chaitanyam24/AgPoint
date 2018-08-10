/*
 * Copyright:  The Gwenilla House, 2017.
 */

/* 
 * File:   MotorControl.h
 *
 * Created on March 2, 2017, 5:24 AM
 * 
 * Used to control the 0-5V input of a motor controller.  0V = slowest.
 * 5V = fastest.  A PWM is run into a low pass filter to create the 0-5V.
 * Note:  The speed of the motor does not need to be changed "quickly".
 * 
 */

#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#define PI_MOTOR_SPEED_CONTROL 3 // BCM GPIO22, Pi header pin 15, GPIO_GEN3.
#define PI_MOTOR_SPEED_ZERO 4       // BCM GPIO23, Pi header pin 16, GPIO_GEN4.

#include <wiringPi.h>
#include <softPwm.h>

class MotorControl {
public:
    MotorControl();
    MotorControl(const MotorControl& orig);
    virtual ~MotorControl();
    void TestPwm();
    void SetSpeed(int speed);
private:
    bool m_WasAtZero;  

};

#endif /* MOTORCONTROL_H */

