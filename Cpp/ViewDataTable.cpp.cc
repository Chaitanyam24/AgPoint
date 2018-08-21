/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ViewDataTable.cpp
 * Author: SHALAKHA
 *
 * Created on December 5, 2017, 9:34 AM
 */

#include "ViewDataTable.h"

ViewDataTable::ViewDataTable() {
    widget.setupUi(this);

    widget.btnHome->setStyleSheet("background-color:white;");
    connect(widget.btnHome, SIGNAL(pressed()), this, SLOT(ExitScreen()));
    widget.tableWidget->setColumnCount(6);
    widget.tableWidget->setHorizontalHeaderLabels(QStringList() << "Lot Code" << "Product ID" <<"Date" <<"Time" << "Count"<<"Bag");
    widget.tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
   
    QFile file("/var/www/html/WebSeedData.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd()) {
        QString line = file.readLine();
        process_line(line);
    }
}

ViewDataTable::~ViewDataTable() {
}

void ViewDataTable::process_line(QString line)
{
    widget.tableWidget->insertRow(widget.tableWidget->rowCount());
    QStringList ss = line.split(',');
    for( int column = 0; column < ss.size(); column++)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem( ss.at(column) );
        widget.tableWidget->setItem( widget.tableWidget->rowCount()-1, column, newItem);
    }   
}

void ViewDataTable::ExitScreen(){
    close();
}