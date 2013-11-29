#ifndef TRAY_H
#define TRAY_H

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMainWindow>

class Tray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit Tray(QObject *parent = 0);
    
    void SetMainWindow(QMainWindow* main);
private:
    void Init();
private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    
public slots:
    
private:
    QMenu *trayIconMenu;

    QMainWindow* mainScene;
};

#endif // TRAY_H
