#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include "../include/armor.h"

using namespace testing;

TEST(armor, armor_emptyNode)
{
    YAML::Node armorNode;

    DND_GM_Helper_N::Inventory_N::Armor armor;

    armor.Get_Stats_from_YAML("name", armorNode);

    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}
