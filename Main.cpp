#include <QMainWindow>
#include <QApplication>
#include <QTextCodec>

#include "./Login/LoginScene.h"
#include "./MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile file("Resource/QSS/Theme.css");
    if (file.open(QIODevice::ReadOnly))
    {
        qApp->setStyleSheet(file.readAll());
    }
    file.close();

    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));

    LoginScene login;
    login.setObjectName("LoginScene");

    if(login.exec() == QDialog::Accepted)
    {
        MainWindow w;
        w.setObjectName("main_window");
        w.show();
        w.resize(1050,601);
        w.resize(1050,600);
        return app.exec();
    }
    return 0;
}
