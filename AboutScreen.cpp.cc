/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   AboutScreen.cpp
 * Author: SHALAKHA
 *
 * Created on November 3, 2017, 10:29 AM
 */

#include "AboutScreen.h"

AboutScreen::AboutScreen() {
    widget.setupUi(this);
     // Sets the dialog's background color.
    setStyleSheet("background-color:white;");
    // Change the background color of the buttons and labels
    widget.btnOK->setStyleSheet("background-color:white;");
    widget.lblAbout->setStyleSheet("background-color:white; color:black;");
    widget.lblAbout->setText("901 Seed Counter");
    widget.lblAboutInfo->setStyleSheet("background-color:white; color:black;");
    GetSerialNumberFromFile();
    widget.lblAboutInfo->setText("Model Name: 901 Seed Counter\nSerial Number: " + SerialNumber + "\nSoftware Version: 1.0\nHardware: Raspberry Pi 3 Model B\nRaspbian OS: 4.9.59-v7+");
    
    connect(widget.btnOK, SIGNAL(pressed()), this, SLOT(ExitToHomeScreen()));

}

AboutScreen::~AboutScreen() {
}

void AboutScreen::ExitToHomeScreen(){
    close();
} 

void AboutScreen::GetSerialNumberFromFile()
{
    std::string serialno;
    std::ifstream SerialFile;
    SerialFile.open("/home/pi/SerialNumber.txt",std::ios_base::in);
    if (SerialFile.is_open())
    {
        SerialFile >> serialno;
        SerialFile.close();
        char const *pchar = serialno.c_str();
        SerialNumber = pchar;
    }    
}