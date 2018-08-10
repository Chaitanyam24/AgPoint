/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   CountingScreen.cpp
 * Author: Dan
 *
 * Created on June 12, 2017, 5:39 AM
 */

#include "CountingScreen.h"
#include "SetHomePosition.h"
#include "PrinterCommands/PrinterCommands.h"
#include <QTimer>
#include <QMessageBox>
#include <QPixmap>
#include <QComboBox>
#include <unistd.h>
#include <QString>
#include <qt4/QtCore/qstring.h>

static volatile int globalMotorSpeed; 
CountingScreen::CountingScreen() {
    widget.setupUi(this);
    
    // Sets the dialog's background color.
    setStyleSheet("background-color:black;");
    
    // Change the background color of the buttons and labels
    widget.btnSetPointValue->setStyleSheet("background-color:white;");
    widget.btnCalibrate->setStyleSheet("background-color:white;");
    widget.btnLoad->setStyleSheet("background-color:white;");
    widget.btnHome->setStyleSheet("background-color:black;");
    widget.btnReset->setStyleSheet("background-color:black;");
    widget.btnMotorSpeed->setStyleSheet("background-color:white;");
    widget.btnBagNo->setStyleSheet("background-color:white;");
    widget.lblCount->setStyleSheet("background-color:black; color:white");
    widget.lblSetpoint->setStyleSheet("background-color:black; color:white;");
     widget.btnLoad_2->setStyleSheet("background-color:white;");
    //widget.label->setStyleSheet("background-color:black; color:white;");
   // widget.label->setText("Motor Speed");
    widget.lblInfo->setStyleSheet("background-color:black; color:white;");
    widget.lblInfo->setText("Press CALIBRATE to change count color to White");
    widget.lblBag->setStyleSheet("background-color:black; color:white;");
    widget.lblBag->setText("Bag #");
    widget.lblDisplayBag->setStyleSheet("background-color:black; color:white;");
    widget.lblMotorSliderValue->setStyleSheet("background-color:black; color:white;");
    widget.lblMotorSliderValue->setText("0");   
    widget.btnStop->setStyleSheet("background-color:black;");
    widget.btnStart->setStyleSheet("background-color:black;");
    widget.lblTotalCount->setStyleSheet("background-color:black; color:white;");
    widget.lblTotalCount->setText("Total Count");
    widget.lblBagNo->setStyleSheet("background-color:black; color:white;");
    widget.lblBagNo->setText("");
    widget.btnMotorInc->setStyleSheet("background-color:white;");
    widget.btnMotorDec->setStyleSheet("background-color:white;");
    widget.btnContinue->setStyleSheet("background-color:black;");
    widget.lblMode->setStyleSheet("background-color:black; color:white;");
    widget.lblMode->setText("901C Seed Carousel");
    widget.btnWait->setStyleSheet("background-color:white;");
    widget.btnCarouselPrint->setStyleSheet("background-color:white; color:black;");
    widget.btnPrint->setStyleSheet("background-color:white; color:black;");
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
  
    connect(widget.btnLoad, SIGNAL(pressed()), this, SLOT(LoadUnload()));
    connect(widget.btnLoad_2, SIGNAL(pressed()), this, SLOT(secsensor()));
    connect(widget.btnCalibrate, SIGNAL(pressed()), this, SLOT(CallCalibrate()));
    connect(widget.btnSetPointValue, SIGNAL(pressed()), this, SLOT(DisplayNumPad()));
    connect(widget.btnMotorSpeed, SIGNAL(pressed()), this, SLOT(DisplayMotorNumPad()));
    connect(widget.btnStop, SIGNAL(pressed()), this, SLOT(StopCounting()));
    connect(widget.btnStart, SIGNAL(pressed()), this, SLOT(StartMotor()));
    connect(widget.btnMotorInc, SIGNAL(pressed()), this, SLOT(IncreaseMotorSpeed()));
    connect(widget.btnMotorDec, SIGNAL(pressed()), this, SLOT(DecreaseMotorSpeed()));
    connect(widget.btnContinue, SIGNAL(pressed()), this, SLOT(PauseContinue()));
    connect(widget.btnCarouselPrint, SIGNAL(pressed()), this, SLOT(PrintForCarousel()));
    connect(widget.btnPrint, SIGNAL(pressed()), this, SLOT(PrintFromFile()));
    connect(widget.btnWait, SIGNAL(pressed()), this, SLOT(SetWaitOnOff()));
    connect(widget.btnBagNo, SIGNAL(pressed()), this, SLOT(CallSetBagNumber()));
    // Read the counter's settings from the database.
    QString result= m_DbTest.LoadCounterConfig(m_SeedCounter);
    //m_SetMaxBagNumber=8;
    //widget.lblBagNo->setText(QString::number(m_SetMaxBagNumber));
    // Variable initialization
    countchange=0;
    m_SetpointEnabled = true;
    m_MotorStatus = false;
    BagOnOff=false;
    //m_Setpoint = 100;
    m_BagNumber=0;
    PrintBagNumber=0;
    widget.lblDisplayBag->setText(QString::number(PrintBagNumber+1));
    CountingStatus = false;
    //m_SetpointNumPad.SetSetpoint(m_Setpoint);
    totalSeedCount=0;
    m_SeedCounter.Calibrate();
    globalMotorSpeed=0;
   // m_SetMotorSpeed=0;
    PauseStatus=false;
    BagChangeStatus=false;
    CountTimer=true;
    ZeroCount();
    m_CheckSeeds=false;
    WaitOnOff=false;
    m_Rotary.GetPositionFromFile();
    // Create a timer to refresh the count.
    QTimer *countRefreshtimer = new QTimer(this);
    connect(countRefreshtimer, SIGNAL(timeout()), this, SLOT(UpdateCount()));
    countRefreshtimer->start(COUNT_REFRESH_TIMER_INTERVAL);
    //timer to check seed status.
    connect(checkRefreshtimer, SIGNAL(timeout()), this, SLOT(CheckforSeeds()));
    checkRefreshtimer->blockSignals(true);
}


void CountingScreen::ExitToHomeWindow()
{   
    //SaveDataToTxtFile();
    checkRefreshtimer->blockSignals(true);
    m_Motor.SetSpeed(0);    // Shut off the motor.    close();
    CountingStatus = false;
    ZeroCount();
    m_Rotary.RotaryStop();   //reset rotary motor to home position
    close();
}

CountingScreen::~CountingScreen() {

}

void CountingScreen::ZeroCount()
{
    m_SeedCounter.ClearCount(); 
    
}

void CountingScreen::MotorTest()
{
    m_Motor.TestPwm();
}

void CountingScreen::ChangeMotorSpeed(int speed)
{   
    widget.lblMotorSliderValue->setText(QString::number(speed));
    globalMotorSpeed = speed;
    m_Motor.SetSpeed(100-speed);
    widget.lblInfo->setText(""); 
}


void CountingScreen::DisplayCounterSetupWindow()
{   
    CounterConfig *configForm = new CounterConfig();
    configForm->setWindowFlags(Qt::FramelessWindowHint);
    configForm->setModal(true);
    configForm->move(0,20);
    configForm->exec(); 
    if (configForm->GetSeedProgramStatus() == true)  seedname="";
    delete configForm;
    widget.lblInfo->setText("Press SET POINT VALUE to set the number of seeds to be filled in a bag");
}

void CountingScreen::DisplayNumPad()
{   
    widget.lblInfo->setText("");
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
    m_Motor.SetSpeed(0); 
    widget.lblInfo->setText("Press SET MOTOR SPEED");
}

void CountingScreen::DisplayMotorNumPad(){
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
        msg->setText("Motor Speed cannot be greater than 999");	     
        msg->show();
    }
    else {
        m_SetMotorSpeed=Speed;
    //ChangeMotorSpeed(m_SetMotorSpeed);
        widget.lblMotorSliderValue->setText(QString::number(m_SetMotorSpeed));
        widget.lblInfo->setText("Press START to count");
    }
}

void CountingScreen::StartMotor(){
    SensorStatus();
    if(m_SetMotorSpeed == 0)
    {
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR");    
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Set Motor Speed");	     
        msg->show();  
    }
    else if( (m_SetMaxBagNumber>1) && !m_Rotary.CheckConn() )
    {
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR");    
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Error! Check Carousel Motor Connection");	     
        msg->show(); 
    }
    else
    { 
        PrintBagNumber=0;
        checkRefreshtimer->blockSignals(false);
        widget.lblDisplayBag->setText(QString::number(PrintBagNumber+1));
        CountingStatus = true;
        PauseStatus=false;
        QPixmap pix5(":/images/continue_button.png");
        QIcon icon5(pix5);
        widget.btnContinue->setIcon(icon5);
        widget.btnContinue->setIconSize(widget.btnContinue->rect().size());
        widget.btnContinue->setFixedSize(widget.btnContinue->rect().size());
        widget.lblInfo->setText("Counting...");
        ZeroCount();
        ClearBagNumber();
        m_Rotary.RotaryStop();
        usleep(1000000);
        ChangeMotorSpeed(m_SetMotorSpeed);        
    }
} 

void CountingScreen::ClearBagNumber()
{
    m_BagNumber=0;
 }
void CountingScreen::CheckBagNumber(){
    if (GetBagNumber() <  m_SetMaxBagNumber)
     {      
        usleep(500000);
        int ActualBag = GetBagNumber()+1; 
        m_Rotary.RotateToNextChute(ActualBag);
        usleep(1500000);
        ZeroCount();
        SensorStatus();
        if(CountingStatus) ChangeMotorSpeed(globalMotorSpeed);// restart vibratory motor
    }
   else{ 
        ClearBagNumber();
        //PrintBagNumber=0;
       // widget.lblDisplayBag->setText(QString::number(PrintBagNumber+1));
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("Done !");	 
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Carousel Completed!");	     
        msg->show();
        widget.lblInfo->setText("Done!");
        usleep(1500000);
        m_Rotary.RotaryStop();   //reset rotary motor to home position
        ZeroCount();
        CountingStatus = false;
        checkRefreshtimer->blockSignals(true);
    } 
}
void CountingScreen::IncrementBagNumber(){
    ++m_BagNumber;
}

int CountingScreen::GetBagNumber(){
    return m_BagNumber;
}

int CountingScreen::GetTotalCount(){
    totalSeedCount = m_SeedCounter.GetTotalCount();
    return totalSeedCount;
}

void CountingScreen::SetSeedIndex(int index){
   switch(index){
        case 0:
               seedname="";
                break;
        case 1:
                seedname="CUCUMBER";
                break;
        case 2 :
                 seedname="POPCORN";
                break;
        case 3:    
                seedname="SMALL SEED";
                break;
        case 4 :
                seedname="SOYBEAN";
                break;
         case 5 :
                seedname="SUNFLOWER";
                break;   
         case 6 :
                seedname="WHEAT";
                break;   
         case 7 :
                seedname="CORN";
                break; 
    }
}

void CountingScreen::SaveDataToTxtFile(){
    
    //Clear Carousel Print file before adding new carousel print
    if(PrintBagNumber == 1 ){
        CarouselFile.open("/home/pi/CarouselPrint.txt", std::fstream::out | std::fstream::trunc);
        CarouselFile.close();
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
    WebFile << LotCode.toStdString() + ","+ ProductID.toStdString()+","+ date + "," + time + "," +std::to_string(m_SeedCounter.GetCount())+","+ std::to_string(PrintBagNumber) ;
    WebFile << "\n";
    PrintFile << LotCode.toStdString() + ","+ ProductID.toStdString()+","+date + "," + time + "," +std::to_string(m_SeedCounter.GetCount())+","+ std::to_string(PrintBagNumber);
    PrintFile << "\n";
    SinglePrintFile << LotCode.toStdString() + ","+ ProductID.toStdString()+","+date + "," + time + "," +std::to_string(m_SeedCounter.GetCount())+","+ std::to_string(PrintBagNumber);
    SinglePrintFile << "\n";
    WebFile.close();
    PrintFile.close();
    SinglePrintFile.close();
    
    //Recent Carousel print file
    CarouselFile.open("/home/pi/CarouselPrint.txt",std::ios_base::app);
    CarouselFile << LotCode.toStdString() + ","+ ProductID.toStdString()+","+date + "," + time + "," +std::to_string(m_SeedCounter.GetCount())+","+ std::to_string(PrintBagNumber);
    CarouselFile << "\n";
    CarouselFile.close();
    
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


void CountingScreen :: UpdateCount()
{   
    char count[10]; 
    bool bHealthGood = m_SeedCounter.ReadHealth(); // Get the health status of the counter.
    sprintf(count, "%d", (m_SeedCounter.GetCount()));
 
    if(bHealthGood) m_CountLblText = "<font color='white'>";
    else {
        m_CountLblText = "<font color='red'>";
        if (CountingStatus == true)
        {
            m_Motor.SetSpeed(0);
            widget.lblInfo->setText("Clean COUNTER Hardware");
        }
    }
    m_CountLblText += count;
    m_CountLblText += "</font";
    widget.lblCount->setText(m_CountLblText);  
    if(CountingStatus && CountTimer &&(m_SeedCounter.GetCount() >= m_Setpoint))
   {  
        CountTimer=false;
        m_Motor.SetSpeed(0);  // Shut off the motor.  
        QTimer::singleShot(2000,this,SLOT(CallBagCheck()));//usleep(1000000);       
    }
    //decrease motor speed only once
    if(CountingStatus && CountTimer && !m_MotorStatus && (m_SeedCounter.GetCount() >= (m_Setpoint- GetReducedSetPoint())))
    {   
            m_MotorStatus = true;
            int speed;
            if(m_SetMotorSpeed >= 80) { speed = m_SetMotorSpeed - 10; }
            else if( m_SetMotorSpeed < 80 && m_SetMotorSpeed >= 75) { speed = m_SetMotorSpeed - 10; }
            else if( m_SetMotorSpeed < 75 && m_SetMotorSpeed >= 68) { speed = m_SetMotorSpeed - 10; }
            else if( m_SetMotorSpeed < 68 && m_SetMotorSpeed >= 62) { speed = m_SetMotorSpeed - 10; }
            else if( m_SetMotorSpeed < 62 && m_SetMotorSpeed >= 55) { speed = m_SetMotorSpeed - 10; }
            else { speed = m_SetMotorSpeed - 5; }
            m_Motor.SetSpeed(100-speed); //reduce motor speed  
    }
      // check the time lag in count change to trigger the Qtimer
    if(m_CheckSeeds && CountingStatus && (countchange != m_SeedCounter.GetCount()))
    { 
        countchange = m_SeedCounter.GetCount();
        widget.lblInfo->setText("");
        checkRefreshtimer->blockSignals(false);
        checkRefreshtimer->start(C_CHECK_TIMER_INTERVAL);
    }
}

void CountingScreen::CallBagCheck()
{
    IncPrintBagNo();
    SaveDataToTxtFile();
    if(m_SetMaxBagNumber > 1) CheckRotaryMotor();
    IncrementBagNumber();
    if(m_SetMaxBagNumber <= 8) { CheckBagNumber();  }  
    else { CheckForMoreBagNumber(); } 
    CountTimer=true;
    m_MotorStatus = false; 
}

int CountingScreen::GetReducedSetPoint()
{
    int sp;
    if( m_Setpoint < 100 && m_Setpoint >= 60) { sp = 7; }
    else if( m_Setpoint < 60 && m_Setpoint >= 30) { sp = 6; }
    else if( m_Setpoint < 30 && m_Setpoint >= 1) { sp = 4; }
    else { sp = 8; }
    return 8;
}
void CountingScreen::IncreaseMotorSpeed(){
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
void CountingScreen::DecreaseMotorSpeed(){
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

void CountingScreen::StopCounting(){
    checkRefreshtimer->blockSignals(true);
    CountingStatus = false;
    m_Motor.SetSpeed(0); 
    ZeroCount();
    PrintBagNumber=0;
    widget.lblDisplayBag->setText(QString::number(PrintBagNumber+1));
    ClearBagNumber();
    QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("Done!");	
    msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
    msg->setText("Carousel Stopped by user 901");	     
    msg->show();
    widget.lblInfo->setText("STOPPED");
    usleep(1500000);
	m_Motor.SetSpeed(0);
    m_Rotary.RotaryStop();   //reset rotary motor to home position
}

void CountingScreen::PauseContinue(){
    if (!PauseStatus && CountingStatus)
    {
        CountTimer=false;
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
        SensorStatus(); 
        CountingStatus = true;  
        CountTimer=true;
        checkRefreshtimer->blockSignals(false);
        checkRefreshtimer->start(C_CHECK_TIMER_INTERVAL);
        ChangeMotorSpeed(globalMotorSpeed); //ChangeMotorSpeed(m_SetMotorSpeed);
        PauseStatus=false;
        QPixmap pix5(":/images/continue_button.png");
        QIcon icon5(pix5);
        widget.btnContinue->setIcon(icon5);
        widget.btnContinue->setIconSize(widget.btnContinue->rect().size());
        widget.btnContinue->setFixedSize(widget.btnContinue->rect().size());
        widget.lblInfo->setText("Counting...");
    }
}

void CountingScreen::LoadUnload(){
    
    m_Motor.SetSpeed(0);    // Shut off the motor.
    LoadScreen *loadForm = new LoadScreen();
    loadForm->setWindowFlags(Qt::FramelessWindowHint);
    loadForm->setModal(true);
    loadForm->move(0,20);
    loadForm->exec(); 
    delete loadForm;
}

void CountingScreen::secsensor(){
    
    m_Motor.SetSpeed(0);    // Shut off the motor.
    SecScreen *loadForm = new SecScreen();
    loadForm->setWindowFlags(Qt::FramelessWindowHint);
    loadForm->setModal(true);
    loadForm->move(0,20);
    loadForm->exec(); 
    delete loadForm;
}


void CountingScreen::CallSetHomePosition(){
    
    SetHomePosition *positionForm = new SetHomePosition();
    positionForm->setWindowFlags(Qt::FramelessWindowHint);
    positionForm->setModal(true);
    positionForm->move(0,20);
    positionForm->exec(); 
    delete positionForm;
    m_Rotary.GetPositionFromFile();
}

void CountingScreen::CallCalibrate()
{
   m_SeedCounter.Calibrate();
   widget.lblInfo->setText("Change SET POINT Value");
}

void CountingScreen::SetPrintMode(bool index)
{
    PrintMode =index;
}

void CountingScreen::SetPrintFormat(bool index)
{
    PrintFormat =index;
}

void CountingScreen::SetLotCode(QString index){
    LotCode=index;
}
void CountingScreen::SetProductID(QString index){
    ProductID=index;
}

void CountingScreen::CallSetBagNumber(){
    
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

void CountingScreen::InitializeCVariables(int a,int b,int c, bool d, bool w) //bag #, sp, speed
{
    m_SetMaxBagNumber = a;
    widget.lblBagNo->setText(QString::number(m_SetMaxBagNumber));
    m_Setpoint = b;
    m_SetpointNumPad.SetSetpoint(m_Setpoint);
    QString temp;
    temp.setNum(m_Setpoint);
    temp = "SP = " + temp;
    widget.lblSetpoint->setText(temp);
   // ChangeMotorSpeed(0);
    m_SetMotorSpeed = c;
    widget.lblMotorSliderValue->setText(QString::number(m_SetMotorSpeed));
    m_CheckSeeds=d;
    if(m_CheckSeeds)
    {
        checkRefreshtimer->start(C_CHECK_TIMER_INTERVAL);
        checkRefreshtimer->blockSignals(true);
    }
    CallWaitOnOff(w); 
}
int * CountingScreen::GetCVariables()
{
    VarArray[0]= m_SetMaxBagNumber;
    VarArray[1]= m_Setpoint;
    VarArray[2]= m_SetMotorSpeed;
    return VarArray;
}

void CountingScreen::SetPrinterFD(int a){
    m_PrinterCommands.SetFD(a);
}

void CountingScreen::CheckForMoreBagNumber(){
    if((PrintBagNumber+1) > m_SetMaxBagNumber)
    {
        m_Motor.SetSpeed(0);
        ClearBagNumber();
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("Done !");	 
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Carousel Completed!");	     
        msg->show();
        widget.lblInfo->setText("Done!");
        usleep(1500000);
        m_Rotary.RotaryStop();   //reset rotary motor to home position
        ZeroCount();
        checkRefreshtimer->blockSignals(true);
        CountingStatus = false;
    }
    else if((PrintBagNumber) % 8 == 0)
    { 
        ClearBagNumber();
        usleep(1500000);
        m_Rotary.SetZeroPosition();
        if(WaitOnOff)
        {
            //pause till ok
            ZeroCount();
            widget.lblInfo->setText("Paused");
            CountingStatus = false;
            PauseStatus = true;
            CountTimer=false;
            checkRefreshtimer->blockSignals(true);
            QPixmap pix5(":/images/pause_button.png");
            QIcon icon5(pix5);
            widget.btnContinue->setIcon(icon5);
            widget.btnContinue->setIconSize(widget.btnContinue->rect().size());
            widget.btnContinue->setFixedSize(widget.btnContinue->rect().size());      
            QMessageBox msgBox;
            msgBox.setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
            msgBox.setText("Please Replace Bags\nPress PAUSE To Continue");
            msgBox.setStandardButtons(QMessageBox::Ok); 
            //connect( msgBox.button(QMessageBox::Ok), SIGNAL(clicked()) ,this, SLOT(PauseContinue()));
            msgBox.exec();
        }
        else {
            usleep(1000000);
            SensorStatus();
            CheckRotaryMotor();
            ZeroCount();
            if(CountingStatus) ChangeMotorSpeed(globalMotorSpeed); 
        }
    }
    else
    {
        usleep(500000);
        int ActualBag = GetBagNumber()+1;
        m_Rotary.RotateToNextChute(ActualBag);
        usleep(1500000);
        SensorStatus();
        ZeroCount();
        if(CountingStatus) ChangeMotorSpeed(globalMotorSpeed); 
    }
}

void CountingScreen::IncPrintBagNo(){
    PrintBagNumber++;
    if((PrintBagNumber+1) <= m_SetMaxBagNumber)
        widget.lblDisplayBag->setText(QString::number(PrintBagNumber+1));
}

void CountingScreen::PrintForCarousel()
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
        m_PrinterCommands.CarousalPrint();
    }
}

void CountingScreen::PrintFromFile()
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
        if(PrintFormat==false){ m_PrinterCommands.CSVPrint();}
        else{ m_PrinterCommands.FormatPrint();}
    }
}
void CountingScreen::SetBagMode(bool c)
{
    BagOnOff=c;
}
void CountingScreen::SensorStatus(){
    if(BagOnOff==true)
    {
        bool s=m_Sensor.TestLeftSensor();
         if (s==false)
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
}

void CountingScreen::CheckforSeeds(){
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
        //msgBox.setStandardButtons(QMessageBox::Ok);
        //connect( msgBox.button(QMessageBox::Ok), SIGNAL(clicked()) ,this, SLOT(PauseContinue()) );
        msgBox.exec();
    }
}

void CountingScreen::SetWaitOnOff()
{
    if(WaitOnOff){
        WaitOnOff=false;
        widget.btnWait->setStyleSheet("background-color:red;");
    }
    else
    {
        WaitOnOff=true;
        widget.btnWait->setStyleSheet("background-color:white;");
    }
}
void CountingScreen::CallWaitOnOff(bool s)
{
    WaitOnOff=s;
    if(WaitOnOff){
        widget.btnWait->setStyleSheet("background-color:white;");       
    }
    else
    {
        widget.btnWait->setStyleSheet("background-color:red;");
    }
    
}

bool CountingScreen::GetWaitOnOff()
{
    return WaitOnOff;
}

void CountingScreen::CheckRotaryMotor()
{
    if(!m_Rotary.CheckConn())
    {
        QMessageBox msgBox;
        msgBox.setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msgBox.setWindowTitle("Counting Error");
        msgBox.setText("Error! Check Carousel Motor Connection");
        msgBox.setStandardButtons(QMessageBox::Ok);  
        msgBox.addButton(QMessageBox::Cancel);
        connect( msgBox.button(QMessageBox::Ok), SIGNAL(clicked()) ,this, SLOT(CheckRotaryMotor()));
        connect( msgBox.button(QMessageBox::Cancel), SIGNAL(clicked()) ,this, SLOT(PauseContinue()));
        msgBox.exec();
    }
}