/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SecScreen.cpp
 * Author: Owner
 *
 * Created on July 18, 2018, 3:07 PM
 */

#include "SecScreen.h"
#include "SetHomePosition.h"
#include <QMessageBox>

SecScreen::SecScreen() {
    widget.setupUi(this);
    
    
    // Sets the dialog's background color.
    setStyleSheet("background-color:black;");
    // Change the background color of the buttons and labels
    widget.btnManual->setStyleSheet("background-color:white;");
    widget.btnDone->setStyleSheet("background-color:white;");
    widget.lblName->setStyleSheet("background-color:black; color:white;");
    widget.lblName->setText("        2nd      ");
    
    
    widget.btnManual->setText("Sensor Test");
   
    
    // Connect signals and slots
    connect(widget.btnManual, SIGNAL(pressed()), this, SLOT(ManualLoadUnload()));
    connect(widget.btnManual, SIGNAL(pressed()), this, SLOT(SensorStatus()));
    connect(widget.btnDone, SIGNAL(pressed()), this, SLOT(ExitToCountScreen()));
   
}

SecScreen::~SecScreen() {
}
void SecScreen::SensorStatus(){
    
        bool s=m_Sensor.TestRightSensor();
         if (s==false)
         {
            QMessageBox msgBox;
            msgBox.setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
            msgBox.setWindowTitle("Error");
            msgBox.setText("No Chute Detected");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.addButton(QMessageBox::Cancel);
            connect( msgBox.button(QMessageBox::Ok), SIGNAL(clicked()) ,this, SLOT(SensorStatus()));
            connect( msgBox.button(QMessageBox::Cancel), SIGNAL(clicked()) ,this, SLOT(PauseContinue()));
            msgBox.exec();   
         }
        
        bool sl=m_Sensor.TestLeftSensor();
         if (sl==false)
         {
            QMessageBox msgBox;
            msgBox.setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
            msgBox.setWindowTitle("Error");
            msgBox.setText("No Bag Detected");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.addButton(QMessageBox::Cancel);
            connect( msgBox.button(QMessageBox::Ok), SIGNAL(clicked()) ,this, SLOT(SensorStatus()));
            connect( msgBox.button(QMessageBox::Cancel), SIGNAL(clicked()) ,this, SLOT(PauseContinue()));
            msgBox.exec();   
         }
    
}
void SecScreen::ManualLoadUnload(){
    if(m_RotateToLoad.CheckConn())
        m_RotateToLoad.Rotate45();
    else
    {
        QMessageBox msgBox;
        msgBox.setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msgBox.setWindowTitle("Counting Error");
        msgBox.setText("Error! Check Carousel Motor Connection");
        msgBox.setStandardButtons(QMessageBox::Ok);  
        msgBox.exec();
    }
}
void SecScreen::ExitToCountScreen(){
    m_RotateToLoad.RotaryStop();
    close();
}