#ifndef ITEM_H
#define ITEM_H

#include <string>

namespace DND_GM_Helper_N {
namespace Inventory_N {

class Item
{
public:
    std::string name;
    std::string description;
    int Prix; //1 = 1 pc | 10 = 1 pa | 100 = 1 po | 1000 = 1 pp |
    int Poids; //en 'g'

    Item(std::string iName , std::string idescription , int iPrix , int iPoids);
};

} // namespace Inventory_N
} // namespace DND_GM_Helper_N

#endif // ITEM_H
