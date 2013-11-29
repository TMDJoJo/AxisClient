#ifndef IWORKSCENE_H
#define IWORKSCENE_H

#include <QWidget>

class IWorkScene : public QWidget
{
    Q_OBJECT
public:
    explicit IWorkScene(const QString& name,QWidget *parent = 0);
    inline const QString GetSceneName(){return sceneName;}
signals:
    
public slots:

private:
    QString sceneName;  ////������������
};

#endif // IWORKSCENE_H
