/********************************************************************************
** Form generated from reading UI file 'showwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWWIDGET_H
#define UI_SHOWWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QListView *listView;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_4;

    void setupUi(QWidget *ShowWidget)
    {
        if (ShowWidget->objectName().isEmpty())
            ShowWidget->setObjectName(QStringLiteral("ShowWidget"));
        ShowWidget->resize(587, 316);
        horizontalLayout_2 = new QHBoxLayout(ShowWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        listView = new QListView(ShowWidget);
        listView->setObjectName(QStringLiteral("listView"));

        horizontalLayout->addWidget(listView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton_3 = new QPushButton(ShowWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(ShowWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(ShowWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_4 = new QPushButton(ShowWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);


        horizontalLayout->addLayout(verticalLayout);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(ShowWidget);

        QMetaObject::connectSlotsByName(ShowWidget);
    } // setupUi

    void retranslateUi(QWidget *ShowWidget)
    {
        ShowWidget->setWindowTitle(QApplication::translate("ShowWidget", "ShowWidget", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("ShowWidget", "\345\206\205\345\255\230\346\203\205\345\206\265", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("ShowWidget", "\347\263\273\347\273\237\344\277\241\346\201\257", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ShowWidget", "\345\206\205\345\255\230\346\200\247\350\203\275\344\277\241\346\201\257", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("ShowWidget", "\346\230\276\347\244\272\346\211\200\346\234\211\350\277\233\347\250\213", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ShowWidget: public Ui_ShowWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWWIDGET_H
