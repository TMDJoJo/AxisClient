#ifndef LOGOSCENE_H
#define LOGOSCENE_H

#include <QWidget>
#include <QMouseEvent>

class MainWindow;

namespace Ui {
class LogoScene;
}

class LogoScene : public QWidget
{
    Q_OBJECT
    
public:
    explicit LogoScene(QWidget *parent = 0);
    bool Init(MainWindow* main);
    ~LogoScene();

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

private:
    Ui::LogoScene *ui;

    MainWindow* main_widget_;
    bool isInit;
};

#endif // LOGOSCENE_H
