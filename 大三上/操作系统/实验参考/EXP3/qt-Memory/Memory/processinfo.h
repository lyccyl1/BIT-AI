#ifndef PROCESSINFO_H
#define PROCESSINFO_H

#include <QWidget>
#include "memoryinfo.h"
#include <QStringListModel>
#include <QStringList>
#include <QDebug>


namespace Ui {
class ProcessInfo;
}

class ProcessInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessInfo(QWidget *parent = 0);
    ProcessInfo(MemoryInfo *mInfo1,int numIndex,QWidget *parent = 0);
    ~ProcessInfo();

private:
    Ui::ProcessInfo *ui;
    MemoryInfo *mInfo;
    QStringListModel *model;
    QStringList list;
};

#endif // PROCESSINFO_H
