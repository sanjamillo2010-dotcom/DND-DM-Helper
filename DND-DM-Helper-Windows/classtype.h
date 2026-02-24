#ifndef CLASSTYPE_H
#define CLASSTYPE_H

#include <string>
#include <vector>

namespace YAML {
class Node;
}

class ClassType {
public:
    std::string name;
    std::vector<std::string> usualLastNames;
    int HPdice = 0;

    ClassType() = default;;

    explicit ClassType(const std::string& className);

    void set_usualLastname(YAML::Node& config,std::string& className);

    void print_ClassType_Info();

    std::string GetRandomLastName();
};
#endif // CLASSTYPE_H
