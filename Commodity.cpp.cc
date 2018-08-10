/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Commodity.cpp
 * Author: SHALAKHA
 *
 * Created on Aug 23, 2017, 5:39 PM
 */

#include <QTimer>
#include <QMessageBox>
#include <QPixmap>
#include <QComboBox>
#include <unistd.h>
#include <string>
#include <stdlib.h>

#include "Commodity.h"
#include "ListDB.h"
#include "CounterConfig.h"
#include "Keypad.h"

enum e_Seed{ mm1=1, mm2, mm3, mm4, mm5, mm6};

Commodity::Commodity() {
    widget.setupUi(this);
    
    //string for type of seeds
    SEED_1 = "1";
    SEED_2 = "2";
    SEED_3= "3";
    SEED_4 = "4";
    SEED_5 = "5";
    SEED_6 = "6";
    m_KeypadValue="";
    LotCode="";
    ProductID="";
    ProgramStatus = false;
    // Sets the dialog's background color.
    setStyleSheet("background-color:black;");
    
    // Change the background color of the buttons and labels
    widget.boxSeedType->setStyleSheet("background-color:white; color:black;");
    widget.cbLotCode->setStyleSheet("background-color:white; color:black;");
    widget.cbLotCode->setMaxCount(20);
    widget.cbProductID->setStyleSheet("background-color:white; color:black;");
    widget.cbProductID->setMaxCount(20);
    widget.btnPrg->setStyleSheet("background-color:white; color:black;");   // White button
    widget.btnLotAdd->setStyleSheet("background-color:white; color:black;"); 
    widget.btnLotRemove->setStyleSheet("background-color:white; color:black;"); 
    widget.btnIDAdd->setStyleSheet("background-color:white; color:black;"); 
    widget.btnIDRemove->setStyleSheet("background-color:white; color:black;"); 
    widget.lblInfo->setStyleSheet("background-color:black; color:white;");
    widget.btnHome->setStyleSheet("background-color:black;");
    //Unchanged Labels
    widget.label->setStyleSheet("background-color:black; color:white");
    widget.label->setText("Set Sensitivity");
    widget.label_2->setStyleSheet("background-color:black; color:white");
    widget.label_2->setText("Teach");
    widget.label_3->setStyleSheet("background-color:black; color:white");
    widget.label_3->setText("Response Speed");
    widget.label_4->setStyleSheet("background-color:black; color:white");
    widget.label_4->setText("Offset %");
    widget.label_5->setStyleSheet("background-color:black; color:white");
    widget.label_5->setText("Button Lock");
    widget.label_6->setStyleSheet("background-color:black; color:white");
    widget.label_6->setText("Total Counts");
    widget.label_7->setStyleSheet("background-color:black; color:white");
    widget.label_7->setText("Total One Shot");
    widget.label_8->setStyleSheet("background-color:black; color:white");
    widget.label_8->setText("Dynamic Event Stretch");
    widget.lblSteps->setStyleSheet("background-color:black; color:white;");
    widget.lblSteps->setText("Step 1: Set Sensitivity\nStep 2: Press PROGRAM\nStep 3: Press OK and HOME");
    widget.lblSensitivity->setStyleSheet("background-color:black; color:white;");
    widget.lblSensitivity->setText("");
    widget.lblLotCode->setStyleSheet("background-color:black; color:white;");
    widget.lblLotCode->setText("Lot Code:");
    widget.lblProductID->setStyleSheet("background-color:black; color:white;");
    widget.lblProductID->setText("Product ID:");
    widget.lblDateTime->setStyleSheet("background-color:black; color:white;");
    
     //labels
    widget.lblTeach->setStyleSheet("background-color:black; color:white");
    widget.lblResponsespeed->setStyleSheet("background-color:black; color:white");
    widget.lblOffsetpercent->setStyleSheet("background-color:black; color:white");
    widget.lblButtonlock->setStyleSheet("background-color:black; color:white");
    widget.lblTotalcounts->setStyleSheet("background-color:black; color:white");
    widget.lblTotaloneshot->setStyleSheet("background-color:black; color:white");
    widget.lblDynamiceventstretch->setStyleSheet("background-color:black; color:white");
    
    widget.btnHome->setText("");    // Remove the text so the bitmap fits the button.
    QPixmap pix(":/images/home_button.png");
    QIcon icon(pix);
    widget.btnHome->setIcon(icon);
    widget.btnHome->setIconSize(widget.btnHome->rect().size());
    widget.btnHome->setFixedSize(widget.btnHome->rect().size());
   
    // Connect signals and slots
    connect(widget.boxSeedType, SIGNAL(currentIndexChanged(int)), this, SLOT(ItemChanged(int)));
    connect(widget.cbLotCode, SIGNAL(currentIndexChanged(int)), this, SLOT(LotItemChanged(int)));
    connect(widget.cbProductID, SIGNAL(currentIndexChanged(int)), this, SLOT(IDItemChanged(int)));
    connect(widget.btnPrg, SIGNAL(pressed()), this, SLOT(ProgramCommodity()));
    connect(widget.btnHome, SIGNAL(pressed()), this, SLOT(DisplayHomeWindow()));
    connect(widget.btnLotAdd, SIGNAL(pressed()), this, SLOT(AddLot()));
    connect(widget.btnLotRemove, SIGNAL(pressed()), this, SLOT(RemoveLot()));
    connect(widget.btnIDAdd, SIGNAL(pressed()), this, SLOT(AddID()));
    connect(widget.btnIDRemove, SIGNAL(pressed()), this, SLOT(RemoveID()));
    
     UpdateDateTime();
    //Timer for date and time
    QTimer *DateTimeRefreshtimer = new QTimer(this);
    connect(DateTimeRefreshtimer, SIGNAL(timeout()), this, SLOT(UpdateDateTime()));
    DateTimeRefreshtimer->start(COMMODITY_DATE_TIME_REFRESH_TIMER);
    
    //m_Seed=0;
    PopulateItems();
    GetLotCodeFromFile();
    GetProductIdFromFile();
}

void Commodity::DisplayHomeWindow()
{   
    SaveLotCodeToFile();
    SaveProductIdToFile();
    close();
}

Commodity::~Commodity() {
}

void Commodity::PopulateItems(){
    widget.boxSeedType->addItem(QString(""));
    widget.boxSeedType->addItem(QString(SEED_1.data()));
    widget.boxSeedType->addItem(QString(SEED_2.data()));
    widget.boxSeedType->addItem(QString(SEED_3.data()));
    widget.boxSeedType->addItem(QString(SEED_4.data()));
    widget.boxSeedType->addItem(QString(SEED_5.data()));
    widget.boxSeedType->addItem(QString(SEED_6.data()));
}

void Commodity::ItemChanged(int index){
    if (index == 0){
        m_Seed=0;
        widget.lblTeach->setText("");
        widget.lblResponsespeed->setText("");
        widget.lblOffsetpercent->setText("");
        widget.lblButtonlock->setText("");
        widget.lblTotalcounts->setText("");
        widget.lblTotaloneshot->setText("");
        widget.lblDynamiceventstretch->setText("");
        widget.lblSensitivity->setText("");
        //PopulateSeedConfig();
    }
    else if(index >= mm1 && index <= mm6)
    {
        m_Seed = index;
         switch (m_Seed){ 
            case 1:
                widget.lblSensitivity->setText("Seed Size\n1mm to 3mm\n(Small Vegetable Seeds)");
                break;
            case 2 :
                widget.lblSensitivity->setText("Seed Size\n3.1mm to 4.9 mm\n(Medium Vegetable,\nWheat)");
                break;
            case 3 :
                widget.lblSensitivity->setText("Seed Size\n5mm to 7.9mm\n(Popcorn, Soybeans)");
                break;
            case 4 :
                widget.lblSensitivity->setText("Seed Size\n8 to 12mm\n(Corn, Beans)");
                break;
            case 5 :
                widget.lblSensitivity->setText("Seed Size\n12.1mm to 15mm\n(Sunflower)");
                break;
            case 6:    
                widget.lblSensitivity->setText("Seed Size\n15.1mm to 19mm");
                break;
            }
        ListDB cdb;
        cdb.DeleteCounterConfig();
        QString result = cdb.LoadSelectedSeed(m_Seed);
        PopulateSeedConfig();
        
        
    // Debugging
    /*std::string s = std::to_string(populatelist.GetTeach());
    char const *pchar = s.c_str();
    QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("Loading from DB");	    
    msg->setText(pchar);	     
    msg->show();*/
    }
}

void Commodity::ProgramCommodity(){
    widget.lblInfo->setText("Programming Counter... Please Wait");
    QTimer::singleShot(100,this,SLOT(CallProgramCommodity()));
}

void Commodity::CallProgramCommodity(){
    ProgramStatus = true;
    m_ProgramSeed = m_Seed;
    m_Counter.ProgramCounter();
    QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("Done !");	
    msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
    msg->setText("Programming Complete");	     
    msg->show();
    widget.lblInfo->setText("Programmed Successfully!");
}
void Commodity::PopulateSeedConfig(){
    populatelistDB.PopulateDbVariables();
    
    switch (populatelistDB.GetTeach()){
            
            case 1:
                widget.lblTeach->setText("Window");
                break;
            case 2 :
                widget.lblTeach->setText("Light");
                break;
            case 3:    
                widget.lblTeach->setText("Dynamic");
            }
    switch(populatelistDB.GetResponseSpeed()){
        case 1:
                widget.lblResponsespeed->setText("25 us");
                break;
        case 2 :
                widget.lblResponsespeed->setText("50 us");
                break;
        case 3:    
                widget.lblResponsespeed->setText("150 us");
                break;
        case 4 :
                widget.lblResponsespeed->setText("250 us");
                break;
         case 5 :
                widget.lblResponsespeed->setText("500 us");        
    }
    //e_OffsetPercent{ pMin=1, p2, p5, p10, p20, p50};
    switch(populatelistDB.GetOffsetPercent()){
        case 1:
                widget.lblOffsetpercent->setText("Min");
                break;
        case 2 :
                widget.lblOffsetpercent->setText("2%");
                break;
        case 3:    
                widget.lblOffsetpercent->setText("5%");
                break;
        case 4 :
                widget.lblOffsetpercent->setText("10%");
                break;
        case 5 :
                widget.lblOffsetpercent->setText("20%"); 
                break;
        case 6 :
                widget.lblOffsetpercent->setText("50%");
    }
     //ButtonLock{ Unlocked=1, Locked}
     switch(populatelistDB.GetButtonLock()){
        case 1:
                widget.lblButtonlock->setText("Unlocked");
                break;
        case 2 :
                widget.lblButtonlock->setText("Locked");
                             
    }
    
//enum e_TotalCounts {cOff=1, c1, c5, c10, c25, c100};
      switch(populatelistDB.GetTotalCounts()){
        case 1:
                widget.lblTotalcounts->setText("Off");
                break;
        case 2 :
                widget.lblTotalcounts->setText("1 Counts");
                break;
        case 3:    
                widget.lblTotalcounts->setText("5 Counts");
                break;
        case 4 :
                widget.lblTotalcounts->setText("10 Counts");
                break;
         case 5 :
                widget.lblTotalcounts->setText("25 Counts");   
                break;
        case 6 :
                widget.lblTotalcounts->setText("100 Counts"); 
    }
//enum e_TotalOneShot{ ts0=1, ts2, ts5, ts10, ts20, ts50};
      switch(populatelistDB.GetTotalOneShot()){
        case 1:
                widget.lblTotaloneshot->setText("0 ms");
                break;
        case 2 :
                widget.lblTotaloneshot->setText("2 ms");
                break;
        case 3:    
                widget.lblTotaloneshot->setText("5 ms");
                break;
        case 4 :
                widget.lblTotaloneshot->setText("10 ms");
                break;
         case 5 :
                widget.lblTotaloneshot->setText("20 ms");   
                break;
        case 6 :
                widget.lblTotaloneshot->setText("50 ms"); 
    }
//enum e_DynamicEventStretch{ dsOff=1, ds25, ds33, ds50, ds100};
     
    switch(populatelistDB.GetDynamicEventStretch()){
        case 1:
                widget.lblDynamiceventstretch->setText("Off");
                break;
        case 2 :
                widget.lblDynamiceventstretch->setText("25%");
                break;
        case 3:    
                widget.lblDynamiceventstretch->setText("33%");
                break;
        case 4 :
                widget.lblDynamiceventstretch->setText("50%");
                break;
         case 5 :
                widget.lblDynamiceventstretch->setText("100%");   
        
    }
}

int Commodity::GetSelectedSeed(){
    return m_ProgramSeed;
}

void Commodity::UpdateDateTime(){
    timeval curTime;
    tm *my_date_time;
    gettimeofday(&curTime, NULL);
    my_date_time = localtime(&curTime.tv_sec);
    std::string date= std::to_string(my_date_time->tm_hour) +":"+ std::to_string(my_date_time->tm_min)+":"+ std::to_string(my_date_time->tm_sec)+"\n" +std::to_string(my_date_time->tm_mon + 1) +"/"+ std::to_string(my_date_time->tm_mday) +"/20"+std::to_string(my_date_time->tm_year - 100);
    char const *tchar = date.c_str();
    widget.lblDateTime->setText(tchar);
}

void Commodity::LotItemChanged(int index){
    LotIndex=index;
    LotCode= widget.cbLotCode->currentText();
    //widget.lblInfo->setText(LotCode);
}
void Commodity::IDItemChanged(int index){
    IDIndex=index;
    ProductID= widget.cbProductID->currentText();
    //widget.lblInfo->setText(ProductID);
}
void Commodity::DisplayKeypad(){
    Keypad *keypadForm = new Keypad();
    keypadForm->setWindowFlags(Qt::FramelessWindowHint);
    keypadForm->setModal(true);
    //keypadForm->move(5,0);  // Move window up a bit to cover main window.
    keypadForm->exec();
    m_KeypadValue = keypadForm->GetInputValue();
    delete keypadForm;
}
void Commodity::AddLot(){
    if((widget.cbLotCode->count()) == 20){
    QMessageBox* msg = new QMessageBox();
     msg->setWindowTitle("OverFlow");    
     msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
     msg->setText("Clear some items to add new");	     
     msg->show(); 
    }
    else {
        DisplayKeypad();
        if(m_KeypadValue != ""){ widget.cbLotCode->addItem(m_KeypadValue);}
    }
    m_KeypadValue="";
}
void Commodity::AddID(){
    if((widget.cbProductID->count()) == 20){
     QMessageBox* msg = new QMessageBox();
     msg->setWindowTitle("OverFlow");    
     msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
     msg->setText("Clear some items to add new");	     
     msg->show(); 
    }
    else {
        DisplayKeypad();
        if(m_KeypadValue != "") widget.cbProductID->addItem(m_KeypadValue);
    }
    m_KeypadValue="";
}
void Commodity::RemoveLot(){
    LotIndex=widget.cbLotCode->currentIndex();
    widget.cbLotCode->removeItem(LotIndex);
}
void Commodity::RemoveID(){
    IDIndex=widget.cbProductID->currentIndex();
    widget.cbProductID->removeItem(IDIndex);
}
QString Commodity::GetLotCode(){
    LotCode=widget.cbLotCode->currentText();
    return LotCode;
}
QString Commodity::GetProductID(){
    ProductID=widget.cbProductID->currentText();
    return ProductID;
}

void Commodity::GetLotCodeFromFile()
{
    std::string code;
    std::ifstream CodeFile;
    CodeFile.open("/home/pi/LotCode.txt",std::ios_base::in);
    if (CodeFile.is_open())
    {
        while(CodeFile >> code)
        {
            char const *pchar = code.c_str();
            widget.cbLotCode->addItem(pchar);
        }
        CodeFile.close();
    }    
}

void Commodity::GetProductIdFromFile()
{
    std::string Id;
    std::ifstream IdFile;
    IdFile.open("/home/pi/ProductID.txt",std::ios_base::in);
    if (IdFile.is_open())
    {
        while(IdFile >> Id)
        {
            char const *pchar = Id.c_str();
            widget.cbProductID->addItem(pchar);
        }
        IdFile.close();
    }  
}

void Commodity::SaveLotCodeToFile()
{
    std::fstream CodeClearFile;
    CodeClearFile.open("/home/pi/LotCode.txt",std::fstream::out | std::fstream::trunc);
    CodeClearFile.close();
    
    std::ofstream CodeFile;
    CodeFile.open("/home/pi/LotCode.txt");
    int i= widget.cbLotCode->count();
    for(int index=0; index<=i; index++)
    {
        CodeFile << (widget.cbLotCode->itemText(index)).toStdString();
        CodeFile << "\n";
    }
    CodeFile.close();  
}

void Commodity::SaveProductIdToFile()
{
    //clear previous data
    std::fstream IDClearFile;
    IDClearFile.open("/home/pi/ProductID.txt",std::fstream::out | std::fstream::trunc);
    IDClearFile.close();
    std::ofstream IDFile;
    //save new data
    IDFile.open("/home/pi/ProductID.txt");
    int i= widget.cbProductID->count();
    for(int index=0; index<=i; index++)
    {
        IDFile << (widget.cbProductID->itemText(index)).toStdString();
        IDFile << "\n";
    }
    IDFile.close();
}

int * Commodity::GetVariables(){
    VarArray[0]= LotIndex;
    VarArray[1]=IDIndex;
    return VarArray;
}

void Commodity::InitializeVariables(int a, int b, int c){
    m_Seed=a;
    widget.boxSeedType->setCurrentIndex(m_Seed);
    LotIndex = b;
    widget.cbLotCode->setCurrentIndex(LotIndex);
    IDIndex = c;
    widget.cbProductID->setCurrentIndex(IDIndex);
}

int Commodity::GetSensitivity()
{
    if (ProgramStatus == true) return m_ProgramSeed; 
    else return -1;
}