/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   NumPad.cpp
 * Author: Dan
 *
 * Created on August 10, 2017, 5:39 AM
 */

#include "NumPad.h"
#include <QTimer>
#include <QMessageBox>
#include <QPixmap>
#include <unistd.h>
#include <string>
#include <QString>

NumPad::NumPad() {
    widget.setupUi(this);

    widget.lblSetpoint->setTextInteractionFlags(Qt::TextSelectableByKeyboard);
    
    // Sets the dialog's background color.
    setStyleSheet("background-color:black;");
    
    
    // Change the background color of the buttons
    widget.pb0->setStyleSheet("background-color:white;");
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
    widget.lblSetpoint->setStyleSheet("background-color:white;");
    
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
    m_ReplaceSetpoint = true;
}

void NumPad::KeyPressed(QString key)
{
    if(QString("10") == key)
    {
        accept();
        
    }
    else if(QString("11") == key)
    {       
            SetNewValue();
            m_Setpoint = "";    // Clear setpoint value
            widget.lblSetpoint->setText(m_Setpoint);
        
    }
    else
    {
        if(m_ReplaceSetpoint){
            m_Setpoint = "";    // Clear setpoint value
            m_ReplaceSetpoint = false;
        }
        m_Setpoint += key;
        widget.lblSetpoint->setText(m_Setpoint); 
    }

}

void NumPad::KeyPressed0(){ KeyPressed("0"); }
void NumPad::KeyPressed1(){ KeyPressed("1"); }
void NumPad::KeyPressed2(){ KeyPressed("2"); }
void NumPad::KeyPressed3(){ KeyPressed("3"); }
void NumPad::KeyPressed4(){ KeyPressed("4"); }
void NumPad::KeyPressed5(){ KeyPressed("5"); }
void NumPad::KeyPressed6(){ KeyPressed("6"); }
void NumPad::KeyPressed7(){ KeyPressed("7"); }
void NumPad::KeyPressed8(){ KeyPressed("8"); }
void NumPad::KeyPressed9(){ KeyPressed("9"); }
void NumPad::KeyPressedEnter(){ KeyPressed("10"); }
void NumPad::KeyPressedClear(){ KeyPressed("11"); }

void NumPad::ExitToHomeWindow()
{
    close();
}

NumPad::~NumPad() {
}

void NumPad::SetSetpoint(int value){
    QString temp;
    temp.setNum(value);
    m_Setpoint = temp;
    widget.lblSetpoint->setText(m_Setpoint); 
    widget.lblSetpoint->setSelection(0,m_Setpoint.length());
    
}

int NumPad::GetSetpoint() { 
     return m_Setpoint.toInt(); 
}

void NumPad::SetNewValue(){
    m_ReplaceSetpoint = true;
}