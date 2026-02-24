#include "widget.h"
#include "NPC.h"
#include "Race.h"
#include "classtype.h"
#include "./ui_widget.h"

#include <iostream>
#include <random>
#include <yaml-cpp/yaml.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DND_GM_Helper)
{
    ui->setupUi(this);
    QString configPath = QCoreApplication::applicationDirPath() + "/conf/NPC_conf.yaml";
    config = YAML::LoadFile(configPath.toStdString());
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
    ui->outNPCinfo->setText("DND 3.5e NPC\nName : "
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
                            + "\nLevel : "
                            + QString::number(npc.level)
                            + "\nXP : "
                            + QString::number(npc.XP)
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
    std::uniform_int_distribution<> dis(npc.race.MaxAge / 6, npc.race.MaxAge + 10);
    npc.Age = dis(gen);
    ui->agetxtin->setText(QString::number(npc.Age));
}


void Widget::on_butCOmandlinemode_clicked()
{
    this->hide(); // Hide Qt window during CLI mode

    // Reopen stdin/stdout to the actual terminal
    freopen("/dev/tty", "r", stdin);
    freopen("/dev/tty", "w", stdout);

    npc.Get_NPC_Stats();
    npc.Print_NPC_Stats();

    // Pause so user can read output
    std::cout << "\nPress Enter to return..." << std::flush;
    std::cin.ignore();
    std::cin.get();

    this->show(); // Restore Qt window
}


void Widget::on_leveltxtin_editingFinished()
{
    npc.level = ui->leveltxtin->text().toInt();
    ui->leveltxtin->setText(QString::number(npc.level));
    if (npc.level >= 20) {npc.XP = 190000;}
    else if (npc.level == 19) {npc.XP = 171000;}
    else if (npc.level == 18){npc.XP = 153000;}
    else if (npc.level == 17){npc.XP = 136000;}
    else if (npc.level == 16){npc.XP = 120000;}
    else if (npc.level == 15){npc.XP = 105000;}
    else if (npc.level == 14){npc.XP = 91000;}
    else if (npc.level == 13){npc.XP = 78000;}
    else if (npc.level == 12){npc.XP = 66000;}
    else if (npc.level == 11){npc.XP = 55000;}
    else if (npc.level == 10){npc.XP = 45000;}
    else if (npc.level == 9){npc.XP = 36000;}
    else if (npc.level == 8){npc.XP = 28000;}
    else if (npc.level == 7){npc.XP = 21000;}
    else if (npc.level == 6){npc.XP = 15000;}
    else if (npc.level == 5){npc.XP = 10000;}
    else if (npc.level == 4){npc.XP = 6000;}
    else if (npc.level == 3){npc.XP = 3000;}
    else if (npc.level == 2){npc.XP = 1000;}
    else if (npc.level == 1){npc.XP = 0;}
    else {npc.XP = 0;}
    ui->xptxtin->setText(QString::number(npc.XP));
}


void Widget::on_xptxtin_editingFinished()
{
    npc.XP = ui->xptxtin->text().toInt();
    ui->xptxtin->setText(QString::number(npc.XP));
    if (npc.XP <= 0) {npc.level = 1;}
    else if (npc.XP <= 1000) {npc.level = 2;}
    else if (npc.XP <= 3000) {npc.level = 3;}
    else if (npc.XP <= 6000) {npc.level = 4;}
    else if (npc.XP <= 10000) {npc.level = 5;}
    else if (npc.XP <= 15000) {npc.level = 6;}
    else if (npc.XP <= 21000) {npc.level = 7;}
    else if (npc.XP <= 28000) {npc.level = 8;}
    else if (npc.XP <= 36000) {npc.level = 9;}
    else if (npc.XP <= 45000) {npc.level = 10;}
    else if (npc.XP <= 55000) {npc.level = 11;}
    else if (npc.XP <= 66000) {npc.level = 12;}
    else if (npc.XP <= 78000) {npc.level = 13;}
    else if (npc.XP <= 91000) {npc.level = 14;}
    else if (npc.XP <= 105000) {npc.level = 15;}
    else if (npc.XP <= 120000) {npc.level = 16;}
    else if (npc.XP <= 136000) {npc.level = 17;}
    else if (npc.XP <= 153000) {npc.level = 18;}
    else if (npc.XP <= 171000) {npc.level = 19;}
    else {npc.level = 20;}
    ui->leveltxtin->setText(QString::number(npc.level));
}


void Widget::on_butrandlevel_clicked()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 20);
    npc.level = dis(gen);
    ui->leveltxtin->setText(QString::number(npc.level));
    if (npc.level >= 20) {npc.XP = 190000;}
    else if (npc.level == 19) {npc.XP = 171000;}
    else if (npc.level == 18){npc.XP = 153000;}
    else if (npc.level == 17){npc.XP = 136000;}
    else if (npc.level == 16){npc.XP = 120000;}
    else if (npc.level == 15){npc.XP = 105000;}
    else if (npc.level == 14){npc.XP = 91000;}
    else if (npc.level == 13){npc.XP = 78000;}
    else if (npc.level == 12){npc.XP = 66000;}
    else if (npc.level == 11){npc.XP = 55000;}
    else if (npc.level == 10){npc.XP = 45000;}
    else if (npc.level == 9){npc.XP = 36000;}
    else if (npc.level == 8){npc.XP = 28000;}
    else if (npc.level == 7){npc.XP = 21000;}
    else if (npc.level == 6){npc.XP = 15000;}
    else if (npc.level == 5){npc.XP = 10000;}
    else if (npc.level == 4){npc.XP = 6000;}
    else if (npc.level == 3){npc.XP = 3000;}
    else if (npc.level == 2){npc.XP = 1000;}
    else if (npc.level == 1){npc.XP = 0;}
    else {npc.XP = 0;}
    ui->xptxtin->setText(QString::number(npc.XP));
}


void Widget::on_butRandXP_clicked()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 190000);
    npc.XP = dis(gen);
    ui->xptxtin->setText(QString::number(npc.XP));
    if (npc.XP <= 0) {npc.level = 1;}
    else if (npc.XP <= 1000) {npc.level = 2;}
    else if (npc.XP <= 3000) {npc.level = 3;}
    else if (npc.XP <= 6000) {npc.level = 4;}
    else if (npc.XP <= 10000) {npc.level = 5;}
    else if (npc.XP <= 15000) {npc.level = 6;}
    else if (npc.XP <= 21000) {npc.level = 7;}
    else if (npc.XP <= 28000) {npc.level = 8;}
    else if (npc.XP <= 36000) {npc.level = 9;}
    else if (npc.XP <= 45000) {npc.level = 10;}
    else if (npc.XP <= 55000) {npc.level = 11;}
    else if (npc.XP <= 66000) {npc.level = 12;}
    else if (npc.XP <= 78000) {npc.level = 13;}
    else if (npc.XP <= 91000) {npc.level = 14;}
    else if (npc.XP <= 105000) {npc.level = 15;}
    else if (npc.XP <= 120000) {npc.level = 16;}
    else if (npc.XP <= 136000) {npc.level = 17;}
    else if (npc.XP <= 153000) {npc.level = 18;}
    else if (npc.XP <= 171000) {npc.level = 19;}
    else {npc.level = 20;}
    ui->leveltxtin->setText(QString::number(npc.level));
}


void Widget::on_HPtxtin_editingFinished()
{
    npc.HP = ui->HPtxtin->text().toInt();
}

void Widget::on_butCalculatehp_clicked()
{
    // Load HPdice from config
    YAML::Node classNode = config["NPC_conf"][npc.classtype.name];
    if (classNode) {
        YAML::Node hpNode;
        if (classNode.IsSequence() && classNode.size() > 0)
            hpNode = classNode[0]["HPdice"];
        else if (classNode.IsMap())
            hpNode = classNode["HPdice"];

        if (hpNode && hpNode.IsScalar()) {
            npc.classtype.HPdice = hpNode.as<int>();
        }
    }

    // Fallback if HPdice still not set or is 0
    if (npc.classtype.HPdice <= 0) {
        static const std::map<std::string, int> defaultHP = {
            {"Barbarian", 12}, {"Bard", 6},    {"Cleric", 8},
            {"Druid", 8},      {"Fighter", 10}, {"Monk", 8},
            {"Paladin", 10},   {"Rogue", 8},    {"Wizard", 4}
        };
        auto it = defaultHP.find(npc.classtype.name);
        npc.classtype.HPdice = (it != defaultHP.end()) ? it->second : 8;
    }

    // Guard: make sure level is valid too
    if (npc.level <= 0) npc.level = 1;

    // Calculate HP
    npc.HP = 0;
    for (int i = 1; i <= npc.level; ++i) {
        if (i == 1)
            npc.HP = npc.classtype.HPdice;
        else
            npc.HP += rand() % npc.classtype.HPdice + 1;
    }

    ui->HPtxtin->setText(QString::number(npc.HP));
}
