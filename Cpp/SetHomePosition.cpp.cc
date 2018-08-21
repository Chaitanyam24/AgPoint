/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SetHomePosition.cpp
 * Author: SHALAKHA
 *
 * Created on November 8, 2017, 1:51 PM
 */

#include "SetHomePosition.h"
#include <QMessageBox>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include <unistd.h>

SetHomePosition::SetHomePosition() {
    widget.setupUi(this);
    // Sets the dialog's background color.
    setStyleSheet("background-color:black;");
    
    // Change the background color of the buttons and labels
    widget.btnCheckConnect->setStyleSheet("background-color:white;");
    widget.btnError->setStyleSheet("background-color:white;");
    widget.btnReconnect->setStyleSheet("background-color:white;");
    widget.btnIncrease->setStyleSheet("background-color:white;");
    widget.btnSetHome->setStyleSheet("background-color:white;");
    widget.btnExit->setStyleSheet("background-color:white;");
    widget.btnReset->setStyleSheet("background-color:white;");
    widget.btnDecrease->setStyleSheet("background-color:white;");
    widget.btnSetHomeDone->setStyleSheet("background-color:white;");
    widget.lblCarouselMotor->setStyleSheet("background-color:black; color:white;");
    widget.lblCarouselMotor->setText("Set Home Position of Carousel Motor");
    widget.lblChute->setStyleSheet("background-color:black; color:white;");
    widget.lblChute->setText("Chute # ");
    widget.lblChuteNumber->setStyleSheet("background-color:black; color:white;");
    widget.lblChuteNumber->setText("1");
    widget.lblPosition->setStyleSheet("background-color:black; color:white;");
    widget.lblPosition->setText("Position Value");
    widget.lblPositionValue->setStyleSheet("background-color:black; color:white;");
    widget.lblPositionValue->setText("0");
    connect(widget.btnIncrease, SIGNAL(pressed()), this, SLOT(IncreasePosition()));
    connect(widget.btnDecrease, SIGNAL(pressed()), this, SLOT(DecreasePosition()));
    connect(widget.btnSetHomeDone, SIGNAL(pressed()), this, SLOT(SetHomePositionDone()));
    connect(widget.btnExit, SIGNAL(pressed()), this, SLOT(ExitToCountScreen()));
    connect(widget.btnReset, SIGNAL(pressed()), this, SLOT(ResetVariables()));
    connect(widget.btnSetHome, SIGNAL(pressed()), this, SLOT(CallPositionZero()));
    connect(widget.btnCheckConnect, SIGNAL(pressed()), this, SLOT(CheckMotorConnection()));
    connect(widget.btnReconnect, SIGNAL(pressed()), this, SLOT(RefreshConnection()));
    connect(widget.btnError, SIGNAL(pressed()), this, SLOT(CheckForError()));
    
    ChuteNumber=1;
    PositionValue=0;
    m_SetRotaryPosition.RotateToZero();
}

SetHomePosition::~SetHomePosition() {
}

void SetHomePosition::ExitToCountScreen()
{
    close();
}
void SetHomePosition::IncreasePosition(){
    bool con= m_SetRotaryPosition.CheckConnection();
    if (con == false){
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR"); 
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Motor not connected");	     
        msg->show();
    }
    PositionValue++;
    m_SetRotaryPosition.RotatePositive();
    widget.lblPositionValue->setText(QString::number(PositionValue)); 
}
void SetHomePosition::DecreasePosition(){
    bool con= m_SetRotaryPosition.CheckConnection();
    if (con == false){
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR"); 
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Motor not connected");	     
        msg->show();
    }
        PositionValue--;
        m_SetRotaryPosition.RotateNegative();
        widget.lblPositionValue->setText(QString::number(PositionValue)); 
       
}
void SetHomePosition::SetHomePositionDone(){
    if(ChuteNumber == 1)
    {
        m_SetRotaryPosition.CheckConn();
        ChutePosition[ChuteNumber-1]= 0;
        m_SetRotaryPosition.SetZeroPosition();
        ChuteNumber++;
        PositionValue=0;
        usleep(250000);
        m_SetRotaryPosition.Rotate45();
        usleep(1000000);
        widget.lblChuteNumber->setText(QString::number(ChuteNumber));
        widget.lblPositionValue->setText(QString::number(PositionValue));
    }
    else {
        ChutePosition[ChuteNumber-1]= PositionValue;
        ChuteNumber++;
            if(ChuteNumber == 9)
             {
                SavePositionToFile();
                close();
            }
            else{
            PositionValue=0;
            usleep(250000);
            m_SetRotaryPosition.Rotate45();
            usleep(1000000);
            widget.lblChuteNumber->setText(QString::number(ChuteNumber));
            widget.lblPositionValue->setText(QString::number(PositionValue));
            }
    }
}

void SetHomePosition::SavePositionToFile()
{
    std::ofstream MotorFile;
    MotorFile.open("/home/pi/MotorPosition.txt");
    for(int i=0; i<8 ;i++)
    {
        MotorFile << std::to_string(ChutePosition[i]) + "\n";
    }
    MotorFile.close();  
}

void SetHomePosition::ResetVariables()
{
    ChuteNumber=1;
    widget.lblChuteNumber->setText("1");
    PositionValue=0;
    widget.lblPositionValue->setText("0");
    m_SetRotaryPosition.RotateToZero();
}

void SetHomePosition::CallPositionZero()
{
    bool con= m_SetRotaryPosition.CheckConnection();
    if (con == true){
    QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("Done!"); 
    msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
    msg->setText("Home Position Set");	     
    msg->show(); 
    m_SetRotaryPosition.SetZeroPosition();
    usleep(1000000);
    }
    else {
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR"); 
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Motor not connected");	     
        msg->show();
    }
}

void SetHomePosition::CheckMotorConnection()
{
    if(m_SetRotaryPosition.CheckConnection())
    {
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR"); 
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Motor is connected");	     
        msg->show();
    }
    else
    {
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR"); 
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Error! Motor is NOT connected");	     
        msg->show();
    }
}
void SetHomePosition::RefreshConnection()
{
    if(m_SetRotaryPosition.Reconnect())
    {
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR"); 
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Motor is connected");	     
        msg->show();
    }
    else
    {
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR"); 
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Error! Motor is NOT connected");	     
        msg->show();
    }
}
void SetHomePosition::CheckForError()
{
    if(m_SetRotaryPosition.CheckForError())
    {
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR"); 
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Error Detected! Try connecting motor again");	     
        msg->show();
    }
    else
    {
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR"); 
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Motor is ready to use!");	     
        msg->show();
    }
}