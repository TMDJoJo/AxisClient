#include "WelcomeScene.h"
#include "ui_WelcomeScene.h"

WelcomeScene::WelcomeScene(const QString& name,IWorkScene *parent) :
    IWorkScene(name,parent),
    ui(new Ui::WelcomeScene)
{
    ui->setupUi(this);
    ui->webView->load(QUrl("http://www.baidu.com"));
    ui->webView->show();
}

WelcomeScene::~WelcomeScene()
{
    delete ui;
}
