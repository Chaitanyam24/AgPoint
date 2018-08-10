/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SolenoidControl.h
 * Author: SHALAKHA
 *
 * Created on December 19, 2017, 10:29 AM
 */


#ifndef SOLENOIDCONTROL_H
#define SOLENOIDCONTROL_H

// The following two defines are examples from the motor control class.  Change for solenoid outputs.  
// GPIO19 is the right solenoid and GPIO26 is the left solenoid.
#define PI_RIGHT_SOLENOID 24    // BCM GPIO19, Pi header pin 35.
#define PI_LEFT_SOLENOID 25     // BCM GPIO26, Pi header pin 36.

#include <wiringPi.h>
class SolenoidControl {
public:
    SolenoidControl();
    SolenoidControl(const SolenoidControl& orig);
    virtual ~SolenoidControl();
        bool GetRight();
    bool GetLeft();
    void Toggle();
    void EnableSolenoids(bool);
    bool GetSolenoidsState();
    
protected:
    void SetRight(bool RightState);
    void SetLeft(bool LeftState);
    
    
protected:
    bool m_LeftOn;
    bool m_RightOn;
    bool m_SolenoidsEnabled;

};

#endif /* SOLENOIDCONTROL_H */

