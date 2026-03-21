#include "../include/armor.h"


namespace DND_GM_Helper_N {
namespace Inventory_N {

Armor::Armor() {}

void Armor::Get_Stats_from_YAML(std::string ArmorName, YAML::Node ArmorNODE) {
    YAML::Node armorData;

    if (ArmorNODE["Armor_conf"] && ArmorNODE["Armor_conf"][ArmorName]) {
        armorData = ArmorNODE["Armor_conf"][ArmorName];
    } else if (ArmorNODE[ArmorName]) {
        armorData = ArmorNODE[ArmorName];
    } else {
        throw std::runtime_error("Armor '" + ArmorName + "' not found in YAML node.");
    }

    Name         = armorData["Name"].as<std::string>();
    Prix         = armorData["Prix"].as<int>();
    Prot         = armorData["Prot"].as<int>();
    MaxDEX_Bonus = armorData["MaxDEX_Bonus"].as<int>();
    Poids        = armorData["Poids"].as<int>();
    Type         = armorData["Type"].as<std::string>();
    isShild      = armorData["isShild"].as<bool>();
}

}//Inventory
}//DND_GM_Helper_N
