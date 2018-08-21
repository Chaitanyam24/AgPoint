/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MotorNumPad.h
 * Author: SHALAKHA
 *
 * Created on October 11, 2017, 5:13 PM
 */

#ifndef _MOTORNUMPAD_H
#define _MOTORNUMPAD_H

#include "ui_MotorNumPad.h"
#include <QDialog>
class MotorNumPad : public QDialog {
    Q_OBJECT
public:
    MotorNumPad();
    virtual ~MotorNumPad();
private:
    Ui::MotorNumPad widget;

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
    QString m_MotorSpeed;
    bool m_ReplaceSpeed;
    
public:
    void SetSpeed(int);
    int GetSpeed();
    void SetNewValue();
    void BlanklblValue();
};

#endif /* _MOTORNUMPAD_H */
