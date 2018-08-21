/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IOSetup.h
 * Author: SHALAKHA
 *
 * Created on October 12, 2017, 11:02 AM
 */

#ifndef _IOSETUP_H
#define _IOSETUP_H

#include "ui_IOSetup.h"
#include "ViewDataTable.h"
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wiringSerial.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <sstream>


class IOSetup : public QDialog {
    Q_OBJECT
public:
    IOSetup();
    virtual ~IOSetup();
   
private:
    Ui::IOSetup widget;
    bool connection;
    int totalIOseedcount;
    int fd;
    std::string seedname;
    bool FormatStatus;
    bool ModeStatus;
    bool wifiStatus;
    std::string WifiName;
    std::string WifiPsd;
    
public slots:
    void PrinterSetup();
    void Exit();
    void CountPrint();
    void GetIPAddress();
    void PrintFromTxtFile();
    void ClearWebPage();
    void CSVSelected();
    void FormatSelected();
    void FileSelected();
    void ContinousSelected();
    bool GetPrintMode();
    bool GetPrintFormat();
    void ViewDataInTable();
    void ScanWifiNames();
    void ConnectToWifi();
    void CallConnectToWifi();
    void DisplayKeypad();
    void WifiConnectionError();
    void PrintForCarousel();
    void InitializeWiFi(std::string, std::string );
    void ButtonPressedPrinterSetup();
public:
    void ResetPrinter();
    void PrintDateTime();
    void PrintMode();
    void CommandMode();
    void PaperCut();
    void SetTotalCount(int);
    int GetTotalCount();
    void SetSeedName(int);
    void InitializeVariables(bool , bool, bool, int);
    std::vector<std::string> explode(const std::string&, const char&);
    bool GetPrinterStatus();
    int GetPrinterConnection();
    std::string GetWifiName();
    std::string GetWifiPassword();
    
};

#endif /* _IOSETUP_H */
