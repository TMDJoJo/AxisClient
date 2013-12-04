#ifndef NAVIGATION_H
#define NAVIGATION_H
#include <QScrollArea>
#include <QPushButton>

#include <QVariant>

#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>

#include "mytableView.h"

class MainWindow;

class Navigation : public QScrollArea
{
    Q_OBJECT
    
public:
    Navigation(QWidget *parent = 0);

    bool Init(MainWindow* main);
    void addNavigationBar(const QString &barname,QIcon &barIcon,QStringList &list);
    void addVerticalSpacer();
    virtual ~Navigation();

protected:
    void resizeEvent(QResizeEvent *);
private:
    void addNavigationList(QStringList &list);
    void updateView(int width);
signals:
    void label(int,int);
private slots:
    void setViewDisplay(); 
    void clearSelection();
    void information(QModelIndex);

private:
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *verticalSpacer;
    QList<QPushButton *> buttonGroup;
    QList<MyTableView *> tableGroup;

    MainWindow* mainWidget;
    bool isInit;
};

#endif // NAVIGATION_H
