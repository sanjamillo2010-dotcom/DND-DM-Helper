#include "widget.h"
#include "NPC.h"
#include "Race.h"
#include "classtype.h"
#include "./ui_widget.h"

#include <iostream>
#include <random>
#include <yaml-cpp/yaml.h>

DND_GM_Helper_N::NPC_N::NPC DND_GM_Helper_N::NPC_N::npc;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DND_GM_Helper)
{
    ui->setupUi(this);
    QString configPath = QCoreApplication::applicationDirPath() + "/conf/NPC_conf.yaml";
    config = YAML::LoadFile(configPath.toStdString());

    // Populate ddDivinity combobox
    YAML::Node divinities = config["NPC_conf"]["Divinite"];
    YAML::Node details = config["NPC_conf"]["DivinityDetails"];

    for (const auto& deity : divinities) {
        std::string name = deity.as<std::string>();
        std::string a1 = details[name]["Alignment1"].as<std::string>();
        std::string a2 = details[name]["Alignment2"].as<std::string>();
        std::string entry = name + " : " + a1 + " " + a2;
        ui->ddDivinity->addItem(QString::fromStdString(entry));
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_ddDivinity_activated(int index)
{
    // Get the selected divinity name (strip the alignment part)
    QString selected = ui->ddDivinity->currentText();
    QString divinityName = selected.split(" : ").first();

    YAML::Node details = config["NPC_conf"]["DivinityDetails"];
    std::string key = divinityName.toStdString();

    if (details[key]) {
        DND_GM_Helper_N::NPC_N::npc.divinity.name = key;
        DND_GM_Helper_N::NPC_N::npc.divinity.alignment.alig1 = details[key]["Alignment1"].as<std::string>();
        DND_GM_Helper_N::NPC_N::npc.divinity.alignment.alig2 = details[key]["Alignment2"].as<std::string>();
    }
    else {
        DND_GM_Helper_N::NPC_N::npc.divinity.name = "None";
        DND_GM_Helper_N::NPC_N::npc.divinity.alignment.alig1 = "None";
        DND_GM_Helper_N::NPC_N::npc.divinity.alignment.alig2 = "";
    }
}

void Widget::on_Racetxtin_editingFinished()
{
    std::cout << "Entered Race" << std::endl;
    DND_GM_Helper_N::NPC_N::npc.race.name = ui->Racetxtin->text().toStdString();
}

void Widget::on_pushButton_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.race = DND_GM_Helper_N::NPC_N::npc.Get_Random_Race();
    ui->Racetxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.race.name));
}

void Widget::on_butPrintNPCinfo_clicked()
{
    ui->outNPCinfo->setText("DND 3.5e NPC\nName : "
                            + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.name)
                            + "\nLast Name : "
                            + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.LastName)
                            + "\nRace : "
                            + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.race.name)
                            + "\nClass : "
                            + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.classtype.name)
                            + "\nSexe : "
                            + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.Sexe)
                            + "\nSize (cm): "
                            + QString::number(DND_GM_Helper_N::NPC_N::npc.Size)
                            + " , "
                            + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.SizeCategory)
                            + "\nAge : "
                            + QString::number(DND_GM_Helper_N::NPC_N::npc.Age)
                            + "\nLevel : "
                            + QString::number(DND_GM_Helper_N::NPC_N::npc.level)
                            + "\nXP : "
                            + QString::number(DND_GM_Helper_N::NPC_N::npc.XP)
                            + "\nAlignment : "
                            + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.alignment.alig1) + " " + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.alignment.alig2)
                            + "\nDivinity : "
                            + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.divinity.name)
                            + " (" + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.divinity.alignment.alig1)
                            + " " + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.divinity.alignment.alig2) + ")"
                            + "\n\n"
                            + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.name)
                            + " "
                            + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.LastName)
                            + " the "
                            + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.race.name)
                            + " "
                            + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.classtype.name)
                            );
}

void Widget::on_Classtxtin_editingFinished()
{
    DND_GM_Helper_N::NPC_N::npc.classtype.name = ui->Classtxtin->text().toStdString();
    std::cout << DND_GM_Helper_N::NPC_N::npc.classtype.name << std::endl;
}

void Widget::on_pushButton_2_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.classtype = DND_GM_Helper_N::NPC_N::npc.Get_Random_Class();
    ui->Classtxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.classtype.name));
}

void Widget::on_Nametxtin_editingFinished()
{
    DND_GM_Helper_N::NPC_N::npc.name = ui->Nametxtin->text().toStdString();
}

void Widget::on_pushButton_3_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.name = DND_GM_Helper_N::NPC_N::npc.race.GetRandomName();
    ui->Nametxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.name));
}

void Widget::on_LastNametxtin_editingFinished()
{
    DND_GM_Helper_N::NPC_N::npc.LastName = ui->LastNametxtin->text().toStdString();
}

void Widget::on_pushButton_4_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.LastName = DND_GM_Helper_N::NPC_N::npc.classtype.GetRandomLastName();
    ui->LastNametxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.LastName));
}

void Widget::on_butMale_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.Sexe = "Male";
    ui->Sexetxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.Sexe));
}

void Widget::on_pushButton_6_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.Sexe = "Female";
    ui->Sexetxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.Sexe));
}

void Widget::on_butnonbinary_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.Sexe = "Non Binary";
    ui->Sexetxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.Sexe));
}

void Widget::on_Sexetxtin_editingFinished()
{
    DND_GM_Helper_N::NPC_N::npc.Sexe = ui->Sexetxtin->text().toStdString();
}

void Widget::on_Sizetxtin_editingFinished()
{
    DND_GM_Helper_N::NPC_N::npc.Size = ui->Sizetxtin->text().toInt();
    if (DND_GM_Helper_N::NPC_N::npc.Size <= 20)        DND_GM_Helper_N::NPC_N::npc.SizeCategory = "Tiny";
    else if (DND_GM_Helper_N::NPC_N::npc.Size <= 100)  DND_GM_Helper_N::NPC_N::npc.SizeCategory = "Small";
    else if (DND_GM_Helper_N::NPC_N::npc.Size <= 190)  DND_GM_Helper_N::NPC_N::npc.SizeCategory = "Medium";
    else if (DND_GM_Helper_N::NPC_N::npc.Size <= 320)  DND_GM_Helper_N::NPC_N::npc.SizeCategory = "Large";
    else if (DND_GM_Helper_N::NPC_N::npc.Size <= 640)  DND_GM_Helper_N::NPC_N::npc.SizeCategory = "Huge";
    else                       DND_GM_Helper_N::NPC_N::npc.SizeCategory = "Gargantuan";
}

void Widget::on_butRandsize_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.race.set_usualname(config, DND_GM_Helper_N::NPC_N::npc.race.name);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(DND_GM_Helper_N::NPC_N::npc.race.MaxSize / 2,DND_GM_Helper_N::NPC_N::npc.race.MaxSize + 10);
    DND_GM_Helper_N::NPC_N::npc.Size = dis(gen);
    ui->Sizetxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.Size));
    if (DND_GM_Helper_N::NPC_N::npc.Size <= 20)        DND_GM_Helper_N::NPC_N::npc.SizeCategory = "Tiny";
    else if (DND_GM_Helper_N::NPC_N::npc.Size <= 100)  DND_GM_Helper_N::NPC_N::npc.SizeCategory = "Small";
    else if (DND_GM_Helper_N::NPC_N::npc.Size <= 190)  DND_GM_Helper_N::NPC_N::npc.SizeCategory = "Medium";
    else if (DND_GM_Helper_N::NPC_N::npc.Size <= 320)  DND_GM_Helper_N::NPC_N::npc.SizeCategory = "Large";
    else if (DND_GM_Helper_N::NPC_N::npc.Size <= 640)  DND_GM_Helper_N::NPC_N::npc.SizeCategory = "Huge";
    else                       DND_GM_Helper_N::NPC_N::npc.SizeCategory = "Gargantuan";
}

void Widget::on_agetxtin_editingFinished()
{
    DND_GM_Helper_N::NPC_N::npc.Age = ui->agetxtin->text().toInt();
}

void Widget::on_pushButton_5_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.race.set_usualname(config, DND_GM_Helper_N::NPC_N::npc.race.name);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(DND_GM_Helper_N::NPC_N::npc.race.MaxAge / 6,  DND_GM_Helper_N::NPC_N::npc.race.MaxAge + 10);
    DND_GM_Helper_N::NPC_N::npc.Age = dis(gen);
    ui->agetxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.Age));
}

void Widget::on_butCOmandlinemode_clicked()
{
    this->hide();
    freopen("/dev/tty", "r", stdin);
    freopen("/dev/tty", "w", stdout);
    DND_GM_Helper_N::NPC_N::npc.Get_NPC_Stats();
    DND_GM_Helper_N::NPC_N::npc.Print_NPC_Stats();
    std::cout << "\nPress Enter to return..." << std::flush;
    std::cin.ignore();
    std::cin.get();
    this->show();
}

void Widget::on_leveltxtin_editingFinished()
{
    DND_GM_Helper_N::NPC_N::npc.level = ui->leveltxtin->text().toInt();
    ui->leveltxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.level));
    DND_GM_Helper_N::NPC_N::npc.XP = DND_GM_Helper_N::NPC_N::npc.XPFromLVL(DND_GM_Helper_N::NPC_N::npc.level);
    ui->xptxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.XP));
}

void Widget::on_xptxtin_editingFinished()
{
    DND_GM_Helper_N::NPC_N::npc.XP = ui->xptxtin->text().toInt();
    ui->xptxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.XP));
    DND_GM_Helper_N::NPC_N::npc.level = DND_GM_Helper_N::NPC_N::npc.LVLFromXP(DND_GM_Helper_N::NPC_N::npc.XP);
    ui->leveltxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.level));
}

void Widget::on_butrandlevel_clicked()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1 , 20);
    DND_GM_Helper_N::NPC_N::npc.level = dis(gen);
    ui->leveltxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.level));
    DND_GM_Helper_N::NPC_N::npc.XP = DND_GM_Helper_N::NPC_N::npc.XPFromLVL(DND_GM_Helper_N::NPC_N::npc.level);
    ui->xptxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.XP));
}

void Widget::on_butRandXP_clicked()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0 , 190000);
    DND_GM_Helper_N::NPC_N::npc.XP = dis(gen);
    ui->xptxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.XP));
    DND_GM_Helper_N::NPC_N::npc.level = DND_GM_Helper_N::NPC_N::npc.LVLFromXP(DND_GM_Helper_N::NPC_N::npc.XP);
    ui->leveltxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.level));
}

void Widget::on_HPtxtin_editingFinished()
{
    DND_GM_Helper_N::NPC_N::npc.HP = ui->HPtxtin->text().toInt();
}

void Widget::on_butCalculatehp_clicked()
{
    YAML::Node classNode = config["NPC_conf"][DND_GM_Helper_N::NPC_N::npc.classtype.name];
    if (classNode) {
        YAML::Node hpNode;
        if (classNode.IsSequence() && classNode.size() > 0)
            hpNode = classNode[0]["HPdice"];
        else if (classNode.IsMap())
            hpNode = classNode["HPdice"];

        if (hpNode && hpNode.IsScalar())
            DND_GM_Helper_N::NPC_N::npc.classtype.HPdice = hpNode.as<int>();
    }

    if (DND_GM_Helper_N::NPC_N::npc.classtype.HPdice <= 0) {
        static const std::map<std::string, int> defaultHP = {
            {"Barbarian", 12}, {"Bard", 6},    {"Cleric", 8},
            {"Druid", 8},      {"Fighter", 10}, {"Monk", 8},
            {"Paladin", 10},   {"Rogue", 8},    {"Wizard", 4}
        };
        auto it = defaultHP.find(DND_GM_Helper_N::NPC_N::npc.classtype.name);
        DND_GM_Helper_N::NPC_N::npc.classtype.HPdice = (it != defaultHP.end()) ? it->second : 8;
    }

    if (DND_GM_Helper_N::NPC_N::npc.level <= 0) DND_GM_Helper_N::NPC_N::npc.level = 1;

    DND_GM_Helper_N::NPC_N::npc.HP = 0;
    for (int i = 1; i <= DND_GM_Helper_N::NPC_N::npc.level; ++i) {
        if (i == 1)
            DND_GM_Helper_N::NPC_N::npc.HP = DND_GM_Helper_N::NPC_N::npc.classtype.HPdice;
        else
            DND_GM_Helper_N::NPC_N::npc.HP += rand() % DND_GM_Helper_N::NPC_N::npc.classtype.HPdice + 1;
    }

    ui->HPtxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.HP));
}

void Widget::on_ddAlimetin_activated(int index)
{
    if (index == 0)      {DND_GM_Helper_N::NPC_N::npc.alignment.alig1 = "Lawful";  DND_GM_Helper_N::NPC_N::npc.alignment.alig2 = "Good";}
    else if (index == 1) {DND_GM_Helper_N::NPC_N::npc.alignment.alig1 = "Neutral"; DND_GM_Helper_N::NPC_N::npc.alignment.alig2 = "Good";}
    else if (index == 2) {DND_GM_Helper_N::NPC_N::npc.alignment.alig1 = "Chaotic"; DND_GM_Helper_N::NPC_N::npc.alignment.alig2 = "Good";}
    else if (index == 3) {DND_GM_Helper_N::NPC_N::npc.alignment.alig1 = "Lawful";  DND_GM_Helper_N::NPC_N::npc.alignment.alig2 = "Neutral";}
    else if (index == 4) {DND_GM_Helper_N::NPC_N::npc.alignment.alig1 = "Neutral"; DND_GM_Helper_N::NPC_N::npc.alignment.alig2 = "Neutral";}
    else if (index == 5) {DND_GM_Helper_N::NPC_N::npc.alignment.alig1 = "Chaotic"; DND_GM_Helper_N::NPC_N::npc.alignment.alig2 = "Neutral";}
    else if (index == 6) {DND_GM_Helper_N::NPC_N::npc.alignment.alig1 = "Lawful";  DND_GM_Helper_N::NPC_N::npc.alignment.alig2 = "Evil";}
    else if (index == 7) {DND_GM_Helper_N::NPC_N::npc.alignment.alig1 = "Neutral"; DND_GM_Helper_N::NPC_N::npc.alignment.alig2 = "Evil";}
    else if (index == 8) {DND_GM_Helper_N::NPC_N::npc.alignment.alig1 = "Chaotic"; DND_GM_Helper_N::NPC_N::npc.alignment.alig2 = "Evil";}
    else                 {DND_GM_Helper_N::NPC_N::npc.alignment.alig1 = "Unknown"; DND_GM_Helper_N::NPC_N::npc.alignment.alig2 = "Unknown";}
}

void Widget::on_pushButton_7_clicked()
{
    int index;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0 , 8);
    index = dis(gen);
    if (index == 0)      {DND_GM_Helper_N::NPC_N::npc.alignment.alig1 = "Lawful";  DND_GM_Helper_N::NPC_N::npc.alignment.alig2 = "Good";}
    else if (index == 1) {DND_GM_Helper_N::NPC_N::npc.alignment.alig1 = "Neutral"; DND_GM_Helper_N::NPC_N::npc.alignment.alig2 = "Good";}
    else if (index == 2) {DND_GM_Helper_N::NPC_N::npc.alignment.alig1 = "Chaotic"; DND_GM_Helper_N::NPC_N::npc.alignment.alig2 = "Good";}
    else if (index == 3) {DND_GM_Helper_N::NPC_N::npc.alignment.alig1 = "Lawful";  DND_GM_Helper_N::NPC_N::npc.alignment.alig2 = "Neutral";}
    else if (index == 4) {DND_GM_Helper_N::NPC_N::npc.alignment.alig1 = "Neutral"; DND_GM_Helper_N::NPC_N::npc.alignment.alig2 = "Neutral";}
    else if (index == 5) {DND_GM_Helper_N::NPC_N::npc.alignment.alig1 = "Chaotic"; DND_GM_Helper_N::NPC_N::npc.alignment.alig2 = "Neutral";}
    else if (index == 6) {DND_GM_Helper_N::NPC_N::npc.alignment.alig1 = "Lawful";  DND_GM_Helper_N::NPC_N::npc.alignment.alig2 = "Evil";}
    else if (index == 7) {DND_GM_Helper_N::NPC_N::npc.alignment.alig1 = "Neutral"; DND_GM_Helper_N::NPC_N::npc.alignment.alig2 = "Evil";}
    else if (index == 8) {DND_GM_Helper_N::NPC_N::npc.alignment.alig1 = "Chaotic"; DND_GM_Helper_N::NPC_N::npc.alignment.alig2 = "Evil";}
    else                 {DND_GM_Helper_N::NPC_N::npc.alignment.alig1 = "Unknown"; DND_GM_Helper_N::NPC_N::npc.alignment.alig2 = "Unknown";}
    ui->ddAlimetin->setCurrentIndex(index);
}

void Widget::on_butRandDivinity_clicked()
{
    YAML::Node divinities = config["NPC_conf"]["Divinite"];
    YAML::Node details = config["NPC_conf"]["DivinityDetails"];

    std::vector<std::string> deityList;
    for (const auto& deity : divinities)
        deityList.push_back(deity.as<std::string>());

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, deityList.size() - 1);
    int index = dis(gen);

    std::string name = deityList[index];
    DND_GM_Helper_N::NPC_N::npc.divinity.name = name;
    DND_GM_Helper_N::NPC_N::npc.divinity.alignment.alig1 = details[name]["Alignment1"].as<std::string>();
    DND_GM_Helper_N::NPC_N::npc.divinity.alignment.alig2 = details[name]["Alignment2"].as<std::string>();

    ui->ddDivinity->setCurrentIndex(index);
}


void Widget::on_butDivinitybyaliment_clicked()
{
    YAML::Node divinities = config["NPC_conf"]["Divinite"];
    YAML::Node details = config["NPC_conf"]["DivinityDetails"];

    std::vector<std::string> matches;
    for (const auto& deity : divinities) {
        std::string name = deity.as<std::string>();
        std::string a1 = details[name]["Alignment1"].as<std::string>();
        std::string a2 = details[name]["Alignment2"].as<std::string>();

        if (a1 == DND_GM_Helper_N::NPC_N::npc.alignment.alig1 && a2 == DND_GM_Helper_N::NPC_N::npc.alignment.alig2)
            matches.push_back(name);
    }

    if (matches.empty()) return; // no deity matches this alignment

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, matches.size() - 1);
    std::string name = matches[dis(gen)];

    DND_GM_Helper_N::NPC_N::npc.divinity.name = name;
    DND_GM_Helper_N::NPC_N::npc.divinity.alignment.alig1 = details[name]["Alignment1"].as<std::string>();
    DND_GM_Helper_N::NPC_N::npc.divinity.alignment.alig2 = details[name]["Alignment2"].as<std::string>();

    QString entry = QString::fromStdString(
        name + " : " + DND_GM_Helper_N::NPC_N::npc.divinity.alignment.alig1 + " " + DND_GM_Helper_N::NPC_N::npc.divinity.alignment.alig2
        );
    int idx = ui->ddDivinity->findText(entry);
    if (idx >= 0) ui->ddDivinity->setCurrentIndex(idx);
}
