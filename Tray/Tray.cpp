#include "Tray.h"
#include <QApplication>

Tray::Tray(QObject *parent) :
    QSystemTrayIcon(parent),
    trayIconMenu(NULL),
    mainScene(NULL)
{
    Init();
}

void Tray::Init(){

    setIcon(QIcon(":/Tray/Resource/Img/Tray/tray_icon.png"));
    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void Tray::iconActivated(QSystemTrayIcon::ActivationReason reason){
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        Q_ASSERT(mainScene);
        ////������ΪTray����QMainWindow,������С�����̺󲻿��ٴ���ʾ
        ////����QMainWindow�е���void Tray::SetMainWindow(QMainWindow* main)
        if( mainScene->isHidden() ){
            emit mainScene->show();
        }
        break;
    default:
        ;
    }
}

void Tray::SetMainWindow(QMainWindow* main){
    Q_ASSERT(main);
    mainScene = main;
}
