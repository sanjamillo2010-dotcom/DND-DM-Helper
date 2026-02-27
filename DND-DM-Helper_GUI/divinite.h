#ifndef DIVINITE_H
#define DIVINITE_H

#include "alignment.h"
#include "widget.h"

#include <string>

namespace DND_GM_Helper_N {
namespace NPC_N {

class Divinite {
public:
    std::string name;
    Alignment alignment;
    Divinite() = default;;
    Divinite(const std::string& divinityName, const Alignment& divinityAlignment) : name(divinityName), alignment(divinityAlignment) {}
    void print_divinity_info_CLmode();
    void print_divinity_info_GUImode();
};

} // namespace DND_GM_Helper_N
} // namespace NPC_N

#endif // DIVINITE_H
