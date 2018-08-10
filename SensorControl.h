/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SensorControl.h
 * Author: SHALAKHA
 *
 * Created on February 20, 2018, 3:49 PM
 */

#ifndef SENSORCONTROL_H
#define SENSORCONTROL_H

#define LEFT_PI_SENSOR 7     // BCM GPIO4, Pi header pin 7.
#define RIGHT_PI_SENSOR 26

#include <wiringPi.h>

class SensorControl{   
public:
    SensorControl();
    virtual ~SensorControl();
public:
    bool TestLeftSensor();
    void SensorInt();
    int GetLeftSensorStatus();
    int GetRightSensorStatus();
    void ResetLeftSensorStatus();
    void ResetRightSensorStatus();
    bool TestRightSensor();  
};

#endif /* SENSORCONTROL_H */

