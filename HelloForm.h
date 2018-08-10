/*
 * Copyright (c) 2009-2010, Oracle and/or its affiliates. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Oracle nor the names of its contributors
 *   may be used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _HELLOFORM_H
#define	_HELLOFORM_H

#define DATE_TIME_REFRESH_TIMER 1000 // In ms.

#include <stdio.h>
#include "ui_HelloForm.h"
#include <QString>
#include "DFG2Counter.h"
#include "MotorControl.h"
#include "SeedDbInterface.h"
#include "CountingScreen.h"
#include "TotalizerCountingScreen.h"
#include "SolenoidCountingScreen.h"
#include "RotaryMotor.h"
#include "Commodity.h"
#include "IOSetup.h"
#include "TestScreen.h"
#include "SetHomePosition.h"
#include "SensorControl.h"
class HelloForm : public QDialog {
    Q_OBJECT
public:
    HelloForm();
    virtual ~HelloForm();
    void TestFunction();
    int totalseedcount;
private:
    Ui::HelloForm widget;
    int Password=901;
    
public slots:
    void DisplayCountWindow();
    void DisplayCommoditySetupWindow();
    void DisplayIoSetupWindow();
    void ExitProgram(); // This will need to shutdown the PI.
    void TurnOffDisplay();
    void TurnOnDisplay();
    void DisplayTestScreen();
    void DisplayAboutScreen();
    void UpdateDateTime();
    void SaveVariablesToFile();
    void GetIniVarFromFile();
    void EnterPassword();
    // The following are no longer used on the main window.
    void MotorTest();
    void ChangeMotorSpeed(int speed);
    void DisplayServiceScreen();
    void InitializeCounter();
    void InitializeWifi();
    void ChangeProgressBar(int);
    void MotorPositionMsg();
    void SetCarousalMotorPosition();
    void SetMode(int m);
private:
    QTimer *DateTimeRefreshtimer = new QTimer(this);
    bool m_Var;
    bool m_OutputHigh;
    int m_ModeStatus=0;
    bool PrintMode;
    bool PrintFormat;
    bool PrintConnection;
    int PrintFD;
    int SeedIndex;
    int ComSensitivity;
    int ComLotIndex;
    int ComProductIndex;
    int T_MotorSpeed;
    bool T_SPstatus;
    int T_SetPoint;
    int C_MotorSpeed;
    int C_SetPoint;
    int C_BagNumber;
    bool C_WaitOnOff;
    int D_MotorSpeed;
    int D_SetPoint;
    int D_BagNumber;
    bool D_SPstatus;
    bool BagOnOff;
    bool D_BagOnOff;
    bool DisplayOnOff;
    bool D_CheckSeeds;
    QString m_CountLblText;
    MotorControl m_Motor;
    SeedDbInterface m_DbTest;
    DFG2Counter m_SeedCounter;
    SensorControl m_Sensor;
    QString LotCode;
    QString ProductID;
    std::string WifiName;
    std::string WifiPassword;
};

#endif	/* _HELLOFORM_H */
