#ifndef RACE_H
#define RACE_H

#include <string>
#include <vector>

namespace YAML {
class Node;
}

class Race {
public:
    std::string name;
    std::vector<std::string> usualNames;
    int MaxSize;
    int MaxAge;

    Race() = default;;

    Race(const std::string& iRaceName);

    void set_usualname(YAML::Node& ioConfig, const std::string& raceName);

    void print_race_info();

    std::string GetRandomName();

};



#endif // RACE_H
