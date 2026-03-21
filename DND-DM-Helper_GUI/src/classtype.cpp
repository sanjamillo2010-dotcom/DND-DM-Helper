#include "../include/classtype.h"

#include <iostream>
#include <random>
#include <yaml-cpp/yaml.h>

namespace DND_GM_Helper_N {
namespace NPC_N {

ClassType::ClassType(const std::string& className) : name(className) {}

void ClassType::set_usualLastname(::YAML::Node& config,std::string& className) {
    try {
        ::YAML::Node Node = config["NPC_conf"][className];
        if (Node) {
            ::YAML::Node namesNode;
            if (Node.IsSequence() && Node.size() > 0) {
                namesNode = Node[0]["usualLastNames"];
            } else if (Node.IsMap()) {
                namesNode = Node["usualLastNames"];
            }

            if (namesNode && namesNode.IsSequence()) {
                usualLastNames = namesNode.as<std::vector<std::string>>();
            } else {
                std::cerr << className << " usualLastNames missing or not a sequence\n";
            }
        } else {
            std::cerr << className << " node missing\n";
        }
    }
    catch (const ::YAML::Exception& e) {
        std::cerr << "YAML error: " << e.what() << "\n";
    }
}

std::string ClassType::GetRandomLastName(){
    if (usualLastNames.empty()) {
        return "Unknown";
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, usualLastNames.size() - 1);

    return usualLastNames[dis(gen)];
}

void ClassType::set_AlowedArmors(YAML::Node config , std::string& className) {
    ClassType::HasLightArmor = config["NPC_conf"][className]["HasLightArmor"].as<bool>();
    ClassType::HasMidArmor = config["NPC_conf"][className]["HasMidArmor"].as<bool>();
    ClassType::HasHeavyArmor = config["NPC_conf"][className]["HasHeavyArmor"].as<bool>();
    ClassType::Hastarge = config["NPC_conf"][className]["Hastarge"].as<bool>();
    ClassType::HasShild = config["NPC_conf"][className]["HasShild"].as<bool>();
}

void ClassType::set_HPdice(::YAML::Node config) {
    YAML::Node classNode = config["NPC_conf"][name];
    if (classNode) {
        YAML::Node hpNode;
        if (classNode.IsSequence() && classNode.size() > 0) {
            hpNode = classNode[0]["HPdice"];
        }
        else if (classNode.IsMap()) {
            hpNode = classNode["HPdice"];
        }
        if (hpNode && hpNode.IsScalar()) {
            HPdice = hpNode.as<int>();
        }
    }
    if (HPdice <= 0) {
        static const std::map<std::string, int> defaultHP = {
            {"Barbarian", 12}, {"Bard", 6},    {"Cleric", 8},
            {"Druid", 8},      {"Fighter", 10}, {"Monk", 8},
            {"Paladin", 10},   {"Rogue", 8},    {"Wizard", 4}
        };
        auto it = defaultHP.find(name);
        HPdice = (it != defaultHP.end()) ? it->second : 8;
    }

}

void ClassType::set_AlowedWeapon(::YAML::Node config) {
    Hassimple_light = config["NPC_conf"][name]["Hassimple_light"].as<bool>();
    Hassimple_one_handed = config["NPC_conf"][name]["Hassimple_one_handed"].as<bool>();
    Hassimple_two_handed = config["NPC_conf"][name]["Hassimple_two_handed"].as<bool>();
    Hassimple_ranged = config["NPC_conf"][name]["Hassimple_ranged"].as<bool>();
    Hasmartial_light = config["NPC_conf"][name]["Hasmartial_light"].as<bool>();
    Hasmartial_one_handed = config["NPC_conf"][name]["Hasmartial_one_handed"].as<bool>();
    Hasmartial_two_handed = config["NPC_conf"][name]["Hasmartial_two_handed"].as<bool>();
    Hasmartial_ranged = config["NPC_conf"][name]["Hasmartial_ranged"].as<bool>();
    Hasexotic_light = config["NPC_conf"][name]["Hasexotic_light"].as<bool>();
    Hasexotic_one_handed = config["NPC_conf"][name]["Hasexotic_one_handed"].as<bool>();
    Hasexotic_two_handed = config["NPC_conf"][name]["Hasexotic_two_handed"].as<bool>();
    Hasexotic_ranged = config["NPC_conf"][name]["Hasexotic_ranged"].as<bool>();
}

void ClassType::Set_ClassType_Stats(YAML::Node config) {
    set_AlowedArmors(config , name);
    set_usualLastname(config , name);
    set_HPdice(config);
    set_AlowedWeapon(config);
}

} // namespace DND_GM_Helper_N
} // namespace NPC_N
