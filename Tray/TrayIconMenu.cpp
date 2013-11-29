#include "TrayIconMenu.h"
#include <QAction>
#include <QApplication>

TrayIconMenu::TrayIconMenu(QWidget *parent) :
    QMenu(parent)
{
    Init();
}

void TrayIconMenu::Init(){

    QAction* openAction = new QAction(tr("&Open"), this);
    this->addAction(openAction);

    QAction* openAction1 = new QAction(tr("&Open1"), this);
    this->addAction(openAction1);

    QAction* openAction11 = new QAction(tr("&Open11"), this);
    this->addAction(openAction11);

    this->addSeparator();

    QAction* quitAction = new QAction(tr("&Quit"), this);
    this->addAction(quitAction);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}
