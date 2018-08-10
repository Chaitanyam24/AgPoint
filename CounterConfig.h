/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CounterConfig.h
 * Author: Dan
 *
 * Created on March 14, 2017, 5:29 AM
 */

#ifndef _COUNTERCONFIG_H
#define _COUNTERCONFIG_H

#include "ui_CounterConfig.h"
#include "DFG2Counter.h"
#include <QDialog>
class CounterConfig : public QDialog {
    Q_OBJECT
public:
    CounterConfig();
    virtual ~CounterConfig();
    bool GetSeedProgramStatus();
    DFG2Counter m_Counter;
    bool ProgramConfig;
    
private:
    Ui::CounterConfig widget;
    
    
private:    // Methods
    void PopulateControls();
    
    
public slots:
    void ExitProgram();
    void ProgramAllCounterSettings();
    void CalibrateCounter();
    void DefaultValues();
    void TeachChanged(int index);
    void ResponseSpeedChanged(int index);
    void OffsetPercentChanged(int index);
    void ButtonLockChanged(int index);
    void TotalCountsChanged(int index);
    void TotalOneShotChanged(int index);
    void DynamicEventStretchChanged(int index);
    void SelectCurrentItemsInCombos();
    void CallProgramAllCounterSettings();
    
};

#endif /* _COUNTERCONFIG_H */
