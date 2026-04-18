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
    bool HasLightArmor;
    bool HasMidArmor;
    bool HasHeavyArmor;

    bool HasShild;
    bool Hastarge;

    bool Hassimple_light;
    bool Hassimple_one_handed;
    bool Hassimple_two_handed;
    bool Hassimple_ranged;

    bool Hasmartial_light;
    bool Hasmartial_one_handed;
    bool Hasmartial_two_handed;
    bool Hasmartial_ranged;

    bool Hasexotic_light;
    bool Hasexotic_one_handed;
    bool Hasexotic_two_handed;
    bool Hasexotic_ranged;

    int HPdice = 0;

    ClassType() = default;

    explicit ClassType(const std::string& className);

    void set_usualLastname(::YAML::Node& config,std::string& className);

    void set_AlowedArmors(::YAML::Node config , std::string& className);

    void set_AlowedWeapon(::YAML::Node config);

    void set_HPdice(::YAML::Node config);

    void print_ClassType_Info_CLmode();

    std::string GetRandomLastName();

    void Set_ClassType_Stats(YAML::Node config);
};

} // namespace DND_GM_Helper_N
} // namespace NPC_N

#endif // CLASSTYPE_H
