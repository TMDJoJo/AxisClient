#include "IWorkScene.h"

IWorkScene::IWorkScene(const QString& name,QWidget *parent) :
    QWidget(parent),
    sceneName(name)
{
}
