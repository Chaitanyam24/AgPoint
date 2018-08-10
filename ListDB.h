/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListDB.h
 * Author: SHALAKHA
 *
 * Created on September 30, 2017, 8:32 PM
 */

#ifndef LISTDB_H
#define LISTDB_H

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
#include <QMessageBox>


// Defines
#define COM_MYSQL_DB "raspberry"
#define COM_TABLE "seedinfo"
#define COMMODITY_DATABASE "seedlist"
#define TABLE_COLUMNS "teach,responsespeed,offsetpercent,buttonlock,totalcounts,totaloneshot,dynamiceventstretch"

class ListDB {
public:
    ListDB();
    virtual ~ListDB();
        
    QString LoadSelectedSeed(int SeedId);
    QString DeleteCounterConfig();
    QString TestQuery();

    
};

#endif /* LISTDB_H */

