/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Service.h
 * Author: SHALAKHA
 *
 * Created on November 20, 2017, 10:29 AM
 */

#ifndef _SERVICE_H
#define _SERVICE_H

#include "ui_Service.h"
#include "CounterConfig.h"
#include "SetHomePosition.h"
#include "SensorControl.h"
#include <QString>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <QDialog>
#include <QMessageBox>
class Service : public QDialog {
    Q_OBJECT
public:
    Service();
    virtual ~Service();
private:
    Ui::Service widget;
    short int ModeStatus;
    bool s_BagOnOff;
    bool s_CheckSeeds;
    SensorControl s_Sensor;
public slots:
    void CallCounterSetup();
    void ExitToHomeScreen();
    void DisplayKeypad();
    QString GetSerialNumber();
    void GetSerialNumberFromFile();
    void SaveSerialNumberToFile();
    void SetRTCDateTime();
    void UpdateDateTime();
    void CallSetHomePosition();
    void CarouselMode();
    void TotalizerMode();
    void DualChuteMode();
    int GetSelectedMode();
    void SetMode(int);
    void BagMode(bool);
    bool GetBagMode();
    void SetBagMode();
    void RightSensorIntStatus();
    void LeftSensorIntStatus();
    void SaveCounterMode();
    void CheckForSeedsOnOff(bool);
     bool GetCheckSeeds();
    void SetCheckSeeds();
public:
    QString m_SerialNumber;
    
};

#endif /* _SERVICE_H */
