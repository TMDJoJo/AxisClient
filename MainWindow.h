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

    void ChangeWorkScene(const QString& workName);  ////�л���������

private:
    void InitUi();
    void InitWorkScene();
    void InitTitle();
    void InitTray();        ////��ʼ������
    void drawWindowShadow(QPainter &p);

    bool AddWorkScene(const QString& name,IWorkScene* scene);    ////��ӹ�������

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

    Tray* tray_;                 ////����
    TrayIconMenu* tray_menu_;      ////���̲˵���

    QToolButton* tool_button_max_;
    QToolButton* tool_button_normal_;

    bool		moveing_;//��갴��
    QPoint	    move_position_;  //�ƶ��ľ���
};

#endif // MAINWINDOW_H
