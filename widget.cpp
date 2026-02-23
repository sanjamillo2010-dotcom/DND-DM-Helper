#include "widget.h"
#include "NPC.h"
#include "Race.h"
#include "classtype.h"
#include "./ui_widget.h"

#include <iostream>
#include <random>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_Racetxtin_editingFinished()
{
    std::cout << "Entered Race" << std::endl;
    npc.race.name = ui->Racetxtin->text().toStdString();
    std::cout << npc.race.name << std::endl;
}

void Widget::on_pushButton_clicked()
{
    npc.race = npc.Get_Random_Race();
    ui->Racetxtin->setText(QString::fromStdString(npc.race.name));
}

void Widget::on_butPrintNPCinfo_clicked()
{
    ui->outNPCinfo->setText("Name : "
                            + QString::fromStdString(npc.name)
                            + "\nLast Name : "
                            + QString::fromStdString(npc.LastName)
                            + "\nRace : "
                            + QString::fromStdString(npc.race.name)
                            + "\nClass : "
                            + QString::fromStdString(npc.classtype.name)
                            + "\nSexe : "
                            + QString::fromStdString(npc.Sexe)
                            + "\nSize (cm): "
                            + QString::number(npc.Size)
                            + " , "
                            + QString::fromStdString(npc.SizeCategory)
                            + "\nAge : "
                            + QString::number(npc.Age)
                            + "\n\n"
                            + QString::fromStdString(npc.name)
                            + " "
                            + QString::fromStdString(npc.LastName)
                            + " the "
                            + QString::fromStdString(npc.race.name)
                            + " "
                            + QString::fromStdString(npc.classtype.name)
                            );
}

void Widget::on_Classtxtin_editingFinished()
{
    npc.classtype.name = ui->Classtxtin->text().toStdString();
    std::cout << npc.classtype.name << std::endl;
}

void Widget::on_pushButton_2_clicked()
{
    npc.classtype = npc.Get_Random_Class();
    ui->Classtxtin->setText(QString::fromStdString(npc.classtype.name));
}

void Widget::on_Nametxtin_editingFinished()
{
    npc.name = ui->Nametxtin->text().toStdString();
}

void Widget::on_pushButton_3_clicked()
{
    npc.name = npc.race.GetRandomName();
    ui->Nametxtin->setText(QString::fromStdString(npc.name));
}

void Widget::on_LastNametxtin_editingFinished()
{
    npc.LastName = ui->LastNametxtin->text().toStdString();
}

void Widget::on_pushButton_4_clicked()
{
    npc.LastName = npc.classtype.GetRandomLastName();
    ui->LastNametxtin->setText(QString::fromStdString(npc.LastName));
}

void Widget::on_butMale_clicked()
{
    npc.Sexe = "Male";
    ui->Sexetxtin->setText(QString::fromStdString(npc.Sexe));
}

void Widget::on_pushButton_6_clicked()
{
    npc.Sexe = "Female";
    ui->Sexetxtin->setText(QString::fromStdString(npc.Sexe));
}

void Widget::on_butnonbinary_clicked()
{
    npc.Sexe = "Non Binary";
    ui->Sexetxtin->setText(QString::fromStdString(npc.Sexe));
}

void Widget::on_Sexetxtin_editingFinished()
{
    npc.Sexe = ui->Sexetxtin->text().toStdString();
}

void Widget::on_Sizetxtin_editingFinished()
{
    npc.Size = ui->Sizetxtin->text().toInt();
    if (npc.Size <= 20)        npc.SizeCategory = "Tiny";
    else if (npc.Size <= 100)  npc.SizeCategory = "Small";
    else if (npc.Size <= 190)  npc.SizeCategory = "Medium";
    else if (npc.Size <= 320)  npc.SizeCategory = "Large";
    else if (npc.Size <= 640)  npc.SizeCategory = "Huge";
    else                   npc.SizeCategory = "Gargantuan";
}

void Widget::on_butRandsize_clicked()
{
    YAML::Node config = YAML::LoadFile("conf/NPC_conf.yaml");
    npc.race.set_usualname(config, npc.race.name);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(npc.race.MaxSize / 2, npc.race.MaxSize + 10);
    npc.Size = dis(gen);
    ui->Sizetxtin->setText(QString::number(npc.Size));
    if (npc.Size <= 20)        npc.SizeCategory = "Tiny";
    else if (npc.Size <= 100)  npc.SizeCategory = "Small";
    else if (npc.Size <= 190)  npc.SizeCategory = "Medium";
    else if (npc.Size <= 320)  npc.SizeCategory = "Large";
    else if (npc.Size <= 640)  npc.SizeCategory = "Huge";
    else                   npc.SizeCategory = "Gargantuan";
}

void Widget::on_agetxtin_editingFinished()
{
    npc.Age = ui->agetxtin->text().toInt();
}
void Widget::on_pushButton_5_clicked()
{
    YAML::Node config = YAML::LoadFile("conf/NPC_conf.yaml");
    npc.race.set_usualname(config, npc.race.name);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(npc.race.MaxAge / 2, npc.race.MaxAge + 10);
    npc.Age = dis(gen);
    ui->agetxtin->setText(QString::number(npc.Age));
}

