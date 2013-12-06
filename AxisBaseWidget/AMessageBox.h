#ifndef AMESSAGEBOX_H
#define AMESSAGEBOX_H

#include <QMessageBox>

class AMessageBox : public QMessageBox
{
    Q_OBJECT
public:
    explicit AMessageBox(QWidget *parent = 0);
    
private:
    void InitUi();

signals:
    
public slots:
    
};

#endif // AMESSAGEBOX_H
