#ifndef DAMAGE_DICE_H
#define DAMAGE_DICE_H

namespace DND_GM_Helper_N {
namespace Inventory_N {

class Damage_Dice {
public:
    int Num_of_Dice;
    int Dice_Value;
    Damage_Dice();

    void Set_Damage_Dice(int Num_of_Dice , int Dice_Value);
};

} // namespace name
} // namespace name

#endif // DAMAGE_DICE_H
