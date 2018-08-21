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

#include "HelloForm.h"
#include "CounterConfig.h"
#include "AboutScreen.h"
#include "Service.h"
#include <QTimer>
#include <QMessageBox>
#include <QProgressBar>
#include <QPixmap>
#include <stdlib.h>
// using ofstream constructors.
#include <iostream>
#include <fstream> 
#include <vector>
#include "IOSetup.h"

HelloForm::HelloForm() {
    widget.setupUi(this);
    setStyleSheet("background-color:black;");   // Sets the dialog's background color.
    m_Var = false;
    m_OutputHigh = false;  
    m_SeedCounter.InitISR();
    m_ModeStatus = 0;
    PrintMode=false;
    LotCode="";
    ProductID="";
    totalseedcount=0;
    SeedIndex=0;
    PrintFormat=true;
    PrintFD=0;
    PrintConnection=false;
    ComSensitivity=0;
    ComLotIndex=0;
    ComProductIndex=0;
    T_MotorSpeed=50;
    T_SPstatus=true;
    T_SetPoint=100;
    C_MotorSpeed=50;
    C_SetPoint=100;
    C_BagNumber=8;
    C_WaitOnOff=false;
    D_MotorSpeed=50;
    D_SetPoint=100;
    D_SPstatus=true;
    D_BagNumber=5;
    BagOnOff=false;
    D_BagOnOff=true;
    WifiName="";
    WifiPassword="";
    DisplayOnOff=false;
    D_CheckSeeds=false;
    //Check for Printer connection
    IOSetup *m_IOPrintConnection = new IOSetup();
    m_IOPrintConnection->PrinterSetup();
    PrintConnection= m_IOPrintConnection->GetPrinterStatus();
    PrintFD= m_IOPrintConnection->GetPrinterConnection();
    delete m_IOPrintConnection;
    //sensitivity,lotcode,productID
    // Change the background color of the buttons
    widget.lblModelNumber->setStyleSheet("background-color:black; color:white");
    widget.lblModelNumber->setText("901C Seed Carousel");
    widget.btnCount->setStyleSheet("background-color:white;");
    widget.btnCommoditySetup->setStyleSheet("background-color:white;");
    widget.btnCommoditySetup->setText("Counter\nSETUP");
    widget.lblInfo->setStyleSheet("background-color:black; color:white");
    widget.lblInfo->setText("Initializing User Settings... Please wait");
    widget.btnIoSetup->setStyleSheet("background-color:white;");
    widget.btnIoSetup->setText("");
    widget.btnIoSetup->setText("Communication\nSETUP");
    widget.btnTestMode->setStyleSheet("background-color:white;");
    widget.btnTestMode->setText("Test");
    widget.btnExit->setStyleSheet("background-color:black;");
    widget.btnSleep->setStyleSheet("background-color:black;");
    widget.btnSleep->setText("Sleep"); 
    widget.btnAwake->setStyleSheet("background-color:black;");
    widget.btnAwake->setVisible(false);
    widget.lblModelNumber->setStyleSheet("background-color:black; color:white");
    widget.btnAbout->setStyleSheet("background-color:black;");
    widget.btnService->setStyleSheet("background-color:black;");
    widget.btnService->setText("Service"); 
    widget.progressBarLoad->setStyleSheet("background-color:white;");
    widget.progressBarLoad->setRange(0,100);
    widget.progressBarLoad->setValue(20);
    //widget.lblCompanyLogo->setStyleSheet("background-color:white;");
    widget.lblDateTime->setStyleSheet("background-color:black; color:white;");
    widget.lblDateTime->setVisible(false);
    // Company logo
    // lblCompanyLogo is the label to load the pic
    QPixmap pix(":/images/seedburo_logo.png");
    int w = widget.lblCompanyLogo->width();
    int h = widget.lblCompanyLogo->height();
    widget.lblCompanyLogo->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    
    // Initialize lblCompanyLogo is the label to load the pic
    QPixmap pix4(":/images/seedburo_logo.png");
    int w4 = widget.lblIniLogo->width();
    int h4 = widget.lblIniLogo->height();
    widget.lblIniLogo->setPixmap(pix.scaled(w4,h4,Qt::KeepAspectRatio));
    
    // Load the power bitmap onto the exit button.
    widget.btnExit->setText("");
    QPixmap pix2(":/images/power_button.png");
    QIcon icon(pix2);
    widget.btnExit->setIcon(icon);
    widget.btnExit->setIconSize(widget.btnExit->rect().size());
    widget.btnExit->setFixedSize(widget.btnExit->rect().size());
    
    // About is the button to load the pic
    widget.btnAbout->setText("");    // Remove the text so the bitmap fits the button.
    QPixmap pix3(":/images/about_button.png");
    QIcon icon3(pix3);
    widget.btnAbout->setIcon(icon3);
    widget.btnAbout->setIconSize(widget.btnAbout->rect().size());
    widget.btnAbout->setFixedSize(widget.btnAbout->rect().size());
    

       // Sleep is the button to load the pic
    // Remove the text so the bitmap fits the button.
    widget.btnSleep->setText("");
    QPixmap pix5(":/images/sleep_button.png");
    QIcon icon5(pix5);
    widget.btnSleep->setIcon(icon5);
    widget.btnSleep->setIconSize(widget.btnSleep->rect().size());
    widget.btnSleep->setFixedSize(widget.btnSleep->rect().size());
    
    widget.btnService->setText("");    // Remove the text so the bitmap fits the button.
    QPixmap pix6(":/images/settings_button.png");
    QIcon icon6(pix6);
    widget.btnService->setIcon(icon6);
    widget.btnService->setIconSize(widget.btnService->rect().size());
    widget.btnService->setFixedSize(widget.btnService->rect().size());
    
    
    // Connect signals and slots
    connect(widget.btnCount, SIGNAL(pressed()), this, SLOT(DisplayCountWindow()));
    connect(widget.btnCommoditySetup, SIGNAL(pressed()), this, SLOT(DisplayCommoditySetupWindow()));
    connect(widget.btnIoSetup, SIGNAL(pressed()), this, SLOT(DisplayIoSetupWindow()));
    connect(widget.btnTestMode, SIGNAL(pressed()), this, SLOT(DisplayTestScreen()));
    connect(widget.btnAbout, SIGNAL(pressed()), this, SLOT(DisplayAboutScreen()));
    connect(widget.btnService, SIGNAL(pressed()), this, SLOT(EnterPassword()));
    // Old buttons.  still using btnExit for now. 6/13/2017
    //widget.btnExit->setStyleSheet("background-color:white;");
    widget.btnManualProgramCounter->setStyleSheet("background-color:white;");
    widget.btnCounterConfig->setStyleSheet("background-color:white;");
    widget.btnZeroCount->setStyleSheet("background-color:white;");
    widget.btnMotorTest->setStyleSheet("background-color:white;");
    widget.lblMotorSliderValue->setStyleSheet("background-color:white;");
    
    // Disable unused controls, for now, until they can be safely removed.
    widget.btnManualProgramCounter->setVisible(false);
    widget.btnCounterConfig->setVisible(false);
    widget.btnZeroCount->setVisible(false);
    widget.btnMotorTest->setVisible(false);
    widget.lblMotorSliderValue->setVisible(false);
    widget.sliderMotorSpeed->setVisible(false);
    widget.lblCount->setVisible(false);
    
    // Connect the exit button to the dialog close() signal.
    connect(widget.btnExit, SIGNAL(pressed()), this, SLOT(ExitProgram()));
    connect(widget.btnSleep, SIGNAL(pressed()), this, SLOT(TurnOffDisplay()));
    connect(widget.btnAwake, SIGNAL(pressed()), this, SLOT(TurnOnDisplay()));
    UpdateDateTime();
    //Timer for date and time
    
    connect(DateTimeRefreshtimer, SIGNAL(timeout()), this, SLOT(UpdateDateTime()));
    DateTimeRefreshtimer->start(DATE_TIME_REFRESH_TIMER);
    
    //Check for all Text files to save data
    std::fstream WebTxtFile;
    WebTxtFile.open("/var/www/html/WebSeedData.txt");
    std::fstream PrintTxtFile;
    PrintTxtFile.open("/home/pi/PrintSeedData.txt");
    std::fstream RecentFile;
    RecentFile.open("/home/pi/RecentFile.txt");
    PrintTxtFile.close();
    WebTxtFile.close();
    RecentFile.close();
    //ProductID
    std::fstream productfile;
    productfile.open("/home/pi/ProductID.txt");
    if(productfile.bad())
    {
        productfile.open("/home/pi/ProductID.txt", std::ios_base::out);
    }
    productfile.close();
    //LotCode
    std::fstream lotfile;
    lotfile.open("/home/pi/LotCode.txt");
    if(lotfile.bad())
    {
        lotfile.open("/home/pi/LotCode.txt", std::ios_base::out);
    }
    lotfile.close();
    //Serial Number
    std::fstream serialfile;
    serialfile.open("/home/pi/SerialNumber.txt");
    if(serialfile.bad())
    {
        serialfile.open("/home/pi/SerialNumber.txt", std::ios_base::out);
    }
    serialfile.close();
    
    //Carousel Print file
    std::fstream carouselfile;
    carouselfile.open("/home/pi/CarouselPrint.txt");
    if(carouselfile.bad())
    {
        carouselfile.open("/home/pi/CarouselPrint.txt", std::ios_base::out);
    }
    carouselfile.close();
    std::fstream dualFile;
    dualFile.open("/home/pi/DualPrint.txt");
    if(dualFile.bad())
    {
        dualFile.open("/home/pi/DualPrint.txt", std::ios_base::out);
    }
    dualFile.close();
    std::fstream Inifile;
    Inifile.open("/home/pi/IniVarFile.txt");
    if(Inifile.bad())
    {
        Inifile.open("/home/pi/IniVarFile.txt", std::ios_base::out);
        for(int i=0; i<12; i++)
        {
            Inifile << "";
            Inifile << "\n";
        }
    }
    Inifile.close();
    std::fstream modefile;
    modefile.open("/home/pi/901Mode.txt");
    if(modefile.bad())
    {
        modefile.open("/home/pi/901Mode.txt", std::ios_base::out);
        modefile << 0;
    }
    modefile.close();
    widget.lblInfo->setText("Initializing User Settings... Please Wait");
    ChangeProgressBar(20);
    
    GetIniVarFromFile();
}

HelloForm::~HelloForm() {
    
}

void HelloForm::ExitProgram()  
{
    SaveVariablesToFile();
    remove("/var/www/html/WebSeedData.txt");
    remove("/home/pi/PrintSeedData.txt");
    //remove("/home/pi/RecentSeedData.txt");
    system("sudo shutdown -h now"); // This will need to shutdown the PI. 
    close();
}

void HelloForm::DisplayCountWindow()
{   DateTimeRefreshtimer->blockSignals(true);
    
    widget.lblInfo->setText("");
    if (m_ModeStatus == 0)
    {
        CountingScreen *countingForm = new CountingScreen();
        countingForm->SetPrintMode(PrintMode);
        countingForm->SetPrintFormat(PrintFormat);
        countingForm->SetLotCode(LotCode);
        countingForm->SetProductID(ProductID);
        countingForm->SetPrinterFD(PrintFD);
        countingForm->InitializeCVariables(C_BagNumber, C_SetPoint, C_MotorSpeed, D_CheckSeeds, C_WaitOnOff);
        countingForm->SetBagMode(BagOnOff);
        countingForm->setWindowFlags(Qt::FramelessWindowHint);
        countingForm->setModal(true);
        countingForm->move(0,20);  // Move window up a bit to cover main window.
        countingForm->SetSeedIndex(SeedIndex);
        countingForm->exec();    
        if(countingForm->seedname == "") { SeedIndex =0; }
        totalseedcount= countingForm->GetTotalCount();
        int *VarArr= countingForm->GetCVariables();
        C_BagNumber=VarArr[0];
        C_SetPoint=VarArr[1];
        C_MotorSpeed = VarArr[2];
        C_WaitOnOff=countingForm->GetWaitOnOff();
        delete countingForm; // delete the object
    }
    else if (m_ModeStatus == 1){
        TotalizerCountingScreen *countingForm = new TotalizerCountingScreen();
        countingForm->SetPrintMode(PrintMode);
        countingForm->SetPrintFormat(PrintFormat);
        countingForm->SetLotCode(LotCode);
        countingForm->SetProductID(ProductID);
        countingForm->SetPrinterFD(PrintFD);
        countingForm->InitializeTVariables(T_SPstatus,T_MotorSpeed,T_SetPoint, D_CheckSeeds);
        countingForm->setWindowFlags(Qt::FramelessWindowHint);
        countingForm->setModal(true);
        countingForm->move(0,20);  // Move window up a bit to cover main window.
        countingForm->SetSeedIndex(SeedIndex);
        countingForm->exec();    
        if(countingForm->seedname == "") { SeedIndex =0; }
        totalseedcount= countingForm->GetTotalCount();
        T_SPstatus = countingForm->GetSPStatus();      
        int *VarArr = countingForm->GetTVariables();
        T_MotorSpeed=VarArr[0];
        T_SetPoint=VarArr[1];
        delete countingForm;
         
    }
    else
    {
        SolenoidCountingScreen *countingForm = new SolenoidCountingScreen();
        countingForm->SetPrintMode(PrintMode);
        countingForm->SetPrintFormat(PrintFormat);
        countingForm->SetLotCode(LotCode);
        countingForm->SetProductID(ProductID);
        countingForm->SetPrinterFD(PrintFD);
        countingForm->SetBagMode(D_BagOnOff);
        countingForm->InitializeDVariables(D_SPstatus,D_SetPoint, D_MotorSpeed, D_BagNumber, D_CheckSeeds);
        countingForm->setWindowFlags(Qt::FramelessWindowHint);
        countingForm->setModal(true);
        countingForm->move(0,20);  // Move window up a bit to cover main window.
        countingForm->exec();    
        int *VarArr= countingForm->GetDVariables();
        D_SetPoint=VarArr[0];
        D_MotorSpeed = VarArr[1];
        D_BagNumber= VarArr[2];
        D_SPstatus = countingForm->GetSPStatus();
        D_BagOnOff=countingForm->GetBagMode();
        delete countingForm; // delete the object  
    }
   widget.lblInfo->setText("To print seed count, press COMMUNICATION SETUP");
   SaveVariablesToFile();
   DateTimeRefreshtimer->blockSignals(false);
}

void HelloForm::DisplayCommoditySetupWindow()
{
    Commodity *commodityForm = new Commodity();
    commodityForm->setWindowFlags(Qt::FramelessWindowHint);
    commodityForm->setModal(true);
    commodityForm->move(0,20);  // Move window up a bit to cover main window.
    commodityForm->InitializeVariables(ComSensitivity, ComLotIndex ,ComProductIndex);
    commodityForm->exec(); 
    SeedIndex= commodityForm->GetSelectedSeed();
    LotCode=commodityForm->GetLotCode();
    ProductID=commodityForm->GetProductID();
    int *ComVar = commodityForm->GetVariables();
    ComLotIndex= ComVar[0];
    ComProductIndex = ComVar[1];
    int comsen =  commodityForm->GetSensitivity();
    if (comsen >=0 && comsen < 7) {ComSensitivity = comsen;}
    delete commodityForm;
    SaveVariablesToFile();
    widget.lblInfo->setText("To start counting, press COUNT");
}

void HelloForm::DisplayIoSetupWindow()
{
    IOSetup *IOForm = new IOSetup();
    IOForm->InitializeVariables(PrintFormat,PrintMode, PrintConnection, PrintFD);
    IOForm->InitializeWiFi(WifiName,WifiPassword);
    IOForm->setWindowFlags(Qt::FramelessWindowHint);
    IOForm->setModal(true);
    IOForm->move(0,20);  // Move window up a bit to cover main window.
    IOForm->SetSeedName(SeedIndex);
    IOForm->SetTotalCount(totalseedcount);
    IOForm->exec(); 
    PrintMode = IOForm->GetPrintMode();
    PrintFormat = IOForm->GetPrintFormat();
    PrintConnection = IOForm->GetPrinterStatus();
    PrintFD=IOForm->GetPrinterConnection();
    WifiName = IOForm->GetWifiName();
    WifiPassword = IOForm->GetWifiPassword();
    /*QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("STATUS"); 
    msg->setText(QString::number(PrintFD));	     
    msg->show();*/
    delete IOForm;
    SaveVariablesToFile();
}

void HelloForm::TestFunction()
{
    
}

void HelloForm::MotorTest()// No longer used on the main screen.
{
    m_Motor.TestPwm();
}

void HelloForm::ChangeMotorSpeed(int speed)// No longer used on the main screen.
{
    //widget.lblMotorSliderValue->setText(QString::number(speed));
    //m_Motor.SetSpeed(speed);
}

void HelloForm::DisplayTestScreen(){
    TestScreen *testForm = new TestScreen();
    testForm->setWindowFlags(Qt::FramelessWindowHint);
    testForm->setModal(true);
    testForm->move(0,20);  // Move window up a bit to cover main window.
    testForm->exec();    
    delete testForm;
}

void HelloForm::DisplayAboutScreen(){
    AboutScreen *aboutForm = new AboutScreen();
    aboutForm->setWindowFlags(Qt::FramelessWindowHint);
    aboutForm->setModal(true);
    aboutForm->move(300,100);  // Move window up a bit to cover main window.
    aboutForm->exec();    
    delete aboutForm;
}

void HelloForm::UpdateDateTime(){
    timeval curTime;
    tm *my_date_time;
    gettimeofday(&curTime, NULL);
    my_date_time = localtime(&curTime.tv_sec);
    std::string date= std::to_string(my_date_time->tm_hour) +":"+ std::to_string(my_date_time->tm_min)+":"+ std::to_string(my_date_time->tm_sec)+"\n" +std::to_string(my_date_time->tm_mon + 1) +"/"+ std::to_string(my_date_time->tm_mday) +"/20"+std::to_string(my_date_time->tm_year - 100);
    char const *tchar = date.c_str();
    widget.lblDateTime->setText(tchar);
    if(DisplayOnOff == true)
    {
        if(m_SeedCounter.GetCount() > 0)
        {
            TurnOnDisplay();
            m_SeedCounter.ClearCount();
        }      
    }
}

void HelloForm::DisplayServiceScreen(){
    Service *serviceForm = new Service();
    serviceForm->SetMode(m_ModeStatus);
    serviceForm->BagMode(BagOnOff);
    serviceForm->CheckForSeedsOnOff(D_CheckSeeds);
    serviceForm->setWindowFlags(Qt::FramelessWindowHint);
    serviceForm->setModal(true);
    serviceForm->move(0,20);  // Move window up a bit to cover main window.
    serviceForm->exec();    
    m_ModeStatus = serviceForm->GetSelectedMode();
    SetMode(m_ModeStatus);
    BagOnOff=serviceForm->GetBagMode();
    D_CheckSeeds=serviceForm->GetCheckSeeds();  
    delete serviceForm;
}

void HelloForm::SaveVariablesToFile()
{
    //clear previous data
    std::fstream IniFile2;
    IniFile2.open("/home/pi/IniVarFile.txt",std::fstream::out | std::fstream::trunc);
    IniFile2.close();
    std::ofstream IniFile;
    //save new data
    IniFile.open("/home/pi/IniVarFile.txt");
    /*
     * ComSensitivity=0;
        ComLotIndex=0;
     *  LotCode="";
        ComProductIndex=0;
     *  ProductID="";
     */
    IniFile << std::to_string(ComSensitivity);
    IniFile << "\n";
    IniFile << std::to_string(ComLotIndex);
    IniFile << "\n";
    IniFile << (LotCode).toStdString();
    IniFile << "\n";
    IniFile << std::to_string(ComProductIndex);
    IniFile << "\n";
    IniFile << (ProductID).toStdString();
    IniFile << "\n";
    PrintFormat == true ? IniFile << "1" : IniFile << "0";
    IniFile << "\n";
    PrintMode == true ? IniFile << "1" : IniFile << "0";
    IniFile << "\n";
    BagOnOff == true ? IniFile << "1" : IniFile << "0";
    IniFile << "\n";
    D_BagOnOff == true ? IniFile << "1" : IniFile << "0";
    IniFile << "\n";
    D_CheckSeeds == true ? IniFile << "1" : IniFile << "0";
    IniFile << "\n";
    C_WaitOnOff == true ? IniFile << "1" : IniFile << "0";
    IniFile.close();
}

void HelloForm::GetIniVarFromFile()
{
    system("echo 0 >/sys/class/backlight/rpi_backlight/bl_power");
    std::string IniVar;
    std::ifstream IniFile;
    std::vector<std::string> IniArr;
    IniFile.open("/home/pi/IniVarFile.txt",std::ios_base::in);
    if (IniFile.is_open())
    {
        while(getline(IniFile, IniVar))
        {
            if (IniVar.empty())
            {
                IniArr.push_back("");
            }
            else {
            IniArr.push_back(IniVar); 
            }
        }
        ComSensitivity= atoi(IniArr[0].c_str()); //atoi(myString.c_str()); 
        ComLotIndex=atoi(IniArr[1].c_str());
        (IniArr[2].empty()) ? LotCode="" : LotCode=QString::fromStdString(IniArr[2]);
        ComProductIndex=atoi(IniArr[3].c_str());        
        (IniArr[4].empty()) ? ProductID="" : ProductID=QString::fromStdString(IniArr[4]); 
        atoi(IniArr[5].c_str()) ? PrintFormat = true : PrintFormat = false;
        atoi(IniArr[6].c_str()) ? PrintMode = true : PrintMode = false;
        atoi(IniArr[7].c_str()) ? BagOnOff= true : BagOnOff = false;
        atoi(IniArr[8].c_str()) ? D_BagOnOff= true : D_BagOnOff = false;
        atoi(IniArr[9].c_str()) ? D_CheckSeeds= true : D_CheckSeeds = false;
        atoi(IniArr[10].c_str()) ? C_WaitOnOff= true : C_WaitOnOff = false;
        IniFile.close();
    }
    std::string ModeString;
    std::ifstream ModeFile;
    ModeFile.open("/home/pi/901Mode.txt",std::ios_base::in);
    if (ModeFile.is_open())
    {
        ModeFile >> ModeString;
        ModeFile.close();
        SetMode(atoi(ModeString.c_str()));
    }  
    QTimer::singleShot(500,this,SLOT(InitializeCounter()));
    QTimer::singleShot(5000,this,SLOT(InitializeWifi()));
    
}

void HelloForm::InitializeCounter()
{
    m_SeedCounter.ProgramCounter(); 
    widget.progressBarLoad->setValue(70);
}
void HelloForm::ChangeProgressBar(int i)
{
    widget.progressBarLoad->setValue(i);
}

void HelloForm::InitializeWifi()
{
    widget.progressBarLoad->setValue(80);
    system("sudo killall wpa_supplicant");
    usleep(1000000);
    widget.progressBarLoad->setValue(90);
    system("wpa_supplicant -D nl80211 -iwlan0 -c/etc/wpa_supplicant/wpa_supplicant.conf -B");
    usleep(1000000);
    widget.progressBarLoad->setValue(95);
    usleep(1000000);
    widget.progressBarLoad->setVisible(false);
    delete  widget.progressBarLoad;
    widget.lblIniLogo->setVisible(false);
    delete widget.lblIniLogo;
    widget.lblInfo->setText("");
    widget.lblDateTime->setVisible(true);
    usleep(1000000);
    if( m_ModeStatus == 0)
    MotorPositionMsg();
    //system("sudo dhclient"); 
    //usleep(3000000);
}

void HelloForm::MotorPositionMsg()
{
    QMessageBox msgBox;
    msgBox.setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
    msgBox.setWindowTitle("Set Positions?");
    msgBox.setText("Do you want to Set Positions For Carousal Motor?");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    connect( msgBox.button(QMessageBox::Yes), SIGNAL(clicked()) ,this, SLOT(SetCarousalMotorPosition()) );
    msgBox.exec(); 
}

void HelloForm::SetCarousalMotorPosition()
{
    SetHomePosition *positionForm = new SetHomePosition();
    positionForm->setWindowFlags(Qt::FramelessWindowHint);
    positionForm->setModal(true);
    positionForm->move(0,20);
    positionForm->exec(); 
    delete positionForm;
}


void HelloForm::EnterPassword(){
    MotorNumPad *passwordForm = new MotorNumPad();
    passwordForm->setWindowFlags(Qt::FramelessWindowHint);
    passwordForm->setModal(true);
    passwordForm->move(300,100);
    passwordForm->exec();
    int psd = passwordForm->GetSpeed();
    if (psd == 901) {
        DisplayServiceScreen();
    }
    else {        
        passwordForm->BlanklblValue();
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR");    
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Wrong Password!");	     
        msg->show();
    }
    m_Motor.SetSpeed(0);
}


void HelloForm::SetMode(int m)
{
    m_ModeStatus=m;
    switch(m)
    {
        case 0:
            widget.lblModelNumber->setText("901C Seed Carousel");
            break;
        case 1:
            widget.lblModelNumber->setText("901T Seed Totalizer");
            break;
        case 2:
            widget.lblModelNumber->setText("901D Seed Dual-Chute");
            break;
        default:
            m_ModeStatus=0;
            widget.lblModelNumber->setText("901C Seed Carousel");
            break;
    }
}

void HelloForm::TurnOffDisplay()
{
    DisplayOnOff=true;
    widget.btnAwake->setVisible(true);
    system("echo 1 >/sys/class/backlight/rpi_backlight/bl_power"); // To turn OFF the display of touchscreen
}

 void HelloForm::TurnOnDisplay()
 {
     DisplayOnOff=false;
     widget.btnAwake->setVisible(false);
     system("echo 0 >/sys/class/backlight/rpi_backlight/bl_power"); // To turn ON the display of touchscreen
 }