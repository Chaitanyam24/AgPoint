/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Commodity.h
 * Author: Dan
 *
 * Created on July 23, 2017, 5:35PM
 */

#ifndef _COMMODITY_H
#define _COMMODITY_H

#define COMMODITY_DATE_TIME_REFRESH_TIMER 1000 // In ms.
#include <QDialog>
#include "ui_Commodity.h"
#include <stdio.h>
#include <QString>
#include <QTimer>
#include <QMessageBox>
#include <QPixmap>
#include <QComboBox>
#include <time.h>
#include <sys/time.h>
#include <QString>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <stdio.h>

#include "ListDB.h"
#include "SeedDbInterface.h"



class Commodity : public QDialog {
    Q_OBJECT
public:
    Commodity();
    virtual ~Commodity();
    void PopulateSeedConfig();
    //Add seed types here
   std::string SEED_1;
   std::string SEED_2;
   std::string SEED_3;
   std::string SEED_4;
   std::string SEED_5;
   std::string SEED_6;
   DFG2Counter m_Counter;
   SeedDbInterface populatelistDB;
   void InitializeVariables(int, int, int);
   int * GetVariables();
   int GetSensitivity();
private:
    Ui::Commodity widget;
public slots:
    void PopulateItems();
    void ItemChanged(int);
    void ProgramCommodity();
    void DisplayHomeWindow();
    int GetSelectedSeed();
    void CallProgramCommodity();
    void UpdateDateTime();
    void LotItemChanged(int);
    void IDItemChanged(int);
    void DisplayKeypad();
    void RemoveLot();
    void RemoveID();
    void AddLot();
    void AddID();
    QString GetLotCode();
    QString GetProductID();
    void GetLotCodeFromFile();
    void GetProductIdFromFile();
    void SaveLotCodeToFile();
    void SaveProductIdToFile();
private:
    int m_Seed;
    int m_SeedIndex;
    int m_ProgramSeed;
    QString m_KeypadValue;
    int LotIndex;
    int IDIndex;
    QString LotCode;
    QString ProductID;
    int VarArray[2];
    bool ProgramStatus;
};

#endif /* _COMMODITY_H */
