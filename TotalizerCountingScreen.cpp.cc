/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TotalizerCountingScreen.cpp
 * Author: SHALAKHA
 *
 * Created on October 30, 2017, 11:35 AM
 */

#include "TotalizerCountingScreen.h"
#include "PrinterCommands/PrinterCommands.h"

#include <QTimer>
#include <QMessageBox>
#include <QPixmap>
#include <QComboBox>
#include <unistd.h>
#include <QString>

static volatile int globalMotorSpeed; 

TotalizerCountingScreen::TotalizerCountingScreen() {
    widget.setupUi(this);
    
    // Sets the dialog's background color.
    setStyleSheet("background-color:black;");
    
    // Change the background color of the buttons and labels
    widget.btnSetpointOnOff->setStyleSheet("background-color:white;");
    widget.btnSetPointValue->setStyleSheet("background-color:white;");
    widget.btnCalibrate->setStyleSheet("background-color:white;");
    widget.btnHome->setStyleSheet("background-color:black;");
    widget.btnReset->setStyleSheet("background-color:black;");
    widget.btnMotorSpeed->setStyleSheet("background-color:white;");
    widget.lblCount->setStyleSheet("background-color:black; color:white");
    widget.lblSetpoint->setStyleSheet("background-color:black; color:white;");
    widget.lblMode->setStyleSheet("background-color:black; color:white;");
    widget.lblMode->setText("901T Seed Totalizer");
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
    widget.btnPrint->setStyleSheet("background-color:white;");

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
    connect(widget.btnSetpointOnOff, SIGNAL(pressed()), this, SLOT(EnableDisableSetpoint()));
    connect(widget.btnCalibrate, SIGNAL(pressed()), this, SLOT(CallCalibrate()));
    connect(widget.btnSetPointValue, SIGNAL(pressed()), this, SLOT(DisplayNumPad()));
    connect(widget.btnMotorSpeed, SIGNAL(pressed()), this, SLOT(DisplayMotorNumPad()));
    connect(widget.btnStop, SIGNAL(pressed()), this, SLOT(StopCounting()));
    connect(widget.btnStart, SIGNAL(pressed()), this, SLOT(StartMotor()));
    connect(widget.btnMotorInc, SIGNAL(pressed()), this, SLOT(IncreaseMotorSpeed()));
    connect(widget.btnMotorDec, SIGNAL(pressed()), this, SLOT(DecreaseMotorSpeed()));
    connect(widget.btnContinue, SIGNAL(pressed()), this, SLOT(PauseContinue()));
    connect(widget.btnPrint, SIGNAL(pressed()), this, SLOT(CallPrint()));
    
    // Read the counter's settings from the database.
    QString result= m_DbTest.LoadCounterConfig(m_SeedCounter);

    // Variable initialization
    countchange=0;
    ZeroCount();
   // m_SetpointEnabled = true;
    //m_Setpoint = 100;
    globalMotorSpeed=0;
    //m_SetpointNumPad.SetSetpoint(m_Setpoint);
    totalSeedCount=0;
    m_MotorStatus = false;
    CountingStatus = false;
    //m_SetMotorSpeed=0;
    PauseStatus=false;
    m_SeedCounter.Calibrate();
    CountTimer=true;
    m_CheckSeeds=false;
    // Create a timer to refresh the count.
    QTimer *countRefreshtimer = new QTimer(this);
    connect(countRefreshtimer, SIGNAL(timeout()), this, SLOT(UpdateCount()));
    countRefreshtimer->start(T_COUNT_REFRESH_TIMER_INTERVAL);
    
    //timer to check seed status.

    connect(checkRefreshtimer, SIGNAL(timeout()), this, SLOT(CheckforSeeds()));
    checkRefreshtimer->blockSignals(true);
}

TotalizerCountingScreen::~TotalizerCountingScreen() {
}


void TotalizerCountingScreen::ExitToHomeWindow()
{   
    checkRefreshtimer->blockSignals(true);
    globalMotorSpeed=0;
    CountingStatus = false;
    ZeroCount();
    m_Motor.SetSpeed(0);    // Shut off the motor.    close();
    close();
}


void TotalizerCountingScreen::ZeroCount()
{
    m_SeedCounter.ClearCount(); 
 }

void TotalizerCountingScreen::MotorTest()
{
    m_Motor.TestPwm();
}

void TotalizerCountingScreen::ChangeMotorSpeed(int speed)
{   
    widget.lblMotorSliderValue->setText(QString::number(speed));
    globalMotorSpeed = speed;
    m_Motor.SetSpeed(100-speed);
    widget.lblInfo->setText("");  
}


void TotalizerCountingScreen::DisplayCounterSetupWindow()
{   
    CounterConfig *configForm = new CounterConfig();
    configForm->setWindowFlags(Qt::FramelessWindowHint);
    configForm->setModal(true);
    configForm->move(0,20);
    configForm->exec(); 
    if (configForm->GetSeedProgramStatus() == true) seedname="";
    delete configForm;
    widget.lblInfo->setText("Select SET POINT ON/OFF, by default ON");
}

void TotalizerCountingScreen::DisplayNumPad()
{   
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

void TotalizerCountingScreen::DisplayMotorNumPad(){
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

void TotalizerCountingScreen::StartMotor(){
    if(m_SetMotorSpeed == 0)
    {
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("ERROR");    
        msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msg->setText("Set Motor Speed");	     
        msg->show();
    }
    else {
    checkRefreshtimer->blockSignals(false);
    ZeroCount();
    CountingStatus = true;
    PauseStatus=false;
    QPixmap pix5(":/images/continue_button.png");
    QIcon icon5(pix5);
    widget.btnContinue->setIcon(icon5);
    widget.btnContinue->setIconSize(widget.btnContinue->rect().size());
    widget.btnContinue->setFixedSize(widget.btnContinue->rect().size());
    ChangeMotorSpeed(m_SetMotorSpeed);
    widget.lblInfo->setText("Counting...");
    }
} 


void TotalizerCountingScreen::CheckforSeeds(){
    checkRefreshtimer->blockSignals(true);
    if(CountingStatus && m_CheckSeeds)
    {  
        if (m_SetpointEnabled == false)
        {
            StopCounting();   

        }
        else {
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
}

int TotalizerCountingScreen::GetTotalCount(){
    totalSeedCount = m_SeedCounter.GetTotalCount();
    return totalSeedCount;
}

void TotalizerCountingScreen::SetSeedIndex(int index){
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

void TotalizerCountingScreen::SaveDataToTxtFile(){
    
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
    WebFile << LotCode.toStdString() + ","+ ProductID.toStdString()+","+date + "," + time + "," +std::to_string(m_SeedCounter.GetCount())+","+" ";
    WebFile << "\n";
    PrintFile << LotCode.toStdString() + ","+ ProductID.toStdString()+","+ date + "," + time + "," +std::to_string(m_SeedCounter.GetCount())+","+" ";
    PrintFile << "\n";
    SinglePrintFile << LotCode.toStdString() + ","+ ProductID.toStdString()+ ","+date + "," + time +  "," +std::to_string(m_SeedCounter.GetCount())+","+" ";
    SinglePrintFile << "\n";
    WebFile.close();
    PrintFile.close();
    SinglePrintFile.close();
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

void TotalizerCountingScreen::UpdateCount()
{       
    char count[10]; 
    bool bHealthGood = m_SeedCounter.ReadHealth(); // Get the health status of the counter.
    sprintf(count, "%d", m_SeedCounter.GetCount());
    if(bHealthGood) m_CountLblText = "<font color='white'>";
    else  {
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
    
    // Get count from counter and update displayed count.
    if(CountingStatus && CountTimer && m_SetpointEnabled && (m_SeedCounter.GetCount() >= m_Setpoint))
    {       
        CountTimer=false;
        m_Motor.SetSpeed(0);    // Shut off the motor. 
        m_MotorStatus = false;
        QTimer::singleShot(2000,this,SLOT(CallEndCount()));//usleep(1000000); 
     
    }
    //decrease motor speed only once
    if(CountingStatus && CountTimer && m_SetpointEnabled && (m_MotorStatus == false) && (m_SeedCounter.GetCount() >= (m_Setpoint-GetReducedSetPoint())))
    {   
      /* m_MotorStatus = true;
        int speed = (m_SetMotorSpeed - 3); //(( 2* m_SetMotorSpeed)/10)
        m_Motor.SetSpeed(100-speed); //reduce motor speed   */
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
        checkRefreshtimer->start(T_CHECK_TIMER_INTERVAL);
    }
}

void TotalizerCountingScreen::CallEndCount()
{
    CountingStatus = false;
    checkRefreshtimer->blockSignals(true);
    QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("Done!");    
    msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
    std::string s = "Total Number of Seeds = "+ std::to_string(m_SeedCounter.GetCount());
    char const *pchar = s.c_str();
    msg->setText(pchar);	     
    msg->show();  
    SaveDataToTxtFile();
    ZeroCount();
    CountTimer=true;
}

int TotalizerCountingScreen::GetReducedSetPoint()
{
    int sp;
    if( m_Setpoint < 100 && m_Setpoint >= 60) { sp = 7; }
    else if( m_Setpoint < 60 && m_Setpoint >= 30) { sp = 6; }
    else if( m_Setpoint < 30 && m_Setpoint >= 1) { sp = 4; }
    else { sp = 8; }
    return 8;
}

void TotalizerCountingScreen::IncreaseMotorSpeed(){
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
void TotalizerCountingScreen::DecreaseMotorSpeed(){
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

void TotalizerCountingScreen::EnableDisableSetpoint()
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

void TotalizerCountingScreen::StopCounting(){
    widget.lblInfo->setText("STOPPED");
    checkRefreshtimer->blockSignals(true);
    if(m_SetpointEnabled == false)
    {
        SaveDataToTxtFile();
        std::string s = "Total Seed Count: "+ std::to_string(m_SeedCounter.GetCount());
        char const *pchar = s.c_str();
        QMessageBox* msgNo = new QMessageBox();
        msgNo->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
        msgNo->setWindowTitle("Count Complete");  
        msgNo->setText(pchar);
        msgNo->show(); 
    }
    CountingStatus = false;
    m_Motor.SetSpeed(0); 
    ZeroCount();
    
}

void TotalizerCountingScreen::PauseContinue(){
   if (!PauseStatus && CountingStatus)
    {
       if(m_SetpointEnabled && (m_SeedCounter.GetCount() >= m_Setpoint) ) { ZeroCount(); }
        CountingStatus = false;
        m_Motor.SetSpeed(0); 
        PauseStatus = true;
        checkRefreshtimer->blockSignals(true);
        checkRefreshtimer->start(T_CHECK_TIMER_INTERVAL);
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
       checkRefreshtimer->blockSignals(false);
        CountingStatus = true;
        ChangeMotorSpeed(m_SetMotorSpeed);
        PauseStatus=false;
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


void TotalizerCountingScreen::CallCalibrate()
{
   m_SeedCounter.Calibrate();
   widget.lblInfo->setText("Select SET POINT ON/OFF, by default ON");
}

void TotalizerCountingScreen::SetPrintMode(bool index)
{
    PrintMode =index; 
}

void TotalizerCountingScreen::SetPrintFormat(bool index)
{
    PrintFormat =index;
}

void TotalizerCountingScreen::SetLotCode(QString index){
    LotCode=index;
}
void TotalizerCountingScreen::SetProductID(QString index){
    ProductID=index;
}

void TotalizerCountingScreen::InitializeTVariables(bool a,int b,int c,bool d){
    m_SetpointEnabled=a;
     if(m_SetpointEnabled == true) {
        widget.lblSetpoint->setStyleSheet("background-color:black; color:white; text-decoration: none;");
    }
    else{
        widget.lblSetpoint->setStyleSheet("background-color:black; color:red; text-decoration: line-through;");   
    }
    m_SetMotorSpeed =b;
    widget.lblMotorSliderValue->setText(QString::number(m_SetMotorSpeed));
    m_Setpoint=c;
    m_SetpointNumPad.SetSetpoint(m_Setpoint);
    QString temp;
    temp.setNum(m_Setpoint);
    temp = "SP = " + temp;
    widget.lblSetpoint->setText(temp);
    /*if(PrintMode==true){
        int PrinterFD = m_PrinterCommands.GetFD();
        if (PrinterFD <=0){
            QMessageBox* msg = new QMessageBox();
            msg->setWindowTitle("ERROR");    
            msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
            msg->setText("Printer Not Connected");	     
            msg->show();
        }
    }*/
    m_CheckSeeds=d;
    if(m_CheckSeeds)
    {
        checkRefreshtimer->start(T_CHECK_TIMER_INTERVAL);
        checkRefreshtimer->blockSignals(true);
    }
}

int * TotalizerCountingScreen::GetTVariables(){
    
    VarArray[0]=m_SetMotorSpeed;
    VarArray[1]=m_Setpoint;
    return VarArray;
}
bool TotalizerCountingScreen::GetSPStatus(){
    return m_SetpointEnabled;
}

void TotalizerCountingScreen::SetPrinterFD(int a){
    m_PrinterCommands.SetFD(a);
    /*QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("STATUS");
    msg->setText(QString::number(a));	     
    msg->show();*/
}

void TotalizerCountingScreen::CallPrint()
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

