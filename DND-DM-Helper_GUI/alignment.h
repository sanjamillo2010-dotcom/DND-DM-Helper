#ifndef ALIGNMENT_H
#define ALIGNMENT_H

#include <string>

namespace DND_GM_Helper_N {
namespace NPC_N {

class Alignment {
public:
    std::string alig1;
    std::string alig2;
    Alignment() = default;
    Alignment(const std::string& n1, const std::string& n2) : alig1(n1), alig2(n2) {}

};

} // namespace DND_GM_Helper_N
} // namespace NPC_N

#endif // ALIGNMENT_H
