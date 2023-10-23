#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H
#include"memoryinfo.h"
#include <QWidget>
#include <QStringListModel>
#include <QStringList>
#include <QDebug>
#include "processinfo.h"
namespace Ui {
class ShowWidget;
}

class ShowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShowWidget(QWidget *parent = 0);
    ~ShowWidget();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_listView_doubleClicked(const QModelIndex &index);

private:
    Ui::ShowWidget *ui;
    MemoryInfo *mInfo;
    QStringListModel *model;
    QStringList list;
    int flag;
    ProcessInfo *page;
};

#endif // SHOWWIDGET_H
