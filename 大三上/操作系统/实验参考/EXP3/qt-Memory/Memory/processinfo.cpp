#include "processinfo.h"
#include "ui_processinfo.h"
#define SHOWMASK(dwTarget, type)          \
    if (TestSet(dwTarget, PAGE_##type)) { \
        cout << "|" << #type;             \
    }


ProcessInfo::ProcessInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProcessInfo)
{
    ui->setupUi(this);
    model = new QStringListModel(this);
    model->setStringList(list);
    ui->listView->setModel(model);
    ui->listView->setEditTriggers(NULL);
}

ProcessInfo::ProcessInfo(MemoryInfo *mInfo1,int numIndex,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProcessInfo)
{
    ui->setupUi(this);
    model = new QStringListModel(this);
    model->setStringList(list);
    ui->listView->setModel(model);
    ui->listView->setEditTriggers(NULL);
    mInfo = new MemoryInfo();
    qDebug()<<"ok";
    QStringList nList = mInfo->processVirtualMemoryInfo(numIndex);
    qDebug()<<"ok1";
    model->setStringList(nList);
}



ProcessInfo::~ProcessInfo()
{
    delete ui;
}




