#include "navigation.h"
#include <QtAlgorithms>
#include <QPainter>

Navigation::Navigation(QWidget *parent):
    QScrollArea(parent),
    mainWidget(NULL),
    isInit(false)
{
    //resize(250,500);
    setWidgetResizable(true);
    scrollAreaWidgetContents = new QWidget;
    scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
    scrollAreaWidgetContents->setGeometry(QRect(0, 0, 150,400));

//    QPalette palette;
//    palette.setColor(QPalette::Background, QColor(57,57,57));
//    scrollAreaWidgetContents->setPalette(palette);
    verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(0,0,0,0);
    setWidget(scrollAreaWidgetContents);
    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum,QSizePolicy::Expanding);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

Navigation::~Navigation()
{
    qDeleteAll(buttonGroup);
    qDeleteAll(tableGroup);
}

bool Navigation::Init(MainWindow* main){
    Q_ASSERT(main);
    if(isInit)
        return false;
    isInit = true;
    mainWidget = main;
    return true;
}

void Navigation::addNavigationBar(const QString &barname,QIcon &barIcon,QStringList &list)
{
    QPushButton *button=new QPushButton(barname);
    Q_ASSERT(button);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(button->sizePolicy().hasHeightForWidth());
    button->setSizePolicy(sizePolicy);
    button->setMinimumSize(QSize(150, 50));

    button->setIcon(barIcon);
    button->setStyleSheet("border:0px;");

    verticalLayout->addWidget(button,1,Qt::AlignHCenter);
    buttonGroup.append(button);

    connect(buttonGroup.at(buttonGroup.count()-1), SIGNAL(clicked()),
                     this,  SLOT(setViewDisplay()));
    addNavigationList(list);
}

void Navigation::addNavigationList(QStringList &list)
{
    MyTableView *tableView=new MyTableView;
    Q_ASSERT(tableView);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
    tableView->setSizePolicy(sizePolicy);

    tableView->setMinimumSize(150,list.count()*40);
    tableView->setMaximumSize(300,list.count()*40);

    tableView->setStringList(list);

    verticalLayout->addWidget(tableView,0,Qt::AlignHCenter);
    //tableView->setColumnWidth( 0,tableView->width() );

    tableGroup.append(tableView);

    connect(tableView , SIGNAL(pressed(QModelIndex)), this, SLOT(information(QModelIndex)));
    connect(tableView , SIGNAL(selectionClear()), this, SLOT(clearSelection()));

}

void Navigation::addVerticalSpacer()
{
    verticalLayout->addItem(verticalSpacer);
}

void Navigation::setViewDisplay()
{
  QPushButton* btn = dynamic_cast<QPushButton*>(sender());
  int i;
  for(i=1;i<=buttonGroup.count();i++)
    {
      if(buttonGroup.at(i-1)==btn)
         break;
    }

  if(tableGroup.at(i-1)->isVisible())
    {
     tableGroup.at(i-1)->hide();
    }
  else tableGroup.at(i-1)->show();
}

void Navigation::resizeEvent(QResizeEvent *event)
{
     QScrollArea::resizeEvent(event);
     for(int i=0;i<tableGroup.count();i++){
         int width = tableGroup.at(i)->width();
         tableGroup.at(i)->setColumnWidth(0,width);
         updateView(tableGroup.at(i)->width());
     }

}

void Navigation::clearSelection()
{

    for(int i=0;i<tableGroup.count();i++)
       {
         tableGroup.at(i)->noSelection();
        // tableGroup.at(i)->repaint();
       }

}

void Navigation::updateView(int width)
{

    for(int i=0;i<tableGroup.count();i++)
       {
         tableGroup.at(i)->setWidth(width);

       }
}
void Navigation::information(QModelIndex index)
{
    MyTableView * sc=dynamic_cast<MyTableView*>(sender());
    Q_ASSERT(sc);
    int m = -1;
    for(int i=0;i<tableGroup.count();i++){
        if(tableGroup.at(i)==sc)
        {
            m=i;
            break;
        }
    }
    //emit label(m,index.row());
    if(m < 0
        ||m > buttonGroup.count()
        ||m > tableGroup.count()){
        return;
    }

    if(isInit){
        QString workSceneName = buttonGroup.at(m)->text() + tableGroup.at(m)->Text(index);
        mainWidget->ChangeWorkScene(workSceneName);
    }
}




