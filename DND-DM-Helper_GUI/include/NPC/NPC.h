#ifndef NPC_H
#define NPC_H

#include <string>
#include <yaml-cpp/yaml.h>

#include "../include/NPC/Race.h"
#include "../include/NPC/classtype.h"
#include "../include/NPC/alignment.h"
#include "../include/Inventory/weapon.h"
#include "../include/NPC/divinite.h"
#include "../include/Inventory/armor.h"
#include "../include/Inventory/item.h"

namespace DND_GM_Helper_N {
namespace NPC_N {

class NPC {
public:
    std::string name;
    std::string LastName;
    Race race;
    ClassType classtype;
    std::string Sexe;
    int Age = 0;
    int Size = 0;
    std::string SizeCategory = "";
    int level = 1;
    int XP = 0;
    int HP = 0;
    int FOR = 10;
    int FOR_Bonus;
    int DEX = 10;
    int DEX_Bonus;
    int CON = 10;
    int CON_Bonus;
    int INT = 10;
    int INT_Bonus;
    int SAG = 10;
    int SAG_Bonus;
    int CHA = 10;
    int CHA_Bonus;
    int CA = 10;
    int Natural_Armor = 0;
    DND_GM_Helper_N::Inventory_N::Armor Armor;
    DND_GM_Helper_N::Inventory_N::Armor Shield;
    DND_GM_Helper_N::Inventory_N::Weapon Weapon1;
    DND_GM_Helper_N::Inventory_N::Weapon Weapon2;
    DND_GM_Helper_N::Inventory_N::Weapon Weapon3;
    DND_GM_Helper_N::Inventory_N::Weapon Weapon4;
    DND_GM_Helper_N::Inventory_N::Weapon Weapon5;
    std::string TempItemName;
    std::string TempItemDescription;
    int TempItemPrix;
    int TempItemPoids;
    std::vector<Inventory_N::Item*> itemVector;
    Alignment alignment;
    Divinite divinity;
    void Print_NPC_Stats();
    Race Get_Random_Race();
    ClassType Get_Random_Class();
    Divinite Get_Random_Divinity();
    int Calculate_Carecteristics();
    void Get_NPC_Stats();
    void Get_NPC_Race();
    int XPFromLVL(int lvl);
    int LVLFromXP(int xp);
    void SizeCategoryfromSize();
    void Calculat_Bonus(std::string What_carak);
    int Calculat_CA();
    void Reset_All_Stats();
    void Calculat_Carak_Race_bonus();
    void Get_Random_Natural_Armor();
    Inventory_N::Item* NewItem(std::string iName , std::string idescription , int iPrix , int iPoids);

    NPC() = default;
};

extern NPC npc;

}// namespace NPC_N
}// namespace DND_GM_Helper_N

#endif // NPC_H
