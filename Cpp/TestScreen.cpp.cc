/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TestScreen.cpp
 * Author: SHALAKHA
 *
 * Created on October 30, 2017, 1:49 PM
 */

#include "TestScreen.h"

#include <QTimer>
#include <QMessageBox>
#include <QPixmap>
#include <QComboBox>
#include <unistd.h>

TestScreen::TestScreen() {
       
    widget.setupUi(this);
    
    // Sets the dialog's background color.
    setStyleSheet("background-color:black;");
    
    // Change the background color of the buttons and labels
    //widget.btnSetpointOnOff->setStyleSheet("background-color:white;");
    //widget.btnSetPointValue->setStyleSheet("background-color:white;");
    widget.btnCounterSetup->setStyleSheet("background-color:white;");
    widget.btnHome->setStyleSheet("background-color:black;");
    widget.btnReset->setStyleSheet("background-color:black;");
    widget.btnMotorSpeed->setStyleSheet("background-color:white;");
    widget.lblCount->setStyleSheet("background-color:black; color:white");
   // widget.lblSetpoint->setStyleSheet("background-color:black; color:white;");
    widget.label->setStyleSheet("background-color:black; color:white;");
    widget.label->setText("Motor Speed");
    widget.lblInfo->setStyleSheet("background-color:black; color:white;");
    widget.lblInfo->setText("Press CALIBRATE to change count color to White");
    widget.lblMotorSliderValue->setStyleSheet("background-color:black; color:white;");
    widget.lblMotorSliderValue->setText("0");   
    widget.btnStop->setStyleSheet("background-color:black;");
    widget.btnStart->setStyleSheet("background-color:black;");
    widget.lblTotalCount->setStyleSheet("background-color:black; color:white;");
    widget.lblTotalCount->setText("Total Count");
    widget.btnMotorInc->setStyleSheet("background-color:white;");
    widget.btnMotorDec->setStyleSheet("background-color:white;");
    widget.btnContinue->setStyleSheet("background-color:black;");
    widget.lblMode->setStyleSheet("background-color:black; color:white;");
    widget.lblMode->setText("Test Mode");

    // Add images to the buttons ///////////////////////////////////////////////
     // Load the Home bitmap onto the Home Screen button.
    widget.btnHome->setText("");    // Remove the text so the bitmap fits the button.
    QPixmap pix(":/images/home_button.png");
    QIcon icon(pix);
    widget.btnHome->setIcon(icon);
    widget.btnHome->setIconSize(widget.btnHome->rect().size());
    widget.btnHome->setFixedSize(widget.btnHome->rect().size());
    
    // Load the Reset bitmap onto the RESET button.
    widget.btnReset->setText("");    // Remove the text so the bitmap fits the button.
    QPixmap pix2(":/images/reset_button.png");
    QIcon icon2(pix2);
    widget.btnReset->setIcon(icon2);
    widget.btnReset->setIconSize(widget.btnReset->rect().size());
    widget.btnReset->setFixedSize(widget.btnReset->rect().size());
    
    // Load the Stop bitmap onto the STOP button.
    widget.btnStop->setText("");    // Remove the text so the bitmap fits the button.
    QPixmap pix3(":/images/stop_button.png");
    QIcon icon3(pix3);
    widget.btnStop->setIcon(icon3);
    widget.btnStop->setIconSize(widget.btnStop->rect().size());
    widget.btnStop->setFixedSize(widget.btnStop->rect().size());
    
    // Load the Start bitmap onto the START button.
    widget.btnStart->setText("");    // Remove the text so the bitmap fits the button.
    QPixmap pix4(":/images/start_button.png");
    QIcon icon4(pix4);
    widget.btnStart->setIcon(icon4);
    widget.btnStart->setIconSize(widget.btnStart->rect().size());
    widget.btnStart->setFixedSize(widget.btnStart->rect().size());
    
    // Load the Continue bitmap onto the CONTINUE button.
    widget.btnContinue->setText("");    // Remove the text so the bitmap fits the button.
    QPixmap pix5(":/images/continue_button.png");
    QIcon icon5(pix5);
    widget.btnContinue->setIcon(icon5);
    widget.btnContinue->setIconSize(widget.btnContinue->rect().size());
    widget.btnContinue->setFixedSize(widget.btnContinue->rect().size());
    
    ////////////////////////////////////////////////////////////////////////////
    // Connect signals and slots
    connect(widget.btnHome, SIGNAL(pressed()), this, SLOT(ExitToHomeWindow()));
    connect(widget.btnReset, SIGNAL(pressed()), this, SLOT(ZeroCount()));
    //connect(widget.btnSetpointOnOff, SIGNAL(pressed()), this, SLOT(EnableDisableSetpoint()));
    connect(widget.btnCounterSetup, SIGNAL(pressed()), this, SLOT(CalibrateCounter()));
   // connect(widget.btnSetPointValue, SIGNAL(pressed()), this, SLOT(DisplayNumPad()));
    connect(widget.btnMotorSpeed, SIGNAL(pressed()), this, SLOT(DisplayMotorNumPad()));
    connect(widget.btnStop, SIGNAL(pressed()), this, SLOT(StopCounting()));
    connect(widget.btnStart, SIGNAL(pressed()), this, SLOT(StartMotor()));
    connect(widget.btnMotorInc, SIGNAL(pressed()), this, SLOT(IncreaseMotorSpeed()));
    connect(widget.btnMotorDec, SIGNAL(pressed()), this, SLOT(DecreaseMotorSpeed()));
    connect(widget.btnContinue, SIGNAL(pressed()), this, SLOT(PauseContinue()));
    
    // Read the counter's settings from the database.
    QString result= m_DbTest.LoadCounterConfig(m_SeedCounter);
    
    totalSeedCount=0;
    CountingStatus=false;
    m_SetMotorSpeed=0;
    PauseStatus=false;
    // Create a timer to refresh the count.
    QTimer *countRefreshtimer = new QTimer(this);
    connect(countRefreshtimer, SIGNAL(timeout()), this, SLOT(UpdateCount()));
    countRefreshtimer->start(TT_COUNT_REFRESH_TIMER_INTERVAL);
    m_SeedCounter.Calibrate();
}

TestScreen::~TestScreen() {
}


void TestScreen::ExitToHomeWindow()
{   
    m_Motor.SetSpeed(0);    // Shut off the motor.    close();
    CountingStatus=false;
    close();
}


void TestScreen::ZeroCount()
{
    m_SeedCounter.ClearCount(); 
 }

void TestScreen::MotorTest()
{
    m_Motor.TestPwm();
}

void TestScreen::ChangeMotorSpeed(int speed)
{   
    widget.lblMotorSliderValue->setText(QString::number(speed));
    m_Motor.SetSpeed(100-speed);
    widget.lblInfo->setText("");    
}


void TestScreen::CalibrateCounter()
{   
    m_SeedCounter.Calibrate();
    widget.lblInfo->setText("Set MOTOR SPEED");
}

void TestScreen::DisplayMotorNumPad(){
          
    m_MotorNumPad.setWindowFlags(Qt::FramelessWindowHint);
    m_MotorNumPad.setModal(true);
    m_MotorNumPad.move(300,100);
    m_MotorNumPad.SetNewValue();
    m_MotorNumPad.exec();
    int Speed = m_MotorNumPad.GetSpeed();
    if (Speed > 99) {
        m_MotorNumPad.BlanklblValue();
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR");    
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Motor Speed cannot be greater than 99");	     
        msg->show();
    }
    else {
        m_SetMotorSpeed=Speed;
    //ChangeMotorSpeed(m_SetMotorSpeed);
        widget.lblMotorSliderValue->setText(QString::number(m_SetMotorSpeed));
        widget.lblInfo->setText("Press START to count");
    }
}

void TestScreen::StartMotor(){
    if(m_SetMotorSpeed == 0)
    {
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR");    
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Set Motor Speed");	     
        msg->show();
    }
    else {
    CountingStatus=true;
    ChangeMotorSpeed(m_SetMotorSpeed);
    }
} 


void TestScreen::CheckforSeeds(){
    widget.lblInfo->setText("Check for Seeds, if done press HOME");
}


void TestScreen::UpdateCount()
{   
    char count[10]; 
    bool bHealthGood = m_SeedCounter.ReadHealth(); // Get the health status of the counter.
      
    sprintf(count, "%d", m_SeedCounter.GetCount());
 
    if(bHealthGood)
        m_CountLblText = "<font color='white'>";
    else
    { 
        m_CountLblText = "<font color='red'>";
        if (CountingStatus)
        {
        m_Motor.SetSpeed(0);
        widget.lblInfo->setText("Clean COUNTER Hardware");
        }
    }
    m_CountLblText += count;
    m_CountLblText += "</font";
    widget.lblCount->setText(m_CountLblText); 
   
}

void TestScreen::IncreaseMotorSpeed(){
    m_SetMotorSpeed++;
    if (m_SetMotorSpeed > 99) {
         m_SetMotorSpeed=99;
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR");    
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Motor Speed cannot be greater than 99");	     
        msg->show();
    }
    else {
    widget.lblMotorSliderValue->setText(QString::number(m_SetMotorSpeed));
    ChangeMotorSpeed(m_SetMotorSpeed);
    }
}
void TestScreen::DecreaseMotorSpeed(){
    m_SetMotorSpeed--;
    if (m_SetMotorSpeed < 0) {
        m_SetMotorSpeed=0;
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR");    
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Motor Speed cannot be less than 0");	     
        msg->show();
    }
    else
    {
    widget.lblMotorSliderValue->setText(QString::number(m_SetMotorSpeed));
    ChangeMotorSpeed(m_SetMotorSpeed);
    }
}

/*void TestScreen::EnableDisableSetpoint()
{
    m_SetpointEnabled = !m_SetpointEnabled;
    if(m_SetpointEnabled)  widget.lblSetpoint->setStyleSheet("background-color:black; color:white; text-decoration: none;");
    else widget.lblSetpoint->setStyleSheet("background-color:black; color:red; text-decoration: line-through;");
}*/

void TestScreen::StopCounting(){
    m_Motor.SetSpeed(0); 
    CountingStatus=false;
    widget.lblInfo->setText("STOPPED");
    ZeroCount();
}

void TestScreen::PauseContinue(){
    if (!PauseStatus && CountingStatus)
    {
        CountingStatus = false;
        m_Motor.SetSpeed(0); 
        PauseStatus = true;
        widget.lblInfo->setText("PAUSED");
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("STATUS");  
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("PAUSED");	     
        msg->show();
    }
   else if (PauseStatus && !CountingStatus)
    {
        CountingStatus = true;
        ChangeMotorSpeed(m_SetMotorSpeed);
        PauseStatus=false;
        widget.lblInfo->setText("Counting...");
    }
}

/*std::string s = std::to_string(m_SeedCounter.GetCount());
    char const *pchar = s.c_str();
    QMessageBox* msg = new QMessageBox();
   msg->setWindowTitle("Count Point"); 
   msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");   
   msg->setText(pchar);	     
   msg->show(); 
*/