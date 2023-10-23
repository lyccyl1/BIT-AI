#include "showwidget.h"
#include "ui_showwidget.h"
#define DIV_GB (1024 * 1024 * 1024)
#define DIV_KB (1024)
ShowWidget::ShowWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowWidget)
{
    ui->setupUi(this);
    mInfo = new MemoryInfo();
    model = new QStringListModel(this);
    model->setStringList(list);
    ui->listView->setModel(model);
    ui->listView->setEditTriggers(NULL);
    flag = 0;
}

ShowWidget::~ShowWidget()
{
    delete ui;
}

void ShowWidget::on_pushButton_3_clicked()
{
    flag = 0;
    MEMORYSTATUSEX statex = mInfo->GetMemoryInfo();
    list.clear();
    list.append("物理内存已使用:     "+QString::number(statex.dwMemoryLoad)+"%");
    list.append("实际物理内存:       "+QString::number((float)statex.ullTotalPhys/DIV_GB)+"GB");
    list.append("当前可用的物理内存:  "+QString::number((float)statex.ullAvailPhys/DIV_GB)+"GB");
    list.append("可提交内存总大小:     "+QString::number((float)statex.ullTotalPageFile/DIV_GB)+"GB");
    list.append("当前可提交内存大小:"+QString::number((float)statex.ullAvailPageFile/DIV_GB)+"GB");
    list.append("虚拟内存总量:       "+QString::number((float)statex.ullTotalVirtual/DIV_GB)+"GB");
    list.append("当前可用虚拟内存:    "+QString::number((float)statex.ullAvailVirtual/DIV_GB)+"GB");
    model->setStringList(list);

}

void ShowWidget::on_pushButton_2_clicked()
{
    flag = 0;
    SYSTEM_INFO si = mInfo->GetSystemInfo1();
    list.clear();
    list.append("内存页面大小为： "+QString::number((int)si.dwPageSize / DIV_KB)+"KB");
    list.append("可用地址空间的最小内存地址为： 0x"+QString::number((int)si.lpMinimumApplicationAddress,16).sprintf("%.8x",(int)si.lpMinimumApplicationAddress));
    list.append("可用地址空间的最大内存地址为： 0x"+QString::number((int)si.lpMaximumApplicationAddress,16).sprintf("%.8x",(int)si.lpMaximumApplicationAddress).toUpper());
    list.append("逻辑处理器个数为："+QString::number(si.dwNumberOfProcessors));
    list.append("虚拟内存分配粒度为： "+QString::number(si.dwAllocationGranularity / DIV_KB)+"KB");
    model->setStringList(list);
}

void ShowWidget::on_pushButton_clicked()
{
    flag = 0;
    PERFORMANCE_INFORMATION pi = mInfo->GetPerformanceInfo1();
    list.clear();
    list.append("系统当前提交的页数为： "+ QString::number(pi.CommitTotal));
    list.append("系统可以提交的最大页数为： "+ QString::number(pi.CommitLimit));
    list.append("系统历史提交页面数量峰值为： "+ QString::number(pi.CommitPeak));
    list.append("以页为单位的实际物理内存量为： "+ QString::number(pi.PhysicalTotal));
    list.append("以页为单位的当前可用物理内存量为： "+ QString::number(pi.PhysicalAvailable));
    list.append("以页为单位的缓存量为： "+QString::number(pi.SystemCache));
    list.append("以页为单位的内核池总量： "+ QString::number(pi.KernelTotal));
    list.append("以页为单位的内核池Paged量： "+ QString::number(pi.KernelPaged));
    list.append("以页为单位的内核池Nonpaged量: "+ QString::number(pi.KernelNonpaged));
    list.append("页的大小为： "+ QString::number(pi.PageSize / DIV_KB)+"KB");
    list.append("当前打开的句柄数为： "+ QString::number(pi.HandleCount));
    list.append("当前进程数为： "+ QString::number(pi.ProcessCount));
    list.append("当前线程数为： "+ QString::number(pi.ThreadCount));
    model->setStringList(list);
}

void ShowWidget::on_pushButton_4_clicked()
{
    flag = 1;
    model->setStringList(mInfo->ShowAllProcessInfo());
}

void ShowWidget::on_listView_doubleClicked(const QModelIndex &index)
{
    if(flag == 1){
        int numIndex = index.row();
        page = new ProcessInfo(mInfo,mInfo->PIDlist[numIndex]);
        page->show();
    }

}
