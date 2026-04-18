#include <iostream>
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "../include/NPC/classtype.h"

using namespace testing;

//classtype_set_AlowedArmors

TEST(classtype, classtype_set_AlowedArmors_NodeEmpty) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config;
    ClassType.name = "Bard";
    try {
        ClassType.set_AlowedArmors(config, ClassType.name);
        FAIL() << "Expected std::runtime_error";
    }
    catch (std::runtime_error& e) {
        EXPECT_STREQ("YAML File Error", e.what());
    }
}

TEST(classtype, classtype_set_AlowedArmors_BadNode) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/conf_Armor_test.yaml");
    ClassType.name = "Bard";
    try {
        ClassType.set_AlowedArmors(config, ClassType.name);
        FAIL() << "Expected std::runtime_error";
    }
    catch (std::runtime_error& e) {
        EXPECT_STREQ("YAML File Error", e.what());
    }
}

TEST(classtype, classtype_set_AlowedArmors_EmptyYAMLFile) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::Load("");
    ClassType.name = "Bard";
    try {
        ClassType.set_AlowedArmors(config, ClassType.name);
        FAIL() << "Expected std::runtime_error";
    }
    catch (std::runtime_error& e) {
        EXPECT_STREQ("YAML File Error", e.what());
    }
}

TEST(classtype, classtype_set_AlowedArmors_BadClassType_Name) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.name = "None Existant";
    try {
        ClassType.set_AlowedArmors(config, ClassType.name);
        FAIL() << "Expected std::runtime_error";
    }
    catch (std::runtime_error& e) {
        EXPECT_STREQ("Bad ClassType name", e.what());
    }
}

TEST(classtype, classtype_set_AlowedArmors_EmptyClassName) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.name = "";
    try {
        ClassType.set_AlowedArmors(config, ClassType.name);
        FAIL() << "Expected std::runtime_error";
    }
    catch (std::runtime_error& e) {
        EXPECT_STREQ("Bad ClassType name", e.what());
    }
}

TEST(classtype, classtype_set_AlowedArmors_CaseSensitiveName) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.name = "bard";
    try {
        ClassType.set_AlowedArmors(config, ClassType.name);
        FAIL() << "Expected std::runtime_error";
    }
    catch (std::runtime_error& e) {
        EXPECT_STREQ("Bad ClassType name", e.what());
    }
}

TEST(classtype, classtype_set_AlowedArmors_LeadingWhitespace) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.name = " Bard";
    try {
        ClassType.set_AlowedArmors(config, ClassType.name);
        FAIL() << "Expected std::runtime_error";
    }
    catch (std::runtime_error& e) {
        EXPECT_STREQ("Bad ClassType name", e.what());
    }
}

TEST(classtype, classtype_set_AlowedArmors_TrailingWhitespace) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.name = "Bard ";
    try {
        ClassType.set_AlowedArmors(config, ClassType.name);
        FAIL() << "Expected std::runtime_error";
    }
    catch (std::runtime_error& e) {
        EXPECT_STREQ("Bad ClassType name", e.what());
    }
}

TEST(classtype, classtype_set_AlowedArmors_WhitespaceOnly) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.name = "   ";
    try {
        ClassType.set_AlowedArmors(config, ClassType.name);
        FAIL() << "Expected std::runtime_error";
    }
    catch (std::runtime_error& e) {
        EXPECT_STREQ("Bad ClassType name", e.what());
    }
}

TEST(classtype, classtype_set_AlowedArmors_SpecialCharacters) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.name = "B@rd";
    try {
        ClassType.set_AlowedArmors(config, ClassType.name);
        FAIL() << "Expected std::runtime_error";
    }
    catch (std::runtime_error& e) {
        EXPECT_STREQ("Bad ClassType name", e.what());
    }
}

TEST(classtype, classtype_set_AlowedArmors_NumericClassName) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.name = "123";
    try {
        ClassType.set_AlowedArmors(config, ClassType.name);
        FAIL() << "Expected std::runtime_error";
    }
    catch (std::runtime_error& e) {
        EXPECT_STREQ("Bad ClassType name", e.what());
    }
}

TEST(classtype, classtype_set_AlowedArmors_Bard) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.name = "Bard";
    ClassType.set_AlowedArmors(config, ClassType.name);
    EXPECT_TRUE(ClassType.HasLightArmor);
    EXPECT_FALSE(ClassType.HasMidArmor);
    EXPECT_FALSE(ClassType.HasHeavyArmor);
    EXPECT_TRUE(ClassType.HasShild);
    EXPECT_FALSE(ClassType.Hastarge);
}

TEST(classtype, classtype_set_AlowedArmors_Barbarian) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.name = "Barbarian";
    ClassType.set_AlowedArmors(config, ClassType.name);
    EXPECT_TRUE(ClassType.HasLightArmor);
    EXPECT_TRUE(ClassType.HasMidArmor);
    EXPECT_TRUE(ClassType.HasHeavyArmor);
    EXPECT_TRUE(ClassType.HasShild);
    EXPECT_TRUE(ClassType.Hastarge);
}

TEST(classtype, classtype_set_AlowedArmors_Monk) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.name = "Monk";
    ClassType.set_AlowedArmors(config, ClassType.name);
    EXPECT_FALSE(ClassType.HasLightArmor);
    EXPECT_FALSE(ClassType.HasMidArmor);
    EXPECT_FALSE(ClassType.HasHeavyArmor);
    EXPECT_FALSE(ClassType.HasShild);
    EXPECT_FALSE(ClassType.Hastarge);
}

TEST(classtype, classtype_set_AlowedArmors_Wizard) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.name = "Wizard";
    ClassType.set_AlowedArmors(config, ClassType.name);
    EXPECT_FALSE(ClassType.HasLightArmor);
    EXPECT_FALSE(ClassType.HasMidArmor);
    EXPECT_FALSE(ClassType.HasHeavyArmor);
    EXPECT_FALSE(ClassType.HasShild);
    EXPECT_FALSE(ClassType.Hastarge);
}

TEST(classtype, classtype_set_AlowedArmors_Cleric) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.name = "Cleric";
    ClassType.set_AlowedArmors(config, ClassType.name);
    EXPECT_TRUE(ClassType.HasLightArmor);
    EXPECT_TRUE(ClassType.HasMidArmor);
    EXPECT_TRUE(ClassType.HasHeavyArmor);
    EXPECT_TRUE(ClassType.HasShild);
    EXPECT_FALSE(ClassType.Hastarge);
}

TEST(classtype, classtype_set_AlowedArmors_Druid) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.name = "Druid";
    ClassType.set_AlowedArmors(config, ClassType.name);
    EXPECT_TRUE(ClassType.HasLightArmor);
    EXPECT_TRUE(ClassType.HasMidArmor);
    EXPECT_FALSE(ClassType.HasHeavyArmor);
    EXPECT_TRUE(ClassType.HasShild);
    EXPECT_FALSE(ClassType.Hastarge);
}

TEST(classtype, classtype_set_AlowedArmors_Rogue) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.name = "Rogue";
    ClassType.set_AlowedArmors(config, ClassType.name);
    EXPECT_TRUE(ClassType.HasLightArmor);
    EXPECT_FALSE(ClassType.HasMidArmor);
    EXPECT_FALSE(ClassType.HasHeavyArmor);
    EXPECT_FALSE(ClassType.HasShild);
    EXPECT_FALSE(ClassType.Hastarge);
}

TEST(classtype, classtype_set_AlowedArmors_Fighter) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.name = "Fighter";
    ClassType.set_AlowedArmors(config, ClassType.name);
    EXPECT_TRUE(ClassType.HasLightArmor);
    EXPECT_TRUE(ClassType.HasMidArmor);
    EXPECT_TRUE(ClassType.HasHeavyArmor);
    EXPECT_TRUE(ClassType.HasShild);
    EXPECT_TRUE(ClassType.Hastarge);
}

TEST(classtype, classtype_set_AlowedArmors_Paladin) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.name = "Paladin";
    ClassType.set_AlowedArmors(config, ClassType.name);
    EXPECT_TRUE(ClassType.HasLightArmor);
    EXPECT_TRUE(ClassType.HasMidArmor);
    EXPECT_TRUE(ClassType.HasHeavyArmor);
    EXPECT_TRUE(ClassType.HasShild);
    EXPECT_TRUE(ClassType.Hastarge);
}

TEST(classtype, classtype_set_AlowedArmors_Overwrite) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");

    ClassType.name = "Barbarian";
    ClassType.set_AlowedArmors(config, ClassType.name);
    EXPECT_TRUE(ClassType.HasHeavyArmor);

    ClassType.name = "Wizard";
    ClassType.set_AlowedArmors(config, ClassType.name);
    EXPECT_FALSE(ClassType.HasLightArmor);
    EXPECT_FALSE(ClassType.HasMidArmor);
    EXPECT_FALSE(ClassType.HasHeavyArmor);
    EXPECT_FALSE(ClassType.HasShild);
    EXPECT_FALSE(ClassType.Hastarge);
}

//classtype_set_AlowedWeapon

TEST(classtype, classtype_set_AlowedWeapon_NONod) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    ClassType.name = "Bard";
    YAML::Node config;
    try {
        ClassType.set_AlowedWeapon(config);
        FAIL() << "Expectede runtime error";
    }
    catch (std::runtime_error& e) {
        EXPECT_STREQ("YAML File Error" , e.what());
    }
}

TEST(classtype, classtype_set_AlowedWeapon_Nodbad) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/conf_Armor_test.yaml");
    ClassType.name = "Bard";
    try {
        ClassType.set_AlowedWeapon(config);
        FAIL() << "Expectede runtime error";
    }
    catch (std::runtime_error& e) {
        EXPECT_STREQ("YAML File Error" , e.what());
    }
}

TEST(classtype, classtype_set_AlowedWeapon_EmtyNod) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/empty.yaml");
    ClassType.name = "Bard";
    try {
        ClassType.set_AlowedWeapon(config);
        FAIL() << "Expectede runtime error";
    }
    catch (std::runtime_error& e) {
        EXPECT_STREQ("YAML File Error" , e.what());
    }
}

TEST(classtype, classtype_set_AlowedWeapon_GoodNod) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.name = "Bard";
    ClassType.set_AlowedWeapon(config);
    EXPECT_TRUE(ClassType.Hassimple_light);
    EXPECT_TRUE(ClassType.Hassimple_one_handed);
    EXPECT_TRUE(ClassType.Hassimple_two_handed);
    EXPECT_TRUE(ClassType.Hassimple_ranged);
    EXPECT_FALSE(ClassType.Hasmartial_light);
    EXPECT_FALSE(ClassType.Hasmartial_one_handed);
    EXPECT_FALSE(ClassType.Hasmartial_two_handed);
    EXPECT_FALSE(ClassType.Hasmartial_ranged);
    EXPECT_FALSE(ClassType.Hasexotic_light);
    EXPECT_FALSE(ClassType.Hasexotic_one_handed);
    EXPECT_FALSE(ClassType.Hasexotic_two_handed);
    EXPECT_FALSE(ClassType.Hasexotic_ranged);
}

//set_HPdice

TEST(classtype , classtype_set_HPdice_NoNode) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config;
    try {
        ClassType.set_HPdice(config);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("YAML File Error",e.what());
    }
}

TEST(classtype , classtype_set_HPdice_emptyNode) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/empty.yaml");
    try {
        ClassType.set_HPdice(config);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("YAML File Error",e.what());
    }
}

TEST(classtype , classtype_set_HPdice_BadNode) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/conf_Armor_test.yaml");
    try {
        ClassType.set_HPdice(config);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("YAML File Error",e.what());
    }
}

TEST(classtype , classtype_set_HPdice_GoodNode) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    ClassType.name = "Bard";
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.set_HPdice(config);
    EXPECT_EQ(6 , ClassType.HPdice);
}

//set_usualLastname

TEST(classtype , classtype_set_usualLastname_NoNode) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    ClassType.name = "Bard";
    YAML::Node config;
    try {
        ClassType.set_usualLastname(config , ClassType.name);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("YAML File Error" , e.what());
    }
}

TEST(classtype , classtype_set_usualLastname_EmptyNode) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    ClassType.name = "Bard";
    YAML::Node config = YAML::LoadFile("conf/test/empty.yaml");
    try {
        ClassType.set_usualLastname(config , ClassType.name);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("YAML File Error" , e.what());
    }
}

TEST(classtype , classtype_set_usualLastname_BadNode) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    ClassType.name = "Bard";
    YAML::Node config = YAML::LoadFile("conf/test/conf_Armor_test.yaml");
    try {
        ClassType.set_usualLastname(config , ClassType.name);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("YAML File Error" , e.what());
    }
}

TEST(classtype , classtype_set_usualLastname_GoodNode_and_GoodClassName) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    ClassType.name = "Bard";
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.set_usualLastname(config , ClassType.name);
    EXPECT_GT(ClassType.usualLastNames.size() , 0);
}

TEST(classtype , classtype_set_usualLastname_NoClassName) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    try {
        ClassType.set_usualLastname(config , ClassType.name);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("ClassType Name Error",e.what());
    }
}

TEST(classtype , classtype_set_usualLastname_EmptyClassName) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    ClassType.name = "";
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    try {
        ClassType.set_usualLastname(config , ClassType.name);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("ClassType Name Error",e.what());
    }
}

TEST(classtype , classtype_set_usualLastname_BadClassName) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    ClassType.name = "None Existance";
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    try {
        ClassType.set_usualLastname(config , ClassType.name);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("ClassType Name Error",e.what());
    }
}

//Set_ClassType_Stats

TEST(classtype , classtype_Set_ClassType_Stats_NoNode) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    ClassType.name = "Bard";
    YAML::Node config;
    try {
        ClassType.Set_ClassType_Stats(config);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("YAML File Error", e.what());
    }
}

TEST(classtype , classtype_Set_ClassType_Stats_EmptyNode) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    ClassType.name = "Bard";
    YAML::Node config = YAML::LoadFile("conf/test/empty.yaml");
    try {
        ClassType.Set_ClassType_Stats(config);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("YAML File Error", e.what());
    }
}

TEST(classtype , classtype_Set_ClassType_Stats_BadNode) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    ClassType.name = "Bard";
    YAML::Node config = YAML::LoadFile("conf/test/conf_Armor_test.yaml");
    try {
        ClassType.Set_ClassType_Stats(config);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("YAML File Error", e.what());
    }
}

TEST(classtype , classtype_Set_ClassType_Stats_GoodNode) {
    DND_GM_Helper_N::NPC_N::ClassType ClassType;
    ClassType.name = "Bard";
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    ClassType.Set_ClassType_Stats(config);
    EXPECT_GT(ClassType.usualLastNames.size() , 0);
    EXPECT_TRUE(ClassType.Hassimple_light);
    EXPECT_TRUE(ClassType.Hassimple_one_handed);
    EXPECT_TRUE(ClassType.Hassimple_two_handed);
    EXPECT_TRUE(ClassType.Hassimple_ranged);
    EXPECT_FALSE(ClassType.Hasmartial_light);
    EXPECT_FALSE(ClassType.Hasmartial_one_handed);
    EXPECT_FALSE(ClassType.Hasmartial_two_handed);
    EXPECT_FALSE(ClassType.Hasmartial_ranged);
    EXPECT_FALSE(ClassType.Hasexotic_light);
    EXPECT_FALSE(ClassType.Hasexotic_one_handed);
    EXPECT_FALSE(ClassType.Hasexotic_two_handed);
    EXPECT_FALSE(ClassType.Hasexotic_ranged);
    EXPECT_TRUE(ClassType.HasLightArmor);
    EXPECT_FALSE(ClassType.HasMidArmor);
    EXPECT_FALSE(ClassType.HasHeavyArmor);
    EXPECT_TRUE(ClassType.HasShild);
    EXPECT_FALSE(ClassType.Hastarge);
    EXPECT_EQ(6 , ClassType.HPdice);
}
