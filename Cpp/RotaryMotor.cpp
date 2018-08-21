/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <unistd.h>
#include "RotaryMotor.h"
#include <QMessageBox>
#include <cstdlib>
#include <unistd.h>

RotaryMotor::RotaryMotor()
{   
    UsbConn=0;
    error=0;
    UsbConn = serialOpen("/dev/ttyUSB0", 9600); // Working
    serialPuts(UsbConn,"FD \r\n"); // factory restore settings
    serialPuts(UsbConn,"H \r\n");
    GetPositionFromFile();     
}
RotaryMotor::~RotaryMotor() 
{
}
void RotaryMotor::Rotate45()
{   
    //CheckConn();
    serialPuts(UsbConn,"MR 575000 \r\n");   //change value to change the degree of rotation
    serialPuts(UsbConn,"H \r\n");
       
}
void RotaryMotor::RotaryStop()    
{
    serialPuts(UsbConn,"MA 0 \r\n");
    serialPuts(UsbConn,"H \r\n");
    //RotateToSpecficValue(1);
}

bool RotaryMotor::CheckConn()
{
    if (!CheckConnection()) { 
        UsbConn = serialOpen("/dev/ttyUSB0", 9600); // Working
        return CheckConnection();      
    }
   else if(CheckForError())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void RotaryMotor::RotatePositive(){
    serialPuts(UsbConn,"MR 18000 \r\n");   //change value to change the degree of rotation
    serialPuts(UsbConn,"H \r\n");
}
void RotaryMotor::RotateNegative(){
    serialPuts(UsbConn,"MR -18000 \r\n");   //change value to change the degree of rotation
    serialPuts(UsbConn,"H \r\n");
}

void RotaryMotor::RotateToSpecficValue(int chute)
{
    if(chute == 1)
    {
        long int ActualPositionValue = (ChutePosition[chute-1] * 18000);
        std::string value="MA " + std::to_string(ActualPositionValue)+" \r\n";
        char const *valuechar = value.c_str();
        serialPuts(UsbConn,valuechar);
        serialPuts(UsbConn,"H \r\n");
    }
}

void RotaryMotor::GetPositionFromFile()
{
    std::ifstream MotorFile;
    MotorFile.open("/home/pi/MotorPosition.txt",std::ios_base::in);
    if (MotorFile.is_open())
    {
        signed int a;
        int i=0;
        while(MotorFile >> a)
        {
            ChutePosition[i]=a;
            i++;
        }   
        MotorFile.close();
    }
    else {
         std::ofstream NewMotorFile;
         NewMotorFile.open("/home/pi/MotorPosition.txt",std::ios_base::out);
         for(int i=0 ; i<8; i++)
         {
             NewMotorFile << "0";
             NewMotorFile << "\n";
         }
         NewMotorFile.close();
    }
    //RotateToSpecficValue(1);
    RotaryStop();
}

void RotaryMotor::RotateToZero()    
{
    serialPuts(UsbConn,"MA 0 \r\n");
    serialPuts(UsbConn,"H \r\n");
}

void RotaryMotor::RotateToNextChute(int chute)
{
    long int ActualPositionValue = 575000 + (ChutePosition[chute-1] * 18000);
    std::string value="MR " + std::to_string(ActualPositionValue)+" \r\n";
    char const *valuechar = value.c_str();
    
    serialPuts(UsbConn,valuechar);
    serialPuts(UsbConn,"H \r\n");
    /*QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("Count Point");    
    msg->setText(valuechar);	     
    msg->show();*/
}

void RotaryMotor::SetZeroPosition(){
    serialPuts(UsbConn,"P 0 \r\n");
    //serialPuts(UsbConn,"H \r\n");
}

bool RotaryMotor::CheckConnection()
{
    if (UsbConn < 0) { 
        return false;
    }
    else {
        return true;
    }
}

bool RotaryMotor::CheckForError()
{
    serialPuts(UsbConn,"PR ER \r\n");
    error = serialGetchar(UsbConn);
    if(error == 86 || error == -1) { 
        serialPuts(UsbConn,"ER 0 \r\n");
        return true;        
    }
    else 
    {
        serialPuts(UsbConn,"ER 0 \r\n"); 
        return false;
    }
}

bool RotaryMotor::Reconnect()
{
    if(CheckConnection())
    {
        serialClose(UsbConn);
    }

    UsbConn = serialOpen("/dev/ttyUSB0", 9600); // Working
    return CheckConnection();       
 
}