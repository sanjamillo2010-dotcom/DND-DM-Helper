#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <yaml-cpp/yaml.h>
#include ".h/main.h"

class Race {
public:
    std::string name;
    std::vector<std::string> usualNames;
    
    Race() = default;
    
    Race(const std::string& raceName) : name(raceName) {}
    
    void set_usualname(YAML::Node config,std::string raceName) {
        try {
            YAML::Node Node = config["NPC_conf"][raceName];
            if (Node) {
                YAML::Node namesNode;
                if (Node.IsSequence() && Node.size() > 0) {
                    namesNode = Node[0]["usualNames"];
                } else if (Node.IsMap()) {
                    namesNode = Node["usualNames"];
                }

                if (namesNode && namesNode.IsSequence()) {
                    usualNames = namesNode.as<std::vector<std::string>>();
                } else {
                    std::cerr << raceName << " usualNames missing or not a sequence\n";
                }
            } else {
                std::cerr << raceName << " node missing\n";
            }
        } 
        catch (const YAML::Exception& e) {
            std::cerr << "YAML error: " << e.what() << "\n";
        }
    }
    void print_race_info() {
        std::cout << "Race: "<< this->name << "\n" << "Usual Names: ";
        for (const auto& name : this->usualNames) {
            std::cout << name << " ";
        }
        std::cout << "\n";
    }
    std::string GetRandomName() {
        if (usualNames.empty()) {        
            return "Unknown";
        }
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, usualNames.size() - 1);
        
        return usualNames[dis(gen)];
    }
};

class ClassType {
public:
    std::string name; 
    std::vector<std::string> usualLastNames;
    
    ClassType() = default;
    explicit ClassType(const std::string& className) : name(className) {}
    
    void set_usualLastname(YAML::Node config,std::string className) {
        try {
            YAML::Node Node = config["NPC_conf"][className];
            if (Node) {
                YAML::Node namesNode;
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
        catch (const YAML::Exception& e) {
            std::cerr << "YAML error: " << e.what() << "\n";
        }
    }
    void print_ClassType_Info(){
        std::cout << "Class : " << name << "\n" << "Usual Last Names : ";
    for (const auto& name : this->usualLastNames) { std::cout << name << " "; }
        std::cout << "\n";
    }
    std::string GetRandomLastName(){
        if (usualLastNames.empty()) {        
            return "Unknown";
        }
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, usualLastNames.size() - 1);
        
        return usualLastNames[dis(gen)];
    }
};

class Alignment {
public:
    std::string alig1;
    std::string alig2;
    Alignment() = default;
    Alignment(const std::string& n1, const std::string& n2) : alig1(n1), alig2(n2) {}
};


class NPC {
public:
    std::string name;
    std::string LastName;
    Race race;
    ClassType classtype;
    int level;
    int XP;
    int HP;
    Alignment alignment;
    void Print_NPC_Stats(){
        std::cout << "\n\n" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Name : " << name << " " << LastName << std::endl;
        std::cout << "Race : " << race.name << std::endl;
        std::cout << "Class : " << classtype.name << std::endl;
        std::cout << "HP : " << HP << std::endl;
        std::cout << "Level : " << level << std::endl;
        std::cout << "XP : " << XP << std::endl;
        std::cout << "Alignment : " << alignment.alig1 << " " << alignment.alig2 << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << name << " " << LastName << " the " << alignment.alig1 << " " << alignment.alig2 << " " << race.name << " " << classtype.name << std::endl;
    }
    Race Get_Random_Race(){
            YAML::Node config = YAML::LoadFile("conf/NPC_conf.yaml");
            YAML::Node racesNode = config["NPC_conf"]["race"];
            if (!racesNode || !racesNode.IsSequence()) {
                std::cerr << "race node missing or not a sequence\n";
                return Race();
            }
            std::vector<std::string> races = racesNode.as<std::vector<std::string>>();
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, races.size() - 1);
            Race r(races[dis(gen)]);
            r.set_usualname(config, r.name);
            return r;
         }
    ClassType Get_Random_Class(){
            YAML::Node config = YAML::LoadFile("conf/NPC_conf.yaml");
            YAML::Node classesNode = config["NPC_conf"]["Classtype"];
            if (!classesNode || !classesNode.IsSequence()) {
                std::cerr << "Classtype node missing or not a sequence\n";
                return ClassType();
            }
            std::vector<std::string> classes = classesNode.as<std::vector<std::string>>();
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, classes.size() - 1);
            ClassType ct(classes[dis(gen)]);
            ct.set_usualLastname(config, ct.name);
            return ct;
         }
    void Get_NPC_Stats(){
        YAML::Node config = YAML::LoadFile("conf/NPC_conf.yaml");
        while (true) {
            std::cout << "Race : " << std::endl << "1- Random Race" << std::endl << "2- Celect Race" << std::endl << "3- Custom Race" << std::endl << "Enter your choice : ";
            int raceChoice;
            if (!(std::cin >> raceChoice)) { std::cin.clear(); std::string skip; std::getline(std::cin, skip); continue; }

            if (raceChoice == 1) {
                race = Get_Random_Race();
                break;
            } else if (raceChoice == 2) {
                while (true) {
                    std::cout << "Please select a race: " << std::endl << "1- Human" << std::endl << "2- Elf" << std::endl << "3- Half-Elf" << std::endl << "4- Dwarf" << std::endl << "5- Halfling" << std::endl << "6- Gnome" << std::endl << "7- Half-Orc" << std::endl << "Enter your choice : ";
                    int specificRaceChoice;
                    if (!(std::cin >> specificRaceChoice)) { std::cin.clear(); std::string skip; std::getline(std::cin, skip); continue; }

                    if (specificRaceChoice >= 1 && specificRaceChoice <= 7) {
                        switch (specificRaceChoice) {
                            case 1: race.name = "Human"; break;
                            case 2: race.name = "Elf"; break;
                            case 3: race.name = "Half-Elf"; break;
                            case 4: race.name = "Dwarf"; break;
                            case 5: race.name = "Halfling"; break;
                            case 6: race.name = "Gnome"; break;
                            case 7: race.name = "Half-Orc"; break;
                        }
                        // Populate usual names for the selected race
                        race.set_usualname(config, race.name);
                        break;
                    } else {
                        std::cout << "Invalid choice. Please select a valid race number (1-7): ";
                    }
                }
                break;
            } else if (raceChoice == 3) {
                std::cout << "Please enter a custom race name: ";
                std::cin >> race.name;
                break;
            } else {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
        system("clear");
        std::cout << "Race : " << race.name << std::endl;
        while (true) {
            std::cout << "Class : " << std::endl << "1- Random Class" << std::endl << "2- Celect Class" << std::endl << "3- Custom Class" << std::endl << "Enter your choice : ";
            int classChoice;
            if (!(std::cin >> classChoice)) { std::cin.clear(); std::string skip; std::getline(std::cin, skip); continue; }

            if (classChoice == 1) {
                classtype = Get_Random_Class();
                break;
            } else if (classChoice == 2) {
                while (true) {
                    std::cout << "Please select a class: " << std::endl << "1- Barbarian" << std::endl << "2- Bard" << std::endl << "3- Cleric" << std::endl << "4- Druid" << std::endl << "5- Fighter" << std::endl << "6- Monk" << std::endl << "7- Paladin" << std::endl << "8- Rogue" << std::endl << "9- Wizard" << std::endl << "Enter your choice : ";
                    int specificClassChoice;
                    if (!(std::cin >> specificClassChoice)) { std::cin.clear(); std::string skip; std::getline(std::cin, skip); continue; }

                    if (specificClassChoice >= 1 && specificClassChoice <= 9) {
                        switch (specificClassChoice) {
                            case 1: classtype.name = "Barbarian"; break;
                            case 2: classtype.name = "Bard"; break;
                            case 3: classtype.name = "Cleric"; break;
                            case 4: classtype.name = "Druid"; break;
                            case 5: classtype.name = "Fighter"; break;
                            case 6: classtype.name = "Monk"; break;
                            case 7: classtype.name = "Paladin"; break;
                            case 8: classtype.name = "Rogue"; break;
                            case 9: classtype.name = "Wizard"; break;
                        }
                        // Populate usual last names for the selected class
                        classtype.set_usualLastname(config, classtype.name);
                        break;
                    } 
                    else {
                        std::cout << "Invalid choice. Please select a valid class number (1-9): ";
                    }
                }
                break;
            } else if (classChoice == 3) {
                std::cout << "Please enter a custom class name: ";
                std::cin >> classtype.name;
                break;
            } else {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
        system("clear");
        std::cout << "Race : " << race.name << std::endl << "Class : " << classtype.name << std::endl;
        while (true) {
            std::cout << "Do you want to generate a random name based on the selected race? (y/n): ";
            char nameChoice;
            std::cin >> nameChoice;
            if (nameChoice == 'y' || nameChoice == 'Y') {
                name = race.GetRandomName();
                break;
            } else if (nameChoice == 'n' || nameChoice == 'N') {
                std::cout << "Please enter a custom name: ";
                std::cin >> name;
                break;
            }
            else {
                std::cout << "Invalid choice. Please enter 'y' or 'n': ";
            }
        }
        system("clear");
        std::cout << "Race : " << race.name << std::endl << "Class : " << classtype.name << std::endl << "Name : " << name << std::endl;
        while (true) {
            std::cout << "Do you want to generate a random last name based on the selected class? (y/n): ";
            char lastNameChoice;
            std::cin >> lastNameChoice;
            if (lastNameChoice == 'y' || lastNameChoice == 'Y') {
                LastName = classtype.GetRandomLastName();
                break;
            } else if (lastNameChoice == 'n' || lastNameChoice == 'N') {
                std::cout << "Please enter a custom last name: ";
                std::cin >> LastName;
                break;
            }
            else {
                std::cout << "Invalid choice. Please enter 'y' or 'n': ";
            }
        }
        system("clear");
        std::cout << "Last Name : " << LastName << std::endl;
        while (true) {
            std::cout << "1- Enter level " << std::endl << "2- Random level" << std::endl << "3- Enter XP" << std::endl << "4- Random XP" << std::endl << "Enter your choice : ";
            int choice;
            std::cin >> choice;
            if (choice == 1) {
                std::cout << "Please enter the NPC's level (1-20): ";
                if (!(std::cin >> level) || level < 1 || level > 20) {
                    std::cin.clear();
                    std::string skip;
                    std::getline(std::cin, skip);
                    std::cout << "Invalid input. Please enter a number between 1 and 20.\n";
                }
                if (level == 1) XP = 0;
                else if (level == 2) XP = 1000;
                else if (level == 3) XP = 3000;
                else if (level == 4) XP = 6000;
                else if (level == 5) XP = 10000;
                else if (level == 6) XP = 15000;
                else if (level == 7) XP = 21000;
                else if (level == 8) XP = 28000;
                else if (level == 9) XP = 36000;
                else if (level == 10) XP = 45000;
                else if (level == 11) XP = 55000;
                else if (level == 12) XP = 66000;
                else if (level == 13) XP = 78000;
                else if (level == 14) XP = 91000;
                else if (level == 15) XP = 105000;
                else if (level == 16) XP = 120000;
                else if (level == 17) XP = 136000;
                else if (level == 18) XP = 153000;
                else if (level == 19) XP = 171000;
                else if (level == 20) XP = 190000;
                break;
            } 
            else if (choice == 2) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(1, 20);
                level = dis(gen);
                if (level == 1) XP = 0;
                else if (level == 2) XP = 1000;
                else if (level == 3) XP = 3000;
                else if (level == 4) XP = 6000;
                else if (level == 5) XP = 10000;
                else if (level == 6) XP = 15000;
                else if (level == 7) XP = 21000;
                else if (level == 8) XP = 28000;
                else if (level == 9) XP = 36000;
                else if (level == 10) XP = 45000;
                else if (level == 11) XP = 55000;
                else if (level == 12) XP = 66000;
                else if (level == 13) XP = 78000;
                else if (level == 14) XP = 91000;
                else if (level == 15) XP = 105000;
                else if (level == 16) XP = 120000;
                else if (level == 17) XP = 136000;
                else if (level == 18) XP = 153000;
                else if (level == 19) XP = 171000;
                else if (level == 20) XP = 190000;
                break;
            } 
            else if (choice == 3) {
                std::cout << "Please enter the NPC's XP: ";
                if (!(std::cin >> XP) || XP < 0) {
                    std::cin.clear();
                    std::string skip;
                    std::getline(std::cin, skip);
                    std::cout << "Invalid input. Please enter a non-negative number.\n";
                    } else {
                    if (XP >= 190000) {
                        level = 20;
                    } else if (XP >= 171000) {
                        level = 19;
                    } else if (XP >= 153000) {
                        level = 18;
                    } else if (XP >= 136000) {
                        level = 17;
                    } else if (XP >= 120000) {
                        level = 16;
                    } else if (XP >= 105000) {
                        level = 15;
                    } else if (XP >= 91000) {
                        level = 14;
                    } else if (XP >= 78000) {
                        level = 13;
                    } else if (XP >= 66000) {
                        level = 12;
                    } else if (XP >= 55000) {
                        level = 11;
                    } else if (XP >= 45000) {
                        level = 10;
                    } else if (XP >= 36000) {
                        level = 9;
                    } else if (XP >= 28000) {
                        level = 8;
                    } else if (XP >= 21000) {
                        level = 7;
                    } else if (XP >= 15000) {
                        level = 6;
                    } else if (XP >= 10000) {
                        level = 5;
                    } else if (XP >= 6000) {
                        level = 4;
                    } else if (XP >= 3000) {
                        level = 3;
                    } else if (XP >= 1000) {
                        level = 2;
                    } else {
                        level = 1;
                    }
                }
                break;
            } 
            else if (choice == 4) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(0, 190000); // Max XP for level 20
                XP = dis(gen);
                if (XP >= 190000) {
                    level = 20;
                } else if (XP >= 171000) {
                    level = 19;
                } else if (XP >= 153000) {
                    level = 18;
                } else if (XP >= 136000) {
                    level = 17;
                } else if (XP >= 120000) {
                    level = 16;
                } else if (XP >= 105000) {
                    level = 15;
                } else if (XP >= 91000) {
                    level = 14;
                } else if (XP >= 78000) {
                    level = 13;
                } else if (XP >= 66000) {
                    level = 12;
                } else if (XP >= 55000) {
                    level = 11;
                } else if (XP >= 45000) {
                    level = 10;
                } else if (XP >= 36000) {
                    level = 9;
                } else if (XP >= 28000) {
                    level = 8;
                } else if (XP >= 21000) {
                    level = 7;
                } else if (XP >= 15000) {
                    level = 6;
                } else if (XP >= 10000) {
                    level = 5;
                } else if (XP >= 6000) {
                    level = 4;
                } else if (XP >= 3000) {
                    level = 3;
                } else if (XP >= 1000) {
                    level = 2;
                } else {
                    level = 1;
                }
                break;
            } 
            else {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
        system("clear");
        std::cout << "Level : " << level << std::endl;
        while (true) {
            std::cout << "1- Enter HP " << std::endl << "2- Calculate HP based on class and level" << std::endl << "Enter your choice : ";
            int hpChoice;
            std::cin >> hpChoice;
            if (hpChoice == 1) {
                std::cout << "Please enter the NPC's HP: ";
                if (!(std::cin >> HP) || HP < 1) {
                    std::cin.clear();
                    std::string skip;
                    std::getline(std::cin, skip);
                    std::cout << "Invalid input. Please enter a positive number.\n";
                }
                break;
            } 
            else if (hpChoice == 2) {
                if (classtype.name == "Barbarian") {
                    for (int i = 1; i <= level; ++i) {
                        if (i == 1) HP = 12;
                        else HP += rand()%12 + 1;
                        //std::cout << "Level " << i << ": HP = " << HP << std::endl;
                    }
                } else if (classtype.name == "Bard") {
                    for (int i = 1; i <= level; ++i) {
                        if (i == 1) HP = 6;
                        else HP += rand()%6 + 1;
                        //std::cout << "Level " << i << ": HP = " << HP << std::endl;
                    }
                } else if (classtype.name == "Cleric") {
                    for (int i = 1; i <= level; ++i) {
                        if (i == 1) HP = 8;
                        else HP += rand()%8 + 1;
                        //std::cout << "Level " << i << ": HP = " << HP << std::endl;
                    }
                } else if (classtype.name == "Druid") {
                    for (int i = 1; i <= level; ++i) {
                        if (i == 1) HP = 8;
                        else HP += rand()%8 + 1;
                        //std::cout << "Level " << i << ": HP = " << HP << std::endl;
                    }
                } else if (classtype.name == "Fighter") {
                    for (int i = 1; i <= level; ++i) {
                        if (i == 1) HP = 10;
                        else HP += rand()%10 + 1;
                        //std::cout << "Level " << i << ": HP = " << HP << std::endl;
                    }
                } else if (classtype.name == "Monk") {
                    for (int i = 1; i <= level; ++i) {
                        if (i == 1) HP = 8;
                        else HP += rand()%8 + 1;
                        //std::cout << "Level " << i << ": HP = " << HP << std::endl;
                    }
                } else if (classtype.name == "Paladin") {
                    for (int i = 1; i <= level; ++i) {
                        if (i == 1) HP = 10;
                        else HP += rand()%10 + 1;
                        //std::cout << "Level " << i << ": HP = " << HP << std::endl;
                    }
                } else if (classtype.name == "Rogue") {
                    for (int i = 1; i <= level; ++i) {
                        if (i == 1) HP = 6;
                        else HP += rand()%6 + 1;
                        //std::cout << "Level " << i << ": HP = " << HP << std::endl;
                    }
                } else if (classtype.name == "Wizard") {
                    for (int i = 1; i <= level; ++i) {
                        if (i == 1) HP = 4;
                        else HP += rand()%4 + 1;
                        //std::cout << "Level " << i << ": HP = " << HP << std::endl;
                    }
                } else {
                    std::cout << "Unknown class. Cannot calculate HP.\n";
                    break;
                }
                break;
            }
            else {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
        system("clear");
        std::cout << "HP : " << HP << std::endl;
        while(true) {
            std::cout << "1- Enter Alignment " << std::endl << "2- Random Alignment" << std::endl << "Enter your choice : ";
            int alignmentChoice;
            std::cin >> alignmentChoice;
            if (alignmentChoice == 1) {
                std::cout << "Enter the first part of the alignment: ";
                std::cin >> alignment.alig1;
                std::cout << "Enter the second part of the alignment: ";
                std::cin >> alignment.alig2;
                break;
            }
            else if (alignmentChoice == 2) {
                std::vector<std::string> alignments1 = {"Lawful", "Neutral", "Chaotic"};
                std::vector<std::string> alignments2 = {"Good", "Neutral", "Evil"};
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis1(0, alignments1.size() - 1);
                std::uniform_int_distribution<> dis2(0, alignments2.size() - 1);
                alignment.alig1 = alignments1[dis1(gen)];
                alignment.alig2 = alignments2[dis2(gen)];
                break;
            }
            else {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
            system("clear");
            std::cout << "Alignment : " << alignment.alig1 << " " << alignment.alig2 << std::endl;
        }
        system("clear");
        std::cout << "Alignment : " << alignment.alig1 << " " << alignment.alig2 << std::endl;
    }
};


int main() {
    YAML::Node config = YAML::LoadFile("conf/NPC_conf.yaml");
    NPC npc;

    Race Humain;
    Humain.name = "Human";
    Humain.set_usualname(config,"Human");

    Race Elf;
    Elf.name = "Elf";
    Elf.set_usualname(config,"Elf");

    Race HalfElf;
    HalfElf.name = "Half-Elf";
    HalfElf.set_usualname(config,"Half-Elf");

    Race Dwarf;
    Dwarf.name = "Dwarf";
    Dwarf.set_usualname(config,"Dwarf");

    Race Halfling;
    Halfling.name = "Halfling";
    Halfling.set_usualname(config,"Halfling");

    Race Gnome;
    Gnome.name = "Gnome";
    Gnome.set_usualname(config,"Gnome");

    Race HalfOrc;
    HalfOrc.name = "Half-Orc";
    HalfOrc.set_usualname(config,"Half-Orc");

    ClassType Barbarian; 
    Barbarian.name = "Barbarian"; 
    Barbarian.set_usualLastname(config,"Barbarian");

    ClassType Bard;
    Bard.name = "Bard";
    Bard.set_usualLastname(config,"Bard");

    ClassType Cleric;
    Cleric.name = "Cleric";
    Cleric.set_usualLastname(config,"Cleric");

    ClassType Druid;
    Druid.name = "Druid";
    Druid.set_usualLastname(config,"Druid");

    ClassType Fighter;
    Fighter.name = "Fighter";
    Fighter.set_usualLastname(config,"Fighter");

    ClassType Monk;
    Monk.name = "Monk";
    Monk.set_usualLastname(config,"Monk");

    ClassType Paladin;
    Paladin.name = "Paladin";
    Paladin.set_usualLastname(config,"Paladin");

    ClassType Rogue;
    Rogue.name = "Rogue";
    Rogue.set_usualLastname(config,"Rogue");

    ClassType Wizard;
    Wizard.name = "Wizard";
    Wizard.set_usualLastname(config,"Wizard");

    npc.Get_NPC_Stats();
    npc.Print_NPC_Stats();
    return 0;
}