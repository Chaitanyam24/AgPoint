
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SolenoidCountingScreen.cpp
 * Author: SHALAKHA
 *
 * Created on December 19, 2017, 10:33 AM
 */

#include "SolenoidCountingScreen.h"
#include "PrinterCommands/PrinterCommands.h"
#include <QTimer>
#include <QMessageBox>
#include <QPixmap>
#include <QComboBox>
#include <unistd.h>
#include <QString>


static volatile int globalMotorSpeed; 

SolenoidCountingScreen::SolenoidCountingScreen() {
    widget.setupUi(this);
    // Sets the dialog's background color.
    setStyleSheet("background-color:black;");
    
    // Change the background color of the buttons and labels
    widget.btnSetpointOnOff->setStyleSheet("background-color:white;");
    widget.btnSetpointOnOff->setVisible(false);
    widget.btnSetPointValue->setStyleSheet("background-color:white;");
    widget.btnTestSolenoids->setStyleSheet("background-color:white;");
    widget.btnDualPrint->setStyleSheet("background-color:white;");
    widget.btnBagNo->setStyleSheet("background-color:white;");
    widget.lblBagNo->setStyleSheet("background-color:black; color:white;");
    widget.lblBagNo->setText("1");
    //widget.btnTestSolenoids->setVisible(false);
    widget.radBtnRight->setStyleSheet("background-color:black; color:white");
    widget.radBtnLeft->setStyleSheet("background-color:black; color:white");
    widget.btnHome->setStyleSheet("background-color:black;");
    widget.btnReset->setStyleSheet("background-color:black;");
    widget.lblCount->setStyleSheet("background-color:black; color:white");
    widget.lblTotalCount->setStyleSheet("background-color:black; color:white");
    widget.lblTotalCount->setText("Total Count"); 
    widget.lblSetpoint->setStyleSheet("background-color:black; color:white;");
    widget.btnEnableSolenoids->setStyleSheet("background-color:white;");
    widget.label->setStyleSheet("background-color:black; color:white;");
    widget.label->setText("Motor Speed");
    widget.lblBag->setStyleSheet("background-color:black; color:white;");
    widget.lblBag->setText("Bag #");
    widget.lblBagNumber->setStyleSheet("background-color:black; color:white;");
    widget.lblBagNumber->setText("1");
    widget.lblMotorSliderValue->setStyleSheet("background-color:black; color:white;");
    widget.lblMotorSliderValue->setText("0");  
    widget.btnStop->setStyleSheet("background-color:black;");
    widget.btnStart->setStyleSheet("background-color:black;");
    widget.btnContinue->setStyleSheet("background-color:black;");
    widget.btnPrint->setStyleSheet("background-color:white;");
    widget.lblInfo->setStyleSheet("background-color:black; color:white;");
    widget.lblInfo->setText("Press CALIBRATE to change count color to White");
    widget.btnCalibrate->setStyleSheet("background-color:white;");
    widget.lblMode->setStyleSheet("background-color:black; color:white;");
    widget.lblMode->setText("901D Seed Dual-Chute");
    widget.btnMotorInc->setStyleSheet("background-color:white;");
    widget.btnMotorDec->setStyleSheet("background-color:white;");
    widget.btnMotorSpeed->setStyleSheet("background-color:white;");
    widget.btnBagSensor->setStyleSheet("background-color:white;");
    
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
    connect(widget.btnTestSolenoids, SIGNAL(pressed()), this, SLOT(ToggleSolenoids()));
    connect(widget.btnSetPointValue, SIGNAL(pressed()), this, SLOT(DisplayNumPad()));
    connect(widget.btnSetpointOnOff, SIGNAL(pressed()), this, SLOT(EnableDisableSetpoint()));
    connect(widget.btnEnableSolenoids, SIGNAL(pressed()), this, SLOT(EnableDisableSolenoids()));
    connect(widget.btnCalibrate, SIGNAL(pressed()), this, SLOT(CallCalibrate()));
    connect(widget.btnMotorSpeed, SIGNAL(pressed()), this, SLOT(DisplayMotorNumPad()));
    connect(widget.btnStop, SIGNAL(pressed()), this, SLOT(StopCounting()));
    connect(widget.btnStart, SIGNAL(pressed()), this, SLOT(StartMotor()));
    connect(widget.btnMotorInc, SIGNAL(pressed()), this, SLOT(IncreaseMotorSpeed()));
    connect(widget.btnMotorDec, SIGNAL(pressed()), this, SLOT(DecreaseMotorSpeed()));
    connect(widget.btnContinue, SIGNAL(pressed()), this, SLOT(PauseContinue()));
    connect(widget.btnPrint, SIGNAL(pressed()), this, SLOT(CallPrint()));
    connect(widget.btnDualPrint, SIGNAL(pressed()), this, SLOT(PrintForDualChute()));
    connect(widget.btnBagNo, SIGNAL(pressed()), this, SLOT(CallSetBagNumber()));
    connect(widget.btnBagSensor, SIGNAL(pressed()), this, SLOT(ToggleBagMode()));
    // Create a timer to refresh the count.
    QTimer *countRefreshtimer = new QTimer(this);
    connect(countRefreshtimer, SIGNAL(timeout()), this, SLOT(UpdateCount()));
    countRefreshtimer->start(D_COUNT_REFRESH_TIMER_INTERVAL);
    
      // Create a timer to refresh the count.
    /*QTimer *interruptRefreshtimer = new QTimer(this);
    connect(interruptRefreshtimer, SIGNAL(timeout()), this, SLOT(SensorInterrupt()));
    interruptRefreshtimer->start(D_INTERRUPT_REFRESH_TIMER_INTERVAL); */
    
    // Variable initialization
    m_SetpointEnabled = true;
    m_Setpoint = 100;
    BagNumber = 1;
    PrintMode=true;
    PrintFormat=true;
    BagOnOff=false;
    // Read the counter's settings from the database.
    QString result= m_DbTest.LoadCounterConfig(m_SeedCounter);

    // Variable initialization
    ZeroCount();
    //m_Setpoint = 100;
    globalMotorSpeed=0;
    //m_SetpointNumPad.SetSetpoint(m_Setpoint);
    m_MotorStatus = false;
    CountingStatus = false;
    //m_SetMotorSpeed=0;
    PauseStatus=false;
    CountTimer=true;
    m_SeedCounter.Calibrate();
    m_SetMaxBagNumber=1;
    countchange=0;
    // Solenoids
    m_Solenoids.EnableSolenoids(true);   
    widget.btnEnableSolenoids->setStyleSheet("background-color:red;"); //Single Batch OFF
    m_SetMotorSpeed=0;
    LotCode="";
    ProductID="";    
    m_CheckSeeds=false;
    //timer to check seed status.
    connect(checkRefreshtimer, SIGNAL(timeout()), this, SLOT(CheckforSeeds()));
    checkRefreshtimer->blockSignals(true);
}

SolenoidCountingScreen::~SolenoidCountingScreen() {
}


void SolenoidCountingScreen::ExitToHomeWindow()
{
    checkRefreshtimer->blockSignals(true);
    if(m_Solenoids.GetSolenoidsState() == true)
        m_Solenoids.EnableSolenoids(false); // Disable solenoids when exiting the counting screen.
    m_Motor.SetSpeed(0);    // Shut off the motor.    close();
    close();
}


void SolenoidCountingScreen::UpdateCount()
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
    widget.radBtnRight->setChecked(m_Solenoids.GetRight());
    widget.radBtnLeft->setChecked(m_Solenoids.GetLeft());
    // Get count from counter and update displayed count.
    if(CountingStatus && CountTimer && (m_SeedCounter.GetCount() >= m_Setpoint) && m_Solenoids.GetSolenoidsState())
    {
        CountTimer=false;
        m_Motor.SetSpeed(0);    // Shut off the motor. SP=0
        m_MotorStatus=false;    
        QTimer::singleShot(1000,this,SLOT(CallCheckBag()));//usleep(1000000);     
    }
  
    if(CountingStatus && CountTimer && m_Solenoids.GetSolenoidsState() && (m_MotorStatus == false) && (m_SeedCounter.GetCount() >= (m_Setpoint- GetReducedSetPoint())))
    {   
        m_MotorStatus = true;
        int speed;
        if(m_SetMotorSpeed >= 80) { speed = 0.55 * m_SetMotorSpeed; }
        else if( m_SetMotorSpeed < 80 && m_SetMotorSpeed >= 75) { speed = 0.60 * m_SetMotorSpeed; }
        else if( m_SetMotorSpeed < 75 && m_SetMotorSpeed >= 68) { speed = 0.65 * m_SetMotorSpeed; }
        else if( m_SetMotorSpeed < 68 && m_SetMotorSpeed >= 62) { speed = 0.70 * m_SetMotorSpeed; }
        else if( m_SetMotorSpeed < 62 && m_SetMotorSpeed >= 55) { speed = 0.80 * m_SetMotorSpeed; }
        else { speed = 0.86 * m_SetMotorSpeed; }
        m_Motor.SetSpeed(100-speed); //reduce motor speed  
    }
      // check the time lag in count change to trigger the Qtimer
    if(m_CheckSeeds && CountingStatus && (countchange != m_SeedCounter.GetCount()))
    { 
        countchange = m_SeedCounter.GetCount();
        widget.lblInfo->setText("");
        checkRefreshtimer->blockSignals(false);
        checkRefreshtimer->start(D_CHECK_TIMER_INTERVAL);
    }
}
int SolenoidCountingScreen::GetReducedSetPoint()
{
     int sp;
    if( m_Setpoint < 100 && m_Setpoint >= 60) { sp = 7; }
    else if( m_Setpoint < 60 && m_Setpoint >= 30) { sp = 6; }
    else if( m_Setpoint < 30 && m_Setpoint >= 1) { sp = 4; }
    else { sp = 8; }
    return 8;
}

void SolenoidCountingScreen::CallCheckBag()
{
    SaveDataToTxtFile();
    ZeroCount();       
    BagNumber++;
    if(BagNumber>m_SetMaxBagNumber)
    {
        widget.lblInfo->setText("Done!");
        QMessageBox* msgNo = new QMessageBox();
        msgNo->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msgNo->setWindowTitle("Count Complete");  
        msgNo->setText("Complete!");
        msgNo->show();
        checkRefreshtimer->blockSignals(true);
        BagNumber=1;
        DisplayBagNumber();
        CountingStatus = false;
    }
    else 
    {
        if(BagOnOff){
            if( !m_Solenoids.GetRight())
            {
                RightSensorIntStatus();
                if(CountingStatus && !PauseStatus)
                {
                    ToggleSolenoids(); 
                    DisplayBagNumber();
                    usleep(250000);
                    ChangeMotorSpeed(globalMotorSpeed);
                }
            }
            else if(!m_Solenoids.GetLeft())
            {
                if(BagNumber==2)
                {                
                    LeftSensor();
                    m_Sensor.ResetLeftSensorStatus();
                    if(CountingStatus && !PauseStatus)
                    {
                        ToggleSolenoids(); 
                        DisplayBagNumber();
                        usleep(250000);
                        ChangeMotorSpeed(globalMotorSpeed);
                    }
                }
                else
                {
                    LeftSensorIntStatus();
                    if(CountingStatus && !PauseStatus)
                    {
                        ToggleSolenoids(); 
                        DisplayBagNumber();
                        usleep(250000);
                        ChangeMotorSpeed(globalMotorSpeed);
                    }
                 }
            }
        else
        {
            ToggleSolenoids(); 
            DisplayBagNumber();
            usleep(250000);
            ChangeMotorSpeed(globalMotorSpeed);
        }       
    }
    CountTimer=true;
}
}

void SolenoidCountingScreen::ZeroCount()
{
    m_SeedCounter.ClearCount(); 
 }

void SolenoidCountingScreen::MotorTest()
{
    m_Motor.TestPwm();
}

void SolenoidCountingScreen::ChangeMotorSpeed(int speed)
{
    widget.lblMotorSliderValue->setText(QString::number(speed));
    globalMotorSpeed = speed;
    m_Motor.SetSpeed(100-speed);
    widget.lblInfo->setText("");  
}

void SolenoidCountingScreen::ToggleSolenoids()
{
    if(m_Solenoids.GetSolenoidsState())
        m_Solenoids.Toggle();
}

void SolenoidCountingScreen::DisplayCounterSetupWindow()
{
    CounterConfig *configForm = new CounterConfig();
    configForm->setWindowFlags(Qt::FramelessWindowHint);
    configForm->move(0,20);
    configForm->setModal(true);
    configForm->exec(); 
    delete configForm;
}

void SolenoidCountingScreen::DisplayNumPad()
{   //Note:  Modal dialogs aren't modal.
    widget.lblInfo->setText("");
    if (m_SetpointEnabled == true)
    {
        m_SetpointNumPad.setWindowFlags(Qt::FramelessWindowHint);
        m_SetpointNumPad.setModal(true);
        m_SetpointNumPad.move(300,100);  // Move towards the center of the Pi screen
        m_SetpointNumPad.SetNewValue();
        m_SetpointNumPad.exec();
        if(m_SetpointNumPad.GetSetpoint()==0) {
            QMessageBox* msg = new QMessageBox();
            msg->setWindowTitle("ERROR");  
            msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
            msg->setText("Set Point cannot be 0");	     
            msg->show();
        }
        else{
            m_Setpoint = m_SetpointNumPad.GetSetpoint();
            m_SetpointNumPad.SetSetpoint(m_Setpoint);
        }
        // Update the displayed setpoint value.
        QString temp;
        temp.setNum(m_Setpoint);
        temp = "SP = " + temp;
        widget.lblSetpoint->setText(temp);
        widget.lblInfo->setText("Press SET MOTOR SPEED");
    }
    else 
    {
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR"); 
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Enable Set Point");	     
        msg->show(); 
    } 
}

void SolenoidCountingScreen::EnableDisableSetpoint()
{
       if(m_SetpointEnabled == false) {
        m_SetpointEnabled=true;
        widget.lblSetpoint->setStyleSheet("background-color:black; color:white; text-decoration: none;");
        widget.lblInfo->setText("Change SET POINT VALUE");
    }
    else{
        m_SetpointEnabled=false;
        widget.lblSetpoint->setStyleSheet("background-color:black; color:red; text-decoration: line-through;");   
        widget.lblInfo->setText("Press SET MOTOR SPEED");
    }
}

void SolenoidCountingScreen::EnableDisableSolenoids()
{
    if(!m_Solenoids.GetRight())
        {
            ToggleSolenoids();
        }
    m_Solenoids.EnableSolenoids(!m_Solenoids.GetSolenoidsState());
    if(m_Solenoids.GetSolenoidsState())
    {
        widget.btnEnableSolenoids->setStyleSheet("background-color:red;"); //Total OFF
    }
    else
    {
        widget.btnEnableSolenoids->setStyleSheet("background-color:green;"); //Total ON      
    }
}



void SolenoidCountingScreen::DisplayMotorNumPad(){
    //debugging
   /* std::string s = std::to_string(m_SeedCounter.GetCount())+ " "+std::to_string(m_Setpoint);
    char const *pchar = s.c_str();
    QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("Count Point");    
    msg->setText(pchar);	     
    msg->show();*/

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
        m_SetMotorSpeed = Speed;
        widget.lblMotorSliderValue->setText(QString::number(m_SetMotorSpeed));
        widget.lblInfo->setText("Press START to count");
    }
    m_Motor.SetSpeed(0);
}

void SolenoidCountingScreen::StartMotor(){    
    if(!m_Solenoids.GetRight())
    {
        ToggleSolenoids(); 
        RightSensor();
    }
    if(m_Solenoids.GetRight())
    {
        RightSensor();
        m_Sensor.ResetRightSensorStatus();
        m_Sensor.ResetLeftSensorStatus();
    }
    if(m_SetMotorSpeed == 0)
    {
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR");    
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Set Motor Speed");	     
        msg->show();
    }
    else 
    { 
        checkRefreshtimer->blockSignals(false);
        ZeroCount();
        CountingStatus = true;
        CountTimer=true;
        PauseStatus=false;
        BagNumber=1;
        DisplayBagNumber();
        QPixmap pix5(":/images/continue_button.png");
        QIcon icon5(pix5);
        widget.btnContinue->setIcon(icon5);
        widget.btnContinue->setIconSize(widget.btnContinue->rect().size());
        widget.btnContinue->setFixedSize(widget.btnContinue->rect().size());
        ChangeMotorSpeed(m_SetMotorSpeed);
        widget.lblInfo->setText("Counting...");
    }
}

void SolenoidCountingScreen::IncreaseMotorSpeed(){
    m_SetMotorSpeed++;
    if(CountingStatus == false)
    {
        m_SetMotorSpeed--;
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR");    
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("This can be used only while motor is ON");	     
        msg->show();
    }
    else if (m_SetMotorSpeed > 99) {
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
void SolenoidCountingScreen::DecreaseMotorSpeed(){
    m_SetMotorSpeed--;
    if(CountingStatus == false)
    {
        m_SetMotorSpeed++;
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR");    
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("This can be used only while motor is ON");	     
        msg->show();
    }
    else if (m_SetMotorSpeed < 0) {
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


void SolenoidCountingScreen::StopCounting(){
    m_Motor.SetSpeed(0); 
    checkRefreshtimer->blockSignals(true);
    CountingStatus = false;
    widget.lblInfo->setText("STOPPED");
    BagNumber=1;
    DisplayBagNumber();   
    ZeroCount(); 
}

void SolenoidCountingScreen::PauseContinue(){
   if (!PauseStatus && CountingStatus)
    {
       if(m_SeedCounter.GetCount() >= m_Setpoint) { ZeroCount(); }
        CountingStatus = false;
        m_Motor.SetSpeed(0); 
        PauseStatus = true;
        checkRefreshtimer->blockSignals(true);
        QPixmap pix5(":/images/pause_button.png");
        QIcon icon5(pix5);
        widget.btnContinue->setIcon(icon5);
        widget.btnContinue->setIconSize(widget.btnContinue->rect().size());
        widget.btnContinue->setFixedSize(widget.btnContinue->rect().size());
        widget.lblInfo->setText("Paused");
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("STATUS");  
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Press PAUSE To Continue");	     
        msg->show();
    }
   else if (PauseStatus && !CountingStatus)
    {
        if(m_Solenoids.GetSolenoidsState() && m_Solenoids.GetRight()) { RightSensor(); }
        else if(m_Solenoids.GetSolenoidsState() && m_Solenoids.GetLeft()) { LeftSensor(); }
        CountingStatus = true;
        CountTimer=true;
        ChangeMotorSpeed(m_SetMotorSpeed);
        PauseStatus=false;
        checkRefreshtimer->blockSignals(false);
        checkRefreshtimer->start(D_CHECK_TIMER_INTERVAL);
        QPixmap pix5(":/images/continue_button.png");
        QIcon icon5(pix5);
        widget.btnContinue->setIcon(icon5);
        widget.btnContinue->setIconSize(widget.btnContinue->rect().size());
        widget.btnContinue->setFixedSize(widget.btnContinue->rect().size());
        widget.lblInfo->setText("Counting...");
    }
}

/*std::string s = std::to_string(m_SeedCounter.GetCount());
    char const *pchar = s.c_str();
    QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("Count Point");    
    msg->setText(pchar);	     
    msg->show(); 
*/


void SolenoidCountingScreen::CallCalibrate()
{
   m_SeedCounter.Calibrate();
   widget.lblInfo->setText("Select SET POINT ON/OFF, by default ON");
}

void SolenoidCountingScreen::DisplayBagNumber()
{
    widget.lblBagNumber->setText(QString::number(BagNumber));
}
void SolenoidCountingScreen::SetPrinterFD(int a){
    m_PrinterCommands.SetFD(a);
    /*QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("STATUS");
    msg->setText(QString::number(a));	     
    msg->show();*/
}

void SolenoidCountingScreen::CallPrint()
{
    int PrinterFD = m_PrinterCommands.GetFD();
     if (PrinterFD <=0){
         QMessageBox* msg = new QMessageBox();
         msg->setWindowTitle("ERROR");    
         msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
         msg->setText("Printer Not Connected");	     
         msg->show();
     }
    else
    {
        if(PrintFormat==false)
        { 
            m_PrinterCommands.CSVPrint();
        }
        else if(PrintFormat==true)
        {
            m_PrinterCommands.FormatPrint();
        }
    }
}


void SolenoidCountingScreen::SaveDataToTxtFile(){
    
    //Clear Carousel Print file before adding new carousel print
    if(BagNumber == 1 ){
        DualFile.open("/home/pi/DualPrint.txt", std::fstream::out | std::fstream::trunc);
        DualFile.close();
    }
    timeval curTime;
    tm *my_date_time;
    gettimeofday(&curTime, NULL);
    my_date_time = localtime(&curTime.tv_sec);
    std::string date=std::to_string(my_date_time->tm_mon + 1) +"/"+ std::to_string(my_date_time->tm_mday) +"/"+std::to_string(my_date_time->tm_year - 100);
    std::string time= std::to_string(my_date_time->tm_hour) +":"+ std::to_string(my_date_time->tm_min) +":"+ std::to_string(my_date_time->tm_sec);
   
    //Save data to SeedData.txt file
    WebFile.open("/var/www/html/WebSeedData.txt",std::ios_base::app); //append data
    PrintFile.open("/home/pi/PrintSeedData.txt",std::ios_base::app);
    SinglePrintFile.open("/home/pi/RecentFile.txt",std::fstream::out);
    WebFile << LotCode.toStdString() + ","+ ProductID.toStdString()+","+ date + "," + time + "," +std::to_string(m_SeedCounter.GetCount())+","+ std::to_string(BagNumber) ;
    WebFile << "\n";
    PrintFile << LotCode.toStdString() + ","+ ProductID.toStdString()+","+date + "," + time + "," +std::to_string(m_SeedCounter.GetCount())+","+ std::to_string(BagNumber);
    PrintFile << "\n";
    SinglePrintFile << LotCode.toStdString() + ","+ ProductID.toStdString()+","+date + "," + time + "," +std::to_string(m_SeedCounter.GetCount())+","+ std::to_string(BagNumber);
    SinglePrintFile << "\n";
    WebFile.close();
    PrintFile.close();
    SinglePrintFile.close();
    
    //Recent Dual print file
    DualFile.open("/home/pi/DualPrint.txt",std::ios_base::app);
    DualFile << LotCode.toStdString() + ","+ ProductID.toStdString()+","+date + "," + time + "," +std::to_string(m_SeedCounter.GetCount())+","+ std::to_string(BagNumber);
    DualFile << "\n";
    DualFile.close();
    
    if(PrintMode==true){
        int PrinterFD = m_PrinterCommands.GetFD();
        if (PrinterFD <=0){
            QMessageBox* msg = new QMessageBox();
            msg->setWindowTitle("ERROR");    
            msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
            msg->setText("Printer Not Connected");	     
            msg->show();
        }
        else {
            if(PrintMode==true && PrintFormat==false){ m_PrinterCommands.CSVPrint();}
            else if(PrintMode==true && PrintFormat==true){ m_PrinterCommands.FormatPrint();}
        }
    }
}

int * SolenoidCountingScreen::GetDVariables()
{
    VarArray[0]= m_Setpoint;
    VarArray[1]= m_SetMotorSpeed;
    VarArray[2]= m_SetMaxBagNumber;
    return VarArray;
}

void SolenoidCountingScreen::InitializeDVariables(bool s,int a,int b, int c, bool d) //SPenable, sp, speed, setBagNumber
{
    m_SetpointEnabled=true;
    m_Setpoint = a;
    m_SetpointNumPad.SetSetpoint(m_Setpoint);
    QString temp;
    temp.setNum(m_Setpoint);
    temp = "SP = " + temp;
    widget.lblSetpoint->setText(temp);
    ChangeMotorSpeed(0);
    m_SetMotorSpeed = b;
    widget.lblMotorSliderValue->setText(QString::number(m_SetMotorSpeed));
    m_Motor.SetSpeed(0);
    m_SetMaxBagNumber=c;
    widget.lblBagNo->setText(QString::number(m_SetMaxBagNumber));
    m_CheckSeeds=d;
    if(m_CheckSeeds)
    {
        checkRefreshtimer->start(D_CHECK_TIMER_INTERVAL);
        checkRefreshtimer->blockSignals(true);
    }
}

void SolenoidCountingScreen::SetPrintMode(bool index)
{
    PrintMode =index;
}

void SolenoidCountingScreen::SetPrintFormat(bool index)
{
    PrintFormat =index;
}

void SolenoidCountingScreen::SetLotCode(QString index){
    LotCode=index;
}
void SolenoidCountingScreen::SetProductID(QString index){
    ProductID=index;
}

bool SolenoidCountingScreen::GetSPStatus(){
    return m_SetpointEnabled;
}

void SolenoidCountingScreen::PrintForDualChute()
{
    int PrinterFD = m_PrinterCommands.GetFD();
    if (PrinterFD <=0)
    {
       QMessageBox* msg = new QMessageBox();
       msg->setWindowTitle("ERROR");    
       msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
       msg->setText("Printer Not Connected");	     
       msg->show();
    }
    else
    {
        m_PrinterCommands.DualChutePrint();
    }
}

void SolenoidCountingScreen::SetBagMode(bool c)
{
    BagOnOff=c;
    if(BagOnOff){
        widget.btnBagSensor->setStyleSheet("background-color:white;");       
    }
    else
    {
        widget.btnBagSensor->setStyleSheet("background-color:red;");
    }
    
}
bool SolenoidCountingScreen::GetBagMode()
{
    return BagOnOff;
}

void SolenoidCountingScreen::ToggleBagMode()
{
    if(BagOnOff){
        BagOnOff=false;
        widget.btnBagSensor->setStyleSheet("background-color:red;");
    }
    else
    {
        BagOnOff=true;
        widget.btnBagSensor->setStyleSheet("background-color:white;");
    }
}


void SolenoidCountingScreen::CallSetBagNumber(){
    MotorNumPad *m_BagNumPad = new MotorNumPad();
    m_BagNumPad->setWindowFlags(Qt::FramelessWindowHint);
    m_BagNumPad->setModal(true);
    m_BagNumPad->move(300,100);
    m_BagNumPad->SetNewValue();
    m_BagNumPad->exec();
    int bagno = m_BagNumPad->GetSpeed();
    if (bagno == 0) {
        m_BagNumPad->BlanklblValue();
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR");    
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Bag Number cannot be 0");	     
        msg->show();
    }
    else {
        m_SetMaxBagNumber=bagno;
        widget.lblBagNo->setText(QString::number(m_SetMaxBagNumber));
    }
    delete m_BagNumPad;
}

void SolenoidCountingScreen::RightSensor()
{
    if(BagOnOff==true)
    {
        bool s=m_Sensor.TestRightSensor();
        if (s==false)
        {
           QMessageBox msgBox;
           msgBox.setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
           msgBox.setWindowTitle("Error");
           msgBox.setText("No Bag Detected on Right Solenoid");
           msgBox.setStandardButtons(QMessageBox::Ok);
           msgBox.addButton(QMessageBox::Cancel);
           connect( msgBox.button(QMessageBox::Ok), SIGNAL(clicked()) ,this, SLOT(RightSensor()));
           connect( msgBox.button(QMessageBox::Cancel), SIGNAL(clicked()) ,this, SLOT(PauseContinue()));
           msgBox.exec();   
        }
    }
    
}
void SolenoidCountingScreen::LeftSensor()
{
     if(BagOnOff==true)
    {
        bool s=m_Sensor.TestLeftSensor();
         if (s==false)
         {
             QMessageBox msgBox;
             msgBox.setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
             msgBox.setWindowTitle("Error");
             msgBox.setText("No Bag Detected on Left Solenoid");
             msgBox.setStandardButtons(QMessageBox::Ok);
             msgBox.addButton(QMessageBox::Cancel);
             connect( msgBox.button(QMessageBox::Ok), SIGNAL(clicked()) ,this, SLOT(LeftSensor()) );
             connect( msgBox.button(QMessageBox::Cancel), SIGNAL(clicked()) ,this, SLOT(PauseContinue()));
             msgBox.exec();
         }
    }
}

void SolenoidCountingScreen::CheckforSeeds(){
    checkRefreshtimer->blockSignals(true);
    if(CountingStatus && m_CheckSeeds)
    {  
        CountingStatus = false;
        m_Motor.SetSpeed(0); 
        PauseStatus = true;
        QPixmap pix5(":/images/pause_button.png");
        QIcon icon5(pix5);
        widget.btnContinue->setIcon(icon5);
        widget.btnContinue->setIconSize(widget.btnContinue->rect().size());
        widget.btnContinue->setFixedSize(widget.btnContinue->rect().size());
        widget.lblInfo->setText("Paused");
        QMessageBox msgBox;
        msgBox.setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msgBox.setWindowTitle("Counting Error");
        msgBox.setText("Please Add Seeds\nPress PAUSE To Continue");
        msgBox.exec();
    }
}

void SolenoidCountingScreen::RightSensorIntStatus(){
    int sw=m_Sensor.GetRightSensorStatus();
    bool st=m_Sensor.TestRightSensor();
    m_Sensor.ResetRightSensorStatus();
    if (sw>0 && st==true)
    {
        /*QMessageBox msgBox;
        msgBox.setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msgBox.setWindowTitle("Done!");
        msgBox.setText("Bag detected");	
        msgBox.exec(); */
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
        connect( msgBox.button(QMessageBox::Cancel), SIGNAL(clicked()) ,this, SLOT(PauseContinue()));
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
        connect( msgBox.button(QMessageBox::Cancel), SIGNAL(clicked()) ,this, SLOT(PauseContinue()));
        msgBox.exec();   
    }
}

void SolenoidCountingScreen::LeftSensorIntStatus(){
    int sw=m_Sensor.GetLeftSensorStatus();
    bool st=m_Sensor.TestLeftSensor();
    m_Sensor.ResetLeftSensorStatus();
    if (sw>0 && st==true)
    {
        /*QMessageBox msgBox;
        msgBox.setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msgBox.setWindowTitle("Done");
        msgBox.setText("Bag detected");	 
        msgBox.exec(); */
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
        connect( msgBox.button(QMessageBox::Cancel), SIGNAL(clicked()) ,this, SLOT(PauseContinue()));
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
        connect( msgBox.button(QMessageBox::Cancel), SIGNAL(clicked()) ,this, SLOT(PauseContinue()));
        msgBox.exec();
    }
}
