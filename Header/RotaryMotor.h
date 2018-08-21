/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RotaryMotor.h
 * Author: SHALAKHA
 *
 * Created on September 16, 2017, 4:28 PM
 */

#ifndef ROTARYMOTOR_H
#define ROTARYMOTOR_H

#include <wiringSerial.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <stdio.h>

class RotaryMotor {
public:
    RotaryMotor();
    virtual ~RotaryMotor();
    void Rotate45();
    void RotaryStop();
    void RotatePositive();
    void RotateNegative();
    bool CheckConn();
    void RotateToSpecficValue(int);
    void GetPositionFromFile();
    void RotateToZero();
    void RotateToNextChute(int);
    void SetZeroPosition();
    bool CheckConnection();
    bool CheckForError();
    bool Reconnect();
private:
    int UsbConn;
    int error;
    signed int ChutePosition[8];
};


#endif /* ROTARYMOTOR_H */

