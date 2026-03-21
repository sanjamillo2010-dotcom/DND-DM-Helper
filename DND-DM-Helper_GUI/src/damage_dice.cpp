#include "../include/damage_dice.h"

namespace DND_GM_Helper_N {
namespace Inventory_N {

Damage_Dice::Damage_Dice() {}

void Damage_Dice::Set_Damage_Dice(int INum_of_Dice , int IDice_Value) {
    Num_of_Dice = INum_of_Dice;
    Dice_Value = INum_of_Dice;
}

} // namespace Inventory_N
} // namespace DND_GM_Helper_N
