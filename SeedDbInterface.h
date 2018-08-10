/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SeedDbInterface.h
 * Author: Dan
 *
 * Created on May 6, 2017, 5:45 AM
 */

#ifndef SEEDDBINTERFACE_H
#define SEEDDBINTERFACE_H

#include "string"
#include "mysql_driver.h"
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include </usr/include/mysql/mysql.h>
#include <QString>

#include "DFG2Counter.h"
// Defines
#define MYSQL_DB "raspberry"
#define DATABASE_NAME "seedlist"
#define TABLE_COUNTER_CONFIG "counterconfig"
#define TABLE_COUNTER_CONFIG_COLUMNS "teach,responsespeed,offsetpercent,buttonlock,totalcounts,totaloneshot,dynamiceventstretch"

class SeedDbInterface {
public:
    SeedDbInterface();
    SeedDbInterface(const SeedDbInterface& orig);
    virtual ~SeedDbInterface();
    QString TestQuery();
    
    QString SaveCounterConfig(DFG2Counter);
    QString LoadCounterConfig(DFG2Counter&);
    QString PopulateDbVariables();
    int GetTeach();
    int GetResponseSpeed();
    int GetOffsetPercent();
    int GetButtonLock();
    int GetTotalCounts();
    int GetTotalOneShot();
    int GetDynamicEventStretch(); 
public:
    DFG2Counter m_Counter; 
        
private:
    int Teach;
    int ResponseSpeed;
    int OffsetPercent;
    int ButtonLock;
    int TotalCounts;
    int TotalOneShot;
    int DynamicEventStretch;    
};

#endif /* SEEDDBINTERFACE_H */

