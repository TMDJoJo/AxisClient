#include "AErrorWidget.h"
#include <QPixmap>
#include <QStyle>
#include <QDebug>

AErrorWidget::AErrorWidget(QWidget *parent) :
    QWidget(parent)
{
    int width = parent->width();
    //this->resize(width, 28);
    //���ñ���������
    this->setWindowFlags(Qt::FramelessWindowHint);
    //���ñ���ɫ͸��
    QPalette palette;
    QColor color(190, 230, 250);
    color.setAlphaF(0.6);
    palette.setBrush(this->backgroundRole(), color);
    this->setPalette(palette);
    //������QWidgetֱ��show�����б���ɫ�ģ���������ŵ�һ����Widget��ʱ������û����Ч����������´����Ϳ����ˣ�
    this->setAutoFillBackground(true);

    //�����رհ�ť
    closeButton= new QToolButton(this);
    QPixmap close_pix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    closeButton->setIcon(close_pix);
    closeButton->setStyleSheet("QToolButton{background-color: transparent;}");

    //��ȡ������Ŀ��
    int height = parent->height();

    closeButton->setGeometry(width-20, 0, 20, 20);
    //������ʾͼƬ
    msgLabel = new QLabel(this);
    msgLabel->setGeometry(QRect(5, 5, 20, 20));
    msgLabel->setStyleSheet("background-color: transparent;");
    msgLabel->setScaledContents(true);
    //������ʾ��Ϣ
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
    //������ʾ��Ϣ
    askLabel->setText(info);
}

void AErrorWidget::setTipIcon(QPixmap pixmap)
{
    msgLabel->setPixmap(pixmap);
}

//�رհ�ť��Ҫ������ʾ�������
bool AErrorWidget::closeWidget()
{
    this->hide();
    return true;
}
