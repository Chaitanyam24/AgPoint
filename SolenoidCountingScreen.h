/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SolenoidCountingScreen.h
 * Author: SHALAKHA
 *
 * Created on December 19, 2017, 10:33 AM
 */

#ifndef _SOLENOIDCOUNTINGSCREEN_H
#define _SOLENOIDCOUNTINGSCREEN_H

#include "ui_SolenoidCountingScreen.h"

#define D_COUNT_REFRESH_TIMER_INTERVAL 20    // In ms.
#define D_INTERRUPT_REFRESH_TIMER_INTERVAL 250 
#define D_CHECK_TIMER_INTERVAL 240000 // 240000 msecs
#include <stdio.h>
#include "ui_CountingScreen.h"
#include "MotorNumPad.h"
#include "PrinterCommands/PrinterCommands.h"
#include "NumPad.h"
#include <QString>
#include <QDialog>
#include "DFG2Counter.h"
#include "MotorControl.h"
#include "SolenoidControl.h"
#include "SeedDbInterface.h"
#include "CounterConfig.h"
#include "SensorControl.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <QTimer>


class SolenoidCountingScreen : public QDialog {
    Q_OBJECT
public:
    SolenoidCountingScreen();
    virtual ~SolenoidCountingScreen();
    void InitializeDVariables(bool,int,int,int,bool); //bag #, sp, speed
    int * GetDVariables();
private:
    Ui::SolenoidCountingScreen widget;
    
public slots:
    void UpdateCount();
    void ZeroCount();
    void MotorTest();
    void ChangeMotorSpeed(int speed);
    void ExitToHomeWindow();
    void ToggleSolenoids();
    void DisplayCounterSetupWindow();
    void DisplayMotorNumPad();
    void DisplayNumPad();
    void EnableDisableSetpoint();
    void EnableDisableSolenoids();
    void CallPrint();
    void SetPrinterFD(int);
    void CallCalibrate();
    void PauseContinue();
    void StopCounting();
    void DecreaseMotorSpeed();
    void IncreaseMotorSpeed();
    void StartMotor();
    void DisplayBagNumber();
    void SaveDataToTxtFile();
    void SetPrintMode(bool);
    void SetPrintFormat(bool);
    void SetLotCode(QString);
    void SetProductID(QString);
    bool GetSPStatus();
    void PrintForDualChute();
    void SetBagMode(bool);
    bool GetBagMode();
    void ToggleBagMode();
    void CallSetBagNumber();
    void RightSensor();
    void LeftSensor();
    void CallCheckBag();
    int GetReducedSetPoint();
    void CheckforSeeds();
    void RightSensorIntStatus();
    void LeftSensorIntStatus();
private:
    bool m_Var;
    bool m_OutputHigh;
    bool m_SetpointEnabled;
    bool m_MotorStatus;
    bool CountingStatus;
    bool CountTimer;
    //m_SetMotorSpeed=0;
    bool PauseStatus;
    bool m_CheckSeeds;
    //bool m_SolenoidsEnabled;
    int m_Setpoint;
    int BagNumber;
    int m_SetMaxBagNumber;
    bool PrintMode;
    bool PrintFormat;
    bool BagOnOff;
    QString LotCode;
    QString ProductID;
    QString m_CountLblText;
    DFG2Counter m_SeedCounter;
    MotorControl m_Motor;
    SeedDbInterface m_DbTest;
    SolenoidControl m_Solenoids;
    NumPad m_SetpointNumPad;
    int  m_SetMotorSpeed;
    MotorNumPad m_MotorNumPad;
    SensorControl m_Sensor;
    PrinterCommands m_PrinterCommands;
    std::fstream WebFile;
    std::fstream PrintFile;
    std::fstream SinglePrintFile;
    std::fstream DualFile;
    int VarArray[3];
    QTimer *checkRefreshtimer = new QTimer(this);
    volatile int countchange;
};

#endif /* _SOLENOIDCOUNTINGSCREEN_H */
