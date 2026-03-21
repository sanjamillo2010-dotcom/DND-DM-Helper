#ifndef NPC_H
#define NPC_H

#include <string>
#include <yaml-cpp/yaml.h>

#include "../include/Race.h"
#include "../include/classtype.h"
#include "../include/alignment.h"
#include "../include/weapon.h"
#include "../include/divinite.h"
#include "../include/armor.h"


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
    int FOR = 3;
    int FOR_Bonus;
    int DEX = 3;
    int DEX_Bonus;
    int CON = 3;
    int CON_Bonus;
    int INT = 3;
    int INT_Bonus;
    int SAG = 3;
    int SAG_Bonus;
    int CHA = 3;
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


    NPC() = default;
};

extern NPC npc;

}// namespace NPC_N
}// namespace DND_GM_Helper_N

#endif // NPC_H
