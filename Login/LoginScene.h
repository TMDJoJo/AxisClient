#ifndef LOGINSCENE_H
#define LOGINSCENE_H

#include <QDialog>
#include <QMouseEvent>
#include <QPropertyAnimation>

namespace Ui {
class LoginScene;
}

class LoginScene : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoginScene(QWidget *parent = 0);
    ~LoginScene();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    void CreateScene();
    void createTitleBar();
private slots:
    void doToolButtonSet();
    void doToolButtonClose();
    void on_pbtn_login_clicked();

private:
    Ui::LoginScene *ui;
    QPropertyAnimation* animation_;

    bool		mMoveing;//鼠标按下
    QPoint	    mMovePosition;  //移动的距离
    //AErrorWidget w;
};

#endif // LOGINSCENE_H
