/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   IOSetup.cpp
 * Author: SHALAKHA
 *
 * Created on October 12, 2017, 11:02 AM
 */

#include "IOSetup.h"
#include "AboutScreen.h"
#include <QMessageBox>
#include <stdio.h>
#include <QString>
#include <QEvent>
#include <QTimer>
#include <QComboBox>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <iwlib.h>
#include "Keypad.h"

IOSetup::IOSetup() {
    widget.setupUi(this);
         
    setStyleSheet("background-color:black;");   
    widget.btnPrinterSetup->setStyleSheet("background-color:white;");
    widget.btnPrint->setStyleSheet("background-color:white;");
    widget.btnViewData->setStyleSheet("background-color:white;");
    widget.btnHome->setStyleSheet("background-color:black;");
    widget.btnGetIP->setStyleSheet("background-color:white;");
    widget.btnClearPage->setStyleSheet("background-color:white;");
    widget.lblPrintStatus->setStyleSheet("background-color:black; color:white;");
    widget.lblPrintStatus->setText("Nothing Printed");
    widget.lblPrinterStatus->setStyleSheet("background-color:black; color:white;");
    widget.lblPrinterStatus->setText("Printer Connection Status");
    widget.lblFormat->setStyleSheet("background-color:black; color:white;");
    widget.lblFormat->setText("Format: ");
    widget.lblMode->setStyleSheet("background-color:black; color:white;");
    widget.lblMode->setText("Mode: ");
    widget.lblIP->setStyleSheet("background-color:black; color:white;");
    widget.lblIP->setText("");
    widget.lblInfo->setStyleSheet("background-color:black; color:white;");
    widget.lblInfo->setText("To connect to the printer, press PRINTER SETUP");
    widget.lblClearPage->setStyleSheet("background-color:black; color:white;");
    widget.lblClearPage->setText("");
    widget.rbCSV->setStyleSheet("background-color:black; color:white");
    widget.rbCSV->setChecked(true);
    widget.rbFormat->setStyleSheet("background-color:black; color:white");
    widget.rbFile->setStyleSheet("background-color:black; color:white");
    widget.rbFile->setChecked(true);
    widget.rbContinuous->setStyleSheet("background-color:black; color:white");
    //Set home button image
    widget.btnHome->setText("");    // Remove the text so the bitmap fits the button.
    QPixmap pix(":/images/home_button.png");
    QIcon icon(pix);
    widget.btnHome->setIcon(icon);
    widget.btnHome->setIconSize(widget.btnHome->rect().size());
    widget.btnHome->setFixedSize(widget.btnHome->rect().size());
    
    //fd=0;
    //connection = false;
    connect(widget.btnPrinterSetup, SIGNAL(pressed()), this, SLOT(ButtonPressedPrinterSetup()));
    connect(widget.btnPrint, SIGNAL(pressed()), this, SLOT(PrintFromTxtFile()));
    connect(widget.btnHome, SIGNAL(pressed()), this, SLOT(Exit()));
    connect(widget.btnGetIP, SIGNAL(pressed()), this, SLOT(GetIPAddress()));
    connect(widget.btnClearPage, SIGNAL(pressed()), this, SLOT(ClearWebPage()));
    connect(widget.btnViewData, SIGNAL(pressed()), this, SLOT(ViewDataInTable()));
    
    //define routine for the radio buttons
    connect(widget.rbCSV, SIGNAL(pressed()), this, SLOT(CSVSelected()));
    connect(widget.rbFormat, SIGNAL(pressed()), this, SLOT(FormatSelected()));
    connect(widget.rbFile, SIGNAL(pressed()), this, SLOT(FileSelected()));
    connect(widget.rbContinuous, SIGNAL(pressed()), this, SLOT(ContinousSelected()));
   
    //wifi connection/////////////////////////////////////////////////////////////
    widget.lblIP->setText("Connected to wifi before? Press GET IP ADDRESS"); 
    widget.lblScanWifi->setStyleSheet("background-color:black; color:white;");
    widget.lblScanWifi->setText("Connect Wifi only for the first time");
    widget.lblWifiName->setStyleSheet("background-color:black; color:white;");
    widget.lblWifiName->setText("Select WiFi:");
    widget.lblWifiPassword->setStyleSheet("background-color:black; color:white;");
    widget.lblWifiPassword->setText("Password:");
    widget.lePassword->setStyleSheet("background-color:white; color:black;");
    connect(widget.lePassword, SIGNAL(selectionChanged()), this, SLOT(DisplayKeypad()));
    widget.cbWifi->setStyleSheet("background-color:white; color:black;");
    //widget.cbWifi->setMaxCount(5);   
    widget.btnScanWifi->setStyleSheet("background-color:white; color:black;");
    connect(widget.btnScanWifi, SIGNAL(pressed()), this, SLOT(ScanWifiNames()));
    widget.btnConnectWifi->setStyleSheet("background-color:white; color:black;");
    connect(widget.btnConnectWifi, SIGNAL(pressed()), this, SLOT(CallConnectToWifi()));
    
     //format false->csv ; true->format 1
   // FormatStatus=false;
    //Mode false->file; true->continous
   // ModeStatus=false;
   // connection=false;
    //fd=0;
    
    wifiStatus=false;
    
    
}

IOSetup::~IOSetup() {
    
}

void IOSetup::CSVSelected(){
    FormatStatus=false;
    widget.rbCSV->setChecked(true);
    widget.rbFormat->setChecked(false);
}
void IOSetup::FormatSelected(){
    FormatStatus=true;
    widget.rbCSV->setChecked(false);
    widget.rbFormat->setChecked(true);
}
void IOSetup::FileSelected(){
    ModeStatus=false;
    widget.rbFile->setChecked(true);
    widget.rbContinuous->setChecked(false);
}
void IOSetup::ContinousSelected(){
    //Set continuous mode true
    ModeStatus=true;
    widget.rbFile->setChecked(false);
    widget.rbContinuous->setChecked(true);  
}
    
void IOSetup::PrinterSetup()
{   
    if (connection == false){
        fd = serialOpen("/dev/usb/lp0",9600);
        if(fd<=0) {
            widget.lblPrinterStatus->setText("Check Printer Connection");
        }
        else{
          widget.lblPrinterStatus->setText("Printer Connected");
          connection = true;
          ResetPrinter();
        }
    }
    else {
        widget.lblPrinterStatus->setText("Printer Connected");
        widget.lblInfo->setText("To print, press PRINT");
    }
}

void IOSetup::ButtonPressedPrinterSetup()
{
    if (connection == false){
        fd = serialOpen("/dev/usb/lp0",9600);
        if(fd<=0) {
            widget.lblPrinterStatus->setText("Check Printer Connection");
        }
        else{
          widget.lblPrinterStatus->setText("Printer Connected");
          connection = true;
          ResetPrinter();
        }
    }
    else {
        serialClose(fd); 
        fd = serialOpen("/dev/usb/lp0",9600);
        if(fd<=0) {
            widget.lblPrinterStatus->setText("Check Printer Connection");
            connection = false;
        }
        else{
          widget.lblPrinterStatus->setText("Printer Connected");
          connection = true;
          ResetPrinter();
        }
    }
}

void IOSetup::CountPrint()
{             
      /*std::string printseedname = "SEED NAME = " + seedname;
      char const *snchar = printseedname.c_str();
       QMessageBox* msg = new QMessageBox();
            msg->setWindowTitle("Print");    
            msg->setText(snchar);	     
            msg->show(); */
    widget.lblInfo->setText("");
    if (fd <=0) { widget.lblPrintStatus->setText("Check Printer Connection"); }
    else{
    serialPutchar(fd,9);
    serialPuts(fd,"SEEDBURO Equipment Company \n\n");
    //PrintLogo();
     // print date and time
    PrintDateTime();
    serialPuts(fd,"\n\n");
    // print seed name
    serialPutchar(fd,9);// HT for tab
    std::string printseedname = "SEED NAME = " + seedname;
    char const *snchar = printseedname.c_str();
    serialPuts(fd,snchar);
    serialPuts(fd,"\n");
    //print seed count

    serialPutchar(fd,9);
    std::string seedcount = "TOTAL SEED COUNT = " + std::to_string(GetTotalCount());
    char const *schar = seedcount.c_str();
    serialPuts(fd,schar);
    serialPutchar(fd,10);
    serialPuts(fd,"\n==============================================\n\n\n\n\n\n\n\n");
    serialPutchar(fd,10);
    PaperCut();
       
    widget.lblPrintStatus->setText("Print Successful");
    
    }
}
void IOSetup::Exit()
{
    //serialClose(fd); 
    close();
}

void IOSetup::PrintDateTime()
{
    timeval curTime;
    tm *my_date_time;
    gettimeofday(&curTime, NULL);
    my_date_time = localtime(&curTime.tv_sec);
    serialPutchar(fd,9);
    std::string date= "Date: " + std::to_string(my_date_time->tm_mon + 1) +"/"+ std::to_string(my_date_time->tm_mday) +"/"+std::to_string(my_date_time->tm_year - 100);
    char const *pchar = date.c_str();
    serialPuts(fd,pchar);

    serialPuts(fd,"\n");
    serialPutchar(fd,9);
    std::string time= "Time: " + std::to_string(my_date_time->tm_hour) +":"+ std::to_string(my_date_time->tm_min) +":"+ std::to_string(my_date_time->tm_sec);
    char const *tchar = time.c_str();
    serialPuts(fd,tchar);
}
void IOSetup::PrintMode()
{
    serialPutchar(fd,27);
    serialPutchar(fd,'L');
    serialPutchar(fd,0); 
}

void IOSetup::CommandMode()
{
    serialPutchar(fd,27);
    serialPutchar(fd,'S');
    serialPutchar(fd,0); 
}

void IOSetup::PaperCut()
{
    serialPutchar(fd,29);
    serialPutchar(fd,'V');
    serialPutchar(fd,0); 
}
void IOSetup::ResetPrinter()
{
    serialPutchar(fd,27);
    serialPutchar(fd,'@');
}

void IOSetup::SetTotalCount(int count){
    totalIOseedcount=count;
}
int IOSetup::GetTotalCount(){
    return totalIOseedcount;
}

void IOSetup::SetSeedName(int index){
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

std::vector<std::string> IOSetup::explode(const std::string & str, const char& ch) {
    std::string next;
    std::vector<std::string> result;

    // For each character in the string
    for (std::string::const_iterator it = str.begin(); it != str.end(); it++) {
        // If we've hit the terminal character
        if (*it == ch) {
            // If we have some characters accumulated
           // if (!next.empty()) {
                // Add them to the result vector
                result.push_back(next);
                next.clear();
            //}
        } else {
            // Accumulate the next character into the sequence
            next += *it;
        }
    }
    if (!next.empty())
        result.push_back(next);
    return result;
}

void IOSetup::PrintFromTxtFile(){
    widget.lblInfo->setText("");
   if (fd <=0) { widget.lblPrintStatus->setText("Check Printer Connection"); }
   else {
       if(FormatStatus==true && ModeStatus==true) //format1 and continuous
    {
            std::string line;
            std::ifstream PrintFile("/home/pi/RecentFile.txt");
            std::getline(PrintFile, line);
            serialPutchar(fd,9);
            serialPuts(fd,"SEEDBURO Equipment Company \n\n");
            std::vector<std::string> result = explode(line, ',');
            // print date
            serialPutchar(fd,9);
            std::string lot= "Lot Code: " + result[0];
            char const *lchar = lot.c_str();
            serialPuts(fd,lchar);
            serialPuts(fd,"\n");
            //print time
            serialPutchar(fd,9);
            std::string id= "Product ID: " + result[1];
            char const *ichar = id.c_str();
            serialPuts(fd,ichar);
            serialPuts(fd,"\n");
            //print seedname
            serialPutchar(fd,9);
            std::string date= "Date: " + result[2];
            char const *dchar = date.c_str();
            serialPuts(fd,dchar);
            serialPuts(fd,"\n");
            serialPutchar(fd,9);
            std::string time= "Time: " + result[3];
            char const *tchar = time.c_str();
            serialPuts(fd,tchar);
            serialPuts(fd,"\n");
            //print Seed Count
            serialPutchar(fd,9);
            std::string SeedCount= "Total Seed Count: " + result[4];
            char const *cchar = SeedCount.c_str();
            serialPuts(fd,cchar);
            serialPuts(fd,"\n");
            if( result[5] != " "){
                serialPutchar(fd,9);
                std::string BagNo= "Bag Number: " + result[5];
                char const *bchar = BagNo.c_str();
                serialPuts(fd,bchar);
            }
            serialPuts(fd,"\n\n");
            serialPutchar(fd,10);
            serialPuts(fd,"\n==============================================\n\n\n\n\n\n\n\n");
            serialPutchar(fd,10);
            PaperCut();
            PrintFile.close();
            widget.lblPrintStatus->setText("Print Successful");                  
    }
    else if(FormatStatus==false && ModeStatus==true) //CSV and continuous
    {
        std::string line;
        std::ifstream PrintFile("/home/pi/RecentFile.txt");
        std::getline(PrintFile, line);
        serialPutchar(fd,9);
        serialPuts(fd,"SEEDBURO Equipment Company \n\n");
        serialPuts(fd,"Lot Code,Product ID,Date,Time,Seed Count,Bag\n");
        // print with commas
        char const *linechar = line.c_str();
        serialPuts(fd,linechar);

        serialPutchar(fd,10);
        serialPuts(fd,"\n==============================================\n\n\n\n\n\n\n\n");
        serialPutchar(fd,10);
        PaperCut();
        PrintFile.close();
        widget.lblPrintStatus->setText("Printed Successfully");
    }
    else if(FormatStatus==true && ModeStatus==false) //format1 and file
    {
        std::string line;
        std::ifstream PrintFile("/home/pi/PrintSeedData.txt");
        while(std::getline(PrintFile, line))
        {
            serialPutchar(fd,9);
            serialPuts(fd,"SEEDBURO Equipment Company \n\n");
            std::vector<std::string> result = explode(line, ',');
            // print date
            serialPutchar(fd,9);
            std::string lot= "Lot Code: " + result[0];
            char const *lchar = lot.c_str();
            serialPuts(fd,lchar);
            serialPuts(fd,"\n");
            //print time
            serialPutchar(fd,9);
            std::string id= "Product ID: " + result[1];
            char const *ichar = id.c_str();
            serialPuts(fd,ichar);
            serialPuts(fd,"\n");
            //print seedname
            serialPutchar(fd,9);
            std::string date= "Date: " + result[2];
            char const *dchar = date.c_str();
            serialPuts(fd,dchar);
            serialPuts(fd,"\n");
            serialPutchar(fd,9);
            std::string time= "Time: " + result[3];
            char const *tchar = time.c_str();
            serialPuts(fd,tchar);
            serialPuts(fd,"\n");
            //print Seed Count
            serialPutchar(fd,9);
            std::string SeedCount= "Total Seed Count: " + result[4];
            char const *cchar = SeedCount.c_str();
            serialPuts(fd,cchar);
            serialPuts(fd,"\n");
            if( result[5] != " "){
                serialPutchar(fd,9);
                std::string BagNo= "Bag Number: " + result[5];
                char const *bchar = BagNo.c_str();
                serialPuts(fd,bchar);
            }
            serialPuts(fd,"\n\n");

            serialPutchar(fd,10);
            serialPuts(fd,"\n==============================================\n\n\n\n\n\n\n\n");
            serialPutchar(fd,10);
            PaperCut();
    }
        PrintFile.close();
        widget.lblPrintStatus->setText("Print Successful");
        PrintFile.open("/home/pi/PrintSeedData.txt", std::fstream::out | std::fstream::trunc);
        PrintFile.close();
    }
    else if(FormatStatus==false && ModeStatus==false) //CSV and file
    {
        std::string line;
        std::ifstream PrintFile("/home/pi/PrintSeedData.txt");
        while(std::getline(PrintFile, line))
        {
            serialPutchar(fd,9);
            serialPuts(fd,"SEEDBURO Equipment Company \n\n");
            // print with commas
            serialPuts(fd,"Lot Code,Product ID,Date,Time,Seed Count,Bag\n");
            char const *linechar = line.c_str(); 
            serialPuts(fd,linechar);
            serialPutchar(fd,10);
            serialPuts(fd,"\n==============================================\n\n\n\n\n\n\n\n");
            serialPutchar(fd,10);
            PaperCut();
        }
    PrintFile.close();
    PrintFile.open("/home/pi/PrintSeedData.txt", std::fstream::out | std::fstream::trunc);
    PrintFile.close();
    widget.lblPrintStatus->setText("Print Successful");
    }
 }
}

bool IOSetup::GetPrintMode(){
    return ModeStatus;
}

bool IOSetup::GetPrintFormat(){
    return FormatStatus;
}


/********************************************************************************************************/
//WEB PAGE 
void IOSetup::GetIPAddress(){
widget.lblInfo->setText("Open web browser on your device and enter IP address");
std::string next;
std::string line;
std::ifstream WifiConn("/sys/class/net/wlan0/operstate");
std::getline(WifiConn, line);
    for (std::string::const_iterator it = line.begin(); it != line.end(); it++) {
        next += *it;
    }
    if(next == "up") {
        usleep(1000000);
        WifiConn.close();
        int ipfd;
        struct ifreq ifr;
        ipfd = socket(AF_INET, SOCK_DGRAM, 0);

        /* get an IPv4 IP address */
        ifr.ifr_addr.sa_family = AF_INET;

        /* IP address attached to "eth0" or "wlan0"*/
        strncpy(ifr.ifr_name, "wlan0", IFNAMSIZ);

        ioctl(ipfd, SIOCGIFADDR, &ifr);

        //close(ipfd);
        /* display result */
        //printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
        wifiStatus = true;
        widget.lblIP->setText(inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
    }
    
    else{ 
        widget.lblIP->setText("ERROR! Try to connect WiFi"); 
        WifiConn.close();
    }
}
void IOSetup::WifiConnectionError(){
 widget.lblIP->setText("Try to connect WiFi again"); 
}

void IOSetup::ClearWebPage(){
    std::fstream WebFile;
    WebFile.open("/var/www/html/WebSeedData.txt", std::fstream::out | std::fstream::trunc);
    WebFile.close();
    widget.lblClearPage->setText("Data Cleared");
}

void IOSetup::ViewDataInTable()
{ 
    ViewDataTable *dataForm = new ViewDataTable();
    dataForm->setWindowFlags(Qt::FramelessWindowHint);
    dataForm->setModal(true);
    dataForm->move(0,20);  // Move window up a bit to cover main window.
    dataForm->exec();    
    delete dataForm;    
}

void IOSetup::ScanWifiNames()
{
  widget.lblScanWifi->setText("Set Wifi and password, press CONNECT");
  widget.cbWifi->clear();
  wireless_scan_head head;
  wireless_scan *result;
  iwrange range;
  int sock;
  char str[]="wlan0";
  /* Open socket to kernel */
  sock = iw_sockets_open();

  /* Get some metadata to use for scanning */
  if (iw_get_range_info(sock, str, &range) < 0) {
    //printf("Error during iw_get_range_info. Aborting.\n");
    QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("ERROR");    
    msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
    msg->setText("Error! Try Again");	     
    msg->show();
    return;
  }

  /* Perform the scan */
  if (iw_scan(sock, str, range.we_version_compiled, &head) < 0) {
    //printf("Error during iw_scan. Aborting.\n");
    QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("ERROR");    
    msg->setStyleSheet("QPushButton {"" background-color: white;" " border-radius: 10px;"" font: bold 14px;" " min-width: 8em;" " padding: 6px;""}" "QLabel {"" font: bold 18px;""}");
    msg->setText("Error! Try Again");	     
    msg->show();
    return;
  }

  /* Traverse the results */
  result = head.result;
  while (NULL != result) {
    //printf("%s\n",result->b.essid);
      if(QString(result->b.essid) != ""){
        widget.cbWifi->addItem(QString(result->b.essid));
      }
    result = result->next;
  }
}

void IOSetup::CallConnectToWifi(){
    widget.lblIP->setText("WiFi Connecting..."); 
    QTimer::singleShot(100,this,SLOT(ConnectToWifi()));
}

void IOSetup::ConnectToWifi()
{
    wifiStatus = false;
    std::string s = "sudo wpa_passphrase \"" + (widget.cbWifi->currentText()).toStdString()+ "\" \""+(widget.lePassword->text()).toStdString() + "\" > /etc/wpa_supplicant/wpa_supplicant.conf";
    WifiName= (widget.cbWifi->currentText()).toStdString();
    WifiPsd = (widget.lePassword->text()).toStdString();
    char const *pchar = s.c_str();
    system(pchar);
    usleep(1000000);
    system("sudo killall wpa_supplicant");
    usleep(1000000);
    system("wpa_supplicant -D nl80211 -iwlan0 -c/etc/wpa_supplicant/wpa_supplicant.conf -B");
    usleep(1000000);
    system("sudo dhclient"); 
    usleep(3000000);
    GetIPAddress();
    if (wifiStatus == false) { 
        widget.lblIP->setText("Error!Try to connect WiFi again"); 
        widget.lblScanWifi->setText("Password must be more than 8 characters");
    }
    else { widget.lblScanWifi->setText(""); }
}

void IOSetup::DisplayKeypad()
{
    Keypad *keypadForm = new Keypad();
    keypadForm->setWindowFlags(Qt::FramelessWindowHint);
    keypadForm->setModal(true);
    keypadForm->exec();
    widget.lePassword->setText(keypadForm->GetInputValue());
    delete keypadForm;
    //system("sudo /home/pi/matchbox-keyboard.sh");

}

void IOSetup::InitializeVariables(bool a, bool b, bool c, int d){
    //format false->csv ; true->format 1
   FormatStatus= a;
   if (FormatStatus==false) {
    widget.rbCSV->setChecked(true);
    widget.rbFormat->setChecked(false);
   } else 
   {
       widget.rbCSV->setChecked(false);
    widget.rbFormat->setChecked(true);
   }
    //Mode false->file; true->continous
   ModeStatus= b;
    if (ModeStatus==false){
    widget.rbFile->setChecked(true);
    widget.rbContinuous->setChecked(false);
    }
    else 
    {
        widget.rbFile->setChecked(false);
        widget.rbContinuous->setChecked(true);
    }
   connection=c;
   fd=d;
   PrinterSetup();
   GetIPAddress();
}
bool IOSetup::GetPrinterStatus(){
   return connection;
}
int IOSetup::GetPrinterConnection(){
    return fd;
}

void IOSetup::PrintForCarousel(){
    if (fd <=0) { widget.lblPrintStatus->setText("Check Printer Connection"); }
    else {
    std::string line;
    std::ifstream PrintFile("/home/pi/CarouselPrint.txt");
    serialPutchar(fd,9); //tab
    serialPuts(fd,"SEEDBURO Equipment Company \n\n");
    std::getline(PrintFile, line);
    std::vector<std::string> result = explode(line, ',');
    std::string date= "Date:" + result[2];
    char const *dchar = date.c_str();
    serialPuts(fd,dchar);
    serialPuts(fd,"\n");
    std::string lot= "Lot Code: " +result[0];
    char const *lchar = lot.c_str();
    serialPuts(fd,lchar);
    serialPuts(fd,"\n");
    std::string id= "Product ID: " + result[1];
    char const *ichar = id.c_str();
    serialPuts(fd,ichar);
    serialPuts(fd,"\n");
    serialPuts(fd,"Bag  Count  Time\n");
    std::string BagNo= result[5] +"  ";
    char const *bchar = BagNo.c_str();
    serialPuts(fd,bchar);    
     //serialPutchar(fd,9);
    std::string SeedCount= result[4] + "  ";
    char const *cchar = SeedCount.c_str();
    serialPuts(fd,cchar);
    //time
   // serialPutchar(fd,9);
    std::string time= result[3];
    char const *tchar = time.c_str();
    serialPuts(fd,tchar);
    //print Seed Count

    serialPuts(fd,"\n");
    while(std::getline(PrintFile, line))
    {
        std::vector<std::string> result = explode(line, ',');
        //bag number
        //serialPutchar(fd,9);
        std::string BagNo= result[5] +"  ";
        char const *bchar = BagNo.c_str();
        serialPuts(fd,bchar);

        //print Seed Count
        //serialPutchar(fd,9);
        std::string SeedCount= result[4]+"  ";
        char const *cchar = SeedCount.c_str();
        serialPuts(fd,cchar);

        // serialPutchar(fd,9);
        std::string time= result[3] +" ";
        char const *tchar = time.c_str();
        serialPuts(fd,tchar);
        serialPuts(fd,"\n");
    }
        serialPutchar(fd,10);
        serialPuts(fd,"\n==============================================\n\n\n\n\n\n\n\n");
        serialPutchar(fd,10);
        PaperCut();
    
    PrintFile.close();
    widget.lblPrintStatus->setText("Print Successful");
    }
}

std::string IOSetup::GetWifiName(){
    return WifiName;
}
std::string IOSetup::GetWifiPassword(){
    return WifiPsd;
}
void IOSetup::InitializeWiFi(std::string wn, std::string wp ){
    WifiName=wn;
    WifiPsd=wp;
    widget.cbWifi->addItem(QString::fromStdString(WifiName));
    widget.lePassword->setText(QString::fromStdString(WifiPsd));
}