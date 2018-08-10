/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SolenoidControl.cpp
 * Author: Dan
 * 
 * Created on July 18, 2017, 5:35 AM
 */

#include <unistd.h>
#include "SolenoidControl.h"

SolenoidControl::SolenoidControl() 
{
    wiringPiSetup();
    
	// The following is an example from the motor control class.  Change for solenoid outputs.
    pinMode(PI_RIGHT_SOLENOID,OUTPUT);
    pinMode(PI_LEFT_SOLENOID,OUTPUT);
    pullUpDnControl (PI_RIGHT_SOLENOID, PUD_OFF);   // Might need pull up off.
    pullUpDnControl (PI_LEFT_SOLENOID, PUD_OFF);   // Might need pull up off.
    digitalWrite(PI_RIGHT_SOLENOID,LOW);   // Keep signal to right solenoid HIGH.
    digitalWrite(PI_LEFT_SOLENOID,LOW);   // Keep signal to left solenoid HIGH.
    
    m_SolenoidsEnabled = true;
    m_RightOn = true;
    m_LeftOn = false;
    SetRight(m_RightOn);
    SetLeft(m_LeftOn);
}

SolenoidControl::SolenoidControl(const SolenoidControl& orig) 
{
    SetRight(false);
    SetLeft(false);
}

SolenoidControl::~SolenoidControl() 
{
    digitalWrite(PI_RIGHT_SOLENOID,LOW);   // Keep signal to right solenoid HIGH.
    digitalWrite(PI_LEFT_SOLENOID,LOW);   // Keep signal to left solenoid HIGH.
//    pinMode(PI_RIGHT_SOLENOID,INPUT);
//    pinMode(PI_LEFT_SOLENOID,INPUT);

}

void SolenoidControl::SetRight(bool RightState)
{
    //m_RightOn = RightState;
    digitalWrite(PI_RIGHT_SOLENOID,RightState?HIGH:LOW);
}
void SolenoidControl::SetLeft(bool LeftState)
{
    //m_LeftOn = LeftState;
     digitalWrite(PI_LEFT_SOLENOID,LeftState?HIGH:LOW);
}

void SolenoidControl::Toggle()
{
    m_SolenoidsEnabled = true;
    
    // Turn off both solenoids so they aren't on at the same time.
    SetRight(false);
    SetLeft(false);
    
    // Toggle the values.
    m_RightOn = !m_RightOn;
    m_LeftOn = !m_LeftOn;
    
    // Activate one of them.
    SetRight(m_RightOn);
    SetLeft(m_LeftOn);
}

bool SolenoidControl::GetRight()
{
    return m_RightOn;
}

bool SolenoidControl::GetLeft()
{
    return m_LeftOn;
}

void SolenoidControl::EnableSolenoids(bool Enable)
{
    m_SolenoidsEnabled = Enable;
    if(m_SolenoidsEnabled)
    {
        SetRight(m_RightOn);
        SetLeft(m_LeftOn);
    }
    else
    {
        SetRight(false);
        SetLeft(false);
 
    }
}

bool SolenoidControl::GetSolenoidsState()
{
    return m_SolenoidsEnabled;
}

