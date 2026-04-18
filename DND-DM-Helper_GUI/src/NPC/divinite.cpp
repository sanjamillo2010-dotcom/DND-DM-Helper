#include "../include/NPC/divinite.h"

#include <iostream>

namespace DND_GM_Helper_N {
namespace NPC_N {

void Divinite::print_divinity_info_CLmode() {
    std::cout << "Divinity: " << name << "\nAlignment: " << alignment.alig1 << " " << alignment.alig2 << "\n";
}

} // namespace DND_GM_Helper_N
} // namespace NPC_N
