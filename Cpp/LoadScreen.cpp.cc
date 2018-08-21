/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   LoadScreen.cpp
 * Author: SHALAKHA
 *
 * Created on November 2, 2017, 1:33 PM
 */

#include "LoadScreen.h"
#include <QMessageBox>

LoadScreen::LoadScreen() {
    widget.setupUi(this);
    // Sets the dialog's background color.
    setStyleSheet("background-color:black;");
    // Change the background color of the buttons and labels
    widget.btnManual->setStyleSheet("background-color:white;");
    widget.btnAutomatic->setStyleSheet("background-color:white;");
    widget.btnDone->setStyleSheet("background-color:white;");
    widget.lblName->setStyleSheet("background-color:black; color:white;");
    widget.lblName->setText("Load/Unload Bags");
    
    widget.lblManualInfo->setStyleSheet("background-color:black; color:white;");
    widget.lblManualInfo->setText("Click MANUAL \nto load one bag");
    widget.lblAutomaticInfo->setStyleSheet("background-color:black; color:white;");
    widget.lblAutomaticInfo->setText("Click AUTOMATIC \nto load eight bags");
    
    // Connect signals and slots
    connect(widget.btnManual, SIGNAL(pressed()), this, SLOT(ManualLoadUnload()));
    connect(widget.btnAutomatic, SIGNAL(pressed()), this, SLOT(AutomaticLoadUnload()));
    connect(widget.btnDone, SIGNAL(pressed()), this, SLOT(ExitToCountScreen()));
    ChuteNumber=2;
}

LoadScreen::~LoadScreen() {
}


void LoadScreen::ManualLoadUnload(){
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
void LoadScreen::AutomaticLoadUnload(){
    if(m_RotateToLoad.CheckConn())
    {
        m_RotateToLoad.GetPositionFromFile();
        m_RotateToLoad.RotateToNextChute(ChuteNumber);
        connect(loadRefreshtimer, SIGNAL(timeout()), this, SLOT(TimerCallRotate()));
        loadRefreshtimer->start(2500);
    }
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
void LoadScreen::ExitToCountScreen(){
    m_RotateToLoad.RotaryStop();
    close();
}

void LoadScreen::TimerCallRotate()
{
    ChuteNumber++;
    if(ChuteNumber >=9)
    { 
        loadRefreshtimer->stop();
        m_RotateToLoad.RotaryStop(); 
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("Done!"); 
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Done Loading!");	     
        msg->show();
    }
    else {
       // m_RotateToLoad.RotateToSpecficValue(ChuteNumber); 
        m_RotateToLoad.RotateToNextChute(ChuteNumber);
    }
}