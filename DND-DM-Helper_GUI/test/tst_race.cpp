#include "../include/NPC/NPC.h"
#include "../include/NPC/Race.h"

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

using namespace testing;

//set_usualname

TEST(Race, Race_set_usualname_NoNode){
    DND_GM_Helper_N::NPC_N::Race Race;
    Race.name = "Elf";
    YAML::Node config;
    try {
        Race.set_usualname(config , Race.name);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("YAML File Error" , e.what());
    }
}

TEST(Race, Race_set_usualname_EmptyNode){
    DND_GM_Helper_N::NPC_N::Race Race;
    Race.name = "Elf";
    YAML::Node config = YAML::LoadFile("conf/test/conf_Armor_test.yaml");
    try {
        Race.set_usualname(config , Race.name);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("YAML File Error" , e.what());
    }
}

TEST(Race, Race_set_usualname_BadNode){
    DND_GM_Helper_N::NPC_N::Race Race;
    Race.name = "Elf";
    YAML::Node config = YAML::LoadFile("conf/test/empty.yaml");
    try {
        Race.set_usualname(config , Race.name);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("YAML File Error" , e.what());
    }
}

TEST(Race, Race_set_usualname_NoRaceName){
    DND_GM_Helper_N::NPC_N::Race Race;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    try {
        Race.set_usualname(config , Race.name);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("Race Name Error" , e.what());
    }
}

TEST(Race, Race_set_usualname_BadRaceName){
    DND_GM_Helper_N::NPC_N::Race Race;
    Race.name = "Bad Name";
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    try {
        Race.set_usualname(config , Race.name);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("Race Name Error" , e.what());
    }
}
TEST(Race, Race_set_usualname_GoodConfig){
    DND_GM_Helper_N::NPC_N::Race Race;
    Race.name = "Elf";
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    Race.set_usualname(config , Race.name);
    EXPECT_GT(Race.usualNames.size() , 0);
}

//GetRandomName

TEST(Race , Race_GetRandomName_NoUsualName) {
    DND_GM_Helper_N::NPC_N::NPC npc;
    npc.name = npc.race.GetRandomName();
    EXPECT_EQ("Unknown" , npc.name);
}

TEST(Race , Race_GetRandomName_GoodUsualName) {
    DND_GM_Helper_N::NPC_N::NPC npc;
    npc.race.name = "Elf";
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    npc.race.set_usualname(config , npc.race.name);
    npc.name = npc.race.GetRandomName();
    if (npc.name != "Unknown") {
        std::cout << npc.name << " != Unknown\n[  PASSED  ]" << std::endl;
        EXPECT_EQ(1,1);
    }
    else {
        FAIL();
    }
}

//Set_Race_Stats

TEST(race , race_Set_Race_Stats_NoNode) {
    DND_GM_Helper_N::NPC_N::NPC npc;
    npc.race.name = "Elf";
    YAML::Node config;
    try {
        npc.race.Set_Race_Stats(config);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("YAML File Error" , e.what());
    }
}

TEST(race , race_Set_Race_Stats_BadNode) {
    DND_GM_Helper_N::NPC_N::NPC npc;
    npc.race.name = "Elf";
    YAML::Node config = YAML::LoadFile("conf/test/conf_Armor_test.yaml");
    try {
        npc.race.Set_Race_Stats(config);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("YAML File Error" , e.what());
    }
}

TEST(race , race_Set_Race_Stats_EmptyNode) {
    DND_GM_Helper_N::NPC_N::NPC npc;
    npc.race.name = "Elf";
    YAML::Node config = YAML::LoadFile("conf/test/empty.yaml");
    try {
        npc.race.Set_Race_Stats(config);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("YAML File Error" , e.what());
    }
}

TEST(race , race_Set_Race_Stats_NoRaceName) {
    DND_GM_Helper_N::NPC_N::NPC npc;
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    try {
        npc.race.Set_Race_Stats(config);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("Race Name Error" , e.what());
    }
}

TEST(race , race_Set_Race_Stats_BadRaceName) {
    DND_GM_Helper_N::NPC_N::NPC npc;
    npc.race.name = "Bad RaceName";
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    try {
        npc.race.Set_Race_Stats(config);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("Race Name Error" , e.what());
    }
}

TEST(race , race_Set_Race_Stats_EmptyRaceName) {
    DND_GM_Helper_N::NPC_N::NPC npc;
    npc.race.name = "";
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    try {
        npc.race.Set_Race_Stats(config);
        FAIL();
    } catch (std::runtime_error e) {
        EXPECT_STREQ("Race Name Error" , e.what());
    }
}

TEST(race , race_Set_Race_Stats_GoodNode_and_GoodRaceName) {
    DND_GM_Helper_N::NPC_N::NPC npc;
    npc.race.name = "Elf";
    YAML::Node config = YAML::LoadFile("conf/test/Test_NPC_conf.yaml");
    npc.race.Set_Race_Stats(config);
    EXPECT_EQ(170 , npc.race.MaxSize);
    EXPECT_EQ(750 , npc.race.MaxAge);
}
