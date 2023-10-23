/********************************************************************************
** Form generated from reading UI file 'processinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCESSINFO_H
#define UI_PROCESSINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProcessInfo
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QListView *listView;

    void setupUi(QWidget *ProcessInfo)
    {
        if (ProcessInfo->objectName().isEmpty())
            ProcessInfo->setObjectName(QStringLiteral("ProcessInfo"));
        ProcessInfo->resize(332, 296);
        horizontalLayout = new QHBoxLayout(ProcessInfo);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        listView = new QListView(ProcessInfo);
        listView->setObjectName(QStringLiteral("listView"));

        verticalLayout->addWidget(listView);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(ProcessInfo);

        QMetaObject::connectSlotsByName(ProcessInfo);
    } // setupUi

    void retranslateUi(QWidget *ProcessInfo)
    {
        ProcessInfo->setWindowTitle(QApplication::translate("ProcessInfo", "\350\277\233\347\250\213\347\233\221\350\247\206", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ProcessInfo: public Ui_ProcessInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCESSINFO_H
