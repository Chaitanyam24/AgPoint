/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Keypad.h
 * Author: SHALAKHA
 *
 * Created on December 3, 2017, 8:25 PM
 */

#ifndef _KEYPAD_H
#define _KEYPAD_H

#include "ui_Keypad.h"
#include <stdio.h>
#include <QString>
#include <QDialog>
class Keypad : public QDialog {
    Q_OBJECT
public:
    Keypad();
    virtual ~Keypad();
private:
    Ui::Keypad widget;

private:
    void KeyPressed(QString);
    void ExitToHomeWindow();
    QString m_Input;
    bool InputCaps;
    
public slots:
    void KeyPressed0();
    void KeyPressed1();
    void KeyPressed2();
    void KeyPressed3();
    void KeyPressed4();
    void KeyPressed5();
    void KeyPressed6();
    void KeyPressed7();
    void KeyPressed8();
    void KeyPressed9();
    void KeyPressedEnter();
    void KeyPressedClear();
    void KeyPressedSpace();
    void ChangeCaps();
    void KeyPresseda();
    void KeyPressedb();
    void KeyPressedc();
    void KeyPressedd();
    void KeyPressede();
    void KeyPressedf();
    void KeyPressedg();
    void KeyPressedh();
    void KeyPressedi();
    void KeyPressedj();
    void KeyPressedk();
    void KeyPressedl();
    void KeyPressedm();
    void KeyPressedn();
    void KeyPressedo();
    void KeyPressedp();
    void KeyPressedq();
    void KeyPressedr();
    void KeyPresseds();
    void KeyPressedt();
    void KeyPressedu();
    void KeyPressedv();
    void KeyPressedw();
    void KeyPressedx();
    void KeyPressedy();
    void KeyPressedz();
    QString GetInputValue();
    void KeyPressed11();
    void KeyPressed12();
    void KeyPressed13();
    void KeyPressed21();
    void KeyPressed22();
    void KeyPressed23();
    void KeyPressed31();
    void KeyPressed32();
    void KeyPressed33();
    void KeyPressed34();
    void KeyPressed41();
    void KeyPressed42();
    void KeyPressed43();
    void KeyPressed44();
    void KeyPressed45();
    void KeyPressed46();
    void KeyPressed51();
    void KeyPressed52();
    void KeyPressed53();
    void KeyPressed54();
    void KeyPressed55();
    void KeyPressed56();
    void KeyPressed57();
    void KeyPressed58();
    void KeyPressed59();
    void KeyPressed510();
    void KeyPressed511();
    void KeyPressed512();    
};

#endif /* _KEYPAD_H */
