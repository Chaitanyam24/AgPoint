/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NumPad
 * Author: Dan
 *
 * Created on August 10, 2017, 5:35AM
 */

#ifndef _NUMPAD_H
#define _NUMPAD_H

#include "ui_NumPad.h"
#include <stdio.h>
#include <QString>
#include "SeedDbInterface.h"


class NumPad : public QDialog {
    Q_OBJECT
public:
    NumPad();
    ~NumPad();

private:
    Ui::NumPad widget;

private:
    void KeyPressed(QString);  
    void ExitToHomeWindow();
    
public slots:
    void KeyPressed0();
    void KeyPressed1();
    void KeyPressed2();
    void KeyPressed3();
    void KeyPressed4();
    void KeyPressed5();
    void KeyPressed6();
    void KeyPressed7();
    void KeyPressed8();
    void KeyPressed9();
    void KeyPressedEnter();
    void KeyPressedClear();
    
private:
    QString m_Setpoint;
    bool m_ReplaceSetpoint;
    
public:
    void SetSetpoint(int);
    int GetSetpoint();
    void SetNewValue();
};

#endif /* _NUMPAD_H*/
