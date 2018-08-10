/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TotalizerCountingScreen.h
 * Author: SHALAKHA
 *
 * Created on October 30, 2017, 11:35 AM
 */

#ifndef _TOTALIZERCOUNTINGSCREEN_H
#define _TOTALIZERCOUNTINGSCREEN_H

#include "ui_TotalizerCountingScreen.h"

#define T_COUNT_REFRESH_TIMER_INTERVAL 35    // In ms.
#define T_CHECK_TIMER_INTERVAL 240000 // 240000 msecs

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
#include "PrinterCommands/PrinterCommands.h"
#include <cstdlib>

#include <iostream>
#include <fstream>
class TotalizerCountingScreen : public QDialog {
    Q_OBJECT
public:
    TotalizerCountingScreen();
    virtual ~TotalizerCountingScreen();
    std::string seedname;
    void InitializeTVariables(bool,int,int,bool);
    int * GetTVariables();
    bool GetSPStatus();
private:
    Ui::TotalizerCountingScreen widget;
    
public slots:
    void UpdateCount();
    void ZeroCount();
    void MotorTest();
    void ChangeMotorSpeed(int speed);
    void ExitToHomeWindow();
    void DisplayCounterSetupWindow();
    void DisplayNumPad();
    void CheckforSeeds();
    void DisplayMotorNumPad();
    int GetTotalCount();
    void SaveDataToTxtFile();
    void SetSeedIndex(int);
    void StartMotor();
    void IncreaseMotorSpeed();
    void DecreaseMotorSpeed();
    void EnableDisableSetpoint();
    void StopCounting();
    void PauseContinue();
    void CallCalibrate();
    void SetPrintMode(bool);
    void SetPrintFormat(bool);
    void SetLotCode(QString);
    void SetProductID(QString);
    void SetPrinterFD(int);
    void CallPrint();
    int GetReducedSetPoint();
    void CallEndCount();
    
private:
    bool m_Var;
    bool m_CheckSeeds;
    bool m_OutputHigh;
    bool m_SetpointEnabled;
    int m_Setpoint;
    int m_SetMotorSpeed;
    bool m_MotorStatus;
    bool CountingStatus;
    bool PauseStatus;
    bool PrintMode;
    bool PrintFormat;
    int VarArray[2];
    bool CountTimer;
    volatile int changecount;
    QString m_CountLblText;
    DFG2Counter m_SeedCounter;
    MotorControl m_Motor;
    SeedDbInterface m_DbTest;
    NumPad m_SetpointNumPad;
    MotorNumPad m_MotorNumPad;
    PrinterCommands m_PrinterCommands;
    QTimer *checkRefreshtimer = new QTimer(this);
    int countchange;
    int totalSeedCount; 
    std::fstream WebFile;
    std::fstream PrintFile;
    std::fstream SinglePrintFile;
    QString LotCode;
    QString ProductID;
};

#endif /* _TOTALIZERCOUNTINGSCREEN_H */
