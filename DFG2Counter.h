/*
 * Copyright:  The Gwenilla House, 2017.
 */

/* 
 * File:   DFG2Counter.h
 * Author: Dan Fay, Owner & CEO of The Gwenilla House
 *
 * Created on February 26, 2017, 4:48 AM
 * 
 * DFG2Counter class
 * Used to interface a Raspberry Pi (Pi3 used here.  Should work with older PIs)
 * with a DF-G2 small object counter from Banner.
 * This class has an interrupt handler which is called each time a seed is 
 * counted.  It reads the health output of the seed counter.  It can program
 * the counter by using pulses.
 * Required:  Raspberry Pi board, wiringPi library, DF-G2 counter (MFR=BANNER).
 * Reference the DF-G2 instruction manual for a description of remotely
 * programming the DF-G2.
 */

#ifndef DFG2COUNTER_H
#define DFG2COUNTER_H

#define PI_COUNT_PORT 0 // BCM GPIO17, Pi header pin 11, GPIO_GEN0
//#define PI_PROGRAM_PORT 3 // BCM GPIO22, Pi header pin 15, GPIO_GEN3
#define PI_PROGRAM_PORT 1 // BCM GPIO18, Pi header pin 12, GPIO_GEN1
#define PI_HEALTH_ALARM_PORT 2 // BCM GPIO27, Pi header pin 13, GPIO_GEN2

// Constant strings
#define TEACH_WINDOW_TEST "Window"

#include <wiringPi.h>
#include <string>


class DFG2Counter {
public:
    DFG2Counter();
    DFG2Counter(const DFG2Counter& orig);
    void InitISR();
    virtual ~DFG2Counter();
    void DefaultValues();
    int GetCount();
    void SetCount(int Count);
    void ProgramTest();
    void DefaultCounter();
    void ClearCount();
    bool ReadHealth();
    void ProgramCounter();  // Programs all counter features.
    void Calibrate();
    // Getters and setters
    int Teach();
    bool Teach(int Value);
    int ResponseSpeed();
    bool ResponseSpeed(int Value);
    int OffsetPercent();
    bool OffsetPercent(int Value);
    int ButtonLock();
    bool ButtonLock(int Value);
    int TotalCounts();
    bool TotalCounts(int Value);
    int TotalOneShot();
    bool TotalOneShot(int Value);
    int DynamicEventStretch();
    bool DynamicEventStretch(int Value);
    int GetTotalCount();
    
private:
    void SingleProgramPulse();
    void ProgramValue(int MainGroup, int VariableGroup, int VariableValue);
    void ProgramTeach();
    void ProgramResponseSpeed();
    void ProgramOffsetPercent();
    void ProgramButtonLock();
    void ProgramTotalCounts();
    void ProgramOneShot();
    void ProgramDynamicEventStretch();
    
private:    // Variables.
    bool m_bHealthOk;
    int m_TotalCounts;
    // The next 6 can be saved to the db.
    int m_Teach;
    int m_ResponseSpeed;
    int m_OffsetPercent;
    int m_ButtonLock;
    int m_TotalOneShot;
    int m_DynamicEventStretch;
 
  
       
    
public:     // Constants
//    const static std::string BUTTON_LOCK_LOCK;
    std::string BUTTON_LOCK_LOCK;
    std::string BUTTON_LOCK_UNLOCK;
    std::string DYNAMIC_EVENT_STRETCH_25;
    std::string DYNAMIC_EVENT_STRETCH_33;
    std::string DYNAMIC_EVENT_STRETCH_50;
    std::string DYNAMIC_EVENT_STRETCH_OFF;
    std::string DYNAMIC_EVENT_STRETCH_100;
    std::string OFFSET_PERCENT_10;
    std::string OFFSET_PERCENT_2;
    std::string OFFSET_PERCENT_20;
    std::string OFFSET_PERCENT_5;
    std::string OFFSET_PERCENT_50;
    std::string OFFSET_PERCENT_MIN;
    std::string RESPONSE_SPEED_150;
    std::string RESPONSE_SPEED_25;
    std::string RESPONSE_SPEED_250;
    std::string RESPONSE_SPEED_50;
    std::string RESPONSE_SPEED_500;
    std::string TEACH_DYNAMIC;
    std::string TEACH_LIGHT;
    std::string TEACH_WINDOW;
    std::string TOTAL_COUNTS_1;
    std::string  TOTAL_COUNTS_10;;
    std::string  TOTAL_COUNTS_100;;
    std::string  TOTAL_COUNTS_25;;
    std::string  TOTAL_COUNTS_5;;
    std::string  TOTAL_COUNTS_OFF;;
    std::string  TOTAL_ONE_SHOT_0;;
    std::string  TOTAL_ONE_SHOT_10;;
    std::string  TOTAL_ONE_SHOT_2;;
    std::string  TOTAL_ONE_SHOT_20;;
    std::string  TOTAL_ONE_SHOT_5;;
    std::string  TOTAL_ONE_SHOT_50;;
};

#endif /* DFG2COUNTER_H */

