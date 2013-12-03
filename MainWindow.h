#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <windows.h>
#include <windowsx.h>

#include <QMainWindow>
#include <QMap>
#include <QPropertyAnimation>

#include "./WorkScene/IWorkScene.h"
#include "./Tray/Tray.h"
#include "./Tray/TrayIconMenu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void ChangeWorkScene(const QString& workName);  ////切换工作场景

private:
    void InitView();
    void InitTitle();
    void InitTray();        ////初始化托盘
    void drawWindowShadow(QPainter &p);

    bool AddWorkScene(const QString& name,IWorkScene* scene);    ////添加工作场景

private slots:
    void Close();

protected:
    void paintEvent(QPaintEvent* event);
    void closeEvent(QCloseEvent* event);
    void showEvent(QShowEvent* event);

    bool winEvent(MSG *message, long *result);
private:
    Ui::MainWindow *ui;
    QMap<QString,IWorkScene*> wrokScenes;

    QPropertyAnimation* animation_;

    Tray* tray;                 ////托盘
    TrayIconMenu* trayMenu;      ////托盘菜单栏

};

#endif // MAINWINDOW_H
