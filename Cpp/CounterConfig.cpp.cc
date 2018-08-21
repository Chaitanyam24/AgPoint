/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   CounterConfig.cpp
 * Author: Dan
 *
 * Created on March 14, 2017, 5:29 AM
 */

#include "CounterConfig.h"
#include "SeedDbInterface.h"
#include <QComboBox>
#include <QMessageBox>
#include <QTimer>

CounterConfig::CounterConfig() {
    widget.setupUi(this);
    setStyleSheet("background-color:black;");   // Sets the dialog's background color.
    
    // Button background colors
    widget.btnExit->setStyleSheet("background-color:white;");   // White button
    widget.btnProgram->setStyleSheet("background-color:white;");   // White button
    widget.btnDefault->setStyleSheet("background-color:white;");   // White button
    widget.btnCalibrate->setStyleSheet("background-color:white;");   // White button
    
    // Static controls
    widget.lblBasic->setStyleSheet("color:white;");   // White text
    widget.lblAdvanced->setStyleSheet("color:white;");   // White text
    widget.lblTeach->setStyleSheet("color:white;");   // White text 
    widget.lblResponseSpeed->setStyleSheet("color:white;");   // White text 
    widget.lblOffsetPercent->setStyleSheet("color:white;");   // White text 
    widget.lblButtonLock->setStyleSheet("color:white;");   // White text 
    widget.lblTotalCounts->setStyleSheet("color:white;");   // White text 
    widget.lblTotalOneShot->setStyleSheet("color:white;");   // White text 
    widget.lblDynamicEventStretch->setStyleSheet("color:white;");   // White text 
    widget.lblInfo->setStyleSheet("background-color:black; color:white;");
    widget.lblInfo->setText("");
    
    // Combobox colors
    widget.cmbTeach->setStyleSheet("background-color:white; color:black;");   // White button, black text
    widget.cmbResponseSpeed->setStyleSheet("background-color:white; color:black;");   // White button, black text
    widget.cmbOffset->setStyleSheet("background-color:white; color:black;");   // White button, black text
    widget.cmbButtonLock->setStyleSheet("background-color:white; color:black;");   // White button, black text
    widget.cmbTotalCounts->setStyleSheet("background-color:white; color:black;");   // White button, black text
    widget.cmbTotalOneShot->setStyleSheet("background-color:white; color:black;");   // White button, black text
    widget.cmbDynamicEventStretch->setStyleSheet("background-color:white; color:black;");   // White button, black text
    
    // Connect signals to slots
    connect(widget.btnExit, SIGNAL(pressed()), this, SLOT(ExitProgram()));
    connect(widget.btnProgram, SIGNAL(pressed()), this, SLOT(ProgramAllCounterSettings()));
    connect(widget.btnCalibrate, SIGNAL(pressed()), this, SLOT(CalibrateCounter()));
    connect(widget.btnDefault, SIGNAL(pressed()), this, SLOT(DefaultValues()));
    connect(widget.cmbTeach, SIGNAL(currentIndexChanged(int)), this, SLOT(TeachChanged(int)));
    connect(widget.cmbResponseSpeed, SIGNAL(currentIndexChanged(int)), this, SLOT(ResponseSpeedChanged(int)));
    connect(widget.cmbOffset, SIGNAL(currentIndexChanged(int)), this, SLOT(OffsetPercentChanged(int)));
    connect(widget.cmbButtonLock, SIGNAL(currentIndexChanged(int)), this, SLOT(ButtonLockChanged(int)));
    connect(widget.cmbTotalCounts, SIGNAL(currentIndexChanged(int)), this, SLOT(TotalCountsChanged(int)));
    connect(widget.cmbTotalOneShot, SIGNAL(currentIndexChanged(int)), this, SLOT(TotalOneShotChanged(int)));
    connect(widget.cmbDynamicEventStretch, SIGNAL(currentIndexChanged(int)), this, SLOT(DynamicEventStretchChanged(int)));
 //   connect(comboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),[=](int index){ /* ... */ });
   ProgramConfig=false;
    PopulateControls();
    // Load data from the database.
    SeedDbInterface db;
    QString result = db.LoadCounterConfig(m_Counter);

        // Debugging
    /*QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("DB save result");	    
    msg->setText(result);	     
    msg->show(); */
    SelectCurrentItemsInCombos();
}

CounterConfig::~CounterConfig() {
}

void CounterConfig::ExitProgram()
{
   SeedDbInterface db;
   QString result = db.SaveCounterConfig(m_Counter);
    
    // Debugging
    /*QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("DB save result");	    
    msg->setText(result);	     
    msg->show(); */  
    
    close();
}

void CounterConfig::ProgramAllCounterSettings()
{   
    widget.lblInfo->setText("Programming Counter...");
    QTimer::singleShot(100,this,SLOT(CallProgramAllCounterSettings()));
}
void CounterConfig::CallProgramAllCounterSettings()
{   
    ProgramConfig=true;
    SeedDbInterface db;  
    db.SaveCounterConfig(m_Counter);
    m_Counter.ProgramCounter();
    QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("Done !");
    msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
    msg->setText("Programming Complete");	     
    msg->show();
    widget.lblInfo->setText("Programmed Successfully!");
}

void CounterConfig::CalibrateCounter()
{
    m_Counter.Calibrate();
    widget.lblInfo->setText("To apply selected settings, press PROGRAM");
}

void CounterConfig::DefaultValues()
{
    m_Counter.DefaultValues();
    SelectCurrentItemsInCombos();
}

void CounterConfig::PopulateControls()
{
    // QT has a bug.  Must run program with a -nograb argument passed to it.
    // e.g.:  myprogram -nograb
    // If not done, clicking a combobox will lock-up the program.
    
    // Teach
//    QString data = m_Counter.TEACH_WINDOW.data();
    widget.cmbTeach->addItem(QString(m_Counter.TEACH_WINDOW.data()));
    widget.cmbTeach->addItem(QString(m_Counter.TEACH_LIGHT.data()));
    widget.cmbTeach->addItem(QString(m_Counter.TEACH_DYNAMIC.data()));
    
    // Response Speed
    widget.cmbResponseSpeed->addItem(QString(m_Counter.RESPONSE_SPEED_25.data()));
    widget.cmbResponseSpeed->addItem(QString(m_Counter.RESPONSE_SPEED_50.data()));
    widget.cmbResponseSpeed->addItem(QString(m_Counter.RESPONSE_SPEED_150.data()));
    widget.cmbResponseSpeed->addItem(QString(m_Counter.RESPONSE_SPEED_250.data()));
    widget.cmbResponseSpeed->addItem(QString(m_Counter.RESPONSE_SPEED_500.data()));
    
    // Offset %
    widget.cmbOffset->addItem(QString(m_Counter.OFFSET_PERCENT_MIN.data()));
    widget.cmbOffset->addItem(QString(m_Counter.OFFSET_PERCENT_2.data()));
    widget.cmbOffset->addItem(QString(m_Counter.OFFSET_PERCENT_5.data()));
    widget.cmbOffset->addItem(QString(m_Counter.OFFSET_PERCENT_10.data()));
    widget.cmbOffset->addItem(QString(m_Counter.OFFSET_PERCENT_20.data()));
    widget.cmbOffset->addItem(QString(m_Counter.OFFSET_PERCENT_50.data()));
    
    // Button Lock
    widget.cmbButtonLock->addItem(QString(m_Counter.BUTTON_LOCK_UNLOCK.data()));
    widget.cmbButtonLock->addItem(QString(m_Counter.BUTTON_LOCK_LOCK.data()));

    // Total Counts
    widget.cmbTotalCounts->addItem(QString(m_Counter.TOTAL_COUNTS_OFF.data()));
    widget.cmbTotalCounts->addItem(QString(m_Counter.TOTAL_COUNTS_1.data()));
    widget.cmbTotalCounts->addItem(QString(m_Counter.TOTAL_COUNTS_5.data()));
    widget.cmbTotalCounts->addItem(QString(m_Counter.TOTAL_COUNTS_10.data()));
    widget.cmbTotalCounts->addItem(QString(m_Counter.TOTAL_COUNTS_25.data()));
    widget.cmbTotalCounts->addItem(QString(m_Counter.TOTAL_COUNTS_100.data()));
    
    // Total One-Shot
    widget.cmbTotalOneShot->addItem(QString(m_Counter.TOTAL_ONE_SHOT_0.data()));
    widget.cmbTotalOneShot->addItem(QString(m_Counter.TOTAL_ONE_SHOT_2.data()));
    widget.cmbTotalOneShot->addItem(QString(m_Counter.TOTAL_ONE_SHOT_5.data()));
    widget.cmbTotalOneShot->addItem(QString(m_Counter.TOTAL_ONE_SHOT_10.data()));
    widget.cmbTotalOneShot->addItem(QString(m_Counter.TOTAL_ONE_SHOT_20.data()));
    widget.cmbTotalOneShot->addItem(QString(m_Counter.TOTAL_ONE_SHOT_50.data()));

    // Dynamic Event Stretch
    widget.cmbDynamicEventStretch->addItem(QString(m_Counter.DYNAMIC_EVENT_STRETCH_OFF.data()));
    widget.cmbDynamicEventStretch->addItem(QString(m_Counter.DYNAMIC_EVENT_STRETCH_25.data()));
    widget.cmbDynamicEventStretch->addItem(QString(m_Counter.DYNAMIC_EVENT_STRETCH_33.data()));
    widget.cmbDynamicEventStretch->addItem(QString(m_Counter.DYNAMIC_EVENT_STRETCH_50.data()));
    widget.cmbDynamicEventStretch->addItem(QString(m_Counter.DYNAMIC_EVENT_STRETCH_100.data()));
}

void CounterConfig::SelectCurrentItemsInCombos()
{
    widget.cmbTeach->setCurrentIndex(m_Counter.Teach()-1);
    widget.cmbResponseSpeed->setCurrentIndex(m_Counter.ResponseSpeed()-1);  
    widget.cmbOffset->setCurrentIndex(m_Counter.OffsetPercent()-1);
    widget.cmbButtonLock->setCurrentIndex(m_Counter.ButtonLock()-1);
    widget.cmbTotalCounts->setCurrentIndex(m_Counter.TotalCounts()-1);
    widget.cmbTotalOneShot->setCurrentIndex(m_Counter.TotalOneShot()-1);
    widget.cmbDynamicEventStretch->setCurrentIndex(m_Counter.DynamicEventStretch()-1);
}

void CounterConfig::TeachChanged(int index)
{
    m_Counter.Teach(index+1);
}

void CounterConfig::ResponseSpeedChanged(int index)
{
    m_Counter.ResponseSpeed(index+1);
}

void CounterConfig::OffsetPercentChanged(int index)
{
    m_Counter.OffsetPercent(index+1);
}

void CounterConfig::ButtonLockChanged(int index)
{
    m_Counter.ButtonLock(index+1);
}

void CounterConfig::TotalCountsChanged(int index)
{
    m_Counter.TotalCounts(index+1);
}

void CounterConfig::TotalOneShotChanged(int index)
{
    m_Counter.TotalOneShot(index+1);
}

void CounterConfig::DynamicEventStretchChanged(int index)
{
    m_Counter.DynamicEventStretch(index+1);
}

bool CounterConfig::GetSeedProgramStatus(){
    return ProgramConfig;
}
