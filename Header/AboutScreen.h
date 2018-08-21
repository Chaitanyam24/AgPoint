/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AboutScreen.h
 * Author: SHALAKHA
 *
 * Created on November 3, 2017, 10:29 AM
 */

#ifndef _ABOUTSCREEN_H
#define _ABOUTSCREEN_H

#include "ui_AboutScreen.h"
#include <QString>
#include <QDialog>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <stdio.h>

class AboutScreen : public QDialog {
    Q_OBJECT
public:
    AboutScreen();
    virtual ~AboutScreen();
private:
    Ui::AboutScreen widget;
    void GetSerialNumberFromFile();
    QString SerialNumber;

private slots:
    void ExitToHomeScreen();
};

#endif /* _ABOUTSCREEN_H */
