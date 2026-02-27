#include "divinite.h"
#include "./ui_widget.h"

#include <iostream>

namespace DND_GM_Helper_N {
namespace NPC_N {

void Divinite::print_divinity_info_CLmode() {
    std::cout << "Divinity: " << name << "\nAlignment: " << alignment.alig1 << " " << alignment.alig2 << "\n";
}
void Divinite::print_divinity_info_GUImode() {

}

} // namespace DND_GM_Helper_N
} // namespace NPC_N
