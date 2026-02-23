#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <yaml-cpp/yaml.h>
#include <QCoreApplication>

#include "alignment.h"
#include "classtype.h"
#include "divinite.h"
#include "Race.h"
#include "NPC.h"

Race NPC::Get_Random_Race() {
    QString configPath = QCoreApplication::applicationDirPath() + "/conf/NPC_conf.yaml";
    YAML::Node config = YAML::LoadFile(configPath.toStdString());
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

ClassType NPC::Get_Random_Class() {
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

Divinite NPC::Get_Random_Divinity() {
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

int NPC::Calculate_Carecteristics() {
    int Diceroll;
    int D1 = rand() % 6 + 1;
    int D2 = rand() % 6 + 1;
    int D3 = rand() % 6 + 1;
    int D4 = rand() % 6 + 1;
    if (D1 < D2) std::swap(D1, D2);
    if (D1 < D3) std::swap(D1, D3);
    if (D1 < D4) std::swap(D1, D4);
    if (D2 < D3) std::swap(D2, D3);
    if (D2 < D4) std::swap(D2, D4);
    if (D3 < D4) std::swap(D3, D4);
    Diceroll = D1 + D2 + D3;
    return Diceroll;
}

void NPC::Get_NPC_Stats() {
    YAML::Node config = YAML::LoadFile("conf/NPC_conf.yaml");

    // --- Race ---
    while (true) {
        std::cout << "Race : " << std::endl
                  << "1- Random Race" << std::endl
                  << "2- Celect Race" << std::endl
                  << "3- Custom Race" << std::endl
                  << "Enter your choice : ";
        int raceChoice;
        if (!(std::cin >> raceChoice)) {
            std::cin.clear();
            std::string skip;
            std::getline(std::cin, skip);
            continue;
        }

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
                if (!(std::cin >> specificRaceChoice)) {
                    std::cin.clear();
                    std::string skip;
                    std::getline(std::cin, skip);
                    continue;
                }
                if (specificRaceChoice >= 1 && specificRaceChoice <= (int)RaceNode.size()) {
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

    // --- Class ---
    while (true) {
        std::cout << "Class : " << std::endl
                  << "1- Random Class" << std::endl
                  << "2- Celect Class" << std::endl
                  << "3- Custom Class" << std::endl
                  << "Enter your choice : ";
        int classChoice;
        if (!(std::cin >> classChoice)) {
            std::cin.clear();
            std::string skip;
            std::getline(std::cin, skip);
            continue;
        }

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
                if (!(std::cin >> specificClassChoice)) {
                    std::cin.clear();
                    std::string skip;
                    std::getline(std::cin, skip);
                    continue;
                }
                if (specificClassChoice >= 1 && specificClassChoice <= (int)ClassNode.size()) {
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
    std::cout << "Race : " << race.name << std::endl
              << "Class : " << classtype.name << std::endl;

    // --- Name ---
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
        } else {
            std::cout << "Invalid choice. Please enter 'y' or 'n': ";
        }
    }
    system("clear");
    std::cout << "Race : " << race.name << std::endl
              << "Class : " << classtype.name << std::endl
              << "Name : " << name << std::endl;

    // --- Last Name ---
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
        } else {
            std::cout << "Invalid choice. Please enter 'y' or 'n': ";
        }
    }
    system("clear");
    std::cout << "Last Name : " << LastName << std::endl;

    // --- Sex ---
    while (true) {
        std::cout << "1- Select Sexe" << std::endl
                  << "2- Random Sexe" << std::endl
                  << "Enter your choice : ";
        int sexeChoice;
        std::cin >> sexeChoice;
        if (sexeChoice == 1) {
            YAML::Node sexesNode = config["NPC_conf"]["Sexes"];
            std::cout << "Available :" << std::endl;
            int i = 1;
            for (YAML::const_iterator it = sexesNode.begin(); it != sexesNode.end(); ++it) {
                std::cout << i << "- " << it->as<std::string>() << std::endl;
                i++;
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
            std::cout << "Invalid choice. Please enter 1 or 2.\n";
        }
    }
    system("clear");
    std::cout << "Sexe : " << Sexe << std::endl;

    // --- Age ---
    while (true) {
        std::cout << "1- Custom Age" << std::endl
                  << "2- Random Age" << std::endl
                  << "Enter your choice : ";
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

    // --- Size ---
    while (true) {
        std::cout << "1- Custom Size" << std::endl
                  << "2- Random Size" << std::endl
                  << "Enter your choice : ";
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
    std::cout << "Size : " << Size << std::endl;

    if (Size <= 20)        SizeCategory = "Tiny";
    else if (Size <= 100)  SizeCategory = "Small";
    else if (Size <= 190)  SizeCategory = "Medium";
    else if (Size <= 320)  SizeCategory = "Large";
    else if (Size <= 640)  SizeCategory = "Huge";
    else                   SizeCategory = "Gargantuan";

    // --- Level / XP ---
    while (true) {
        std::cout << "1- Enter level" << std::endl
                  << "2- Random level" << std::endl
                  << "3- Enter XP" << std::endl
                  << "4- Random XP" << std::endl
                  << "Enter your choice : ";
        int choice;
        std::cin >> choice;

        auto levelFromXP = [&](int xp) {
            if (xp >= 190000)     return 20;
            else if (xp >= 171000) return 19;
            else if (xp >= 153000) return 18;
            else if (xp >= 136000) return 17;
            else if (xp >= 120000) return 16;
            else if (xp >= 105000) return 15;
            else if (xp >= 91000)  return 14;
            else if (xp >= 78000)  return 13;
            else if (xp >= 66000)  return 12;
            else if (xp >= 55000)  return 11;
            else if (xp >= 45000)  return 10;
            else if (xp >= 36000)  return 9;
            else if (xp >= 28000)  return 8;
            else if (xp >= 21000)  return 7;
            else if (xp >= 15000)  return 6;
            else if (xp >= 10000)  return 5;
            else if (xp >= 6000)   return 4;
            else if (xp >= 3000)   return 3;
            else if (xp >= 1000)   return 2;
            else                   return 1;
        };

        auto xpFromLevel = [&](int lvl) {
            const int table[] = { 0, 0, 1000, 3000, 6000, 10000, 15000, 21000,
                                 28000, 36000, 45000, 55000, 66000, 78000,
                                 91000, 105000, 120000, 136000, 153000, 171000, 190000 };
            return table[lvl];
        };

        if (choice == 1) {
            std::cout << "Please enter the NPC's level (1-20): ";
            if (!(std::cin >> level) || level < 1 || level > 20) {
                std::cin.clear();
                std::string skip;
                std::getline(std::cin, skip);
                std::cout << "Invalid input. Please enter a number between 1 and 20.\n";
                continue;
            }
            XP = xpFromLevel(level);
            break;
        } else if (choice == 2) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 20);
            level = dis(gen);
            XP = xpFromLevel(level);
            break;
        } else if (choice == 3) {
            std::cout << "Please enter the NPC's XP: ";
            if (!(std::cin >> XP) || XP < 0) {
                std::cin.clear();
                std::string skip;
                std::getline(std::cin, skip);
                std::cout << "Invalid input. Please enter a non-negative number.\n";
                continue;
            }
            level = levelFromXP(XP);
            break;
        } else if (choice == 4) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, 190000);
            XP = dis(gen);
            level = levelFromXP(XP);
            break;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    system("clear");
    std::cout << "Level : " << level << std::endl;

    // --- HP ---
    while (true) {
        std::cout << "1- Enter HP" << std::endl
                  << "2- Calculate HP based on class and level" << std::endl
                  << "Enter your choice : ";
        int hpChoice;
        std::cin >> hpChoice;
        if (hpChoice == 1) {
            std::cout << "Please enter the NPC's HP: ";
            if (!(std::cin >> HP) || HP < 1) {
                std::cin.clear();
                std::string skip;
                std::getline(std::cin, skip);
                std::cout << "Invalid input. Please enter a positive number.\n";
                continue;
            }
            break;
        } else if (hpChoice == 2) {
            int loadedHP = 0;
            YAML::Node classNode = config["NPC_conf"][classtype.name];
            if (classNode) {
                YAML::Node hpNode;
                if (classNode.IsSequence() && classNode.size() > 0)
                    hpNode = classNode[0]["HPdice"];
                else if (classNode.IsMap())
                    hpNode = classNode["HPdice"];

                if (hpNode && hpNode.IsScalar()) {
                    try {
                        loadedHP = hpNode.as<int>();
                    } catch (const YAML::Exception& e) {
                        std::cerr << "HPdice conversion error for class " << classtype.name << ": " << e.what() << "\n";
                    }
                }
            }

            if (loadedHP > 0) {
                classtype.HPdice = loadedHP;
            } else {
                static const std::map<std::string, int> defaultHP = {
                    {"Barbarian", 12}, {"Bard", 6},    {"Cleric", 8},
                    {"Druid", 8},      {"Fighter", 10}, {"Monk", 8},
                    {"Paladin", 10},   {"Rogue", 8},    {"Wizard", 4}
                };
                auto it = defaultHP.find(classtype.name);
                classtype.HPdice = (it != defaultHP.end()) ? it->second : 8;
            }

            for (int i = 1; i <= level; ++i) {
                if (i == 1) HP = classtype.HPdice;
                else        HP += rand() % classtype.HPdice + 1;
            }
            break;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    system("clear");
    std::cout << "HP : " << HP << std::endl;

    // --- Alignment ---
    while (true) {
        std::cout << "1- Celect Alignment" << std::endl
                  << "2- Random Alignment" << std::endl
                  << "Enter your choice : ";
        int alignmentChoice;
        std::cin >> alignmentChoice;
        if (alignmentChoice == 1) {
            std::cout << "Please select an alignment: " << std::endl
                      << "1- Lawful Good"    << std::endl
                      << "2- Neutral Good"   << std::endl
                      << "3- Chaotic Good"   << std::endl
                      << "4- Lawful Neutral" << std::endl
                      << "5- Neutral Neutral"<< std::endl
                      << "6- Chaotic Neutral"<< std::endl
                      << "7- Lawful Evil"    << std::endl
                      << "8- Neutral Evil"   << std::endl
                      << "9- Chaotic Evil"   << std::endl
                      << "Enter your choice : ";
            int specificAlignmentChoice;
            if (!(std::cin >> specificAlignmentChoice)) {
                std::cin.clear();
                std::string skip;
                std::getline(std::cin, skip);
            }
            switch (specificAlignmentChoice) {
            case 1: alignment.alig1 = "Lawful";  alignment.alig2 = "Good";    break;
            case 2: alignment.alig1 = "Neutral"; alignment.alig2 = "Good";    break;
            case 3: alignment.alig1 = "Chaotic"; alignment.alig2 = "Good";    break;
            case 4: alignment.alig1 = "Lawful";  alignment.alig2 = "Neutral"; break;
            case 5: alignment.alig1 = "Neutral"; alignment.alig2 = "Neutral"; break;
            case 6: alignment.alig1 = "Chaotic"; alignment.alig2 = "Neutral"; break;
            case 7: alignment.alig1 = "Lawful";  alignment.alig2 = "Evil";    break;
            case 8: alignment.alig1 = "Neutral"; alignment.alig2 = "Evil";    break;
            case 9: alignment.alig1 = "Chaotic"; alignment.alig2 = "Evil";    break;
            }
            break;
        } else if (alignmentChoice == 2) {
            std::vector<std::string> alignments1 = {"Lawful", "Neutral", "Chaotic"};
            std::vector<std::string> alignments2 = {"Good", "Neutral", "Evil"};
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis1(0, alignments1.size() - 1);
            std::uniform_int_distribution<> dis2(0, alignments2.size() - 1);
            alignment.alig1 = alignments1[dis1(gen)];
            alignment.alig2 = alignments2[dis2(gen)];
            break;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    system("clear");
    std::cout << "Alignment : " << alignment.alig1 << " " << alignment.alig2 << std::endl;

    // --- Divinity ---
    while (true) {
        std::cout << "Do you want your NPC to be a worshipper of a divinity? (y/n): ";
        char divinityChoice;
        std::cin >> divinityChoice;
        if (divinityChoice == 'y' || divinityChoice == 'Y') {
            std::cout << "1- Random Divinity" << std::endl
                      << "2- Select Divinity" << std::endl
                      << "3- Divinity By Alignment" << std::endl
                      << "Enter your choice : ";
            int specificDivinityChoice;
            if (!(std::cin >> specificDivinityChoice)) {
                std::cin.clear();
                std::string skip;
                std::getline(std::cin, skip);
            }

            if (specificDivinityChoice == 1) {
                divinity = Get_Random_Divinity();
                divinity.print_divinity_info();
            } else if (specificDivinityChoice == 2) {
                YAML::Node divinitiesNode = config["NPC_conf"]["Divinite"];
                std::cout << "Please select a divinity: " << std::endl;
                for (size_t i = 0; i < divinitiesNode.size(); ++i) {
                    std::string dname = divinitiesNode[i].as<std::string>();
                    std::cout << i + 1 << "- " << dname
                              << " Alignment: "
                              << config["NPC_conf"]["DivinityDetails"][dname]["Alignment1"].as<std::string>()
                              << " "
                              << config["NPC_conf"]["DivinityDetails"][dname]["Alignment2"].as<std::string>()
                              << std::endl;
                }
                int divinityIndex;
                std::cout << "Enter your choice : ";
                if (!(std::cin >> divinityIndex) || divinityIndex < 1 || divinityIndex > (int)divinitiesNode.size()) {
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
                std::map<std::string, std::vector<std::string>> alignmentToDivinities;
                alignmentToDivinities["Lawful Good"]    = {"Heironeous", "Moradin", "Yondalla"};
                alignmentToDivinities["Neutral Good"]   = {"Ehlonna", "Garl Brilledor", "Pelor"};
                alignmentToDivinities["Chaotic Good"]   = {"Kord"};
                alignmentToDivinities["Lawful Neutral"] = {"St. Cuthbert", "Wy-Djaz"};
                alignmentToDivinities["Neutral Neutral"]= {"Boccob", "Fharlanghn", "Obad-Hai"};
                alignmentToDivinities["Chaotic Neutral"]= {"Olidammara"};
                alignmentToDivinities["Lawful Evil"]    = {"Hextor"};
                alignmentToDivinities["Neutral Evil"]   = {"Nerull", "Vecna"};
                alignmentToDivinities["Chaotic Evil"]   = {"Erythnul", "Gruumsh"};

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

    // --- Characteristics ---
    while (true) {
        std::cout << "Carecteristiques : " << std::endl
                  << "1- Custom Carecteristiqes" << std::endl
                  << "2- Calculate Carecteristiqes with class (does not work rn)" << std::endl
                  << "3- Random Carecteristiqes" << std::endl
                  << "Enter your choice : ";
        int carecteristicsChoice;
        std::cin >> carecteristicsChoice;

        if (carecteristicsChoice == 1) {
            std::cout << "Please enter the NPC's Strength: ";     std::cin >> FOR;
            std::cout << "Please enter the NPC's Dexterity: ";    std::cin >> DEX;
            std::cout << "Please enter the NPC's Constitution: "; std::cin >> CON;
            std::cout << "Please enter the NPC's Intelligence: "; std::cin >> INT;
            std::cout << "Please enter the NPC's Wisdom: ";       std::cin >> SAG;
            std::cout << "Please enter the NPC's Charisma: ";     std::cin >> CHA;
            break;
        } else if (carecteristicsChoice == 2) {
            std::cout << "Currunly not working" << std::endl;
        } else if (carecteristicsChoice == 3) {
            bool validStats = false;
            while (!validStats) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(3, 18);
                FOR = dis(gen);
                DEX = dis(gen);
                CON = dis(gen);
                INT = dis(gen);
                SAG = dis(gen);
                CHA = dis(gen);
                validStats = (FOR + DEX + CON + INT + SAG + CHA >= 50);
            }
            for (int i = 0; i < level / 4; ++i) {
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
    std::cout << "Strength : "     << FOR << std::endl
              << "Dexterity : "    << DEX << std::endl
              << "Constitution : " << CON << std::endl
              << "Intelligence : " << INT << std::endl
              << "Wisdom : "       << SAG << std::endl
              << "Charisma : "     << CHA << std::endl;

    // --- AC ---
    while (true) {
        CA = 10 + (DEX - 10) / 2;
        if      (SizeCategory == "Tiny")      CA += 2;
        else if (SizeCategory == "Small")     CA += 1;
        else if (SizeCategory == "Large")     CA -= 1;
        else if (SizeCategory == "Huge")      CA -= 2;
        else if (SizeCategory == "Gargantuan")CA -= 4;
        std::cout << "AC : " << CA << std::endl;

        auto askBonus = [&](const std::string& prompt) {
            std::cout << prompt;
            std::string answer;
            std::cin >> answer;
            if (answer == "y" || answer == "Y") {
                std::cout << "Please enter the AC bonus: ";
                int bonus;
                if (!(std::cin >> bonus) || bonus < 0) {
                    std::cin.clear();
                    std::string skip;
                    std::getline(std::cin, skip);
                    std::cout << "Invalid input. Please enter a non-negative number.\n";
                } else {
                    CA += bonus;
                    std::cout << "AC : " << CA << std::endl;
                }
            } else if (answer != "n" && answer != "N") {
                std::cout << "Invalid choice. Please enter 'y' or 'n': ";
            }
        };

        askBonus("NPC has armor? (y/n) ");
        askBonus("NPC has a shield? (y/n) ");
        askBonus("NPC has natural armor? (y/n) ");
        askBonus("NPC has magical objects that give an AC bonus? (y/n) ");

        std::cout << "AC : " << CA << std::endl;
        std::cout << "Do you want to adjust the AC further? (y/n) ";
        std::string adjustCA;
        std::cin >> adjustCA;
        if (adjustCA == "y" || adjustCA == "Y") {
            std::cout << "Final Modifier : ";
            int finalmod;
            std::cin >> finalmod;
            CA += finalmod;
            std::cout << "AC : " << CA << std::endl;
        }
        break;
    }
    system("clear");
    std::cout << "AC : " << CA << std::endl;
}
