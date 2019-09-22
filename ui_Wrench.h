/********************************************************************************
** Form generated from reading UI file 'Wrench.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WRENCH_H
#define UI_WRENCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Wrench
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *mainLayout;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_5;
    QTextEdit *infText;
    QHBoxLayout *horizontalLayout;
    QSpinBox *pageSpinBox;
    QLabel *pageLabel;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *searchWrenchBt;
    QLabel *numofWrechLb;
    QLineEdit *wrenchLineEdit;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *setCountBt;
    QLabel *wrenchIdLb;
    QSpinBox *wrechSpinBox;
    QLabel *countLb;
    QSpinBox *CountspinBox;

    void setupUi(QWidget *Wrench)
    {
        if (Wrench->objectName().isEmpty())
            Wrench->setObjectName(QString::fromUtf8("Wrench"));
        Wrench->resize(395, 443);
        gridLayout = new QGridLayout(Wrench);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mainLayout = new QVBoxLayout();
        mainLayout->setSpacing(6);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        label_2 = new QLabel(Wrench);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        mainLayout->addLayout(horizontalLayout_4);

        infText = new QTextEdit(Wrench);
        infText->setObjectName(QString::fromUtf8("infText"));

        mainLayout->addWidget(infText);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pageSpinBox = new QSpinBox(Wrench);
        pageSpinBox->setObjectName(QString::fromUtf8("pageSpinBox"));

        horizontalLayout->addWidget(pageSpinBox);

        pageLabel = new QLabel(Wrench);
        pageLabel->setObjectName(QString::fromUtf8("pageLabel"));

        horizontalLayout->addWidget(pageLabel);


        mainLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        searchWrenchBt = new QPushButton(Wrench);
        searchWrenchBt->setObjectName(QString::fromUtf8("searchWrenchBt"));

        horizontalLayout_3->addWidget(searchWrenchBt);

        numofWrechLb = new QLabel(Wrench);
        numofWrechLb->setObjectName(QString::fromUtf8("numofWrechLb"));

        horizontalLayout_3->addWidget(numofWrechLb);

        wrenchLineEdit = new QLineEdit(Wrench);
        wrenchLineEdit->setObjectName(QString::fromUtf8("wrenchLineEdit"));
        wrenchLineEdit->setEnabled(false);
        wrenchLineEdit->setDragEnabled(false);

        horizontalLayout_3->addWidget(wrenchLineEdit);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        mainLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        setCountBt = new QPushButton(Wrench);
        setCountBt->setObjectName(QString::fromUtf8("setCountBt"));

        horizontalLayout_2->addWidget(setCountBt);

        wrenchIdLb = new QLabel(Wrench);
        wrenchIdLb->setObjectName(QString::fromUtf8("wrenchIdLb"));

        horizontalLayout_2->addWidget(wrenchIdLb);

        wrechSpinBox = new QSpinBox(Wrench);
        wrechSpinBox->setObjectName(QString::fromUtf8("wrechSpinBox"));

        horizontalLayout_2->addWidget(wrechSpinBox);

        countLb = new QLabel(Wrench);
        countLb->setObjectName(QString::fromUtf8("countLb"));

        horizontalLayout_2->addWidget(countLb);

        CountspinBox = new QSpinBox(Wrench);
        CountspinBox->setObjectName(QString::fromUtf8("CountspinBox"));

        horizontalLayout_2->addWidget(CountspinBox);


        mainLayout->addLayout(horizontalLayout_2);


        gridLayout->addLayout(mainLayout, 0, 0, 1, 1);


        retranslateUi(Wrench);

        QMetaObject::connectSlotsByName(Wrench);
    } // setupUi

    void retranslateUi(QWidget *Wrench)
    {
        Wrench->setWindowTitle(QApplication::translate("Wrench", "Wrench", nullptr));
        label_2->setText(QApplication::translate("Wrench", "\345\276\205\344\270\212\344\274\240\344\277\241\346\201\257\350\241\250", nullptr));
        pageLabel->setText(QApplication::translate("Wrench", "0/0\351\241\265", nullptr));
        searchWrenchBt->setText(QApplication::translate("Wrench", "\346\220\234\347\264\242\346\211\263\346\211\213", nullptr));
        numofWrechLb->setText(QApplication::translate("Wrench", "\346\211\263\346\211\213\346\225\260\347\233\256\357\274\232", nullptr));
        setCountBt->setText(QApplication::translate("Wrench", "\350\256\276\347\275\256\350\256\241\346\225\260\345\200\274", nullptr));
        wrenchIdLb->setText(QApplication::translate("Wrench", "\346\211\263\346\211\213ID\357\274\232", nullptr));
        countLb->setText(QApplication::translate("Wrench", "\350\256\241\346\225\260\345\200\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Wrench: public Ui_Wrench {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WRENCH_H
