#ifndef NPC_H
#define NPC_H

#include <string>
#include <yaml-cpp/yaml.h>
#include "Race.h"
#include "classtype.h"
#include "alignment.h"
#include "divinite.h"


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
    NPC() = default;
};

extern NPC npc;

#endif // NPC_H
