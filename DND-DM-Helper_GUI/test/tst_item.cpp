#include "../include/Inventory/item.h"
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

using namespace testing;
using namespace DND_GM_Helper_N::Inventory_N;

TEST(Item, Item_ItemGoodConfig)
{
    Item Item("Test Name" , "Test Description\nNew Line", 30 , 20);
    EXPECT_EQ("Test Name" , Item.name);
    EXPECT_EQ("Test Description\nNew Line" , Item.description);
    EXPECT_EQ(30 , Item.Prix);
    EXPECT_EQ(20 , Item.Poids);
}
