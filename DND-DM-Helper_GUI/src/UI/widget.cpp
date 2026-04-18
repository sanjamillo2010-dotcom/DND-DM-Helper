#include "../include/UI/widget.h"
#include "../include/NPC/NPC.h"
#include "../include/NPC/Race.h"
#include "../include/NPC/classtype.h"
#include "ui_widget.h"
#include "../include/UI/npcbattlestats.h"
#include "../include/Export/pdfexporter.h"

#include <QFileDialog>
#include <QDir>
#include <iostream>
#include <random>
#include <yaml-cpp/yaml.h>

DND_GM_Helper_N::NPC_N::NPC DND_GM_Helper_N::NPC_N::npc;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DND_GM_Helper)
{
    ui->setupUi(this);
    config = YAML::LoadFile("conf/NPC_conf.yaml");

    // Populate ddDivinity combobox
    YAML::Node divinities = config["NPC_conf"]["Divinite"];
    YAML::Node details = config["NPC_conf"]["DivinityDetails"];
    YAML::Node Race_list = config["NPC_conf"]["race"];
    YAML::Node ClassType_list = config["NPC_conf"]["Classtype"];

    for (const auto& deity : divinities) {
        std::string name = deity.as<std::string>();
        std::string a1 = details[name]["Alignment1"].as<std::string>();
        std::string a2 = details[name]["Alignment2"].as<std::string>();
        std::string entry = name + " : " + a1 + " " + a2;
        ui->ddDivinity->addItem(QString::fromStdString(entry));
    }
    for (const auto& Race : Race_list) {
        std::string RaceFileName = Race.as<std::string>();
        ui->ddRace->addItem(QString::fromStdString(RaceFileName));
    }
    for (const auto& ClassType : ClassType_list) {
        std::string ClassTypeFileName = ClassType.as<std::string>();
        ui->ddClassType->addItem(QString::fromStdString(ClassTypeFileName));
    }
    ui->Racetxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.race.name));
    ui->Classtxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.classtype.name));
    ui->Nametxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.name));
    ui->LastNametxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.LastName));
    ui->Sexetxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.Sexe));
    ui->Sizetxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.Size));
    ui->agetxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.Age));
    ui->leveltxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.level));
    ui->xptxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.XP));
    ui->HPtxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.HP));
    ui->ddAlimetin->setCurrentIndex(DND_GM_Helper_N::NPC_N::npc.alignment.index);
    ui->ddDivinity->setCurrentIndex(DND_GM_Helper_N::NPC_N::npc.divinity.alignment.index);
}

Widget::~Widget()
{
    delete ui;
}

//Race !!! To unit Test !!! (0/3)

void Widget::on_Racetxtin_textChanged(const QString &arg1)
{
    YAML::Node config = YAML::LoadFile("conf/NPC_conf.yaml");
    if (arg1.toStdString() == "") {
        DND_GM_Helper_N::NPC_N::npc.race.name = "";
        std::fill(DND_GM_Helper_N::NPC_N::npc.race.usualNames.begin(), DND_GM_Helper_N::NPC_N::npc.race.usualNames.end() , "");
        DND_GM_Helper_N::NPC_N::npc.race.MaxAge = 0;
        DND_GM_Helper_N::NPC_N::npc.race.MaxSize = 0;
    }
    else {
        YAML::Node YAMLRaceList = config["NPC_conf"]["race"];
        std::vector<std::string> RaceList;
        for (const auto& node : YAMLRaceList) {
            RaceList.push_back(node.as<std::string>());
        }
        if (std::find(RaceList.begin(), RaceList.end(), arg1.toStdString()) != RaceList.end()) {
            DND_GM_Helper_N::NPC_N::npc.race.name = arg1.toStdString();
            DND_GM_Helper_N::NPC_N::npc.race.Set_Race_Stats(config);
            YAML::Node NPC_Name_list = config["NPC_conf"][DND_GM_Helper_N::NPC_N::npc.race.name]["usualNames"];
            for (const auto& node : NPC_Name_list) {
                std::string NPC_Name = node.as<std::string>();
                ui->ddName->addItem(QString::fromStdString(NPC_Name));
            }
            ui->ddRace->setCurrentText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.race.name));
        }
        else {
            DND_GM_Helper_N::NPC_N::npc.race.name = arg1.toStdString();
            ui->ddRace->setCurrentText("None");
        }
    }
}

void Widget::on_ddRace_activated(int index)
{
    QString selected = ui->ddRace->currentText();
    std::string RaceKey = selected.toStdString();
    YAML::Node raceNode = config["NPC_conf"][RaceKey];
    if (index > 0) {
        DND_GM_Helper_N::NPC_N::npc.race.name = RaceKey;
        DND_GM_Helper_N::NPC_N::npc.race.Set_Race_Stats(config);
    }
    else {
        DND_GM_Helper_N::NPC_N::npc.race.name = "";
        DND_GM_Helper_N::NPC_N::npc.race.usualNames.clear();
        DND_GM_Helper_N::NPC_N::npc.race.MaxAge = 0;
        DND_GM_Helper_N::NPC_N::npc.race.MaxSize = 0;
    }
    YAML::Node NPC_Name_list = config["NPC_conf"][DND_GM_Helper_N::NPC_N::npc.race.name]["usualNames"];
    for (const auto& node : NPC_Name_list) {
        std::string NPC_Name = node.as<std::string>();
        ui->ddName->addItem(QString::fromStdString(NPC_Name));
    }
    ui->Racetxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.race.name));
}

void Widget::on_pushButton_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.race = DND_GM_Helper_N::NPC_N::npc.Get_Random_Race();
    DND_GM_Helper_N::NPC_N::npc.race.Set_Race_Stats(config);
    YAML::Node NPC_Name_list = config["NPC_conf"][DND_GM_Helper_N::NPC_N::npc.race.name]["usualNames"];
    for (const auto& node : NPC_Name_list) {
        std::string NPC_Name = node.as<std::string>();
        ui->ddName->addItem(QString::fromStdString(NPC_Name));
    }
    ui->Racetxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.race.name));
}

//ClassType !!! To unit Test !!! (0/3)

void Widget::on_Classtxtin_textChanged(const QString &arg1)
{
    YAML::Node config = YAML::LoadFile("conf/NPC_conf.yaml");
    YAML::Node YAMLClassTypeList = config["NPC_conf"]["Classtype"];
    std::vector<std::string> ClassTypeList;
    for (const auto& node : YAMLClassTypeList) {
        ClassTypeList.push_back(node.as<std::string>());
    }
    if (std::find(ClassTypeList.begin(), ClassTypeList.end(), arg1.toStdString()) != ClassTypeList.end()) {
        DND_GM_Helper_N::NPC_N::npc.classtype.name = arg1.toStdString();
        DND_GM_Helper_N::NPC_N::npc.classtype.Set_ClassType_Stats(config);
        YAML::Node LastName_list = config["NPC_conf"][DND_GM_Helper_N::NPC_N::npc.classtype.name]["usualLastNames"];
        for (const auto& Node : LastName_list) {
            std::string NPC_LastName = Node.as<std::string>();
            ui->ddLastName->addItem(QString::fromStdString(NPC_LastName));
        }
        ui->ddClassType->setCurrentText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.classtype.name));
    }
    else {
        DND_GM_Helper_N::NPC_N::npc.classtype.name = arg1.toStdString();
        ui->ddClassType->setCurrentText("None");
    }
}

void Widget::on_pushButton_2_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.classtype = DND_GM_Helper_N::NPC_N::npc.Get_Random_Class();
    ui->Classtxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.classtype.name));
    YAML::Node LastName_list = config["NPC_conf"][DND_GM_Helper_N::NPC_N::npc.classtype.name]["usualLastNames"];
    for (const auto& Node : LastName_list) {
        std::string NPC_LastName = Node.as<std::string>();
        ui->ddLastName->addItem(QString::fromStdString(NPC_LastName));
    }
}

void Widget::on_ddClassType_activated(int index)
{
    QString selected = ui->ddClassType->currentText();
    std::string ClassTypeKey = selected.toStdString();
    if (index > 0) {
        DND_GM_Helper_N::NPC_N::npc.classtype.name = ClassTypeKey;
    }
    else {
        DND_GM_Helper_N::NPC_N::npc.classtype.name = "";
        DND_GM_Helper_N::NPC_N::npc.classtype.usualLastNames.clear();
        DND_GM_Helper_N::NPC_N::npc.classtype.HPdice = 0;
        DND_GM_Helper_N::NPC_N::npc.classtype.HasLightArmor = false;
        DND_GM_Helper_N::NPC_N::npc.classtype.HasMidArmor = false;
        DND_GM_Helper_N::NPC_N::npc.classtype.HasHeavyArmor = false;
        DND_GM_Helper_N::NPC_N::npc.classtype.HasShild = false;
        DND_GM_Helper_N::NPC_N::npc.classtype.Hastarge = false;
    }
    ui->Classtxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.classtype.name));
}

//Name !!! To unit Test !!! (0/3)


void Widget::on_Nametxtin_textChanged(const QString &arg1)
{
    DND_GM_Helper_N::NPC_N::npc.name = arg1.toStdString();
    YAML::Node YAML_Name_List = config["NPC_conf"][DND_GM_Helper_N::NPC_N::npc.race.name]["usualNames"];
    std::vector<std::string> Name_List;
    for (const auto& Node : YAML_Name_List) {
        Name_List.push_back(Node.as<std::string>());
    }
    if (std::find(Name_List.begin(), Name_List.end(), arg1.toStdString()) != Name_List.end()){
        ui->ddName->setCurrentText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.name));
    }
    else {
        ui->ddName->setCurrentText("None");
    }
}

void Widget::on_pushButton_3_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.name = DND_GM_Helper_N::NPC_N::npc.race.GetRandomName();
    ui->Nametxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.name));
}

void Widget::on_ddName_activated(int index)
{
    QString selected = ui->ddName->currentText();
    std::string NameKey = selected.toStdString();
    if (index > 0) {
        DND_GM_Helper_N::NPC_N::npc.name = NameKey;
    }
    else {
        DND_GM_Helper_N::NPC_N::npc.name = "";
    }
    ui->Nametxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.name));
}

//LastName

void Widget::on_LastNametxtin_textChanged(const QString &arg1)
{
    DND_GM_Helper_N::NPC_N::npc.LastName = arg1.toStdString();
    YAML::Node YAML_LastName_List = config["NPC_conf"][DND_GM_Helper_N::NPC_N::npc.classtype.name]["usualLastNames"];
    std::vector<std::string> LastName_List;
    for (const auto& Node : YAML_LastName_List) {
        LastName_List.push_back(Node.as<std::string>());
    }
    if (std::find(LastName_List.begin(), LastName_List.end(), arg1.toStdString()) != LastName_List.end()){
        ui->ddLastName->setCurrentText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.LastName));
    }
    else {
        ui->ddLastName->setCurrentText("None");
    }
}

void Widget::on_ddLastName_activated(int index)
{
    QString selected = ui->ddLastName->currentText();
    std::string LastNameKey = selected.toStdString();
    if (index > 0) {
        DND_GM_Helper_N::NPC_N::npc.LastName = LastNameKey;
    }
    else {
        DND_GM_Helper_N::NPC_N::npc.LastName = "";
    }
    ui->LastNametxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.LastName));
}

void Widget::on_butPrintNPCinfo_clicked() {
    std::string ItemEntry;
    for (int i = 0; i < DND_GM_Helper_N::NPC_N::npc.itemVector.size(); i++) {
        ItemEntry += "Item " + std::to_string(i+1) + " : " + DND_GM_Helper_N::NPC_N::npc.itemVector[i]->name + " | Price : " + std::to_string(DND_GM_Helper_N::NPC_N::npc.itemVector[i]->Prix) + + " | Weight : " + std::to_string(DND_GM_Helper_N::NPC_N::npc.itemVector[i]->Poids) + "\n";
    }
    std::string ArmorEntry;
    if (DND_GM_Helper_N::NPC_N::npc.Armor.Name != "") {
        ArmorEntry += "Armor : " + DND_GM_Helper_N::NPC_N::npc.Armor.Name + "(" + std::to_string(DND_GM_Helper_N::NPC_N::npc.Armor.Prot) + ")\n";
    }
    if (DND_GM_Helper_N::NPC_N::npc.Shield.Name != "") {
        ArmorEntry += "Armor : " + DND_GM_Helper_N::NPC_N::npc.Shield.Name + "(" + std::to_string(DND_GM_Helper_N::NPC_N::npc.Shield.Prot) + ")\n";
    }
    std::string WeaponEntry;
    if (DND_GM_Helper_N::NPC_N::npc.Weapon1.Name != "") {
        WeaponEntry += "Weapon 1 : " + DND_GM_Helper_N::NPC_N::npc.Weapon1.Name + " (" + std::to_string(DND_GM_Helper_N::NPC_N::npc.Weapon1.Attack.Num_of_Dice) + "d" + std::to_string(DND_GM_Helper_N::NPC_N::npc.Weapon1.Attack.Dice_Value) + ")\n";
    }
    if (DND_GM_Helper_N::NPC_N::npc.Weapon2.Name != "") {
        WeaponEntry += "Weapon 2 : " + DND_GM_Helper_N::NPC_N::npc.Weapon2.Name + " (" + std::to_string(DND_GM_Helper_N::NPC_N::npc.Weapon2.Attack.Num_of_Dice) + "d" + std::to_string(DND_GM_Helper_N::NPC_N::npc.Weapon2.Attack.Dice_Value) + ")\n";
    }
    if (DND_GM_Helper_N::NPC_N::npc.Weapon3.Name != "") {
        WeaponEntry += "Weapon 3 : " + DND_GM_Helper_N::NPC_N::npc.Weapon3.Name + " (" + std::to_string(DND_GM_Helper_N::NPC_N::npc.Weapon3.Attack.Num_of_Dice) + "d" + std::to_string(DND_GM_Helper_N::NPC_N::npc.Weapon3.Attack.Dice_Value) + ")\n";
    }
    if (DND_GM_Helper_N::NPC_N::npc.Weapon4.Name != "") {
        WeaponEntry += "Weapon 2 : " + DND_GM_Helper_N::NPC_N::npc.Weapon4.Name + " (" + std::to_string(DND_GM_Helper_N::NPC_N::npc.Weapon4.Attack.Num_of_Dice) + "d" + std::to_string(DND_GM_Helper_N::NPC_N::npc.Weapon4.Attack.Dice_Value) + ")\n";
    }
    if (DND_GM_Helper_N::NPC_N::npc.Weapon5.Name != "") {
        WeaponEntry += "Weapon 3 : " + DND_GM_Helper_N::NPC_N::npc.Weapon5.Name + " (" + std::to_string(DND_GM_Helper_N::NPC_N::npc.Weapon5.Attack.Num_of_Dice) + "d" + std::to_string(DND_GM_Helper_N::NPC_N::npc.Weapon5.Attack.Dice_Value) + ")\n";
    }
    std::string IdentetyEntry;
    if (DND_GM_Helper_N::NPC_N::npc.name != "" && DND_GM_Helper_N::NPC_N::npc.LastName != "" && DND_GM_Helper_N::NPC_N::npc.classtype.name != "" && DND_GM_Helper_N::NPC_N::npc.race.name != "") {
        IdentetyEntry = "\n\n" + DND_GM_Helper_N::NPC_N::npc.name + " " + DND_GM_Helper_N::NPC_N::npc.LastName + " the " + DND_GM_Helper_N::NPC_N::npc.classtype.name + " " + DND_GM_Helper_N::NPC_N::npc.race.name + "\n";
    }
    ui->outNPCinfo->setText("DND 3.5e NPC\nName : "
                            + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.name) + "\n"
                            + "Last Name : " + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.LastName) + "\n"
                            + "Race : " + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.race.name) + "\n"
                            + "Class : " + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.classtype.name) + "\n"
                            + "Sexe : " + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.Sexe) + "\n"
                            + "Size (cm): "
                            + QString::number(DND_GM_Helper_N::NPC_N::npc.Size)
                            + " , "
                            + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.SizeCategory) + "\n"
                            + "Age : "
                            + QString::number(DND_GM_Helper_N::NPC_N::npc.Age) + "\n"
                            + "Level : "
                            + QString::number(DND_GM_Helper_N::NPC_N::npc.level) + "\n"
                            + "XP : "
                            + QString::number(DND_GM_Helper_N::NPC_N::npc.XP) + "\n"
                            + "Alignment : "
                            + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.alignment.alig1) + " " + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.alignment.alig2) + "\n"
                            + "Divinity : "
                            + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.divinity.name)
                            + " (" + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.divinity.alignment.alig1)
                            + " " + QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.divinity.alignment.alig2) + ")"
                            + "\n----------------------------------------------------\nBattle Stats"
                            + "\nStr : " + QString::number(DND_GM_Helper_N::NPC_N::npc.FOR) + " (" + QString::number(DND_GM_Helper_N::NPC_N::npc.FOR_Bonus) + ")"
                            + "\nDex : " + QString::number(DND_GM_Helper_N::NPC_N::npc.DEX) + " (" + QString::number(DND_GM_Helper_N::NPC_N::npc.DEX_Bonus) + ")"
                            + "\nCon : " + QString::number(DND_GM_Helper_N::NPC_N::npc.CON) + " (" + QString::number(DND_GM_Helper_N::NPC_N::npc.CON_Bonus) + ")"
                            + "\nInt : " + QString::number(DND_GM_Helper_N::NPC_N::npc.INT) + " (" + QString::number(DND_GM_Helper_N::NPC_N::npc.INT_Bonus) + ")"
                            + "\nWis : " + QString::number(DND_GM_Helper_N::NPC_N::npc.SAG) + " (" + QString::number(DND_GM_Helper_N::NPC_N::npc.SAG_Bonus) + ")"
                            + "\nCha : " + QString::number(DND_GM_Helper_N::NPC_N::npc.CHA) + " (" + QString::number(DND_GM_Helper_N::NPC_N::npc.CHA_Bonus) + ")"
                            + "\nAC : " + QString::number(DND_GM_Helper_N::NPC_N::npc.CA)
                            + "\n----------------------------------------------------\nInventory\n"
                            + QString::fromStdString(ArmorEntry)
                            + QString::fromStdString(WeaponEntry)
                            + QString::fromStdString(ItemEntry)
                            + QString::fromStdString(IdentetyEntry)
                            );
}

void Widget::on_ddDivinity_activated(int index)
{
    // Fix for 1.3.2 and make it in a function
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
    DND_GM_Helper_N::NPC_N::npc.divinity.alignment.index = index;
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
    DND_GM_Helper_N::NPC_N::npc.SizeCategoryfromSize();
}

void Widget::on_butRandsize_clicked()
{
    if (DND_GM_Helper_N::NPC_N::npc.race.MaxSize == 0) {
        ui->Sizetxtin->setText("No race selected");
    }
    else {
        std::random_device SIZErd;
        std::mt19937 SIZEgen(SIZErd());
        std::uniform_int_distribution<> SIZEdis(DND_GM_Helper_N::NPC_N::npc.race.MaxSize / 2,DND_GM_Helper_N::NPC_N::npc.race.MaxSize + 10);
        DND_GM_Helper_N::NPC_N::npc.Size = SIZEdis(SIZEgen);
        ui->Sizetxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.Size));
        DND_GM_Helper_N::NPC_N::npc.SizeCategoryfromSize();
    }

}

void Widget::on_agetxtin_editingFinished()
{
    DND_GM_Helper_N::NPC_N::npc.Age = ui->agetxtin->text().toInt();
}

void Widget::on_pushButton_5_clicked()
{
    if (DND_GM_Helper_N::NPC_N::npc.race.MaxAge == 0) {
        ui->agetxtin->setText("No race selected");
    }
    else {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(DND_GM_Helper_N::NPC_N::npc.race.MaxAge / 6,  DND_GM_Helper_N::NPC_N::npc.race.MaxAge + 10);
        DND_GM_Helper_N::NPC_N::npc.Age = dis(gen);
        ui->agetxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.Age));
    }

}

void Widget::on_butCOmandlinemode_clicked()
{
    //Fix in v1.3.2
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
    if (DND_GM_Helper_N::NPC_N::npc.level <= 0) DND_GM_Helper_N::NPC_N::npc.level = 1;
    DND_GM_Helper_N::NPC_N::npc.HP = 0;
    for (int i = 1; i <= DND_GM_Helper_N::NPC_N::npc.level; ++i) {
        if (i == 1)
            DND_GM_Helper_N::NPC_N::npc.HP = DND_GM_Helper_N::NPC_N::npc.classtype.HPdice + DND_GM_Helper_N::NPC_N::npc.CON_Bonus;
        else
            DND_GM_Helper_N::NPC_N::npc.HP += rand() % DND_GM_Helper_N::NPC_N::npc.classtype.HPdice + 1 +  + DND_GM_Helper_N::NPC_N::npc.CON_Bonus;
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
    DND_GM_Helper_N::NPC_N::npc.alignment.index = index;
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
    DND_GM_Helper_N::NPC_N::npc.alignment.index = index;
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
    DND_GM_Helper_N::NPC_N::npc.divinity.alignment.index = index;
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

    if (matches.empty()) return;

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
    DND_GM_Helper_N::NPC_N::npc.divinity.alignment.index = idx;
}

void Widget::on_butMakeNPCFItablain_clicked()
{
    NPCbattlestats *widget = new NPCbattlestats();
    widget->show();
    this->close();

}

void Widget::on_butResetallstatsin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.Reset_All_Stats();
    on_butPrintNPCinfo_clicked();
    ui->Racetxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.race.name));
    ui->Classtxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.classtype.name));
    ui->Nametxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.name));
    ui->LastNametxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.LastName));
    ui->Sexetxtin->setText(QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.Sexe));
    ui->Sizetxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.Size));
    ui->agetxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.Age));
    ui->leveltxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.level));
    ui->xptxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.XP));
    ui->HPtxtin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.HP));
    ui->ddAlimetin->setCurrentIndex(0);
    ui->ddDivinity->setCurrentIndex(0);
}

void Widget::on_pushButton_8_clicked()
{
    std::cout << "open Main menu " << std::endl;
}

void Widget::on_butPrintNPCinfoPDF_clicked() {
    QString defaultName = QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.name) + "_" +
                          QString::fromStdString(DND_GM_Helper_N::NPC_N::npc.LastName) + ".pdf";

    QString filePath = QFileDialog::getSaveFileName(
        nullptr,
        "Save NPC Sheet as PDF",
        QDir::homePath() + "/" + defaultName,
        "PDF Files (*.pdf)"
        );

    if (filePath.isEmpty()) return; // user cancelled

    DND_GM_Helper_N::Export_N::PdfExporter::exportNpcToPdf(
        DND_GM_Helper_N::NPC_N::npc, filePath);
}
