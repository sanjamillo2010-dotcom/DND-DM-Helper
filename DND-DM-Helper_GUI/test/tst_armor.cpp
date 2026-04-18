/*
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include "../include/armor.h"

using namespace testing;

TEST(armor, armor_emptyNode)
{


    YAML::Node armorNode;

    DND_GM_Helper_N::Inventory_N::Armor armor;

    try  {
        armor.Get_Stats_from_YAML("name", armorNode);
        FAIL();

    }catch (std::runtime_error e)
    {
        EXPECT_STREQ("Armor 'name' not found in YAML node.", e.what());
    }

    //ASSERT_THAT(0, Eq(0));
}


TEST(armor, armor_mainstream)
{

    YAML::Node config = YAML::LoadFile("conf/conf_Armor_test.yaml");

    DND_GM_Helper_N::Inventory_N::Armor armor;

    try  {
        armor.Get_Stats_from_YAML("quilted_armor", config);

    }catch (std::runtime_error e)
    {
        EXPECT_STREQ("", e.what());
        FAIL();
    }

    EXPECT_EQ(std::string("Quilted Armor"), armor.Name);
    //ASSERT_THAT(0, Eq(0));
}
*/
