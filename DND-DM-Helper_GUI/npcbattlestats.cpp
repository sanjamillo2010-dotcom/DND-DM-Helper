#include "npcbattlestats.h"
#include "ui_npcbattlestats.h"
#include "NPC.h"
#include "Race.h"
#include "classtype.h"
#include "ui_widget.h"
#include "widget.h"

#include <random>

NPCbattlestats::NPCbattlestats(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NPCbattlestats)
{
    ui->setupUi(this);
    ui->txtStrin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.FOR));
    ui->txtDexin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.DEX));
    ui->TxtConin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CON));
    ui->txtIntin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.INT));
    ui->txtWisin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.SAG));
    ui->txtChain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CHA));
    ui->txtcain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CA));
    ui->txtNAin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.Natural_Armor));
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("ALL");
}

NPCbattlestats::~NPCbattlestats()
{
    delete ui;
}


void NPCbattlestats::on_txtStrin_textChanged(const QString &arg1)
{
    DND_GM_Helper_N::NPC_N::npc.FOR =  ui->txtStrin->text().toInt();
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("FOR");
}


void NPCbattlestats::on_butBackin_clicked()
{
    Widget *widget = new Widget();
    widget->show();
    this->close();
}

void NPCbattlestats::on_txtDexin_textChanged(const QString &arg1)
{
    DND_GM_Helper_N::NPC_N::npc.DEX =  ui->txtDexin->text().toInt();
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("DEX");
}

void NPCbattlestats::on_TxtConin_textChanged(const QString &arg1)
{
    DND_GM_Helper_N::NPC_N::npc.CON =  ui->TxtConin->text().toInt();
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("CON");
}

void NPCbattlestats::on_txtIntin_textChanged(const QString &arg1)
{
    DND_GM_Helper_N::NPC_N::npc.INT =  ui->txtIntin->text().toInt();
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("INT");
}

void NPCbattlestats::on_txtWisin_textChanged(const QString &arg1)
{
    DND_GM_Helper_N::NPC_N::npc.SAG =  ui->txtWisin->text().toInt();
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("SAG");
}

void NPCbattlestats::on_txtChain_textChanged(const QString &arg1)
{
    DND_GM_Helper_N::NPC_N::npc.CHA =  ui->txtChain->text().toInt();
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("CHA");
}

void NPCbattlestats::on_butbonusin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.Calculat_Carak_Race_bonus();
    ui->txtStrin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.FOR));
    ui->txtDexin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.DEX));
    ui->TxtConin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CON));
    ui->txtIntin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.INT));
    ui->txtChain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CHA));
}


void NPCbattlestats::on_butaddstrin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.FOR = DND_GM_Helper_N::NPC_N::npc.FOR + 1;
    ui->txtStrin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.FOR));
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("FOR");
}

void NPCbattlestats::on_butsubstrin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.FOR = DND_GM_Helper_N::NPC_N::npc.FOR - 1;
    ui->txtStrin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.FOR));
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("FOR");
}

void NPCbattlestats::on_butadddexin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.DEX = DND_GM_Helper_N::NPC_N::npc.DEX + 1;
    ui->txtDexin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.DEX));
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("DEX");
}

void NPCbattlestats::on_butsubdexin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.DEX = DND_GM_Helper_N::NPC_N::npc.DEX - 1;
    ui->txtDexin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.DEX));
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("DEX");
}

void NPCbattlestats::on_butaddconin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.CON = DND_GM_Helper_N::NPC_N::npc.CON + 1;
    ui->TxtConin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CON));
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("CON");
}

void NPCbattlestats::on_butsubconin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.CON = DND_GM_Helper_N::NPC_N::npc.CON - 1;
    ui->TxtConin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CON));
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("CON");
}

void NPCbattlestats::on_butaddintin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.INT = DND_GM_Helper_N::NPC_N::npc.INT + 1;
    ui->txtIntin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.INT));
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("INT");
}

void NPCbattlestats::on_butsubintin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.INT = DND_GM_Helper_N::NPC_N::npc.INT - 1;
    ui->txtIntin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.INT));
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("INT");
}

void NPCbattlestats::on_butaddwisin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.SAG = DND_GM_Helper_N::NPC_N::npc.SAG + 1;
    ui->txtWisin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.SAG));
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("SAG");
}

void NPCbattlestats::on_butsubwisin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.SAG = DND_GM_Helper_N::NPC_N::npc.SAG - 1;
    ui->txtWisin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.SAG));
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("SAG");
}

void NPCbattlestats::on_butaddchain_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.CHA = DND_GM_Helper_N::NPC_N::npc.CHA + 1;
    ui->txtChain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CHA));
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("CHA");
}

void NPCbattlestats::on_butsubchain_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.CHA = DND_GM_Helper_N::NPC_N::npc.CHA - 1;
    ui->txtChain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CHA));
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("CHA");
}

void NPCbattlestats::on_butRandabilityin_clicked()
{
    bool isabilityvalid = false ;
    while (isabilityvalid == false){
        DND_GM_Helper_N::NPC_N::npc.FOR = DND_GM_Helper_N::NPC_N::npc.Calculate_Carecteristics();
        DND_GM_Helper_N::NPC_N::npc.DEX = DND_GM_Helper_N::NPC_N::npc.Calculate_Carecteristics();
        DND_GM_Helper_N::NPC_N::npc.CON = DND_GM_Helper_N::NPC_N::npc.Calculate_Carecteristics();
        DND_GM_Helper_N::NPC_N::npc.INT = DND_GM_Helper_N::NPC_N::npc.Calculate_Carecteristics();
        DND_GM_Helper_N::NPC_N::npc.SAG = DND_GM_Helper_N::NPC_N::npc.Calculate_Carecteristics();
        DND_GM_Helper_N::NPC_N::npc.CHA = DND_GM_Helper_N::NPC_N::npc.Calculate_Carecteristics();
        if (DND_GM_Helper_N::NPC_N::npc.FOR + DND_GM_Helper_N::NPC_N::npc.DEX + DND_GM_Helper_N::NPC_N::npc.CON + DND_GM_Helper_N::NPC_N::npc.INT + DND_GM_Helper_N::NPC_N::npc.SAG + DND_GM_Helper_N::NPC_N::npc.CHA > 27) {
            isabilityvalid = true;
        }
    }
    ui->txtStrin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.FOR));
    ui->txtDexin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.DEX));
    ui->TxtConin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CON));
    ui->txtIntin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.INT));
    ui->txtWisin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.SAG));
    ui->txtChain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CHA));
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("ALL");
}

void NPCbattlestats::on_txtcain_textChanged(const QString &arg1)
{
    DND_GM_Helper_N::NPC_N::npc.CA = ui->txtcain->text().toInt();
}


void NPCbattlestats::on_butsubACin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.CA = DND_GM_Helper_N::NPC_N::npc.CA - 1;
    ui->txtcain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CA));
}


void NPCbattlestats::on_butaddACin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.CA = DND_GM_Helper_N::NPC_N::npc.CA + 1;
    ui->txtcain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CA));
}

void NPCbattlestats::on_butrandcain_clicked()
{
    std::random_device rdCA;
    std::mt19937 genCA(rdCA());
    std::uniform_int_distribution<> disCA(3 , 20);
    DND_GM_Helper_N::NPC_N::npc.CA = disCA(genCA);
    ui->txtcain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CA));
}


void NPCbattlestats::on_butCalCAin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.CA = DND_GM_Helper_N::NPC_N::npc.Calculat_CA();
    ui->txtcain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CA));
}


void NPCbattlestats::on_butResetallstatsin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.Reset_All_Stats();
    ui->txtStrin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.FOR));
    ui->txtDexin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.DEX));
    ui->TxtConin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CON));
    ui->txtIntin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.INT));
    ui->txtWisin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.SAG));
    ui->txtChain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CHA));
    ui->txtcain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CA));
    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("ALL");
}

void NPCbattlestats::on_txtNAin_textChanged(const QString &arg1)
{
    DND_GM_Helper_N::NPC_N::npc.Natural_Armor = ui->txtNAin->text().toInt();
}

void NPCbattlestats::on_butsubNAin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.Natural_Armor = DND_GM_Helper_N::NPC_N::npc.Natural_Armor - 1;
    ui->txtNAin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.Natural_Armor));
}

void NPCbattlestats::on_butaddNAin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.Natural_Armor = DND_GM_Helper_N::NPC_N::npc.Natural_Armor + 1;
    ui->txtNAin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.Natural_Armor));
}

void NPCbattlestats::on_butrandNAin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.Get_Random_Natural_Armor();
    ui->txtNAin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.Natural_Armor));
}

void NPCbattlestats::on_DDArmorin_activated(int index)
{
    //Temporary
    if (index == 1) {
        DND_GM_Helper_N::NPC_N::npc.CA = DND_GM_Helper_N::NPC_N::npc.CA + 2;
        ui->txtcain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CA));
    }
}

void NPCbattlestats::on_DDShieldin_activated(int index)
{
    //Temporary
    if (index == 1) {
        DND_GM_Helper_N::NPC_N::npc.CA = DND_GM_Helper_N::NPC_N::npc.CA + 2;
        ui->txtcain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CA));
    }
}
