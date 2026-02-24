#include "Race.h"

#include <iostream>
#include <random>
#include <yaml-cpp/yaml.h>

Race::Race(const std::string& raceName) : name(raceName), MaxSize(0), MaxAge(0) {}

void Race::set_usualname(YAML::Node& config, const std::string& raceName) {
    try {
        YAML::Node Node = config["NPC_conf"][raceName];
        if (Node) {
            YAML::Node namesNode;
            YAML::Node maxSizeNode;
            YAML::Node maxAgeNode;

            if (Node.IsSequence() && Node.size() > 0) {
                namesNode = Node[0]["usualNames"];
                if (Node.size() > 1) {
                    maxSizeNode = Node[1]["MaxSize"];
                }
                if (Node.size() > 2) {
                    maxAgeNode = Node[2]["MaxAge"];
                }
            } else if (Node.IsMap()) {
                namesNode = Node["usualNames"];
                maxSizeNode = Node["MaxSize"];
                maxAgeNode = Node["MaxAge"];
            }

            if (namesNode && namesNode.IsSequence()) {
                usualNames = namesNode.as<std::vector<std::string>>();
            } else {
                std::cerr << raceName << " usualNames missing or not a sequence\n";
            }

            if (maxSizeNode && maxSizeNode.IsScalar()) {
                MaxSize = maxSizeNode.as<int>();
            }

            if (maxAgeNode && maxAgeNode.IsScalar()) {
                MaxAge = maxAgeNode.as<int>();
            }
        } else {
            std::cerr << raceName << " node missing\n";
        }
    }
    catch (const YAML::Exception& e) {
        std::cerr << "YAML error: " << e.what() << "\n";
    }
}

void Race::print_race_info() {
    std::cout << "Race: "<< this->name << "\n" << "Usual Names: ";
    for (const auto& name : this->usualNames) {
        std::cout << name << " ";
    }
    std::cout << "\nMax Size: " << MaxSize << std::endl << "Max Age: " << MaxAge << std::endl;
}

std::string Race::GetRandomName() {
    if (usualNames.empty()) {
        return "Unknown";
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, usualNames.size() - 1);

    return usualNames[dis(gen)];
}
