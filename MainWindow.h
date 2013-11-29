#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

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
    void ViewInit();
    void DataInit();
    void TrayInit();        ////初始化托盘

    bool AddWorkScene(const QString& name,IWorkScene* scene);    ////添加工作场景

protected:
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QMap<QString,IWorkScene*> wrokScenes;


    Tray* tray;                 ////托盘
    TrayIconMenu* trayMenu;      ////托盘菜单栏

};

#endif // MAINWINDOW_H
