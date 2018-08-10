/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SetHomePosition.h
 * Author: SHALAKHA
 *
 * Created on November 8, 2017, 1:51 PM
 */

#ifndef _SETHOMEPOSITION_H
#define _SETHOMEPOSITION_H

#include "ui_SetHomePosition.h"
#include "RotaryMotor.h"

class SetHomePosition : public QDialog {
    Q_OBJECT
public:
    SetHomePosition();
    virtual ~SetHomePosition();
    
private:
    Ui::SetHomePosition widget;
  
private slots:
    void IncreasePosition();
    void DecreasePosition();
    void SetHomePositionDone();
    void ExitToCountScreen();
    void ResetVariables();
    void CallPositionZero();
    void CheckMotorConnection();
    void RefreshConnection();
    void CheckForError();
private:
    void SavePositionToFile();
    signed int ChutePosition[8];  
    int ChuteNumber;
    signed int PositionValue;
    RotaryMotor m_SetRotaryPosition;   
};

#endif /* _SETHOMEPOSITION_H */
