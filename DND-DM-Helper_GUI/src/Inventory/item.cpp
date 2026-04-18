#include "../include/Inventory/item.h"

namespace DND_GM_Helper_N {
namespace Inventory_N {

Item::Item(std::string iName , std::string idescription , int iPrix , int iPoids):
    name(iName),
    description(idescription),
    Prix(iPrix),
    Poids(iPoids)
    {}

} // namespace Inventory_N
} // namespace DND_GM_Helper_N
