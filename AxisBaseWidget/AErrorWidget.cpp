#include "AErrorWidget.h"
#include <QPixmap>
#include <QStyle>
#include <QDebug>

AErrorWidget::AErrorWidget(QWidget *parent) :
    QWidget(parent)
{
    int width = parent->width();
    //this->resize(width, 28);
    //设置标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint);
    //设置背景色透明
    QPalette palette;
    QColor color(190, 230, 250);
    color.setAlphaF(0.6);
    palette.setBrush(this->backgroundRole(), color);
    this->setPalette(palette);
    //如果这个QWidget直接show，是有背景色的，但是如果放到一个父Widget中时，它就没有了效果。添加如下代码后就可以了：
    this->setAutoFillBackground(true);

    //构建关闭按钮
    closeButton= new QToolButton(this);
    QPixmap close_pix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    closeButton->setIcon(close_pix);
    closeButton->setStyleSheet("QToolButton{background-color: transparent;}");

    //获取主界面的宽度
    int height = parent->height();

    closeButton->setGeometry(width-20, 0, 20, 20);
    //设置提示图片
    msgLabel = new QLabel(this);
    msgLabel->setGeometry(QRect(5, 5, 20, 20));
    msgLabel->setStyleSheet("background-color: transparent;");
    msgLabel->setScaledContents(true);
    //设置提示信息
    askLabel = new QLabel(this);
    askLabel->setStyleSheet("background-color: transparent; color:#EE4545;");
    askLabel->setGeometry( QRect( 10, 0, width - 10, 40 ) );
    askLabel->setAlignment(Qt::AlignCenter);

    askLabel->setText("aaaaa");

    closeButton->setCursor(Qt::PointingHandCursor);
    QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(closeWidget()));

    setGeometry(QRect(0,height-40,width,40));
}
AErrorWidget::~AErrorWidget(){
    if(msgLabel == NULL)
        delete msgLabel,msgLabel = NULL;
    if(closeButton == NULL)
        delete closeButton,closeButton = NULL;
    if(askLabel == NULL)
        delete askLabel,askLabel = NULL;

}
void AErrorWidget::setTipInfo(QString info)
{
    //设置提示信息
    askLabel->setText(info);
}

void AErrorWidget::setTipIcon(QPixmap pixmap)
{
    msgLabel->setPixmap(pixmap);
}

//关闭按钮主要进行提示框的隐藏
bool AErrorWidget::closeWidget()
{
    this->hide();
    return true;
}
