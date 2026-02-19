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
    int MaxSize;
    int MaxAge;
    
    Race() = default;
    
    Race(const std::string& raceName) : name(raceName), MaxSize(0), MaxAge(0) {}
    
    void set_usualname(YAML::Node config,std::string raceName) {
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
    void print_race_info() {
        std::cout << "Race: "<< this->name << "\n" << "Usual Names: ";
        for (const auto& name : this->usualNames) {
            std::cout << name << " ";
        }
        std::cout << "\nMax Size: " << MaxSize << std::endl << "Max Age: " << MaxAge << std::endl;
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
    int HPdice = 0;
    
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

class Divinite {
public:
    std::string name;
    Alignment alignment;
    Divinite() = default;
    Divinite(const std::string& divinityName, const Alignment& divinityAlignment) : name(divinityName), alignment(divinityAlignment) {}
    void print_divinity_info() {
        std::cout << "Divinity: " << name << "\nAlignment: " << alignment.alig1 << " " << alignment.alig2 << "\n";
    }
};


class NPC {
public:
    std::string name;
    std::string LastName;
    Race race;
    ClassType classtype;
    std::string Sexe;
    int Age = 0;
    int Size = 0;
    std::string SizeCategory = "";
    int level = 1;
    int XP = 0;
    int HP = 0;
    int FOR;
    int DEX;
    int CON;
    int INT;
    int SAG;
    int CHA;
    int CA = 10;
    Alignment alignment;
    Divinite divinity;
    void Print_NPC_Stats(){
        std::cout << "\n\n" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Name : " << name << " " << LastName << std::endl;
        std::cout << "Race : " << race.name << std::endl;
        std::cout << "Class : " << classtype.name << std::endl;
        std::cout << "Age : " << Age << std::endl;
        std::cout << "Size : " << Size << std::endl;
        std::cout << "Size category : " << SizeCategory << std::endl;
        std::cout << "HP : " << HP << std::endl;
        std::cout << "Level : " << level << std::endl;
        std::cout << "XP : " << XP << std::endl;
        std::cout << "Alignment : " << alignment.alig1 << " " << alignment.alig2 << std::endl;
        std::cout << "Divinity : " << divinity.name << " Alignment: " << divinity.alignment.alig1 << " " << divinity.alignment.alig2 << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "strength : " << FOR << std::endl << "dexterity : " << DEX << std::endl << "constitution : " << CON << std::endl << "intelligence : " << INT << std::endl << "wisdom : " << SAG << std::endl << "charisma : " << CHA << std::endl;
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
            std::string selectedRace = races[dis(gen)];
            Race r(selectedRace);
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
    Divinite Get_Random_Divinity(){
            YAML::Node config = YAML::LoadFile("conf/NPC_conf.yaml");
            YAML::Node divinitiesNode = config["NPC_conf"]["Divinite"];
            if (!divinitiesNode || !divinitiesNode.IsSequence()) {
                std::cerr << "Divinite node missing or not a sequence\n";
                return Divinite();
            }
            std::vector<std::string> divinities = divinitiesNode.as<std::vector<std::string>>();
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, divinities.size() - 1);
            std::string chosenDivinity = divinities[dis(gen)];
            
            // Fetch alignment details
            YAML::Node divinityDetails = config["NPC_conf"]["DivinityDetails"][chosenDivinity];
            Alignment alignment;
            if (divinityDetails) {
                alignment.alig1 = divinityDetails["Alignment1"].as<std::string>();
                alignment.alig2 = divinityDetails["Alignment2"].as<std::string>();
            }
            
            Divinite d(chosenDivinity, alignment);
            return d;
        }
    int Calculate_Carecteristics(){
        int Diceroll; int D1 = rand() % 6 + 1; int D2 = rand() % 6 + 1; int D3 = rand() % 6 + 1; int D4 = rand() % 6 + 1;
        //std::cout << "Debug: First roll: " << D1 << " " << D2 << " " << D3 << " " << D4 << std::endl;
        if (D1 < D2) std::swap(D1, D2);
        if (D1 < D3) std::swap(D1, D3);
        if (D1 < D4) std::swap(D1, D4);
        if (D2 < D3) std::swap(D2, D3);
        if (D2 < D4) std::swap(D2, D4);
        if (D3 < D4) std::swap(D3, D4);
        Diceroll = D1 + D2 + D3;
        //std::cout << "Debug: First roll: " << D1 << "+" << D2 << "+" << D3 << std::endl;
        return Diceroll;
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
                    std::cout << "Please select a race" << std::endl;
                    int specificRaceChoice;
                    YAML::Node RaceNode = config["NPC_conf"]["race"];
                    std::cout << "Available :" << std::endl;
                    for (size_t i = 0; i < RaceNode.size(); ++i) {
                       std::cout << i + 1 << "- " << RaceNode[i].as<std::string>() << std::endl;
                    }
                    if (!(std::cin >> specificRaceChoice)) { std::cin.clear(); std::string skip; std::getline(std::cin, skip); continue; }

                    if (specificRaceChoice >= 1 && specificRaceChoice <= RaceNode.size()) {
                        race.name = RaceNode[specificRaceChoice - 1].as<std::string>();
                        race.set_usualname(config, race.name);
                        break;
                    } else {
                        std::cout << "Invalid choice. Please select a valid race number (1-" << RaceNode.size() << "): ";
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
                    std::cout << "Please select a class" << std::endl;
                    YAML::Node ClassNode = config["NPC_conf"]["Classtype"];
                    std::cout << "Available :" << std::endl;
                    for (size_t i = 0; i < ClassNode.size(); ++i) {
                       std::cout << i + 1 << "- " << ClassNode[i].as<std::string>() << std::endl;
                    }
                    int specificClassChoice;
                    if (!(std::cin >> specificClassChoice)) { std::cin.clear(); std::string skip; std::getline(std::cin, skip); continue; }

                    if (specificClassChoice >= 1 && specificClassChoice <= ClassNode.size()) {
                        classtype.name = ClassNode[specificClassChoice - 1].as<std::string>();
                        classtype.set_usualLastname(config, classtype.name);
                        break;
                    } else {
                        std::cout << "Invalid choice. Please select a valid class number (1-" << ClassNode.size() << "): ";
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
            std::cout << "1- Select Sexe" << std::endl << "2- Random Sexe" << std::endl << "Enter your choice : ";
            int sexeChoice;
            std::cin >> sexeChoice;
            if (sexeChoice == 1) {
                YAML::Node sexesNode = config["NPC_conf"]["Sexes"];
                std::cout << "Available :" << std::endl;
                int i = 1;
                for (YAML::const_iterator it = sexesNode.begin(); it != sexesNode.end(); ++it) {
                    std::cout << i << "- " << it->as<std::string>() << std::endl;
                    i = i + 1;
                }
                std::cout << "Please enter the NPC's sexe: ";
                std::cin >> sexeChoice;
                Sexe = sexesNode[sexeChoice - 1].as<std::string>();
                break;
            } else if (sexeChoice == 2) {
                YAML::Node sexesNode = config["NPC_conf"]["Sexes"];
                std::vector<std::string> availableSexes;
                for (YAML::const_iterator it = sexesNode.begin(); it != sexesNode.end(); ++it) {
                    availableSexes.push_back(it->as<std::string>());
                }
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(0, availableSexes.size() - 1);
                Sexe = availableSexes[dis(gen)];
                break;
            } else {
                std::cout << "Invalid choice. Please enter -1 or 2.\n";
            }
        }
        system("clear");
        std::cout << "Sexe : " << Sexe << std::endl;
        while (true) {
            std::cout << "1- Custom Age" << std::endl << "2- Random Age" << std::endl << "Enter your choice : ";
            int ageChoice;
            std::cin >> ageChoice;
            if (ageChoice == 1) {
                std::cout << "Please enter the NPC's age: ";
                if (!(std::cin >> Age) || Age < 0 || Age > race.MaxAge) {
                    std::cin.clear();
                    std::string skip;
                    std::getline(std::cin, skip);
                    std::cout << "Invalid input. Please enter a number between 0 and " << race.MaxAge << ".\n";
                } else {
                    break;
                }
            } else if (ageChoice == 2) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(race.MaxAge / 2, race.MaxAge + 10);
                Age = dis(gen);
                break;
            } else {
                std::cout << "Invalid choice. Please enter 1 or 2.\n";
            }
        }
        system("clear");
        std::cout << "Age : " << Age << std::endl;
        while (true) {
            std::cout << "1- Custom Size" << std::endl << "2- Random Size" << std::endl << "Enter your choice : ";
            int sizeChoice;
            std::cin >> sizeChoice;
            if (sizeChoice == 1) {
                std::cout << "Please enter the NPC's size: ";
                if (!(std::cin >> Size) || Size < 0 || Size > race.MaxSize) {
                    std::cin.clear();
                    std::string skip;
                    std::getline(std::cin, skip);
                    std::cout << "Invalid input. Please enter a number between 0 and " << race.MaxSize << ".\n";
                } else {
                    break;
                }
            } else if (sizeChoice == 2) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(race.MaxSize / 2, race.MaxSize + 10);
                Size = dis(gen);
                break;
            } else {
                std::cout << "Invalid choice. Please enter 1 or 2.\n";
            }
        }
        system("clear");
        std::cout  << "Size : " << Size << std::endl;
        if (Size <= 20) SizeCategory = "Tiny";
        else if (Size <= 100) SizeCategory = "Small";
        else if (Size <= 190) SizeCategory = "Medium";
        else if (Size <= 320) SizeCategory = "Large";
        else if (Size <= 640) SizeCategory = "Huge";
        else SizeCategory = "Gargantuan";
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
                YAML::Node config = YAML::LoadFile("conf/NPC_conf.yaml");
                // attempt to load HPdice robustly
                int loadedHP = 0;
                YAML::Node classNode = config["NPC_conf"][classtype.name];
                if (classNode) {
                    YAML::Node hpNode;
                    if (classNode.IsSequence() && classNode.size() > 0) hpNode = classNode[0]["HPdice"];
                    else if (classNode.IsMap()) hpNode = classNode["HPdice"];

                    if (hpNode && hpNode.IsScalar()) {
                        try {
                            loadedHP = hpNode.as<int>();
                        } catch (const YAML::Exception &e) {
                            std::cerr << "HPdice conversion error for class " << classtype.name << ": " << e.what() << "\n";
                        }
                    }
                }

                if (loadedHP > 0) {
                    classtype.HPdice = loadedHP;
                } else {
                    static const std::map<std::string,int> defaultHP = {{"Barbarian",12},{"Bard",6},{"Cleric",8},{"Druid",8},{"Fighter",10},{"Monk",8},{"Paladin",10},{"Rogue",8},{"Wizard",4}};
                    auto it = defaultHP.find(classtype.name);
                    classtype.HPdice = (it != defaultHP.end()) ? it->second : 8;
                }

                for (int i = 1; i <= level; ++i) {
                    if (i == 1) HP = classtype.HPdice;
                    else HP += rand() % classtype.HPdice + 1; // + CON mod 
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
            std::cout << "1- Celect Alignment " << std::endl << "2- Random Alignment" << std::endl << "Enter your choice : ";
            int alignmentChoice;
            std::cin >> alignmentChoice;
            if (alignmentChoice == 1) {
                std::cout << "Please select an alignment: " << std::endl << "1- Lawful Good" << std::endl << "2- Neutral Good" << std::endl << "3- Chaotic Good" << std::endl << "4- Lawful Neutral" << std::endl << "5- Neutral Neutral" << std::endl << "6- Chaotic Neutral" << std::endl << "7- Lawful Evil" << std::endl << "8- Neutral Evil" << std::endl << "9- Chaotic Evil" << std::endl << "Enter your choice : ";
                int specificAlignmentChoice;
                if (!(std::cin >> specificAlignmentChoice)) { std::cin.clear(); std::string skip; std::getline(std::cin, skip); }
                switch (specificAlignmentChoice)                {
                    case 1: alignment.alig1 = "Lawful"; alignment.alig2 = "Good"; break;
                    case 2: alignment.alig1 = "Neutral"; alignment.alig2 = "Good"; break;
                    case 3: alignment.alig1 = "Chaotic"; alignment.alig2 = "Good"; break;
                    case 4: alignment.alig1 = "Lawful"; alignment.alig2 = "Neutral"; break;
                    case 5: alignment.alig1 = "Neutral"; alignment.alig2 = "Neutral"; break;
                    case 6: alignment.alig1 = "Chaotic"; alignment.alig2 = "Neutral"; break;
                    case 7: alignment.alig1 = "Lawful"; alignment.alig2 = "Evil"; break;
                    case 8: alignment.alig1 = "Neutral"; alignment.alig2 = "Evil"; break;
                    case 9: alignment.alig1 = "Chaotic"; alignment.alig2 = "Evil";break;
                }
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
        while (true) {
            std::cout << "Do you want your NPC to be a worshipper of a divinity? (y/n): ";
            char divinityChoice;
            std::cin >> divinityChoice;
            if (divinityChoice == 'y' || divinityChoice == 'Y') {
                std::cout << "1- Random Divinity" << std::endl << "2- Select Divinity" << std::endl << "3- Divinity By Alignment" << std::endl << "Enter your choice : ";
                int specificDivinityChoice;
                if (!(std::cin >> specificDivinityChoice)) { std::cin.clear(); std::string skip; std::getline(std::cin, skip); }
                if (specificDivinityChoice == 1) {
                    divinity = Get_Random_Divinity();
                    divinity.print_divinity_info();
                } else if (specificDivinityChoice == 2) {
                    YAML::Node divinitiesNode = config["NPC_conf"]["Divinite"];
                    std::cout << "Please select a divinity: " << std::endl;
                    for (size_t i = 0; i < divinitiesNode.size(); ++i) {
                        std::cout << i + 1 << "- " << divinitiesNode[i].as<std::string>() << " Alignment: " << config["NPC_conf"]["DivinityDetails"][divinitiesNode[i].as<std::string>()]["Alignment1"].as<std::string>() << " " << config["NPC_conf"]["DivinityDetails"][divinitiesNode[i].as<std::string>()]["Alignment2"].as<std::string>() << std::endl;
                    }
                    int divinityIndex;
                    std::cout << "Enter your choice : ";
                    if (!(std::cin >> divinityIndex) || divinityIndex < 1 || divinityIndex > divinitiesNode.size()) {
                        std::cin.clear();
                        std::string skip;
                        std::getline(std::cin, skip);
                        std::cout << "Invalid choice. Please select a valid divinity number.\n";
                    } else {
                        std::string chosenDivinity = divinitiesNode[divinityIndex - 1].as<std::string>();
                        YAML::Node divinityDetails = config["NPC_conf"]["DivinityDetails"][chosenDivinity];
                        if (divinityDetails) {
                            Alignment divinityAlignment;
                            divinityAlignment.alig1 = divinityDetails["Alignment1"].as<std::string>();
                            divinityAlignment.alig2 = divinityDetails["Alignment2"].as<std::string>();
                            divinity = Divinite(chosenDivinity, divinityAlignment);
                            divinity.print_divinity_info();
                        } else {
                            std::cout << "Details for the selected divinity are missing in the configuration.\n";
                        }
                    }
                } else if (specificDivinityChoice == 3) {
                    // Map alignments to available deities from the YAML configuration
                    std::map<std::string, std::vector<std::string>> alignmentToDivinities;
                    alignmentToDivinities["Lawful Good"] = {"Heironeous", "Moradin", "Yondalla"};
                    alignmentToDivinities["Neutral Good"] = {"Ehlonna", "Garl Brilledor", "Pelor"};
                    alignmentToDivinities["Chaotic Good"] = {"Kord"};
                    alignmentToDivinities["Lawful Neutral"] = {"St. Cuthbert", "Wy-Djaz"};
                    alignmentToDivinities["Neutral Neutral"] = {"Boccob", "Fharlanghn", "Obad-Hai"};
                    alignmentToDivinities["Chaotic Neutral"] = {"Olidammara"};
                    alignmentToDivinities["Lawful Evil"] = {"Hextor"};
                    alignmentToDivinities["Neutral Evil"] = {"Nerull", "Vecna"};
                    alignmentToDivinities["Chaotic Evil"] = {"Erythnul", "Gruumsh"};
                    
                    std::string alignmentKey = alignment.alig1 + " " + alignment.alig2;
                    
                    if (alignmentToDivinities.find(alignmentKey) != alignmentToDivinities.end()) {
                        std::vector<std::string>& possibleDivinities = alignmentToDivinities[alignmentKey];
                        std::random_device rd;
                        std::mt19937 gen(rd());
                        std::uniform_int_distribution<> dis(0, possibleDivinities.size() - 1);
                        std::string chosenDivinity = possibleDivinities[dis(gen)];
                        
                        YAML::Node divinityDetails = config["NPC_conf"]["DivinityDetails"][chosenDivinity];
                        if (divinityDetails) {
                            Alignment divinityAlignment;
                            divinityAlignment.alig1 = divinityDetails["Alignment1"].as<std::string>();
                            divinityAlignment.alig2 = divinityDetails["Alignment2"].as<std::string>();
                            divinity = Divinite(chosenDivinity, divinityAlignment);
                            divinity.print_divinity_info();
                        }
                    } else {
                        divinity.name = "None";
                        divinity.alignment.alig1 = alignment.alig1;
                        divinity.alignment.alig2 = alignment.alig2;
                    }
                } else {
                    std::cout << "Invalid choice. Please try again.\n";
                }
                break;
            } else if (divinityChoice == 'n' || divinityChoice == 'N') {
                divinity.name = "None";
                divinity.alignment.alig1 = alignment.alig1;
                divinity.alignment.alig2 = alignment.alig2;
                break;
            } else {
                std::cout << "Invalid choice. Please enter 'y' or 'n': ";
            }
        }
        system("clear");
        std::cout << "Divinity : " << divinity.name << std::endl;
        while (true) {
            std::cout << "Carecteristiques : " << std::endl << "1- Custom Carecteristiqes" << std::endl << "2- Calculate Carecteristiqes with class (dos not work rn)" << std::endl << "3- Random Carecteristiqes" << std::endl << "Enter your choice : ";
            int carecteristicsChoice;
            std::cin >> carecteristicsChoice;
            if (carecteristicsChoice == 1) {
                std::cout << "Please enter the NPC's Strength: ";
                std::cin >> FOR;
                std::cout << "Please enter the NPC's Dexterity: ";
                std::cin >> DEX;
                std::cout << "Please enter the NPC's Constitution: ";
                std::cin >> CON;
                std::cout << "Please enter the NPC's Intelligence: ";
                std::cin >> INT;
                std::cout << "Please enter the NPC's Wisdom: ";
                std::cin >> SAG;
                std::cout << "Please enter the NPC's Charisma: ";
                std::cin >> CHA;
                break;
            } else if (carecteristicsChoice == 2) {
                std::cout << "Currunly not working" << std::endl;
                /*int Diceroll1, Diceroll2, Diceroll3, Diceroll4, Diceroll5, Diceroll6;
                Diceroll1 = Calculate_Carecteristics();
                Diceroll2 = Calculate_Carecteristics();
                Diceroll3 = Calculate_Carecteristics();
                Diceroll4 = Calculate_Carecteristics();
                Diceroll5 = Calculate_Carecteristics();
                Diceroll6 = Calculate_Carecteristics();
                std::cout << "Generated rolls: " << Diceroll1 << ", " << Diceroll2 << ", " << Diceroll3 << ", " << Diceroll4 << ", " << Diceroll5 << ", " << Diceroll6 << std::endl;
                if (Diceroll1 < Diceroll2) std::swap(Diceroll1, Diceroll2);
                if (Diceroll1 < Diceroll3) std::swap(Diceroll1, Diceroll3);
                if (Diceroll1 < Diceroll4) std::swap(Diceroll1, Diceroll4);
                if (Diceroll1 < Diceroll5) std::swap(Diceroll1, Diceroll5);
                if (Diceroll1 < Diceroll6) std::swap(Diceroll1, Diceroll6);
                if (Diceroll2 < Diceroll3) std::swap(Diceroll2, Diceroll3);
                if (Diceroll2 < Diceroll4) std::swap(Diceroll2, Diceroll4);
                if (Diceroll2 < Diceroll5) std::swap(Diceroll2, Diceroll5);
                if (Diceroll2 < Diceroll6) std::swap(Diceroll2, Diceroll6);
                if (Diceroll3 < Diceroll4) std::swap(Diceroll3, Diceroll4);
                if (Diceroll3 < Diceroll5) std::swap(Diceroll3, Diceroll5);
                if (Diceroll3 < Diceroll6) std::swap(Diceroll3, Diceroll6);
                if (Diceroll4 < Diceroll5) std::swap(Diceroll4, Diceroll5);
                if (Diceroll4 < Diceroll6) std::swap(Diceroll4, Diceroll6);
                if (Diceroll5 < Diceroll6) std::swap(Diceroll5, Diceroll6);
                std::cout << "Generated rolls: " << Diceroll1 << ", " << Diceroll2 << ", " << Diceroll3 << ", " << Diceroll4 << ", " << Diceroll5 << ", " << Diceroll6 << std::endl;
                YAML::Node config = YAML::LoadFile("conf/NPC_conf.yaml");
                std::string priority1 = config["NPC_conf"][classtype.name]["Caracteristicspriority"][0].as<std::string>();
                std::string priority2 = config["NPC_conf"][classtype.name]["Caracteristicspriority"][1].as<std::string>();
                std::string priority3 = config["NPC_conf"][classtype.name]["Caracteristicspriority"][2].as<std::string>();
                std::string priority4 = config["NPC_conf"][classtype.name]["Caracteristicspriority"][3].as<std::string>();
                std::string priority5 = config["NPC_conf"][classtype.name]["Caracteristicspriority"][4].as<std::string>();
                std::string priority6 = config["NPC_conf"][classtype.name]["Caracteristicspriority"][5].as<std::string>();
                //give the highest roll to the highest priority stat, the second highest to the second priority, etc.
                std::map<std::string, int*> statMap = {{"FOR", &FOR}, {"DEX", &DEX}, {"CON", &CON}, {"INT", &INT}, {"SAG", &SAG}, {"CHA", &CHA}};
                if (statMap.find(priority1) != statMap.end()) *statMap[priority1] = Diceroll1;
                if (statMap.find(priority2) != statMap.end()) *statMap[priority2] = Diceroll2;
                if (statMap.find(priority3) != statMap.end()) *statMap[priority3] = Diceroll3;
                if (statMap.find(priority4) != statMap.end()) *statMap[priority4] = Diceroll4;
                if (statMap.find(priority5) != statMap.end()) *statMap[priority5] = Diceroll5;
                if (statMap.find(priority6) != statMap.end()) *statMap[priority6] = Diceroll6;
                break;*/
            } else if (carecteristicsChoice == 3) {
                bool validStats = false;
                while (validStats == false) {
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> dis(3, 18);
                    FOR = dis(gen);
                    DEX = dis(gen);
                    CON = dis(gen);
                    INT = dis(gen);
                    SAG = dis(gen);
                    CHA = dis(gen);
                    if (FOR + DEX + CON + INT + SAG + CHA >= 50) validStats = true;
                    else validStats = false; //std::cout << "Debug: Generated stats sum = " << FOR + DEX + CON + INT + SAG + CHA << " (regenerating...)\n";
                }
                for (int i = 0; i < level / 4; ++i) {
                    //std::cout << "Debug: i = " << i << std::endl;
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> dis(1, 6);
                    if (dis(gen) == 1) FOR += 1;
                    if (dis(gen) == 2) DEX += 1;
                    if (dis(gen) == 3) CON += 1;
                    if (dis(gen) == 4) INT += 1;
                    if (dis(gen) == 5) SAG += 1;
                    if (dis(gen) == 6) CHA += 1;
                }
                break;
            } else {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
        system("clear");
        std::cout << "Strength : " << FOR << std::endl << "Dexterity : " << DEX << std::endl << "Constitution : " << CON << std::endl << "Intelligence : " << INT << std::endl << "Wisdom : " << SAG << std::endl << "Charisma : " << CHA << std::endl;
        while (true){
            CA = 10 + (DEX - 10) / 2;
            if (SizeCategory == "Tiny") CA += 2;
            else if (SizeCategory == "Small") CA += 1;
            else if (SizeCategory == "Large") CA -= 1;
            else if (SizeCategory == "Huge") CA -= 2;
            else if (SizeCategory == "Gargantuan") CA -= 4;
            std::cout << "AC : " << CA << std::endl;
            std::cout << "NPC has a armor? (y/n) ";
            std::string armor;
            std::cin >> armor;
            if (armor == "y" || armor == "Y") {
                std::cout << "Please enter the armor's AC bonus: ";
                int armorBonus;
                if (!(std::cin >> armorBonus) || armorBonus < 0) {
                    std::cin.clear();
                    std::string skip;
                    std::getline(std::cin, skip);
                    std::cout << "Invalid input. Please enter a non-negative number.\n";
                } else {
                    CA += armorBonus;
                    std::cout << "AC : " << CA << std::endl;
                }
            }
            else if (armor == "n" || armor == "N") {
                std::cout << "AC : " << CA << std::endl;
            } else {
                std::cout << "Invalid choice. Please enter 'y' or 'n': ";
            }
            std::cout << "NPC has a shield? (y/n) ";
            std::string shield;
            std::cin >> shield;
            if (shield == "y" || shield == "Y") {
                std::cout << "AC : " << CA << std::endl;
                std::cout << "Please enter the shield's AC bonus: ";
                int shieldBonus;
                if (!(std::cin >> shieldBonus) || shieldBonus < 0) {
                    std::cin.clear();
                    std::string skip;
                    std::getline(std::cin, skip);
                    std::cout << "Invalid input. Please enter a non-negative number.\n";
                } else {
                    CA += shieldBonus;
                    std::cout << "AC : " << CA << std::endl;
                }
            }
            else if (shield == "n" || shield == "N") {
                std::cout << "AC : " << CA << std::endl;
            } else {
                std::cout << "Invalid choice. Please enter 'y' or 'n': ";
            }
            std::cout << "NPC has a natural armor? (y/n) ";
            std::string naturalArmor;
            std::cin >> naturalArmor;
            if (naturalArmor == "y" || naturalArmor == "Y") {
                std::cout << "Please enter the natural armor's AC bonus: ";
                int naturalArmorBonus;
                if (!(std::cin >> naturalArmorBonus) || naturalArmorBonus < 0) {
                    std::cin.clear();
                    std::string skip;
                    std::getline(std::cin, skip);
                    std::cout << "Invalid input. Please enter a non-negative number.\n";
                } else {
                    CA += naturalArmorBonus;
                    std::cout << "AC : " << CA << std::endl;
                }
            }
            else if (naturalArmor == "n" || naturalArmor == "N") {
                std::cout << "AC : " << CA << std::endl;
            } else {
                std::cout << "Invalid choice. Please enter 'y' or 'n': ";
            }
            std::cout << "NPC has magical objects that give it an AC bonus? (y/n) ";
            std::string magicalObjects;
            std::cin >> magicalObjects;
            if (magicalObjects == "y" || magicalObjects == "Y") {
                std::cout << "Please enter the total AC bonus from magical objects: ";
                int magicalObjectsBonus;
                if (!(std::cin >> magicalObjectsBonus) || magicalObjectsBonus < 0) {
                    std::cin.clear();
                    std::string skip;
                    std::getline(std::cin, skip);
                    std::cout << "Invalid input. Please enter a non-negative number.\n";
                } else {
                    CA += magicalObjectsBonus;
                    std::cout << "AC : " << CA << std::endl;
                }
            }
            else if (magicalObjects == "n" || magicalObjects == "N") {
               std::cout << "AC : " <<  CA << std::endl;
            } else {
                std::cout << "Invalid choice. Please enter 'y' or 'n': ";
            }
            std::cout << "AC : " << CA << std::endl;
            std::cout << "Do you want to adjust the AC further? (y/n) ";
            std::string adjustCA;
            std::cin >> adjustCA;
            if (adjustCA == "n" || adjustCA == "N") {
                std::cout << "AC : " << CA << std::endl;
            } else if (adjustCA != "y" && adjustCA != "Y") {
                std::cout << "Final Modifier : ";
                int finalmod;
                std::cin >> finalmod;
                CA += finalmod;
                std::cout << "AC : " << CA << std::endl;
            }
            else {
                std::cout << "Invalid choice. Please enter 'y' or 'n': ";
            }
            break;
        }
        system("clear");
        std::cout << "AC : " << CA << std::endl;
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
