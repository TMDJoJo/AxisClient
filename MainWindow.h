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
#include "./Logo/LogoScene.h"
#include "./Navigation/navigation.h"

class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void ChangeWorkScene(const QString& workName);  ////切换工作场景

private:
    void InitUi();
    void InitWorkScene();
    void InitTitle();
    void InitTray();        ////初始化托盘
    void drawWindowShadow(QPainter &p);

    bool AddWorkScene(const QString& name,IWorkScene* scene);    ////添加工作场景

private slots:
    void Close();
    void Mail();
    void MaxOrNormal();
protected:
    void paintEvent(QPaintEvent* event);
    void closeEvent(QCloseEvent* event);
    void showEvent(QShowEvent* event);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    bool winEvent(MSG *message, long *result);
private:

    QMap<QString,IWorkScene*> wrokScenes;

    QPropertyAnimation* animation_;

    QGridLayout* grid_layout_;
    LogoScene* logo_;
    QWidget* main_window_title_;
    Navigation* navigation_;
    QStackedWidget* stacked_widget_;

    Tray* tray_;                 ////托盘
    TrayIconMenu* tray_menu_;      ////托盘菜单栏

    QToolButton* tool_button_max_;
    QToolButton* tool_button_normal_;

    bool		moveing_;//鼠标按下
    QPoint	    move_position_;  //移动的距离
};

#endif // MAINWINDOW_H
