#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

    void ChangeWorkScene(const QString& workName);  ////�л���������

private:
    void InitView();
    void InitData();
    void InitTray();        ////��ʼ������

    bool AddWorkScene(const QString& name,IWorkScene* scene);    ////��ӹ�������

protected:
    void paintEvent(QPaintEvent* event);
    void closeEvent(QCloseEvent* event);
    void showEvent(QShowEvent* event);

private:
    Ui::MainWindow *ui;
    QMap<QString,IWorkScene*> wrokScenes;

    QPropertyAnimation* animation_;

    Tray* tray;                 ////����
    TrayIconMenu* trayMenu;      ////���̲˵���

};

#endif // MAINWINDOW_H
