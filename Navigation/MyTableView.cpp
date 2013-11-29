#include<QPainter>
#include<QMouseEvent>
#include"MyTableView.h"
#include<QStyledItemDelegate>
#include<QApplication>
#include<QPushButton>
#include <QAbstractButton>
#include<QHeaderView>

#include <QTextCodec>
#include<QDebug>
#include "mystandarditemmodel.h"
#include "myitemdelegate.h"

MyTableView::MyTableView(QWidget * parent):QTableView(parent)
{
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setMouseTracking(true);

    this->verticalHeader()->setVisible(false);
    this->horizontalHeader()->setVisible(false);
    this->setVerticalScrollMode(ScrollPerPixel);
}


void MyTableView::setStringList(QStringList list)
{
    delegate=new MyItemDelegate;
    Q_ASSERT(delegate);
    model=new MyStandardItemModel;
    Q_ASSERT(model);

    model->setRowCount(list.count());
    model->setColumnCount(1);

    model->setStringList(list);

    this->setModel(model);
    this->setItemDelegate(delegate);

    for(int i=0;i<list.count();i++)
      this->setRowHeight(i,40);
    this->setColumnWidth(0,150);

    connect(delegate , SIGNAL(selection()), this, SLOT(selection()));

}

void MyTableView::selection()
{
   emit selectionClear();
}

void MyTableView::setWidth(int width)
{
    delegate->setWidth(width);
}

void MyTableView::noSelection()
{
    model->noSelection();

}

const QString MyTableView::Text(const QModelIndex &index, int role){

    return  model->data(index,role).toString();
}
