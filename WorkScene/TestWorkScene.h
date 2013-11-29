#ifndef TESTWORKSCENE_H
#define TESTWORKSCENE_H

#include <QWidget>
#include "./IWorkScene.h"
namespace Ui {
class TestWorkScene;
}

class TestWorkScene : public IWorkScene
{
    Q_OBJECT
    
public:
    explicit TestWorkScene(const QString& name,QWidget *parent = 0);
    ~TestWorkScene();
    void SetText(const QString str);
private:
    Ui::TestWorkScene *ui;
};

#endif // TESTWORKSCENE_H
