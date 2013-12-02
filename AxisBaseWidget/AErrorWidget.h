#ifndef AERRORWIDGET_H
#define AERRORWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>
#include <QMessageBox>

class AErrorWidget : public QWidget
{
    Q_OBJECT

    enum LifeStatus{
        BORNING        = 0,
        LIVING            ,
        DYING
    };

public:
    ~AErrorWidget();

    static void warning(QWidget* parent,
                        const QString& msg,
                        const QPixmap& icon = QPixmap(":/Resource/Img/AxisBaseWidget/warning.png"),
                        int live_time_ms = 2000);

    static void information(QWidget* parent,
                        const QString& msg,
                        const QPixmap& icon = QPixmap(":/Resource/Img/AxisBaseWidget/information.png"),
                        int live_time_ms = 2000);


    void setTipInfo(const QString& info);
    void setTipIcon(const QPixmap& pixmap);

protected:
    void paintEvent(QPaintEvent* event);
protected slots:
    //关闭按钮主要进行提示框的隐藏
    void CloseWidget();
    void OnAnimationFinish();
signals:

private:
    explicit AErrorWidget(QWidget *parent,int life_time_ms);
private:
    QToolButton* close_button_;
    QLabel* icon_label_;
    QLabel* ask_label_;
    
    int parent_height_;  //父窗口高
    int parent_width_;   ////父窗口宽

    LifeStatus life_;
    int life_time_;         ////存活时间，默认2秒
    QTimer* destroy_time_;
    QPropertyAnimation* animation_;
};

#endif // AERRORWIDGET_H
