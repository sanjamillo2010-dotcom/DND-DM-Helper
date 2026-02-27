#ifndef NPC_H
#define NPC_H

#include <string>
#include <yaml-cpp/yaml.h>
#include "Race.h"
#include "classtype.h"
#include "alignment.h"
#include "divinite.h"

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
    int FOR;
    int DEX;
    int CON;
    int INT;
    int SAG;
    int CHA;
    int CA = 10;
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
    NPC() = default;
};

extern NPC npc;

}// namespace NPC_N
}// namespace DND_GM_Helper_N

#endif // NPC_H
