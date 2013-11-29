#include "TestWorkScene.h"
#include "ui_TestWorkScene.h"

TestWorkScene::TestWorkScene(const QString& name,QWidget *parent) :
    IWorkScene(name,parent),
    ui(new Ui::TestWorkScene)
{
    ui->setupUi(this);
}

TestWorkScene::~TestWorkScene()
{
    delete ui;
}

void TestWorkScene::SetText(const QString str){
    ui->label->setText(str);
}
