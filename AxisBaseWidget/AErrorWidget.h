#ifndef AERRORWIDGET_H
#define AERRORWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>

class AErrorWidget : public QWidget
{
    Q_OBJECT

    enum LifeStatus{
        BORNING        = 0,
        LIVING            ,
        DYING
    };

public:
    explicit AErrorWidget(QWidget *parent = 0);
    ~AErrorWidget();

    void setTipInfo(QString info);
    void setTipIcon(QPixmap pixmap);
protected slots:
    //关闭按钮主要进行提示框的隐藏
    void CloseWidget();
    void OnAnimationFinish();
signals:
    


private:
    QToolButton* close_button_;
    QLabel* msg_label_;
    QLabel* ask_label_;
    
    int parent_height_;  //父窗口高
    int parent_width_;   ////父窗口宽

    LifeStatus life_;
    int life_time_;         ////存活时间，默认2秒
    QTimer* destroy_time_;
    QPropertyAnimation* animation_;
};

#endif // AERRORWIDGET_H
