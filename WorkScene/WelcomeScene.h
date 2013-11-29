#ifndef WELCOMESCENE_H
#define WELCOMESCENE_H

#include <QWidget>
#include <QtWebKit/QWebView>
#include "./IWorkScene.h"


namespace Ui {
class WelcomeScene;
}

class WelcomeScene : public IWorkScene
{
    Q_OBJECT
    
public:
    explicit WelcomeScene(const QString& name,IWorkScene *parent = 0);
    ~WelcomeScene();
    
private:
    Ui::WelcomeScene *ui;
};

#endif // WELCOMESCENE_H
