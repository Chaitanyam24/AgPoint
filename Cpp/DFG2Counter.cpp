/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DFG2Counter.cpp
 * Author: Dan
 * 
 * Created on February 26, 2017, 4:48 AM
 */

#include "DFG2Counter.h"
#include <unistd.h>

static volatile int globalCounter;  // Holds the count.
static volatile int totalglobalCounter;
// Enums
enum e_Teach{ Window=1, Light, Dynamic};
enum e_ResponseSpeed{ s25=1, s50, s150, s250, s500};
enum e_OffsetPercent{ pMin=1, p2=2, p5=3, p10=4, p20=5, p50=6};
enum e_ButtonLock{ Unlocked=1, Locked};
enum e_TotalCounts {cOff=1, c1, c5, c10, c25, c100};
enum e_TotalOneShot{ ts0=1, ts2, ts5, ts10, ts20, ts50};
enum e_DynamicEventStretch{ dsOff=1, ds25, ds33, ds50, ds100};

void PiIntHandler(void) // Used by interrupt to increment the count.
{
    ++globalCounter;
    ++totalglobalCounter;
}

DFG2Counter::DFG2Counter() 
{
   
    // String constants
    // Would like to load these from the StringResources.properties.
    BUTTON_LOCK_UNLOCK = "Unlock";
    BUTTON_LOCK_LOCK = "Locked";
    DYNAMIC_EVENT_STRETCH_OFF = "Off";
    DYNAMIC_EVENT_STRETCH_25 = "25%";
    DYNAMIC_EVENT_STRETCH_33 = "33%";
    DYNAMIC_EVENT_STRETCH_50 = "50%";
    DYNAMIC_EVENT_STRETCH_100 = "100%";
    OFFSET_PERCENT_MIN = "Min";
    OFFSET_PERCENT_2 = "2%";
    OFFSET_PERCENT_5 = "5%";
    OFFSET_PERCENT_10 = "10%";
    OFFSET_PERCENT_20 = "20%";
    OFFSET_PERCENT_50 = "50%";
    RESPONSE_SPEED_25 = "25 us";
    RESPONSE_SPEED_50 = "50 us";
    RESPONSE_SPEED_150 = "150 us";
    RESPONSE_SPEED_250 = "250 us";
    RESPONSE_SPEED_500 = "500 us";
    TEACH_WINDOW = "Window";
    TEACH_LIGHT = "Light";
    TEACH_DYNAMIC = "Dynamic";
    TOTAL_COUNTS_OFF = "Off";
    TOTAL_COUNTS_1 = "1 count";
    TOTAL_COUNTS_5 = "5 counts";
    TOTAL_COUNTS_10 = "10 counts";
    TOTAL_COUNTS_25 = "25 counts";
    TOTAL_COUNTS_100 = "100 counts";
    TOTAL_ONE_SHOT_0 = "0 ms";
    TOTAL_ONE_SHOT_2 = "2 ms";
    TOTAL_ONE_SHOT_5 = "5 ms";
    TOTAL_ONE_SHOT_10 = "10 ms";
    TOTAL_ONE_SHOT_20 = "20 ms";
    TOTAL_ONE_SHOT_50 = "50 ms";
    
    // Default counter values.
    DefaultValues();
    globalCounter=0;
    totalglobalCounter=0;
    m_bHealthOk = true;
    wiringPiSetup();    // Must be called before using wiringPi.
    pinMode(PI_COUNT_PORT,INPUT);   // Set GPIO17 to input.
    pinMode(PI_PROGRAM_PORT,OUTPUT);   // Set GPIO18 to input.
    pinMode(PI_HEALTH_ALARM_PORT,INPUT);   // Set GPIO27 to input.
    digitalWrite (PI_PROGRAM_PORT, HIGH) ;
        
}

DFG2Counter::DFG2Counter(const DFG2Counter& orig) 
{
    DefaultValues();
    m_ButtonLock = orig.m_ButtonLock;
    m_bHealthOk = orig.m_bHealthOk;
    m_Teach = orig.m_Teach;
    m_ResponseSpeed = orig.m_ResponseSpeed;
    m_OffsetPercent = orig.m_OffsetPercent;
    m_ButtonLock = orig.m_ButtonLock;
    m_TotalCounts = orig.m_TotalCounts;
    m_TotalOneShot = orig.m_TotalOneShot;
    m_DynamicEventStretch = orig.m_DynamicEventStretch;
}

DFG2Counter::~DFG2Counter() 
{
    
}

void DFG2Counter::InitISR()
{
    // Set GPIO17 to trigger an interrupt on the falling edge.
    wiringPiISR(PI_COUNT_PORT, INT_EDGE_FALLING, &PiIntHandler);    
}

void DFG2Counter::DefaultValues()
{
    m_Teach = Window;
    m_ResponseSpeed = s25;
    m_OffsetPercent = pMin;
    m_ButtonLock = Unlocked;
    m_TotalCounts = cOff;
    m_TotalOneShot = ts0;
    m_DynamicEventStretch = dsOff;    
}

// Returns the current count.
int DFG2Counter::GetCount()
{
    return globalCounter;
}

void DFG2Counter::SetCount(int Count)
{
    globalCounter = Count;
}

// Clears the current count.
void DFG2Counter::ClearCount()
{   
    totalglobalCounter =  0;
    globalCounter = 0;
}

// Provides a single pulse to the DF-G2.
void DFG2Counter::SingleProgramPulse()
{
    digitalWrite (PI_PROGRAM_PORT, LOW);
    usleep(100000); // delay for 100ms.
    digitalWrite (PI_PROGRAM_PORT, HIGH);
    usleep(100000); // delay for 100ms.   
}

// Just a test.
void DFG2Counter::ProgramTest()
{
    // SingleProgramPulse();
    ProgramTeach();
}
void DFG2Counter::Calibrate()
{
    SingleProgramPulse();
}

/*
 * void DFG2Counter::DefaultCounter()
 * Defaults the counter.
 */
void DFG2Counter::DefaultCounter()
{
    // Write 8 single pulses to counter to default it.
    for(int i=0;i<8;i++)
        SingleProgramPulse();
}

// Reads the heath output of the DF-G2.
bool DFG2Counter::ReadHealth()
{
    return(TRUE == digitalRead(PI_HEALTH_ALARM_PORT)?true:false);
}

void DFG2Counter::ProgramValue(int MainGroup, int VariableGroup, int VariableValue)
{
    int i=0;
    
    // Got to the main group
    for(i=0;i<MainGroup;i++)
        SingleProgramPulse();
    usleep(1100000); // delay for 1100ms to go to next group
    
     // Go to the setting that is to be configured.
    for(i=0;i<VariableGroup;i++)
        SingleProgramPulse();
    usleep(1100000); // delay for 1100ms to go to next group
    
   // Program the value
    for(i=0;i<VariableValue;i++)
        SingleProgramPulse();
    usleep(1100000); // delay for 1100ms so another variable can be programmed. 
}
void DFG2Counter::ProgramTeach()
{
    ProgramValue(2, 1,m_Teach);
}

void DFG2Counter::ProgramResponseSpeed()
{
    ProgramValue(2, 2,m_ResponseSpeed);
}

void DFG2Counter::ProgramOffsetPercent()
{
    ProgramValue(2, 3,m_OffsetPercent);
}

void DFG2Counter::ProgramButtonLock()
{
    ProgramValue(2, 4,m_ButtonLock);
}

void DFG2Counter::ProgramTotalCounts()
{
    ProgramValue(3, 1,m_TotalCounts);
}

void DFG2Counter::ProgramOneShot()
{
    ProgramValue(3, 2,m_TotalOneShot);
}

void DFG2Counter::ProgramDynamicEventStretch()
{
    ProgramValue(3, 3,m_DynamicEventStretch);
}
    
int DFG2Counter::Teach()
{
    return m_Teach;
}

bool DFG2Counter::Teach(int Value)
{
    if(Value >= Window && Value <= Dynamic)
    {
        m_Teach = Value;
        return true;
    }
    return false;
}

int DFG2Counter::ResponseSpeed()
{
    return m_ResponseSpeed;
}

bool DFG2Counter::ResponseSpeed(int Value)
{
    if(Value >= s25 && Value <= s500)
    {
        m_ResponseSpeed = Value;
        return true;
    }
    return false;
}

int DFG2Counter::OffsetPercent()
{
    return m_OffsetPercent;
}

bool DFG2Counter::OffsetPercent(int Value)
{
    if(Value >= pMin && Value <= p50)
    {
        m_OffsetPercent = Value;
        return true;
    }
    return false;
}

int DFG2Counter::ButtonLock()
{
    return m_ButtonLock;
}
bool DFG2Counter::ButtonLock(int Value)
{
    if(Value >= Unlocked && Value <= Locked)
    {
        m_ButtonLock = Value;
        return true;
    }
    return false;
}
int DFG2Counter::TotalCounts()
{
    return m_TotalCounts;
}
bool DFG2Counter::TotalCounts(int Value)
{
    if(Value >= cOff && Value <= c100)
    {
        m_TotalCounts = Value;
        return true;
    }
    return false;
}
int DFG2Counter::TotalOneShot()
{
    return m_TotalOneShot;
}
bool DFG2Counter::TotalOneShot(int Value)
{
    if(Value >= ts0 && Value <= ts50)
    {
        m_TotalOneShot = Value;
        return true;
    }
    return false;
}
int DFG2Counter::DynamicEventStretch()
{
    return m_DynamicEventStretch;
}

bool DFG2Counter::DynamicEventStretch(int Value)
{
    if(Value >= dsOff && Value <= ds100)
    {
        m_DynamicEventStretch = Value;
        return true;
    }
    return false;
}

// Programs all counter features.
void DFG2Counter::ProgramCounter()
{
    ProgramTeach();
    ProgramResponseSpeed();
    ProgramOffsetPercent();
    ProgramButtonLock();
    ProgramTotalCounts();
    ProgramOneShot();
    ProgramDynamicEventStretch();
}

int DFG2Counter::GetTotalCount()
{
    return totalglobalCounter;
}
