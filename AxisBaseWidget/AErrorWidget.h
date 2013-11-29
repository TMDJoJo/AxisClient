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
    //�رհ�ť��Ҫ������ʾ�������
    void CloseWidget();
    void OnAnimationFinish();
signals:
    


private:
    QToolButton* close_button_;
    QLabel* msg_label_;
    QLabel* ask_label_;
    
    int parent_height_;  //�����ڸ�
    int parent_width_;   ////�����ڿ�

    LifeStatus life_;
    int life_time_;         ////���ʱ�䣬Ĭ��2��
    QTimer* destroy_time_;
    QPropertyAnimation* animation_;
};

#endif // AERRORWIDGET_H
