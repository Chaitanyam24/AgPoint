/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ViewDataTable.h
 * Author: SHALAKHA
 *
 * Created on December 5, 2017, 9:34 AM
 */

#ifndef _VIEWDATATABLE_H
#define _VIEWDATATABLE_H

#include "ui_ViewDataTable.h"
#include <QFile>
#include <QTableWidget>

class ViewDataTable : public QDialog {
    Q_OBJECT
public:
    ViewDataTable();
    virtual ~ViewDataTable();
private:
    Ui::ViewDataTable widget;
    void process_line(QString);
    
public slots:
    void ExitScreen();
};

#endif /* _VIEWDATATABLE_H */
