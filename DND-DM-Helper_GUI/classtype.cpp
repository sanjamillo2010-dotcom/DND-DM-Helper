#include "classtype.h"

#include <iostream>
#include <random>
#include <yaml-cpp/yaml.h>

namespace DND_GM_Helper_N {
namespace NPC_N {

ClassType::ClassType(const std::string& className) : name(className) {}

void DND_GM_Helper_N::NPC_N::ClassType::set_usualLastname(::YAML::Node& config,std::string& className) {
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

} // namespace DND_GM_Helper_N
} // namespace NPC_N
