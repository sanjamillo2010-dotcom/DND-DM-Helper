#ifndef DIVINITE_H
#define DIVINITE_H

#include "alignment.h"
#include <string>

class Divinite {
public:
    std::string name;
    Alignment alignment;
    Divinite() = default;;
    Divinite(const std::string& divinityName, const Alignment& divinityAlignment) : name(divinityName), alignment(divinityAlignment) {}
    void print_divinity_info();
};

#endif // DIVINITE_H
