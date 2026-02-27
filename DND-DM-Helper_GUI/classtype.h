#ifndef CLASSTYPE_H
#define CLASSTYPE_H

#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

namespace DND_GM_Helper_N {
namespace NPC_N {

class ClassType {
public:
    std::string name;
    std::vector<std::string> usualLastNames;
    int HPdice = 0;

    ClassType() = default;;

    explicit ClassType(const std::string& className);

    void set_usualLastname(::YAML::Node& config,std::string& className);

    void print_ClassType_Info_CLmode();

    std::string GetRandomLastName();
};

} // namespace DND_GM_Helper_N
} // namespace NPC_N

#endif // CLASSTYPE_H
