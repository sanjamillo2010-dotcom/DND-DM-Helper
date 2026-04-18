#ifndef ARMOR_H
#define ARMOR_H

#include <yaml-cpp/yaml.h>

namespace DND_GM_Helper_N {
namespace Inventory_N {

class Armor
{
public:
    std::string Name;
    std::string FileName;
    int Prix; //1 = 1 pc | 10 = 1 pa | 100 = 1 po | 1000 = 1 pp |
    int Prot;
    int MaxDEX_Bonus;
    int Poids; //en 'g'
    std::string Type;
    bool isShild;
    bool asIron;
    int index;
    Armor();
    void Get_Stats_from_YAML(std::string ArmorName , YAML::Node ArmorNODE);
};

}//Inventory
}//DND_GM_Helper_N

#endif // ARMOR_H
