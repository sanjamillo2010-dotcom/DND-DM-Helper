/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DND_GM_Helper
{
public:
    QLineEdit *Racetxtin;
    QLabel *Race;
    QPushButton *pushButton;
    QTextEdit *outNPCinfo;
    QPushButton *butPrintNPCinfo;
    QLabel *label;
    QLineEdit *Classtxtin;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QLineEdit *Nametxtin;
    QPushButton *pushButton_3;
    QLabel *label_3;
    QLineEdit *LastNametxtin;
    QPushButton *pushButton_4;
    QLabel *label_4;
    QPushButton *butMale;
    QPushButton *pushButton_6;
    QPushButton *butnonbinary;
    QLineEdit *Sexetxtin;
    QLabel *label_5;
    QLineEdit *Sizetxtin;
    QPushButton *butRandsize;
    QLabel *Age;
    QLineEdit *agetxtin;
    QPushButton *pushButton_5;
    QPushButton *butCOmandlinemode;
    QLabel *label_6;
    QLineEdit *leveltxtin;
    QPushButton *butrandlevel;
    QLabel *label_7;
    QLineEdit *xptxtin;
    QPushButton *butRandXP;
    QLabel *HP;
    QLineEdit *HPtxtin;
    QPushButton *butCalculatehp;
    QLabel *Aliment;
    QComboBox *ddAlimetin;
    QPushButton *pushButton_7;
    QLabel *Divinity;
    QComboBox *ddDivinity;
    QPushButton *butRandDivinity;
    QPushButton *butDivinitybyaliment;

    void setupUi(QWidget *DND_GM_Helper)
    {
        if (DND_GM_Helper->objectName().isEmpty())
            DND_GM_Helper->setObjectName("DND_GM_Helper");
        DND_GM_Helper->resize(796, 595);
        Racetxtin = new QLineEdit(DND_GM_Helper);
        Racetxtin->setObjectName("Racetxtin");
        Racetxtin->setGeometry(QRect(70, 10, 113, 26));
        Race = new QLabel(DND_GM_Helper);
        Race->setObjectName("Race");
        Race->setGeometry(QRect(10, 10, 66, 21));
        pushButton = new QPushButton(DND_GM_Helper);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(190, 10, 88, 26));
        outNPCinfo = new QTextEdit(DND_GM_Helper);
        outNPCinfo->setObjectName("outNPCinfo");
        outNPCinfo->setGeometry(QRect(420, 30, 371, 561));
        outNPCinfo->setReadOnly(true);
        butPrintNPCinfo = new QPushButton(DND_GM_Helper);
        butPrintNPCinfo->setObjectName("butPrintNPCinfo");
        butPrintNPCinfo->setGeometry(QRect(420, 5, 371, 21));
        label = new QLabel(DND_GM_Helper);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 40, 66, 21));
        Classtxtin = new QLineEdit(DND_GM_Helper);
        Classtxtin->setObjectName("Classtxtin");
        Classtxtin->setGeometry(QRect(70, 40, 113, 26));
        pushButton_2 = new QPushButton(DND_GM_Helper);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(190, 40, 88, 26));
        label_2 = new QLabel(DND_GM_Helper);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 70, 66, 18));
        Nametxtin = new QLineEdit(DND_GM_Helper);
        Nametxtin->setObjectName("Nametxtin");
        Nametxtin->setGeometry(QRect(80, 70, 113, 26));
        pushButton_3 = new QPushButton(DND_GM_Helper);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(200, 70, 88, 26));
        label_3 = new QLabel(DND_GM_Helper);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 100, 111, 31));
        LastNametxtin = new QLineEdit(DND_GM_Helper);
        LastNametxtin->setObjectName("LastNametxtin");
        LastNametxtin->setGeometry(QRect(120, 100, 113, 26));
        pushButton_4 = new QPushButton(DND_GM_Helper);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(240, 100, 121, 26));
        label_4 = new QLabel(DND_GM_Helper);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 130, 66, 31));
        butMale = new QPushButton(DND_GM_Helper);
        butMale->setObjectName("butMale");
        butMale->setGeometry(QRect(200, 130, 51, 26));
        pushButton_6 = new QPushButton(DND_GM_Helper);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(260, 130, 61, 26));
        butnonbinary = new QPushButton(DND_GM_Helper);
        butnonbinary->setObjectName("butnonbinary");
        butnonbinary->setGeometry(QRect(330, 130, 81, 26));
        Sexetxtin = new QLineEdit(DND_GM_Helper);
        Sexetxtin->setObjectName("Sexetxtin");
        Sexetxtin->setGeometry(QRect(70, 130, 121, 26));
        label_5 = new QLabel(DND_GM_Helper);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 160, 66, 31));
        Sizetxtin = new QLineEdit(DND_GM_Helper);
        Sizetxtin->setObjectName("Sizetxtin");
        Sizetxtin->setGeometry(QRect(70, 160, 113, 26));
        butRandsize = new QPushButton(DND_GM_Helper);
        butRandsize->setObjectName("butRandsize");
        butRandsize->setGeometry(QRect(190, 160, 161, 26));
        Age = new QLabel(DND_GM_Helper);
        Age->setObjectName("Age");
        Age->setGeometry(QRect(10, 190, 66, 21));
        agetxtin = new QLineEdit(DND_GM_Helper);
        agetxtin->setObjectName("agetxtin");
        agetxtin->setGeometry(QRect(70, 190, 113, 26));
        pushButton_5 = new QPushButton(DND_GM_Helper);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(190, 190, 161, 26));
        butCOmandlinemode = new QPushButton(DND_GM_Helper);
        butCOmandlinemode->setObjectName("butCOmandlinemode");
        butCOmandlinemode->setGeometry(QRect(3, 572, 141, 26));
        label_6 = new QLabel(DND_GM_Helper);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 220, 66, 21));
        leveltxtin = new QLineEdit(DND_GM_Helper);
        leveltxtin->setObjectName("leveltxtin");
        leveltxtin->setGeometry(QRect(73, 220, 41, 26));
        butrandlevel = new QPushButton(DND_GM_Helper);
        butrandlevel->setObjectName("butrandlevel");
        butrandlevel->setGeometry(QRect(120, 220, 88, 26));
        label_7 = new QLabel(DND_GM_Helper);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(215, 221, 51, 21));
        xptxtin = new QLineEdit(DND_GM_Helper);
        xptxtin->setObjectName("xptxtin");
        xptxtin->setGeometry(QRect(270, 220, 71, 26));
        butRandXP = new QPushButton(DND_GM_Helper);
        butRandXP->setObjectName("butRandXP");
        butRandXP->setGeometry(QRect(346, 220, 71, 26));
        HP = new QLabel(DND_GM_Helper);
        HP->setObjectName("HP");
        HP->setGeometry(QRect(10, 250, 66, 21));
        HPtxtin = new QLineEdit(DND_GM_Helper);
        HPtxtin->setObjectName("HPtxtin");
        HPtxtin->setGeometry(QRect(50, 250, 61, 26));
        butCalculatehp = new QPushButton(DND_GM_Helper);
        butCalculatehp->setObjectName("butCalculatehp");
        butCalculatehp->setGeometry(QRect(120, 250, 181, 26));
        Aliment = new QLabel(DND_GM_Helper);
        Aliment->setObjectName("Aliment");
        Aliment->setGeometry(QRect(10, 280, 91, 21));
        ddAlimetin = new QComboBox(DND_GM_Helper);
        ddAlimetin->addItem(QString());
        ddAlimetin->addItem(QString());
        ddAlimetin->addItem(QString());
        ddAlimetin->addItem(QString());
        ddAlimetin->addItem(QString());
        ddAlimetin->addItem(QString());
        ddAlimetin->addItem(QString());
        ddAlimetin->addItem(QString());
        ddAlimetin->addItem(QString());
        ddAlimetin->setObjectName("ddAlimetin");
        ddAlimetin->setGeometry(QRect(98, 280, 121, 26));
        pushButton_7 = new QPushButton(DND_GM_Helper);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(225, 280, 111, 26));
        Divinity = new QLabel(DND_GM_Helper);
        Divinity->setObjectName("Divinity");
        Divinity->setGeometry(QRect(10, 310, 91, 21));
        ddDivinity = new QComboBox(DND_GM_Helper);
        ddDivinity->addItem(QString());
        ddDivinity->setObjectName("ddDivinity");
        ddDivinity->setGeometry(QRect(100, 310, 251, 26));
        butRandDivinity = new QPushButton(DND_GM_Helper);
        butRandDivinity->setObjectName("butRandDivinity");
        butRandDivinity->setGeometry(QRect(10, 340, 111, 26));
        butDivinitybyaliment = new QPushButton(DND_GM_Helper);
        butDivinitybyaliment->setObjectName("butDivinitybyaliment");
        butDivinitybyaliment->setGeometry(QRect(130, 340, 131, 26));

        retranslateUi(DND_GM_Helper);

        QMetaObject::connectSlotsByName(DND_GM_Helper);
    } // setupUi

    void retranslateUi(QWidget *DND_GM_Helper)
    {
        DND_GM_Helper->setWindowTitle(QCoreApplication::translate("DND_GM_Helper", "Widget", nullptr));
        Race->setText(QCoreApplication::translate("DND_GM_Helper", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700;\">Race :</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("DND_GM_Helper", "Rand Race", nullptr));
        butPrintNPCinfo->setText(QCoreApplication::translate("DND_GM_Helper", "Print NPC info", nullptr));
        label->setText(QCoreApplication::translate("DND_GM_Helper", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700;\">Class :</span></p></body></html>", nullptr));
        pushButton_2->setText(QCoreApplication::translate("DND_GM_Helper", "Rand Class", nullptr));
        label_2->setText(QCoreApplication::translate("DND_GM_Helper", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700;\">Name :</span></p></body></html>", nullptr));
        pushButton_3->setText(QCoreApplication::translate("DND_GM_Helper", "Rand Name", nullptr));
        label_3->setText(QCoreApplication::translate("DND_GM_Helper", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700;\">Last Name : </span></p></body></html>", nullptr));
        pushButton_4->setText(QCoreApplication::translate("DND_GM_Helper", "Rand Last Name", nullptr));
        label_4->setText(QCoreApplication::translate("DND_GM_Helper", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700;\">Sexe :</span></p></body></html>", nullptr));
        butMale->setText(QCoreApplication::translate("DND_GM_Helper", "Male", nullptr));
        pushButton_6->setText(QCoreApplication::translate("DND_GM_Helper", "Female", nullptr));
        butnonbinary->setText(QCoreApplication::translate("DND_GM_Helper", "Non Binary", nullptr));
        label_5->setText(QCoreApplication::translate("DND_GM_Helper", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700;\">Size :</span></p></body></html>", nullptr));
        butRandsize->setText(QCoreApplication::translate("DND_GM_Helper", "Rand Size (with race)", nullptr));
        Age->setText(QCoreApplication::translate("DND_GM_Helper", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700;\">Age :</span></p></body></html>", nullptr));
        pushButton_5->setText(QCoreApplication::translate("DND_GM_Helper", "Rand Age (with race)", nullptr));
        butCOmandlinemode->setText(QCoreApplication::translate("DND_GM_Helper", "Command line Mod", nullptr));
        label_6->setText(QCoreApplication::translate("DND_GM_Helper", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700;\">Level : </span></p></body></html>", nullptr));
        butrandlevel->setText(QCoreApplication::translate("DND_GM_Helper", "Rand Level", nullptr));
        label_7->setText(QCoreApplication::translate("DND_GM_Helper", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700;\">| XP : </span></p></body></html>", nullptr));
        butRandXP->setText(QCoreApplication::translate("DND_GM_Helper", "Rand XP", nullptr));
        HP->setText(QCoreApplication::translate("DND_GM_Helper", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700;\">HP : </span></p></body></html>", nullptr));
        butCalculatehp->setText(QCoreApplication::translate("DND_GM_Helper", "Calculate HP (with class)", nullptr));
        Aliment->setText(QCoreApplication::translate("DND_GM_Helper", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700;\">Aliment : </span></p></body></html>", nullptr));
        ddAlimetin->setItemText(0, QCoreApplication::translate("DND_GM_Helper", "Lawful Good", nullptr));
        ddAlimetin->setItemText(1, QCoreApplication::translate("DND_GM_Helper", "Neutral Good", nullptr));
        ddAlimetin->setItemText(2, QCoreApplication::translate("DND_GM_Helper", "Chaotic Good", nullptr));
        ddAlimetin->setItemText(3, QCoreApplication::translate("DND_GM_Helper", "Lawful Neutral", nullptr));
        ddAlimetin->setItemText(4, QCoreApplication::translate("DND_GM_Helper", "Neutral Neutral", nullptr));
        ddAlimetin->setItemText(5, QCoreApplication::translate("DND_GM_Helper", "Chaotic Neutral", nullptr));
        ddAlimetin->setItemText(6, QCoreApplication::translate("DND_GM_Helper", "Lawful Evil", nullptr));
        ddAlimetin->setItemText(7, QCoreApplication::translate("DND_GM_Helper", "Neutral Evil", nullptr));
        ddAlimetin->setItemText(8, QCoreApplication::translate("DND_GM_Helper", "Chaotic Evil", nullptr));

        pushButton_7->setText(QCoreApplication::translate("DND_GM_Helper", "Rand aliment", nullptr));
        Divinity->setText(QCoreApplication::translate("DND_GM_Helper", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700;\">Divinity : </span></p></body></html>", nullptr));
        ddDivinity->setItemText(0, QCoreApplication::translate("DND_GM_Helper", "No divinity", nullptr));

        butRandDivinity->setText(QCoreApplication::translate("DND_GM_Helper", "Rand Divinity", nullptr));
        butDivinitybyaliment->setText(QCoreApplication::translate("DND_GM_Helper", "Divinity by aliment", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DND_GM_Helper: public Ui_DND_GM_Helper {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
