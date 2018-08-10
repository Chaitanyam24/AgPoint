/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LoadScreen.h
 * Author: SHALAKHA
 *
 * Created on November 2, 2017, 1:33 PM
 */

#ifndef _LOADSCREEN_H
#define _LOADSCREEN_H

#include "ui_LoadScreen.h"
#include "RotaryMotor.h"
#include <unistd.h>
#include <QTimer>
#include <QDialog>
class LoadScreen : public QDialog {
    Q_OBJECT
public:
    LoadScreen();
    virtual ~LoadScreen();
    
private:
    Ui::LoadScreen widget;
    
private:
    RotaryMotor m_RotateToLoad;
    int ChuteNumber;
    QTimer *loadRefreshtimer = new QTimer(this);
    
public slots:
    void ManualLoadUnload();
    void TimerCallRotate();
    void AutomaticLoadUnload();
    void ExitToCountScreen();
    
};

#endif /* _LOADSCREEN_H */
