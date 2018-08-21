/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CountingScreen.h
 * Author: Dan
 *
 * Created on June 12, 2017, 5:39 AM
 */

#ifndef _COUNTINGSCREEN_H
#define _COUNTINGSCREEN_H

#define COUNT_REFRESH_TIMER_INTERVAL 35  // In 50 ms.
#define C_CHECK_TIMER_INTERVAL 240000 //  240000

#include <stdio.h>
#include "ui_CountingScreen.h"
#include "NumPad.h"
#include "LoadScreen.h"
#include "SecScreen.h"
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
#include "RotaryMotor.h"
#include "MotorNumPad.h"
#include "SetHomePosition.h"
#include "PrinterCommands/PrinterCommands.h"
#include "SensorControl.h"
#include <cstdlib>

#include <iostream>
#include <fstream>


class CountingScreen : public QDialog {
    Q_OBJECT
public:
    CountingScreen();
    virtual ~CountingScreen();
    std::string seedname;
    void InitializeCVariables(int,int,int,bool,bool); //bag #, sp, speed
    int * GetCVariables();
    void SetPrinterFD(int);
    void IncPrintBagNo();
    
private:
    Ui::CountingScreen widget;
    
public slots:
    void UpdateCount();
    void ZeroCount();
    void MotorTest();
    void ChangeMotorSpeed(int speed);
    void ExitToHomeWindow();
    void DisplayCounterSetupWindow();
    void DisplayNumPad();
    void ClearBagNumber();
    void CheckBagNumber();
    void IncrementBagNumber();
    int GetBagNumber();
    void CheckforSeeds();
    void DisplayMotorNumPad();
    int GetTotalCount();
    void SaveDataToTxtFile();
    void SetSeedIndex(int);
    void StartMotor();
    void IncreaseMotorSpeed();
    void DecreaseMotorSpeed();
    void StopCounting();
    void PauseContinue();
    void LoadUnload();
    void secsensor();
    void CallSetHomePosition();
    void CallCalibrate();
    void SetPrintMode(bool);
    void SetPrintFormat(bool);
    void SetLotCode(QString);
    void SetProductID(QString);
    void CallSetBagNumber();
    void CheckForMoreBagNumber();
    void PrintForCarousel();
    void PrintFromFile();
    void SensorStatus();
    void SetBagMode(bool);
    void CallBagCheck();
    int GetReducedSetPoint();
    void SetWaitOnOff();
    void CallWaitOnOff(bool);
    bool GetWaitOnOff();
    void CheckRotaryMotor();
private:
    bool m_Var;
    bool m_OutputHigh;
    bool m_SetpointEnabled;
    bool m_RotaryConnCheck;
    bool m_MotorStatus;
    int m_Setpoint;
    int m_BagNumber;
    int m_SetMotorSpeed;
    int m_SetMaxBagNumber;
    volatile int changecount;
    bool CountingStatus;
    bool PauseStatus;
    bool PrintMode;
    bool PrintFormat;
    bool BagOnOff;
    bool CountTimer;
    bool m_CheckSeeds;
    bool WaitOnOff;
    QString m_CountLblText;
    DFG2Counter m_SeedCounter;
    MotorControl m_Motor;
    SeedDbInterface m_DbTest;
    NumPad m_SetpointNumPad;
    MotorNumPad m_MotorNumPad;
    RotaryMotor m_Rotary;
    PrinterCommands m_PrinterCommands;
    SensorControl m_Sensor;
    QTimer *checkRefreshtimer = new QTimer(this);
    int countchange;
    int totalSeedCount;
    int BagChangeStatus;
    int PrintBagNumber;
    QString LotCode;
    QString ProductID;
    std::fstream WebFile;
    std::fstream PrintFile;
    std::fstream SinglePrintFile;
    std::fstream CarouselFile;
    int VarArray[3];
};

#endif /* _COUNTINGSCREEN_H */
