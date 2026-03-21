#ifndef WEAPON_H
#define WEAPON_H

#include "../include/damage_dice.h"

#include <iostream>

namespace DND_GM_Helper_N {
namespace Inventory_N {


class Weapon {
public:
    std::string Name;
    Damage_Dice Attack;
    int Prix; //1 = 1 pc | 10 = 1 pa | 100 = 1 po | 1000 = 1 pp |
    int Poids; //en 'g'
    std::string Type;
    int Index;
    Weapon() = default;
};

} // namespace Inventory_N
} // namespace DND_GM_Helper_N

#endif // WEAPON_H
