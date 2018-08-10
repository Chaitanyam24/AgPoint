/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Keypad.cpp
 * Author: SHALAKHA
 *
 * Created on December 3, 2017, 8:25 PM
 */

#include "Keypad.h"
#include <QTimer>
#include <QMessageBox>
#include <QPixmap>
#include <unistd.h>
#include <string>
#include <QString>

Keypad::Keypad() {
    widget.setupUi(this);
    widget.lblInput->setTextInteractionFlags(Qt::TextSelectableByKeyboard);
    // Sets the dialog's background color.
    setStyleSheet("background-color:black;");
    // Change the background color of the buttons
    widget.btn0->setStyleSheet("background-color:white;");
    widget.btn1->setStyleSheet("background-color:white;");
    widget.btn2->setStyleSheet("background-color:white;");
    widget.btn3->setStyleSheet("background-color:white;");
    widget.btn4->setStyleSheet("background-color:white;");
    widget.btn5->setStyleSheet("background-color:white;");
    widget.btn6->setStyleSheet("background-color:white;");
    widget.btn7->setStyleSheet("background-color:white;");
    widget.btn8->setStyleSheet("background-color:white;");
    widget.btn9->setStyleSheet("background-color:white;");
    widget.btnEnter->setStyleSheet("background-color:white;");
    widget.btnClear->setStyleSheet("background-color:white;");
    widget.btnCaps->setStyleSheet("background-color:white;");
    widget.lblInput->setStyleSheet("background-color:white;");   
    widget.btnA->setStyleSheet("background-color:white;");
    widget.btnB->setStyleSheet("background-color:white;");
    widget.btnC->setStyleSheet("background-color:white;");
    widget.btnD->setStyleSheet("background-color:white;");
    widget.btnE->setStyleSheet("background-color:white;");
    widget.btnF->setStyleSheet("background-color:white;");
    widget.btnG->setStyleSheet("background-color:white;");
    widget.btnH->setStyleSheet("background-color:white;");
    widget.btnI->setStyleSheet("background-color:white;");
    widget.btnJ->setStyleSheet("background-color:white;");
    widget.btnK->setStyleSheet("background-color:white;");
    widget.btnL->setStyleSheet("background-color:white;");
    widget.btnM->setStyleSheet("background-color:white;");
    widget.btnN->setStyleSheet("background-color:white;");
    widget.btnO->setStyleSheet("background-color:white;");
    widget.btnP->setStyleSheet("background-color:white;");
    widget.btnQ->setStyleSheet("background-color:white;");
    widget.btnR->setStyleSheet("background-color:white;");
    widget.btnS->setStyleSheet("background-color:white;");
    widget.btnT->setStyleSheet("background-color:white;");
    widget.btnU->setStyleSheet("background-color:white;");
    widget.btnV->setStyleSheet("background-color:white;");
    widget.btnW->setStyleSheet("background-color:white;");
    widget.btnX->setStyleSheet("background-color:white;");
    widget.btnY->setStyleSheet("background-color:white;");
    widget.btnZ->setStyleSheet("background-color:white;");
    widget.btnSpace->setStyleSheet("background-color:white;");
    //Special symbols
    widget.btn11->setStyleSheet("background-color:white;");
    widget.btn12->setStyleSheet("background-color:white;");
    widget.btn13->setStyleSheet("background-color:white;");
    widget.btn21->setStyleSheet("background-color:white;");
    widget.btn22->setStyleSheet("background-color:white;");
    widget.btn23->setStyleSheet("background-color:white;");
    widget.btn31->setStyleSheet("background-color:white;");
    widget.btn32->setStyleSheet("background-color:white;");
    widget.btn33->setStyleSheet("background-color:white;");
    widget.btn34->setStyleSheet("background-color:white;");
    widget.btn41->setStyleSheet("background-color:white;");
    widget.btn42->setStyleSheet("background-color:white;");
    widget.btn43->setStyleSheet("background-color:white;");
    widget.btn44->setStyleSheet("background-color:white;");
    widget.btn45->setStyleSheet("background-color:white;");
    widget.btn46->setStyleSheet("background-color:white;");
    widget.btn51->setStyleSheet("background-color:white;");
    widget.btn52->setStyleSheet("background-color:white;");
    widget.btn53->setStyleSheet("background-color:white;");
    widget.btn54->setStyleSheet("background-color:white;");
    widget.btn55->setStyleSheet("background-color:white;");
    widget.btn56->setStyleSheet("background-color:white;");
    widget.btn57->setStyleSheet("background-color:white;");
    widget.btn58->setStyleSheet("background-color:white;");
    widget.btn59->setStyleSheet("background-color:white;");
    widget.btn510->setStyleSheet("background-color:white;");
    widget.btn511->setStyleSheet("background-color:white;");
    widget.btn512->setStyleSheet("background-color:white;");
    
    ////////////////////////////////////////////////////////////////////////////
    // Connect signals and slots
    connect(widget.btn0, SIGNAL(pressed()), this, SLOT(KeyPressed0()));
    connect(widget.btn1, SIGNAL(pressed()), this, SLOT(KeyPressed1()));
    connect(widget.btn2, SIGNAL(pressed()), this, SLOT(KeyPressed2()));
    connect(widget.btn3, SIGNAL(pressed()), this, SLOT(KeyPressed3()));
    connect(widget.btn4, SIGNAL(pressed()), this, SLOT(KeyPressed4()));
    connect(widget.btn5, SIGNAL(pressed()), this, SLOT(KeyPressed5()));
    connect(widget.btn6, SIGNAL(pressed()), this, SLOT(KeyPressed6()));
    connect(widget.btn7, SIGNAL(pressed()), this, SLOT(KeyPressed7()));
    connect(widget.btn8, SIGNAL(pressed()), this, SLOT(KeyPressed8()));
    connect(widget.btn9, SIGNAL(pressed()), this, SLOT(KeyPressed9()));
    connect(widget.btnEnter, SIGNAL(pressed()), this, SLOT(KeyPressedEnter()));
    connect(widget.btnClear, SIGNAL(pressed()), this, SLOT(KeyPressedClear()));
    connect(widget.btnSpace, SIGNAL(pressed()), this, SLOT(KeyPressedSpace()));
    connect(widget.btnCaps, SIGNAL(pressed()), this, SLOT(ChangeCaps()));
    widget.btnCaps->setText("Caps On");
    connect(widget.btnA, SIGNAL(pressed()), this, SLOT(KeyPresseda()));
    connect(widget.btnB, SIGNAL(pressed()), this, SLOT(KeyPressedb()));
    connect(widget.btnC, SIGNAL(pressed()), this, SLOT(KeyPressedc()));
    connect(widget.btnD, SIGNAL(pressed()), this, SLOT(KeyPressedd()));
    connect(widget.btnE, SIGNAL(pressed()), this, SLOT(KeyPressede()));
    connect(widget.btnF, SIGNAL(pressed()), this, SLOT(KeyPressedf()));
    connect(widget.btnG, SIGNAL(pressed()), this, SLOT(KeyPressedg()));
    connect(widget.btnH, SIGNAL(pressed()), this, SLOT(KeyPressedh()));
    connect(widget.btnI, SIGNAL(pressed()), this, SLOT(KeyPressedi()));
    connect(widget.btnJ, SIGNAL(pressed()), this, SLOT(KeyPressedj()));
    connect(widget.btnK, SIGNAL(pressed()), this, SLOT(KeyPressedk()));
    connect(widget.btnL, SIGNAL(pressed()), this, SLOT(KeyPressedl()));
    connect(widget.btnM, SIGNAL(pressed()), this, SLOT(KeyPressedm()));
    connect(widget.btnN, SIGNAL(pressed()), this, SLOT(KeyPressedn()));
    connect(widget.btnO, SIGNAL(pressed()), this, SLOT(KeyPressedo()));
    connect(widget.btnP, SIGNAL(pressed()), this, SLOT(KeyPressedp()));
    connect(widget.btnQ, SIGNAL(pressed()), this, SLOT(KeyPressedq()));
    connect(widget.btnR, SIGNAL(pressed()), this, SLOT(KeyPressedr()));
    connect(widget.btnS, SIGNAL(pressed()), this, SLOT(KeyPresseds()));
    connect(widget.btnT, SIGNAL(pressed()), this, SLOT(KeyPressedt()));
    connect(widget.btnU, SIGNAL(pressed()), this, SLOT(KeyPressedu()));
    connect(widget.btnV, SIGNAL(pressed()), this, SLOT(KeyPressedv()));
    connect(widget.btnW, SIGNAL(pressed()), this, SLOT(KeyPressedw()));
    connect(widget.btnX, SIGNAL(pressed()), this, SLOT(KeyPressedx()));
    connect(widget.btnY, SIGNAL(pressed()), this, SLOT(KeyPressedy()));
    connect(widget.btnZ, SIGNAL(pressed()), this, SLOT(KeyPressedz()));
    
    connect(widget.btn11, SIGNAL(pressed()), this, SLOT(KeyPressed11()));
    connect(widget.btn12, SIGNAL(pressed()), this, SLOT(KeyPressed12()));
    connect(widget.btn13, SIGNAL(pressed()), this, SLOT(KeyPressed13()));
    connect(widget.btn21, SIGNAL(pressed()), this, SLOT(KeyPressed21()));
    connect(widget.btn22, SIGNAL(pressed()), this, SLOT(KeyPressed22()));
    connect(widget.btn23, SIGNAL(pressed()), this, SLOT(KeyPressed23()));
    connect(widget.btn31, SIGNAL(pressed()), this, SLOT(KeyPressed31()));
    connect(widget.btn32, SIGNAL(pressed()), this, SLOT(KeyPressed32()));
    connect(widget.btn33, SIGNAL(pressed()), this, SLOT(KeyPressed33()));
    connect(widget.btn34, SIGNAL(pressed()), this, SLOT(KeyPressed34()));
    connect(widget.btn41, SIGNAL(pressed()), this, SLOT(KeyPressed41()));
    connect(widget.btn42, SIGNAL(pressed()), this, SLOT(KeyPressed42()));
    connect(widget.btn43, SIGNAL(pressed()), this, SLOT(KeyPressed43()));
    connect(widget.btn44, SIGNAL(pressed()), this, SLOT(KeyPressed44()));
    connect(widget.btn45, SIGNAL(pressed()), this, SLOT(KeyPressed45()));
    connect(widget.btn46, SIGNAL(pressed()), this, SLOT(KeyPressed46()));
    connect(widget.btn51, SIGNAL(pressed()), this, SLOT(KeyPressed51()));
    connect(widget.btn52, SIGNAL(pressed()), this, SLOT(KeyPressed52()));
    connect(widget.btn53, SIGNAL(pressed()), this, SLOT(KeyPressed53()));
    connect(widget.btn54, SIGNAL(pressed()), this, SLOT(KeyPressed54()));
    connect(widget.btn55, SIGNAL(pressed()), this, SLOT(KeyPressed55()));
    connect(widget.btn56, SIGNAL(pressed()), this, SLOT(KeyPressed56()));
    connect(widget.btn57, SIGNAL(pressed()), this, SLOT(KeyPressed57()));
    connect(widget.btn58, SIGNAL(pressed()), this, SLOT(KeyPressed58()));
    connect(widget.btn59, SIGNAL(pressed()), this, SLOT(KeyPressed59()));
    connect(widget.btn510, SIGNAL(pressed()), this, SLOT(KeyPressed510()));
    connect(widget.btn511, SIGNAL(pressed()), this, SLOT(KeyPressed511()));
    connect(widget.btn512, SIGNAL(pressed()), this, SLOT(KeyPressed512()));
    m_Input="";
    InputCaps=false;
    widget.btnCaps->setText("Caps OFF");
    widget.lblInput->setText(m_Input);
}

Keypad::~Keypad() {
}


void Keypad::KeyPressed(QString key)
{
    if(QString("10") == key)
    {
        accept();
        
    }
    else if(QString("11") == key)
    {       
        m_Input = "";    // Clear setpoint value
        widget.lblInput->setText(m_Input);
        
    }
    else
    {
        if(InputCaps==true) { m_Input += key; }
        else{ m_Input += key.toLower();}
        
        widget.lblInput->setText(m_Input); 
    }

}

void Keypad::KeyPressed0(){ KeyPressed("0"); }
void Keypad::KeyPressed1(){ KeyPressed("1"); }
void Keypad::KeyPressed2(){ KeyPressed("2"); }
void Keypad::KeyPressed3(){ KeyPressed("3"); }
void Keypad::KeyPressed4(){ KeyPressed("4"); }
void Keypad::KeyPressed5(){ KeyPressed("5"); }
void Keypad::KeyPressed6(){ KeyPressed("6"); }
void Keypad::KeyPressed7(){ KeyPressed("7"); }
void Keypad::KeyPressed8(){ KeyPressed("8"); }
void Keypad::KeyPressed9(){ KeyPressed("9"); }

void Keypad::KeyPressedEnter(){ KeyPressed("10"); }
void Keypad::KeyPressedClear(){ KeyPressed("11"); }
void Keypad::KeyPressedSpace(){ KeyPressed(" "); }

void Keypad::KeyPresseda(){ KeyPressed("A"); }
void Keypad::KeyPressedb(){ KeyPressed("B"); }
void Keypad::KeyPressedc(){ KeyPressed("C"); }
void Keypad::KeyPressedd(){ KeyPressed("D"); }
void Keypad::KeyPressede(){ KeyPressed("E"); }
void Keypad::KeyPressedf(){ KeyPressed("F"); }
void Keypad::KeyPressedg(){ KeyPressed("G"); }
void Keypad::KeyPressedh(){ KeyPressed("H"); }
void Keypad::KeyPressedi(){ KeyPressed("I"); }
void Keypad::KeyPressedj(){ KeyPressed("J"); }
void Keypad::KeyPressedk(){ KeyPressed("K"); }
void Keypad::KeyPressedl(){ KeyPressed("L"); }
void Keypad::KeyPressedm(){ KeyPressed("M"); }
void Keypad::KeyPressedn(){ KeyPressed("N"); }
void Keypad::KeyPressedo(){ KeyPressed("O"); }
void Keypad::KeyPressedp(){ KeyPressed("P"); }
void Keypad::KeyPressedq(){ KeyPressed("Q"); }
void Keypad::KeyPressedr(){ KeyPressed("R"); }
void Keypad::KeyPresseds(){ KeyPressed("S"); }
void Keypad::KeyPressedt(){ KeyPressed("T"); }
void Keypad::KeyPressedu(){ KeyPressed("U"); }
void Keypad::KeyPressedv(){ KeyPressed("V"); }
void Keypad::KeyPressedw(){ KeyPressed("W"); }
void Keypad::KeyPressedx(){ KeyPressed("X"); }
void Keypad::KeyPressedy(){ KeyPressed("Y"); }
void Keypad::KeyPressedz(){ KeyPressed("Z"); }

void Keypad::KeyPressed11(){ KeyPressed("!"); }
void Keypad::KeyPressed12(){ KeyPressed("@"); }
void Keypad::KeyPressed13(){ KeyPressed("'"); }
void Keypad::KeyPressed21(){ KeyPressed("#"); }
void Keypad::KeyPressed22(){ KeyPressed("$"); }
void Keypad::KeyPressed23(){ KeyPressed("|"); }
void Keypad::KeyPressed31(){ KeyPressed("&"); }
void Keypad::KeyPressed32(){ KeyPressed("%"); }
void Keypad::KeyPressed33(){ KeyPressed("<"); }
void Keypad::KeyPressed34(){ KeyPressed(">"); }
void Keypad::KeyPressed41(){ KeyPressed("?"); }
void Keypad::KeyPressed42(){ KeyPressed("~"); }
void Keypad::KeyPressed43(){ KeyPressed("-"); }
void Keypad::KeyPressed44(){ KeyPressed("_"); }
void Keypad::KeyPressed45(){ KeyPressed("^"); }
void Keypad::KeyPressed46(){ KeyPressed("/"); }
void Keypad::KeyPressed51(){ KeyPressed("("); }
void Keypad::KeyPressed52(){ KeyPressed(")"); }
void Keypad::KeyPressed53(){ KeyPressed("'"); }
void Keypad::KeyPressed54(){ KeyPressed(","); }
void Keypad::KeyPressed55(){ KeyPressed("."); }
void Keypad::KeyPressed56(){ KeyPressed(";"); }
void Keypad::KeyPressed57(){ KeyPressed(":"); }
void Keypad::KeyPressed58(){ KeyPressed("*"); }
void Keypad::KeyPressed59(){ KeyPressed("+"); }
void Keypad::KeyPressed510(){ KeyPressed("["); }
void Keypad::KeyPressed511(){ KeyPressed("]"); }
void Keypad::KeyPressed512(){ KeyPressed("="); }

void Keypad::ExitToHomeWindow(){ close();}
QString Keypad::GetInputValue(){ return m_Input;}

void Keypad::ChangeCaps() { 
    if(InputCaps==true){ 
        InputCaps=false;
        widget.btnCaps->setText("Caps OFF");
    }
    else{
        InputCaps=true;
        widget.btnCaps->setText("Caps ON");
    }
}