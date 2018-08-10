/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MotorNumPad.cpp
 * Author: SHALAKHA
 *
 * Created on October 11, 2017, 5:13 PM
 */

#include "MotorNumPad.h"

#include <QTimer>
#include <QMessageBox>
#include <QPixmap>
#include <unistd.h>
#include <string.h>
#include <QString>

MotorNumPad::MotorNumPad() {
    widget.setupUi(this);
    
     widget.lblMotorSpeed->setTextInteractionFlags(Qt::TextSelectableByKeyboard);
    
    // Sets the dialog's background color.
    setStyleSheet("background-color:black;");
    
    // Change the background color of the buttons
    widget.pb0->setStyleSheet("background-color:blue;");
    widget.pb1->setStyleSheet("background-color:white;");
    widget.pb2->setStyleSheet("background-color:white;");
    widget.pb3->setStyleSheet("background-color:white;");
    widget.pb4->setStyleSheet("background-color:white;");
    widget.pb5->setStyleSheet("background-color:white;");
    widget.pb6->setStyleSheet("background-color:white;");
    widget.pb7->setStyleSheet("background-color:white;");
    widget.pb8->setStyleSheet("background-color:white;");
    widget.pb9->setStyleSheet("background-color:white;");
    widget.pbEnter->setStyleSheet("background-color:white;");
    widget.pbClear->setStyleSheet("background-color:white;");
    widget.lblMotorSpeed->setStyleSheet("background-color:white;");
    
    ////////////////////////////////////////////////////////////////////////////
    // Connect signals and slots
    connect(widget.pb0, SIGNAL(pressed()), this, SLOT(KeyPressed0()));
    connect(widget.pb1, SIGNAL(pressed()), this, SLOT(KeyPressed1()));
    connect(widget.pb2, SIGNAL(pressed()), this, SLOT(KeyPressed2()));
    connect(widget.pb3, SIGNAL(pressed()), this, SLOT(KeyPressed3()));
    connect(widget.pb4, SIGNAL(pressed()), this, SLOT(KeyPressed4()));
    connect(widget.pb5, SIGNAL(pressed()), this, SLOT(KeyPressed5()));
    connect(widget.pb6, SIGNAL(pressed()), this, SLOT(KeyPressed6()));
    connect(widget.pb7, SIGNAL(pressed()), this, SLOT(KeyPressed7()));
    connect(widget.pb8, SIGNAL(pressed()), this, SLOT(KeyPressed8()));
    connect(widget.pb9, SIGNAL(pressed()), this, SLOT(KeyPressed9()));
    connect(widget.pbEnter, SIGNAL(pressed()), this, SLOT(KeyPressedEnter()));
    connect(widget.pbClear, SIGNAL(pressed()), this, SLOT(KeyPressedClear()));
    
    // Variable initialization
    m_ReplaceSpeed = true;
}

MotorNumPad::~MotorNumPad() {
}


void MotorNumPad::KeyPressed(QString key)
{
    if(QString("10") == key)
    {
        accept();
        
    }
    else if(QString("11") == key)
    {       
            SetNewValue();
            m_MotorSpeed=  "";    // Clear setpoint value
            widget.lblMotorSpeed->setText(m_MotorSpeed);
        
    }
    else
    {
        if(m_ReplaceSpeed){
            m_MotorSpeed = "";    // Clear setpoint value
            m_ReplaceSpeed = false;
        }
        m_MotorSpeed += key;
        widget.lblMotorSpeed->setText(m_MotorSpeed); 
    }

}

void MotorNumPad::KeyPressed0(){ KeyPressed("0"); }
void MotorNumPad::KeyPressed1(){ KeyPressed("1"); }
void MotorNumPad::KeyPressed2(){ KeyPressed("2"); }
void MotorNumPad::KeyPressed3(){ KeyPressed("3"); }
void MotorNumPad::KeyPressed4(){ KeyPressed("4"); }
void MotorNumPad::KeyPressed5(){ KeyPressed("5"); }
void MotorNumPad::KeyPressed6(){ KeyPressed("6"); }
void MotorNumPad::KeyPressed7(){ KeyPressed("7"); }
void MotorNumPad::KeyPressed8(){ KeyPressed("8"); }
void MotorNumPad::KeyPressed9(){ KeyPressed("9"); }
void MotorNumPad::KeyPressedEnter(){ KeyPressed("10"); }
void MotorNumPad::KeyPressedClear(){ KeyPressed("11"); }

void MotorNumPad::ExitToHomeWindow()
{
    close();
}


void MotorNumPad::SetSpeed(int value){
    QString temp;
    temp.setNum(value);
    m_MotorSpeed = temp;
    widget.lblMotorSpeed->setText(m_MotorSpeed); 
    widget.lblMotorSpeed->setSelection(0,m_MotorSpeed.length());
    
}

int MotorNumPad::GetSpeed() { 
    return m_MotorSpeed.toInt(); 
}

void MotorNumPad::SetNewValue(){
    m_ReplaceSpeed = true;
}

void MotorNumPad::BlanklblValue(){
    m_MotorSpeed = ""; 
    widget.lblMotorSpeed->setText(m_MotorSpeed);
}