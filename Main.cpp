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
    if(login.exec() == QDialog::Accepted)
    {
        MainWindow* w = new MainWindow;
        w->setObjectName("main_window");
        w->show();
        w->resize(1050,601);
        w->resize(1050,600);

        int re = app.exec();
        if(NULL != w)
            delete w,w = NULL;
        return re;
    }

    return 0;
}
