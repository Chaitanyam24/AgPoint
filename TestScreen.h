/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestScreen.h
 * Author: SHALAKHA
 *
 * Created on October 30, 2017, 1:50 PM
 */

#ifndef _TESTSCREEN_H
#define _TESTSCREEN_H

#include "ui_TestScreen.h"

#define TT_COUNT_REFRESH_TIMER_INTERVAL 35    // In ms.

#include <stdio.h>
#include "NumPad.h"
#include <QString>
#include <QDialog>
#include <QTimer>
#include <string>
#include <time.h>
#include <sys/time.h>
#include "DFG2Counter.h"
#include "MotorControl.h"
#include "SeedDbInterface.h"
#include "CounterConfig.h"
#include "MotorNumPad.h"
#include <cstdlib>

class TestScreen : public QDialog {
    Q_OBJECT
public:
    TestScreen();
    virtual ~TestScreen();
private:
    Ui::TestScreen widget;
    
public slots:
    void UpdateCount();
    void ZeroCount();
    void MotorTest();
    void ChangeMotorSpeed(int speed);
    void ExitToHomeWindow();
    void CalibrateCounter();
    //void DisplayNumPad();
    void CheckforSeeds();
    void DisplayMotorNumPad();
    void StartMotor();
    void IncreaseMotorSpeed();
    void DecreaseMotorSpeed();
    //void EnableDisableSetpoint();
    void StopCounting();
    void PauseContinue();
private:
    bool m_Var;
    bool m_OutputHigh;
    //bool m_SetpointEnabled;
   // int m_Setpoint;
    bool CountingStatus;
    int m_SetMotorSpeed;
    QString m_CountLblText;
    DFG2Counter m_SeedCounter;
    MotorControl m_Motor;
    SeedDbInterface m_DbTest;
    //NumPad m_SetpointNumPad;
    MotorNumPad m_MotorNumPad;
    int countchange;
    int totalSeedCount;
    bool PauseStatus;
};

#endif /* _TESTSCREEN_H */
