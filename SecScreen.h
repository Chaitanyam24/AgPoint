/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SecScreen.h
 * Author: Owner
 *
 * Created on July 18, 2018, 3:07 PM
 */

#ifndef _SECSCREEN_H
#define _SECSCREEN_H
#include "RotaryMotor.h"
#include "ui_SecScreen.h"
#include "SensorControl.h"
#include <unistd.h>
#include <QDialog>
class SecScreen : public QDialog {
    Q_OBJECT
public:
    SecScreen();
    virtual ~SecScreen();
private:
    Ui::SecScreen widget;
    
private:
    RotaryMotor m_RotateToLoad;
    
    SensorControl m_Sensor;
    
public slots:
    void ManualLoadUnload();
    void ExitToCountScreen();    
    void SensorStatus();
    
};

#endif /* _SECSCREEN_H */
