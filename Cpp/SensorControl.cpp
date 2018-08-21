/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SensorControl.cpp
 * Author: SHALAKHA
 * 
 * Created on February 20, 2018, 3:49 PM
 */

#include "SensorControl.h"

static volatile bool LeftSensor;
static volatile bool RightSensor;
static volatile int countRight;
static volatile int countLeft;
SensorControl::SensorControl() 
{
    wiringPiSetup();   
    pinMode(LEFT_PI_SENSOR,INPUT);
    pinMode(RIGHT_PI_SENSOR,INPUT);
    pullUpDnControl (LEFT_PI_SENSOR, PUD_OFF);
    pullUpDnControl (RIGHT_PI_SENSOR, PUD_OFF);
    digitalRead(RIGHT_PI_SENSOR)? RightSensor= true : RightSensor= false;  //digital 1 object detected
    digitalRead(LEFT_PI_SENSOR) ? LeftSensor= true : LeftSensor= false;
    SensorInt();
}

SensorControl::~SensorControl() {
}

bool SensorControl::TestLeftSensor()
{
    int i=digitalRead(LEFT_PI_SENSOR);
    if (i==1) {return true ;}
    else {return false; } 
}
bool SensorControl::TestRightSensor()
{
    int i=digitalRead(RIGHT_PI_SENSOR);
    if (i==1) {return true ;}
    else {return false; } 
}
void LeftSensorIntHandler(void)
{
    countLeft++;
}
void RightSensorIntHandler(void)
{
   countRight++;
}

void SensorControl::SensorInt()
{
    wiringPiISR(LEFT_PI_SENSOR, INT_EDGE_RISING, &LeftSensorIntHandler ) ;
    wiringPiISR(RIGHT_PI_SENSOR, INT_EDGE_RISING, &RightSensorIntHandler ) ;
}

int SensorControl::GetLeftSensorStatus()
{
    return countLeft;
}

int SensorControl::GetRightSensorStatus()
{
    return countRight;
}

void SensorControl::ResetLeftSensorStatus()
{
    countLeft=0;
}

void SensorControl::ResetRightSensorStatus()
{
    countRight=0;
}