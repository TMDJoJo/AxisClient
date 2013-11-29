#ifndef AERRORWIDGET_H
#define AERRORWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QLabel>

class AErrorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AErrorWidget(QWidget *parent = 0);
    ~AErrorWidget();

    void setTipInfo(QString info);
    void setTipIcon(QPixmap pixmap);
protected slots:
    //�رհ�ť��Ҫ������ʾ�������
    bool closeWidget();

signals:
    


private:
    QToolButton* closeButton;
    QLabel* msgLabel;
    QLabel* askLabel;
    
};

#endif // AERRORWIDGET_H
