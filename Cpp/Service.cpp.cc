/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Service.cpp
 * Author: SHALAKHA
 *
 * Created on November 20, 2017, 10:29 AM
 */

#include "Service.h"
#include "Keypad.h"
#include "SolenoidCountingScreen.h"
#include <QTimer>
#include <unistd.h>
#include <string>
#include <stdlib.h>

Service::Service() {
    widget.setupUi(this);
      // Sets the dialog's background color.
    setStyleSheet("background-color:black;");
    widget.lblModelNumber->setStyleSheet("background-color:black; color:white");
    widget.lblSelectMode->setStyleSheet("background-color:black; color:white");
    widget.lblSelectMode->setText("Select Mode :");
    widget.rbModeCarousel->setStyleSheet("background-color:black; color:white");
    widget.rbModeCarousel->setChecked(true);
    widget.rbModeTotalizer->setStyleSheet("background-color:black; color:white");
    widget.rbModeTotalizer->setChecked(false);
    widget.rbModeDualChute->setStyleSheet("background-color:black; color:white");
    widget.rbModeDualChute->setChecked(false);
    connect(widget.rbModeTotalizer, SIGNAL(pressed()), this, SLOT(TotalizerMode()));
    connect(widget.rbModeCarousel, SIGNAL(pressed()), this, SLOT(CarouselMode()));
    connect(widget.rbModeDualChute, SIGNAL(pressed()), this, SLOT(DualChuteMode()));
    // Change the background color of the buttons and labels
    widget.btnCounterSetup->setStyleSheet("background-color:white;");
    connect(widget.btnCounterSetup, SIGNAL(pressed()), this, SLOT(CallCounterSetup()));
    widget.btnHome->setStyleSheet("background-color:black;");
    connect(widget.btnHome, SIGNAL(pressed()), this, SLOT(ExitToHomeScreen()));
    widget.btnSetSerialNo->setStyleSheet("background-color:white;");
    connect(widget.btnSetSerialNo, SIGNAL(pressed()), this, SLOT(DisplayKeypad()));
    widget.lblSerialNumber->setStyleSheet("background-color:black; color:white");
    widget.btnCheckSeeds->setStyleSheet("background-color:white;");
    connect(widget.btnCheckSeeds, SIGNAL(pressed()), this, SLOT(SetCheckSeeds()));
    widget.btnBagSensor->setStyleSheet("background-color:white;");
    connect(widget.btnBagSensor, SIGNAL(pressed()), this, SLOT(SetBagMode()));
     // Load the Home bitmap onto the Home Screen button.
    widget.btnHome->setText("");    // Remove the text so the bitmap fits the button.
    QPixmap pix(":/images/home_button.png");
    QIcon icon(pix);
    widget.btnHome->setIcon(icon);
    widget.btnHome->setIconSize(widget.btnHome->rect().size());
    widget.btnHome->setFixedSize(widget.btnHome->rect().size());
    
    GetSerialNumberFromFile();
    widget.lblSerialNumber->setText(m_SerialNumber); 
    widget.lblDateTime->setStyleSheet("background-color:black; color:white");
    widget.lblRTC->setStyleSheet("background-color:black; color:white");
    widget.lblRTC->setText("Make sure WiFi is connected");
    widget.btnSetRTC->setStyleSheet("background-color:white;");
    connect(widget.btnSetRTC, SIGNAL(pressed()), this, SLOT(SetRTCDateTime()));
    
    UpdateDateTime();
    //Timer for date and time
    QTimer *DateTimeRefreshtimer = new QTimer(this);
    connect(DateTimeRefreshtimer, SIGNAL(timeout()), this, SLOT(UpdateDateTime()));
    DateTimeRefreshtimer->start(1000);
    
    widget.btnRotaryHome->setStyleSheet("background-color:white;");
    connect(widget.btnRotaryHome, SIGNAL(pressed()), this, SLOT(CallSetHomePosition()));
    
    widget.btnLeftSensor->setStyleSheet("background-color:white; color:black;");
    connect(widget.btnLeftSensor, SIGNAL(pressed()), this, SLOT(LeftSensorIntStatus()));
    widget.btnRightSensor->setStyleSheet("background-color:white; color:black;");
    connect(widget.btnRightSensor, SIGNAL(pressed()), this, SLOT(RightSensorIntStatus()));
}

Service::~Service() {
}

void Service::CallCounterSetup()
{
    CounterConfig *configForm = new CounterConfig();
    configForm->setWindowFlags(Qt::FramelessWindowHint);
    configForm->setModal(true);
    configForm->move(0,20);
    configForm->exec();
    delete configForm;
}

void Service::DisplayKeypad(){
    Keypad *keypadForm = new Keypad();
    keypadForm->setWindowFlags(Qt::FramelessWindowHint);
    keypadForm->setModal(true);
    keypadForm->move(0,20);  // Move window up a bit to cover main window.
    keypadForm->exec();
    m_SerialNumber = keypadForm->GetInputValue();
    SaveSerialNumberToFile();
    widget.lblSerialNumber->setText(m_SerialNumber); 
    delete keypadForm;
}
void Service::ExitToHomeScreen()
{
    SaveCounterMode();
    close();
}

QString Service::GetSerialNumber()
{
    return m_SerialNumber;
}

void Service::GetSerialNumberFromFile()
{
    std::string serialno;
    std::ifstream SerialFile;
    SerialFile.open("/home/pi/SerialNumber.txt",std::ios_base::in);
    if (SerialFile.is_open())
    {
        SerialFile >> serialno;
        SerialFile.close();
        char const *pchar = serialno.c_str();
        m_SerialNumber = pchar;
    }    
}

void Service::SaveSerialNumberToFile()
{
    std::ofstream SerialFile;
    SerialFile.open("/home/pi/SerialNumber.txt");
    SerialFile << m_SerialNumber.toStdString();
    SerialFile.close();  
}

void Service::SetRTCDateTime(){
    system("sudo hwclock -w");
    widget.lblRTC->setText("Done!");
}

void Service::UpdateDateTime(){
    timeval curTime;
    tm *my_date_time;
    gettimeofday(&curTime, NULL);
    my_date_time = localtime(&curTime.tv_sec);
    std::string date= std::to_string(my_date_time->tm_hour) +":"+ std::to_string(my_date_time->tm_min)+":"+ std::to_string(my_date_time->tm_sec)+"\n" +std::to_string(my_date_time->tm_mon + 1) +"/"+ std::to_string(my_date_time->tm_mday) +"/20"+std::to_string(my_date_time->tm_year - 100);
    char const *tchar = date.c_str();
    widget.lblDateTime->setText(tchar);
}

void Service::CallSetHomePosition(){
    
    SetHomePosition *positionForm = new SetHomePosition();
    positionForm->setWindowFlags(Qt::FramelessWindowHint);
    positionForm->setModal(true);
    positionForm->move(0,20);
    positionForm->exec(); 
    delete positionForm;
    //m_Rotary.GetPositionFromFile();
}

void Service::CarouselMode()
{
    widget.rbModeCarousel->setChecked(true);
    widget.rbModeTotalizer->setChecked(false);
    widget.rbModeDualChute->setChecked(false);
    widget.lblModelNumber->setText("901C Seed Carousel");
    ModeStatus=0;
    
}

void Service::TotalizerMode()
{
    widget.rbModeTotalizer->setChecked(true);
    widget.rbModeCarousel->setChecked(false);
    widget.rbModeDualChute->setChecked(false);
    widget.lblModelNumber->setText("901T Seed Totalizer");
    ModeStatus=1;
 
}

void Service::DualChuteMode()
{
    widget.rbModeDualChute->setChecked(true);
    widget.rbModeTotalizer->setChecked(false);
    widget.rbModeCarousel->setChecked(false);
    widget.lblModelNumber->setText("901D Seed Dual-Chute");
    ModeStatus=2;
    
}

void Service::SaveCounterMode()
{
    std::ofstream ModeFile;
    ModeFile.open("/home/pi/901Mode.txt");
    ModeFile <<  std::to_string(ModeStatus);
    ModeFile.close(); 
}

int Service::GetSelectedMode()
{
    return ModeStatus;
}

void Service::SetMode(int m)
{
    ModeStatus=m;
    switch(m)
    {
        case 0:
            widget.rbModeCarousel->setChecked(true);
            widget.rbModeTotalizer->setChecked(false);
            widget.rbModeDualChute->setChecked(false);
            widget.lblModelNumber->setText("901C Seed Carousel");
            break;
        case 1:
            widget.rbModeTotalizer->setChecked(true);
            widget.rbModeCarousel->setChecked(false);
            widget.rbModeDualChute->setChecked(false);
            widget.lblModelNumber->setText("901T Seed Totalizer");
            break;
        case 2:
            widget.rbModeDualChute->setChecked(true);
            widget.rbModeTotalizer->setChecked(false);
            widget.rbModeCarousel->setChecked(false);
            widget.lblModelNumber->setText("901D Seed Dual-Chute");
            break;
    }
}

void Service::BagMode(bool c)
{
    s_BagOnOff=c;
    if(s_BagOnOff){
        widget.btnBagSensor->setStyleSheet("background-color:white;");       
    }
    else
    {
        widget.btnBagSensor->setStyleSheet("background-color:red;");
    }
    
}

bool Service::GetBagMode()
{
    return s_BagOnOff;
}

void Service::SetBagMode()
{
    if(s_BagOnOff){
        s_BagOnOff=false;
        widget.btnBagSensor->setStyleSheet("background-color:red;");
    }
    else
    {
        s_BagOnOff=true;
        widget.btnBagSensor->setStyleSheet("background-color:white;");
    }
}



void Service::RightSensorIntStatus(){
    int sw=s_Sensor.GetRightSensorStatus();
    bool st=s_Sensor.TestRightSensor();
    s_Sensor.ResetRightSensorStatus();
    if (sw>0 && st==true)
    {
        QMessageBox msgBox;
        msgBox.setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msgBox.setWindowTitle("Done!");
        msgBox.setText("Bag detected");	
       // msgBox.setText(QString::number(sw));
        msgBox.exec(); 
    }
    else if(st==false)
    {
        QMessageBox msgBox;
        msgBox.setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msgBox.setWindowTitle("Error");
        msgBox.setText("NO Bag Detected on Right Solenoid");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.addButton(QMessageBox::Cancel);
        connect( msgBox.button(QMessageBox::Ok), SIGNAL(clicked()) ,this, SLOT(RightSensorIntStatus()));
        msgBox.exec();   
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msgBox.setWindowTitle("Error");
        msgBox.setText("SAME Bag Detected on Right Solenoid");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.addButton(QMessageBox::Cancel);
        connect( msgBox.button(QMessageBox::Ok), SIGNAL(clicked()) ,this, SLOT(RightSensorIntStatus()));
        msgBox.exec();   
    }
}

void Service::LeftSensorIntStatus(){
    int sw=s_Sensor.GetLeftSensorStatus();
    bool st=s_Sensor.TestLeftSensor();
    s_Sensor.ResetLeftSensorStatus();
    if (sw>0 && st==true)
    {
        QMessageBox msgBox;
        msgBox.setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msgBox.setWindowTitle("Done");
        msgBox.setText("Bag detected");	 
        msgBox.exec(); 
              
    }
    else if(st==false)
    {
        QMessageBox msgBox;
        msgBox.setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msgBox.setWindowTitle("Error");
        msgBox.setText("NO Bag Detected on Left Solenoid");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.addButton(QMessageBox::Cancel);
        connect( msgBox.button(QMessageBox::Ok), SIGNAL(clicked()) ,this, SLOT(LeftSensorIntStatus()));
        msgBox.exec();   
    }
    else
    {
       QMessageBox msgBox;
        msgBox.setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msgBox.setWindowTitle("Error");
        msgBox.setText("SAME Bag Detected on Left Solenoid");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.addButton(QMessageBox::Cancel);
        connect( msgBox.button(QMessageBox::Ok), SIGNAL(clicked()) ,this, SLOT(LeftSensorIntStatus()));
        msgBox.exec();
    
    }
}


void Service::CheckForSeedsOnOff(bool s)
{
    s_CheckSeeds=s;
    if(s_CheckSeeds){
        widget.btnCheckSeeds->setStyleSheet("background-color:white;");       
    }
    else
    {
        widget.btnCheckSeeds->setStyleSheet("background-color:red;");
    }
    
}

bool Service::GetCheckSeeds()
{
    return s_CheckSeeds;
}
void Service::SetCheckSeeds()
{
     if(s_CheckSeeds){
        s_CheckSeeds=false;
        widget.btnCheckSeeds->setStyleSheet("background-color:red;");
    }
    else
    {
        s_CheckSeeds=true;
        widget.btnCheckSeeds->setStyleSheet("background-color:white;");
    }
}