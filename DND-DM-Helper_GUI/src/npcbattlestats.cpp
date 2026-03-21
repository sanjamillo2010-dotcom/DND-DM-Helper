#include "../include/npcbattlestats.h"
#include "ui_npcbattlestats.h"
#include "../include/NPC.h"
#include "../include/widget.h"

#include <random>
#include <yaml-cpp/yaml.h>
#include <iostream>

YAML::Node config = YAML::LoadFile("conf/Armor_conf.yaml");
YAML::Node WeaponConfig = YAML::LoadFile("conf/Weapon_conf.yaml");
YAML::Node npcConfig = YAML::LoadFile("conf/NPC_conf.yaml");

YAML::Node Armors = config["Armor_conf"]["Armors"];
YAML::Node Light_Armors_list = config["Armor_conf"]["Armors_list"]["light_armor"];
YAML::Node Mid_Armors_list = config["Armor_conf"]["Armors_list"]["mid_armor"];
YAML::Node Heavy_Armors_list = config["Armor_conf"]["Armors_list"]["heavy_armor"];
YAML::Node Shild_list = config["Armor_conf"]["Armors_list"]["shild"];

YAML::Node Weapon_list = WeaponConfig["Weapon_conf"]["Weapon_list"];
YAML::Node Weapon_class_Specifique_list = WeaponConfig["Weapon_conf"]["Weapon_list_class_specifique"]["List_of_class"];

NPCbattlestats::NPCbattlestats(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NPCbattlestats)
{
    ui->setupUi(this);
    if (DND_GM_Helper_N::NPC_N::npc.classtype.HasLightArmor == true) {
        for (const auto& Armor : Light_Armors_list ) {
            std::string ArmorFileName = Armor.as<std::string>();
            bool isShild = Armors[ArmorFileName]["isShild"].as<bool>();
            bool HasIron = config["Armor_conf"]["Armors"][ArmorFileName]["asIron"].as<bool>();
            if (isShild == false) {
                if (DND_GM_Helper_N::NPC_N::npc.classtype.name == "Druid" && HasIron == true) {
                    continue;
                }
                std::string ArmorName = Armors[ArmorFileName]["Name"].as<std::string>();
                std::string ArmorProt = Armors[ArmorFileName]["Prot"].as<std::string>();
                std::string ArmorEntry = ArmorName + " ( +" + ArmorProt + " CA )";
                ui->DDArmorin->addItem(QString::fromStdString(ArmorEntry));
            }
        }
    }

    if (DND_GM_Helper_N::NPC_N::npc.classtype.HasMidArmor == true) {
        for (const auto& Armor : Mid_Armors_list ) {
            std::string ArmorFileName = Armor.as<std::string>();
            bool isShild = Armors[ArmorFileName]["isShild"].as<bool>();
            bool HasIron = config["Armor_conf"]["Armors"][ArmorFileName]["asIron"].as<bool>();
            if (isShild == false) {
                if (DND_GM_Helper_N::NPC_N::npc.classtype.name == "Druid" && HasIron == true) {
                    continue;
                }
                std::string ArmorName = Armors[ArmorFileName]["Name"].as<std::string>();
                std::string ArmorProt = Armors[ArmorFileName]["Prot"].as<std::string>();
                std::string ArmorEntry = ArmorName + " ( +" + ArmorProt + " CA )";
                ui->DDArmorin->addItem(QString::fromStdString(ArmorEntry));
            }
        }
    }

    if (DND_GM_Helper_N::NPC_N::npc.classtype.HasHeavyArmor == true) {
        for (const auto& Armor : Heavy_Armors_list ) {
            std::string ArmorFileName = Armor.as<std::string>();
            bool isShild = Armors[ArmorFileName]["isShild"].as<bool>();
            if (isShild == false) {
                std::string ArmorName = Armors[ArmorFileName]["Name"].as<std::string>();
                std::string ArmorProt = Armors[ArmorFileName]["Prot"].as<std::string>();
                std::string ArmorEntry = ArmorName + " ( +" + ArmorProt + " CA )";
                ui->DDArmorin->addItem(QString::fromStdString(ArmorEntry));
            }
        }
    }

    if (DND_GM_Helper_N::NPC_N::npc.classtype.HasShild == true) {
        for (const auto& Armor : Shild_list) {
            std::string ArmorFileName = Armor.as<std::string>();
            if (ArmorFileName == "targe" && !DND_GM_Helper_N::NPC_N::npc.classtype.Hastarge) {
                continue;
            }
            std::string ArmorName = Armors[ArmorFileName]["Name"].as<std::string>();
            std::string ArmorProt = Armors[ArmorFileName]["Prot"].as<std::string>();
            std::string ArmorEntry = ArmorName + " (+" + ArmorProt + " CA)";
            ui->DDShieldin->addItem(QString::fromStdString(ArmorEntry));
        }
    }
    YAML::Node UnarmedKey_list = WeaponConfig["Weapon_conf"]["Weapon_list"]["unarmed"];
    for (const auto& UnarmedKey : UnarmedKey_list) {
        std::string Unarmed_WeaponName = WeaponConfig["Weapon_conf"]["Weapons"][UnarmedKey.as<std::string>()]["Name"].as<std::string>();
        std::string Unarmed_Num_of_Dice = WeaponConfig["Weapon_conf"]["Weapons"][UnarmedKey.as<std::string>()]["Num_of_Dice"].as<std::string>();
        std::string Unarmed_Dice_Value = WeaponConfig["Weapon_conf"]["Weapons"][UnarmedKey.as<std::string>()]["Dice_Value"].as<std::string>();
        std::string Entry = Unarmed_WeaponName + " : " + Unarmed_Num_of_Dice + "d" + Unarmed_Dice_Value;
        ui->ddWeapons1->addItem(QString::fromStdString(Entry));
        ui->ddWeapons2->addItem(QString::fromStdString(Entry));
        ui->ddWeapons3->addItem(QString::fromStdString(Entry));
        ui->ddWeapons4->addItem(QString::fromStdString(Entry));
        ui->ddWeapons5->addItem(QString::fromStdString(Entry));

    }
    if (DND_GM_Helper_N::NPC_N::npc.classtype.Hassimple_light == true) {
        YAML::Node simple_light_list = WeaponConfig["Weapon_conf"]["Weapon_list"]["simple_light"];
        for (const auto& WeaponKey : simple_light_list) {
            std::string simple_light_WeaponName = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Name"].as<std::string>();
            std::string simple_light_Num_of_Dice = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Num_of_Dice"].as<std::string>();
            std::string simple_light_Dice_Value = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Dice_Value"].as<std::string>();
            std::string Entry = simple_light_WeaponName + " : " + simple_light_Num_of_Dice + "d" + simple_light_Dice_Value;
            ui->ddWeapons1->addItem(QString::fromStdString(Entry));
            ui->ddWeapons2->addItem(QString::fromStdString(Entry));
            ui->ddWeapons3->addItem(QString::fromStdString(Entry));
            ui->ddWeapons4->addItem(QString::fromStdString(Entry));
            ui->ddWeapons5->addItem(QString::fromStdString(Entry));
        }
    }
    if (DND_GM_Helper_N::NPC_N::npc.classtype.Hassimple_one_handed == true) {
        YAML::Node simple_one_handed_list = WeaponConfig["Weapon_conf"]["Weapon_list"]["simple_one_handed"];
        for (const auto& WeaponKey : simple_one_handed_list) {
            std::string simple_one_handed_WeaponName = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Name"].as<std::string>();
            std::string simple_one_handed_Num_of_Dice = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Num_of_Dice"].as<std::string>();
            std::string simple_one_handed_Dice_Value = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Dice_Value"].as<std::string>();
            std::string Entry = simple_one_handed_WeaponName + " : " + simple_one_handed_Num_of_Dice + "d" + simple_one_handed_Dice_Value;
            ui->ddWeapons1->addItem(QString::fromStdString(Entry));
            ui->ddWeapons2->addItem(QString::fromStdString(Entry));
            ui->ddWeapons3->addItem(QString::fromStdString(Entry));
            ui->ddWeapons4->addItem(QString::fromStdString(Entry));
            ui->ddWeapons5->addItem(QString::fromStdString(Entry));
        }
    }
    if (DND_GM_Helper_N::NPC_N::npc.classtype.Hassimple_two_handed == true) {
        YAML::Node simple_two_handed_list = WeaponConfig["Weapon_conf"]["Weapon_list"]["simple_two_handed"];
        for (const auto& WeaponKey : simple_two_handed_list) {
            std::string simple_two_handed_WeaponName = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Name"].as<std::string>();
            std::string simple_two_handed_Num_of_Dice = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Num_of_Dice"].as<std::string>();
            std::string simple_two_handed_Dice_Value = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Dice_Value"].as<std::string>();
            std::string Entry = simple_two_handed_WeaponName + " : " + simple_two_handed_Num_of_Dice + "d" + simple_two_handed_Dice_Value;
            ui->ddWeapons1->addItem(QString::fromStdString(Entry));
            ui->ddWeapons2->addItem(QString::fromStdString(Entry));
            ui->ddWeapons3->addItem(QString::fromStdString(Entry));
            ui->ddWeapons4->addItem(QString::fromStdString(Entry));
            ui->ddWeapons5->addItem(QString::fromStdString(Entry));
        }
    }
    if (DND_GM_Helper_N::NPC_N::npc.classtype.Hassimple_ranged == true) {
        YAML::Node simple_ranged_list = WeaponConfig["Weapon_conf"]["Weapon_list"]["simple_ranged"];
        for (const auto& WeaponKey : simple_ranged_list) {
            std::string simple_ranged_WeaponName = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Name"].as<std::string>();
            std::string simple_ranged_Num_of_Dice = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Num_of_Dice"].as<std::string>();
            std::string simple_ranged_Dice_Value = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Dice_Value"].as<std::string>();
            std::string Entry = simple_ranged_WeaponName + " : " + simple_ranged_Num_of_Dice + "d" + simple_ranged_Dice_Value;
            ui->ddWeapons1->addItem(QString::fromStdString(Entry));
            ui->ddWeapons2->addItem(QString::fromStdString(Entry));
            ui->ddWeapons3->addItem(QString::fromStdString(Entry));
            ui->ddWeapons4->addItem(QString::fromStdString(Entry));
            ui->ddWeapons5->addItem(QString::fromStdString(Entry));
        }
    }
    if (DND_GM_Helper_N::NPC_N::npc.classtype.Hasmartial_light == true) {
        YAML::Node martial_light_list = WeaponConfig["Weapon_conf"]["Weapon_list"]["martial_light"];
        for (const auto& WeaponKey : martial_light_list) {
            std::string martial_light_WeaponName = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Name"].as<std::string>();
            std::string martial_light_Num_of_Dice = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Num_of_Dice"].as<std::string>();
            std::string martial_light_Dice_Value = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Dice_Value"].as<std::string>();
            std::string Entry = martial_light_WeaponName + " : " + martial_light_Num_of_Dice + "d" + martial_light_Dice_Value;
            ui->ddWeapons1->addItem(QString::fromStdString(Entry));
            ui->ddWeapons2->addItem(QString::fromStdString(Entry));
            ui->ddWeapons3->addItem(QString::fromStdString(Entry));
            ui->ddWeapons4->addItem(QString::fromStdString(Entry));
            ui->ddWeapons5->addItem(QString::fromStdString(Entry));
        }
    }
    if (DND_GM_Helper_N::NPC_N::npc.classtype.Hasmartial_one_handed == true) {
        YAML::Node martial_one_handed_list = WeaponConfig["Weapon_conf"]["Weapon_list"]["martial_one_handed"];
        for (const auto& WeaponKey : martial_one_handed_list) {
            std::string martial_one_handed_WeaponName = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Name"].as<std::string>();
            std::string martial_one_handed_Num_of_Dice = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Num_of_Dice"].as<std::string>();
            std::string martial_one_handed_Dice_Value = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Dice_Value"].as<std::string>();
            std::string Entry = martial_one_handed_WeaponName + " : " + martial_one_handed_Num_of_Dice + "d" + martial_one_handed_Dice_Value;
            ui->ddWeapons1->addItem(QString::fromStdString(Entry));
            ui->ddWeapons2->addItem(QString::fromStdString(Entry));
            ui->ddWeapons3->addItem(QString::fromStdString(Entry));
            ui->ddWeapons4->addItem(QString::fromStdString(Entry));
            ui->ddWeapons5->addItem(QString::fromStdString(Entry));
        }
    }
    if (DND_GM_Helper_N::NPC_N::npc.classtype.Hasmartial_two_handed == true) {
        YAML::Node martial_two_handed_list = WeaponConfig["Weapon_conf"]["Weapon_list"]["martial_two_handed"];
        for (const auto& WeaponKey : martial_two_handed_list) {
            std::string martial_two_handed_WeaponName = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Name"].as<std::string>();
            std::string martial_two_handed_Num_of_Dice = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Num_of_Dice"].as<std::string>();
            std::string martial_two_handed_Dice_Value = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Dice_Value"].as<std::string>();
            std::string Entry = martial_two_handed_WeaponName + " : " + martial_two_handed_Num_of_Dice + "d" + martial_two_handed_Dice_Value;
            ui->ddWeapons1->addItem(QString::fromStdString(Entry));
            ui->ddWeapons2->addItem(QString::fromStdString(Entry));
            ui->ddWeapons3->addItem(QString::fromStdString(Entry));
            ui->ddWeapons4->addItem(QString::fromStdString(Entry));
            ui->ddWeapons5->addItem(QString::fromStdString(Entry));
        }
    }
    if (DND_GM_Helper_N::NPC_N::npc.classtype.Hasmartial_ranged == true) {
        YAML::Node martial_ranged_list = WeaponConfig["Weapon_conf"]["Weapon_list"]["martial_ranged"];
        for (const auto& WeaponKey : martial_ranged_list) {
            std::string martial_ranged_WeaponName = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Name"].as<std::string>();
            std::string martial_ranged_Num_of_Dice = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Num_of_Dice"].as<std::string>();
            std::string martial_ranged_Dice_Value = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Dice_Value"].as<std::string>();
            std::string Entry = martial_ranged_WeaponName + " : " + martial_ranged_Num_of_Dice + "d" + martial_ranged_Dice_Value;
            ui->ddWeapons1->addItem(QString::fromStdString(Entry));
            ui->ddWeapons2->addItem(QString::fromStdString(Entry));
            ui->ddWeapons3->addItem(QString::fromStdString(Entry));
            ui->ddWeapons4->addItem(QString::fromStdString(Entry));
            ui->ddWeapons5->addItem(QString::fromStdString(Entry));
        }
    }
    if (DND_GM_Helper_N::NPC_N::npc.classtype.Hasexotic_light == true) {
        YAML::Node exotic_light_list = WeaponConfig["Weapon_conf"]["Weapon_list"]["exotic_light"];
        for (const auto& WeaponKey : exotic_light_list) {
            std::string exotic_light_WeaponName = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Name"].as<std::string>();
            std::string exotic_light_Num_of_Dice = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Num_of_Dice"].as<std::string>();
            std::string exotic_light_Dice_Value = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Dice_Value"].as<std::string>();
            std::string Entry = exotic_light_WeaponName + " : " + exotic_light_Num_of_Dice + "d" + exotic_light_Dice_Value;
            ui->ddWeapons1->addItem(QString::fromStdString(Entry));
            ui->ddWeapons2->addItem(QString::fromStdString(Entry));
            ui->ddWeapons3->addItem(QString::fromStdString(Entry));
            ui->ddWeapons4->addItem(QString::fromStdString(Entry));
            ui->ddWeapons5->addItem(QString::fromStdString(Entry));
        }
    }
    if (DND_GM_Helper_N::NPC_N::npc.classtype.Hasexotic_one_handed == true) {
        YAML::Node exotic_one_handed_list = WeaponConfig["Weapon_conf"]["Weapon_list"]["exotic_one_handed"];
        for (const auto& WeaponKey : exotic_one_handed_list) {
            std::string exotic_one_handed_WeaponName = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Name"].as<std::string>();
            std::string exotic_one_handed_Num_of_Dice = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Num_of_Dice"].as<std::string>();
            std::string exotic_one_handed_Dice_Value = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Dice_Value"].as<std::string>();
            std::string Entry = exotic_one_handed_WeaponName + " : " + exotic_one_handed_Num_of_Dice + "d" + exotic_one_handed_Dice_Value;
            ui->ddWeapons1->addItem(QString::fromStdString(Entry));
            ui->ddWeapons2->addItem(QString::fromStdString(Entry));
            ui->ddWeapons3->addItem(QString::fromStdString(Entry));
            ui->ddWeapons4->addItem(QString::fromStdString(Entry));
            ui->ddWeapons5->addItem(QString::fromStdString(Entry));
        }
    }
    if (DND_GM_Helper_N::NPC_N::npc.classtype.Hasexotic_two_handed == true) {
        YAML::Node exotic_two_handed_list = WeaponConfig["Weapon_conf"]["Weapon_list"]["exotic_two_handed"];
        for (const auto& WeaponKey : exotic_two_handed_list) {
            std::string exotic_two_handed_WeaponName = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Name"].as<std::string>();
            std::string exotic_two_handed_Num_of_Dice = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Num_of_Dice"].as<std::string>();
            std::string exotic_two_handed_Dice_Value = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Dice_Value"].as<std::string>();
            std::string Entry = exotic_two_handed_WeaponName + " : " + exotic_two_handed_Num_of_Dice + "d" + exotic_two_handed_Dice_Value;
            ui->ddWeapons1->addItem(QString::fromStdString(Entry));
            ui->ddWeapons2->addItem(QString::fromStdString(Entry));
            ui->ddWeapons3->addItem(QString::fromStdString(Entry));
            ui->ddWeapons4->addItem(QString::fromStdString(Entry));
            ui->ddWeapons5->addItem(QString::fromStdString(Entry));
        }
    }
    if (DND_GM_Helper_N::NPC_N::npc.classtype.Hasexotic_ranged == true) {
        YAML::Node exotic_ranged_list = WeaponConfig["Weapon_conf"]["Weapon_list"]["exotic_ranged"];
        for (const auto& WeaponKey : exotic_ranged_list) {
            std::string exotic_ranged_WeaponName = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Name"].as<std::string>();
            std::string exotic_ranged_Num_of_Dice = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Num_of_Dice"].as<std::string>();
            std::string exotic_ranged_Dice_Value = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Dice_Value"].as<std::string>();
            std::string Entry = exotic_ranged_WeaponName + " : " + exotic_ranged_Num_of_Dice + "d" + exotic_ranged_Dice_Value;
            ui->ddWeapons1->addItem(QString::fromStdString(Entry));
            ui->ddWeapons2->addItem(QString::fromStdString(Entry));
            ui->ddWeapons3->addItem(QString::fromStdString(Entry));
            ui->ddWeapons4->addItem(QString::fromStdString(Entry));
            ui->ddWeapons5->addItem(QString::fromStdString(Entry));
        }
    }
    std::vector<std::string> class_Specifique_list;
    for (const auto& Node : Weapon_class_Specifique_list) {
        class_Specifique_list.push_back(Node.as<std::string>());
    }
    if (std::find(class_Specifique_list.begin(), class_Specifique_list.end(), DND_GM_Helper_N::NPC_N::npc.classtype.name) != class_Specifique_list.end()) {
        YAML::Node Specifique_Weapon_list = WeaponConfig["Weapon_conf"]["Weapon_list_class_specifique"][DND_GM_Helper_N::NPC_N::npc.classtype.name];
        for (const auto& WeaponKey : Specifique_Weapon_list) {
            std::string Specifique_Weapon_WeaponName = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Name"].as<std::string>();
            std::string Specifique_Weapon_Num_of_Dice = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Num_of_Dice"].as<std::string>();
            std::string Specifique_Weapon_Dice_Value = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey.as<std::string>()]["Dice_Value"].as<std::string>();
            std::string Entry = Specifique_Weapon_WeaponName + " : " + Specifique_Weapon_Num_of_Dice + "d" + Specifique_Weapon_Dice_Value;
            ui->ddWeapons1->addItem(QString::fromStdString(Entry));
            ui->ddWeapons2->addItem(QString::fromStdString(Entry));
            ui->ddWeapons3->addItem(QString::fromStdString(Entry));
            ui->ddWeapons4->addItem(QString::fromStdString(Entry));
            ui->ddWeapons5->addItem(QString::fromStdString(Entry));
        }
    }
    if (DND_GM_Helper_N::NPC_N::npc.classtype.name == "Cleric") {
        if (DND_GM_Helper_N::NPC_N::npc.divinity.name.empty()) {
            std::cout << "Cleric has no divinity assigned, skipping favored weapon." << std::endl;
        } else {
            std::string deityName = DND_GM_Helper_N::NPC_N::npc.divinity.name;
            YAML::Node weaponNode = npcConfig["NPC_conf"]["DivinityDetails"][deityName]["FavoritWeapon"];
            if (!weaponNode.IsDefined()) {
                std::cout << "WARNING: Deity [" << deityName << "] not found in DivinityDetails" << std::endl;
            } else {
                std::string FavoritWeapon = weaponNode.as<std::string>();
                std::string FavoritWeapon_Name = WeaponConfig["Weapon_conf"]["Weapons"][FavoritWeapon]["Name"].as<std::string>();
                std::string FavoritWeapon_Num_of_Dice = WeaponConfig["Weapon_conf"]["Weapons"][FavoritWeapon]["Num_of_Dice"].as<std::string>();
                std::string FavoritWeapon_Dice_Value = WeaponConfig["Weapon_conf"]["Weapons"][FavoritWeapon]["Dice_Value"].as<std::string>();
                std::string Entry = FavoritWeapon_Name + " : " + FavoritWeapon_Num_of_Dice + "d" + FavoritWeapon_Dice_Value;
                ui->ddWeapons1->addItem(QString::fromStdString(Entry));
                ui->ddWeapons2->addItem(QString::fromStdString(Entry));
                ui->ddWeapons3->addItem(QString::fromStdString(Entry));
                ui->ddWeapons4->addItem(QString::fromStdString(Entry));
                ui->ddWeapons5->addItem(QString::fromStdString(Entry));
            }
        }
    }


    DND_GM_Helper_N::NPC_N::npc.Calculat_Bonus("ALL");
    DND_GM_Helper_N::NPC_N::npc.Calculat_CA();
    ui->txtStrin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.FOR));
    ui->txtDexin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.DEX));
    ui->TxtConin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CON));
    ui->txtIntin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.INT));
    ui->txtWisin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.SAG));
    ui->txtChain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CHA));
    ui->txtcain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CA));
    ui->txtNAin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.Natural_Armor));
    ui->DDArmorin->setCurrentIndex(DND_GM_Helper_N::NPC_N::npc.Armor.index);
    ui->DDShieldin->setCurrentIndex(DND_GM_Helper_N::NPC_N::npc.Shield.index);
    ui->txtcain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CA));
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
    std::cout << "Added" << std::endl;
    DND_GM_Helper_N::NPC_N::npc.FOR = DND_GM_Helper_N::NPC_N::npc.FOR + 1;
    ui->txtStrin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.FOR));
}

void NPCbattlestats::on_butsubstrin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.FOR = DND_GM_Helper_N::NPC_N::npc.FOR - 1;
    ui->txtStrin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.FOR));
}

void NPCbattlestats::on_butadddexin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.DEX = DND_GM_Helper_N::NPC_N::npc.DEX + 1;
    ui->txtDexin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.DEX));

}

void NPCbattlestats::on_butsubdexin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.DEX = DND_GM_Helper_N::NPC_N::npc.DEX - 1;
    ui->txtDexin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.DEX));
}

void NPCbattlestats::on_butaddconin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.CON = DND_GM_Helper_N::NPC_N::npc.CON + 1;
    ui->TxtConin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CON));
}

void NPCbattlestats::on_butsubconin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.CON = DND_GM_Helper_N::NPC_N::npc.CON - 1;
    ui->TxtConin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CON));
}

void NPCbattlestats::on_butaddintin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.INT = DND_GM_Helper_N::NPC_N::npc.INT + 1;
    ui->txtIntin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.INT));
}

void NPCbattlestats::on_butsubintin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.INT = DND_GM_Helper_N::NPC_N::npc.INT - 1;
    ui->txtIntin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.INT));
}

void NPCbattlestats::on_butaddwisin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.SAG = DND_GM_Helper_N::NPC_N::npc.SAG + 1;
    ui->txtWisin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.SAG));
}

void NPCbattlestats::on_butsubwisin_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.SAG = DND_GM_Helper_N::NPC_N::npc.SAG - 1;
    ui->txtWisin->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.SAG));
}

void NPCbattlestats::on_butaddchain_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.CHA = DND_GM_Helper_N::NPC_N::npc.CHA + 1;
    ui->txtChain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CHA));
}

void NPCbattlestats::on_butsubchain_clicked()
{
    DND_GM_Helper_N::NPC_N::npc.CHA = DND_GM_Helper_N::NPC_N::npc.CHA - 1;
    ui->txtChain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CHA));
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
    DND_GM_Helper_N::NPC_N::npc.Armor.index = index;
    if (index > 0) {
        QString selected = ui->DDArmorin->currentText();
        QString ArmorName = selected.split(" (").first();
        ArmorName = ArmorName.toLower();
        ArmorName = ArmorName.replace(" " , "_");

        std::string ArmorKey = ArmorName.toStdString();
        DND_GM_Helper_N::NPC_N::npc.Armor.Name = config["Armor_conf"]["Armors"][ArmorKey]["Name"].as<std::string>();
        DND_GM_Helper_N::NPC_N::npc.Armor.Prix = config["Armor_conf"]["Armors"][ArmorKey]["Prix"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Armor.Prot = config["Armor_conf"]["Armors"][ArmorKey]["Prot"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Armor.MaxDEX_Bonus = config["Armor_conf"]["Armors"][ArmorKey]["MaxDEX_Bonus"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Armor.Poids = config["Armor_conf"]["Armors"][ArmorKey]["Poids"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Armor.Type = config["Armor_conf"]["Armors"][ArmorKey]["Type"].as<std::string>();
        DND_GM_Helper_N::NPC_N::npc.Armor.isShild = config["Armor_conf"]["Armors"][ArmorKey]["isShild"].as<bool>();
    }
    else {
        DND_GM_Helper_N::NPC_N::npc.Armor.Name = "";
        DND_GM_Helper_N::NPC_N::npc.Armor.Prix = 0;
        DND_GM_Helper_N::NPC_N::npc.Armor.Prot = 0;
        DND_GM_Helper_N::NPC_N::npc.Armor.Poids = 0;
        DND_GM_Helper_N::NPC_N::npc.Armor.Type = "";
        DND_GM_Helper_N::NPC_N::npc.Armor.isShild = false;
        DND_GM_Helper_N::NPC_N::npc.Armor.asIron  = false;
    }
    DND_GM_Helper_N::NPC_N::npc.Calculat_CA();
    ui->txtcain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CA));
}

void NPCbattlestats::on_DDShieldin_activated(int index)
{
    DND_GM_Helper_N::NPC_N::npc.Shield.index = index;
    if (index > 0) {
        QString selected = ui->DDShieldin->currentText();
        QString ArmorName = selected.split(" (").first();
        ArmorName = ArmorName.toLower();
        ArmorName = ArmorName.replace(" " , "_");

        std::string ArmorKey = ArmorName.toStdString();
        DND_GM_Helper_N::NPC_N::npc.Shield.Name = config["Armor_conf"]["Armors"][ArmorKey]["Name"].as<std::string>();
        DND_GM_Helper_N::NPC_N::npc.Shield.Prix = config["Armor_conf"]["Armors"][ArmorKey]["Prix"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Shield.Prot = config["Armor_conf"]["Armors"][ArmorKey]["Prot"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Shield.Poids = config["Armor_conf"]["Armors"][ArmorKey]["Poids"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Shield.Type = config["Armor_conf"]["Armors"][ArmorKey]["Type"].as<std::string>();
        DND_GM_Helper_N::NPC_N::npc.Shield.isShild = config["Armor_conf"]["Armors"][ArmorKey]["isShild"].as<bool>();
        DND_GM_Helper_N::NPC_N::npc.Shield.asIron = config["Armor_conf"]["Armors"][ArmorKey]["asIron"].as<bool>();
    }
    else {
        DND_GM_Helper_N::NPC_N::npc.Shield.Name = "";
        DND_GM_Helper_N::NPC_N::npc.Shield.Prix = 0;
        DND_GM_Helper_N::NPC_N::npc.Shield.Prot = 0;
        DND_GM_Helper_N::NPC_N::npc.Shield.Poids = 0;
        DND_GM_Helper_N::NPC_N::npc.Shield.Type = "";
        DND_GM_Helper_N::NPC_N::npc.Shield.isShild = false;
        DND_GM_Helper_N::NPC_N::npc.Shield.asIron  = false;
    }
    DND_GM_Helper_N::NPC_N::npc.Calculat_CA();
    ui->txtcain->setText(QString::number(DND_GM_Helper_N::NPC_N::npc.CA));
}

void NPCbattlestats::on_ddWeapons1_activated(int index)
{
    DND_GM_Helper_N::NPC_N::npc.Weapon1.Index = index;
    if (index > 0) {
        QString selected = ui->ddWeapons1->currentText();
        QString WeaponName = selected.split(" : ").first();
        WeaponName = WeaponName.toLower();
        WeaponName = WeaponName.replace(" " , "_");
        WeaponName = WeaponName.remove(",");

        std::string WeaponKey = WeaponName.toStdString();
        DND_GM_Helper_N::NPC_N::npc.Weapon1.Name = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Name"].as<std::string>();
        DND_GM_Helper_N::NPC_N::npc.Weapon1.Attack.Num_of_Dice = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Num_of_Dice"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Weapon1.Attack.Dice_Value = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Dice_Value"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Weapon1.Prix = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Prix"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Weapon1.Poids = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Poids"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Weapon1.Type = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Type"].as<std::string>();
    }
    else {
        DND_GM_Helper_N::NPC_N::npc.Weapon1.Name = "";
        DND_GM_Helper_N::NPC_N::npc.Weapon1.Attack.Num_of_Dice = 0;
        DND_GM_Helper_N::NPC_N::npc.Weapon1.Attack.Dice_Value = 0;
        DND_GM_Helper_N::NPC_N::npc.Weapon1.Prix = 0;
        DND_GM_Helper_N::NPC_N::npc.Weapon1.Poids = 0;
        DND_GM_Helper_N::NPC_N::npc.Weapon1.Type = "";
    }
}


void NPCbattlestats::on_ddWeapons2_activated(int index)
{
    DND_GM_Helper_N::NPC_N::npc.Weapon2.Index = index;
    if (index > 0) {
        QString selected = ui->ddWeapons2->currentText();
        QString WeaponName = selected.split(" : ").first();
        WeaponName = WeaponName.toLower();
        WeaponName = WeaponName.replace(" " , "_");
        WeaponName = WeaponName.remove(",");

        std::string WeaponKey = WeaponName.toStdString();
        DND_GM_Helper_N::NPC_N::npc.Weapon2.Name = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Name"].as<std::string>();
        DND_GM_Helper_N::NPC_N::npc.Weapon2.Attack.Num_of_Dice = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Num_of_Dice"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Weapon2.Attack.Dice_Value = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Dice_Value"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Weapon2.Prix = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Prix"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Weapon2.Poids = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Poids"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Weapon2.Type = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Type"].as<std::string>();
    }
    else {
        DND_GM_Helper_N::NPC_N::npc.Weapon2.Name = "";
        DND_GM_Helper_N::NPC_N::npc.Weapon2.Attack.Num_of_Dice = 0;
        DND_GM_Helper_N::NPC_N::npc.Weapon2.Attack.Dice_Value = 0;
        DND_GM_Helper_N::NPC_N::npc.Weapon2.Prix = 0;
        DND_GM_Helper_N::NPC_N::npc.Weapon2.Poids = 0;
        DND_GM_Helper_N::NPC_N::npc.Weapon2.Type = "";
    }
}


void NPCbattlestats::on_ddWeapons3_activated(int index)
{
    DND_GM_Helper_N::NPC_N::npc.Weapon3.Index = index;
    if (index > 0) {
        QString selected = ui->ddWeapons3->currentText();
        QString WeaponName = selected.split(" : ").first();
        WeaponName = WeaponName.toLower();
        WeaponName = WeaponName.replace(" " , "_");
        WeaponName = WeaponName.remove(",");

        std::string WeaponKey = WeaponName.toStdString();
        DND_GM_Helper_N::NPC_N::npc.Weapon3.Name = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Name"].as<std::string>();
        DND_GM_Helper_N::NPC_N::npc.Weapon3.Attack.Num_of_Dice = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Num_of_Dice"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Weapon3.Attack.Dice_Value = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Dice_Value"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Weapon3.Prix = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Prix"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Weapon3.Poids = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Poids"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Weapon3.Type = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Type"].as<std::string>();
    }
    else {
        DND_GM_Helper_N::NPC_N::npc.Weapon3.Name = "";
        DND_GM_Helper_N::NPC_N::npc.Weapon3.Attack.Num_of_Dice = 0;
        DND_GM_Helper_N::NPC_N::npc.Weapon3.Attack.Dice_Value = 0;
        DND_GM_Helper_N::NPC_N::npc.Weapon3.Prix = 0;
        DND_GM_Helper_N::NPC_N::npc.Weapon3.Poids = 0;
        DND_GM_Helper_N::NPC_N::npc.Weapon3.Type = "";
    }
}


void NPCbattlestats::on_ddWeapons4_activated(int index)
{
    DND_GM_Helper_N::NPC_N::npc.Weapon4.Index = index;
    if (index > 0) {
        QString selected = ui->ddWeapons4->currentText();
        QString WeaponName = selected.split(" : ").first();
        WeaponName = WeaponName.toLower();
        WeaponName = WeaponName.replace(" " , "_");
        WeaponName = WeaponName.remove(",");

        std::string WeaponKey = WeaponName.toStdString();
        DND_GM_Helper_N::NPC_N::npc.Weapon4.Name = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Name"].as<std::string>();
        DND_GM_Helper_N::NPC_N::npc.Weapon4.Attack.Num_of_Dice = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Num_of_Dice"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Weapon4.Attack.Dice_Value = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Dice_Value"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Weapon4.Prix = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Prix"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Weapon4.Poids = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Poids"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Weapon4.Type = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Type"].as<std::string>();
    }
    else {
        DND_GM_Helper_N::NPC_N::npc.Weapon4.Name = "";
        DND_GM_Helper_N::NPC_N::npc.Weapon4.Attack.Num_of_Dice = 0;
        DND_GM_Helper_N::NPC_N::npc.Weapon4.Attack.Dice_Value = 0;
        DND_GM_Helper_N::NPC_N::npc.Weapon4.Prix = 0;
        DND_GM_Helper_N::NPC_N::npc.Weapon4.Poids = 0;
        DND_GM_Helper_N::NPC_N::npc.Weapon4.Type = "";
    }
}


void NPCbattlestats::on_ddWeapons5_activated(int index)
{
    DND_GM_Helper_N::NPC_N::npc.Weapon5.Index = index;
    if (index > 0) {
        QString selected = ui->ddWeapons5->currentText();
        QString WeaponName = selected.split(" : ").first();
        WeaponName = WeaponName.toLower();
        WeaponName = WeaponName.replace(" " , "_");
        WeaponName = WeaponName.remove(",");

        std::string WeaponKey = WeaponName.toStdString();
        DND_GM_Helper_N::NPC_N::npc.Weapon5.Name = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Name"].as<std::string>();
        DND_GM_Helper_N::NPC_N::npc.Weapon5.Attack.Num_of_Dice = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Num_of_Dice"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Weapon5.Attack.Dice_Value = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Dice_Value"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Weapon5.Prix = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Prix"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Weapon5.Poids = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Poids"].as<int>();
        DND_GM_Helper_N::NPC_N::npc.Weapon5.Type = WeaponConfig["Weapon_conf"]["Weapons"][WeaponKey]["Type"].as<std::string>();
    }
    else {
        DND_GM_Helper_N::NPC_N::npc.Weapon5.Name = "";
        DND_GM_Helper_N::NPC_N::npc.Weapon5.Attack.Num_of_Dice = 0;
        DND_GM_Helper_N::NPC_N::npc.Weapon5.Attack.Dice_Value = 0;
        DND_GM_Helper_N::NPC_N::npc.Weapon5.Prix = 0;
        DND_GM_Helper_N::NPC_N::npc.Weapon5.Poids = 0;
        DND_GM_Helper_N::NPC_N::npc.Weapon5.Type = "";
    }
}

