#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "../include/NPC/NPC.h"

using namespace testing;
using namespace DND_GM_Helper_N::NPC_N;

// ─────────────────────────────────────────────
// XPFromLVL
// ─────────────────────────────────────────────

TEST(NPC_XPFromLVL, Level1Returns0) {
    NPC n;
    // Level 1 requires 0 XP — you start here
    EXPECT_EQ(n.XPFromLVL(1), 0);
}

TEST(NPC_XPFromLVL, Level2Returns1000) {
    NPC n;
    EXPECT_EQ(n.XPFromLVL(2), 1000);
}

TEST(NPC_XPFromLVL, Level3Returns3000) {
    NPC n;
    EXPECT_EQ(n.XPFromLVL(3), 3000);
}

TEST(NPC_XPFromLVL, Level4Returns6000) {
    NPC n;
    EXPECT_EQ(n.XPFromLVL(4), 6000);
}

TEST(NPC_XPFromLVL, Level20Returns190000) {
    NPC n;
    EXPECT_EQ(n.XPFromLVL(20), 190000);
}

// ─────────────────────────────────────────────
// LVLFromXP
// ─────────────────────────────────────────────

TEST(NPC_LVLFromXP, ZeroXPReturnsLevel1) {
    NPC n;
    EXPECT_EQ(n.LVLFromXP(0), 1);
}

TEST(NPC_LVLFromXP, NegativeXPReturnsLevel1) {
    NPC n;
    EXPECT_EQ(n.LVLFromXP(-500), 1);
}

TEST(NPC_LVLFromXP, ExactLevel2Threshold) {
    NPC n;
    EXPECT_EQ(n.LVLFromXP(999),  1);   // just below level 2
    EXPECT_EQ(n.LVLFromXP(1000), 2);   // exactly level 2 threshold
    EXPECT_EQ(n.LVLFromXP(2999), 2);   // just below level 3
    EXPECT_EQ(n.LVLFromXP(3000), 3);   // exactly level 3 threshold
}

TEST(NPC_LVLFromXP, MidRangeXP) {
    NPC n;
    // XP_TABLE: level 4 = 6000, level 10 = 45000, level 11 = 55000
    EXPECT_EQ(n.LVLFromXP(6000),  4);
    EXPECT_EQ(n.LVLFromXP(45000), 10);
    EXPECT_EQ(n.LVLFromXP(55000), 11);
}

TEST(NPC_LVLFromXP, MaxXPReturnsLevel20) {
    NPC n;
    EXPECT_EQ(n.LVLFromXP(190000), 20);
    EXPECT_EQ(n.LVLFromXP(999999), 20);
}

TEST(NPC_LVLFromXP, RoundTripConsistency) {
    NPC n;
    // Level 19 shares the 190000 threshold with level 20 in XP_TABLE,
    // so LVLFromXP(XPFromLVL(19)) returns 20. Test levels 1-18 and 20.
    for (int lvl = 1; lvl <= 18; ++lvl) {
        int xp = n.XPFromLVL(lvl);
        EXPECT_EQ(n.LVLFromXP(xp), lvl)
            << "Round-trip failed for level " << lvl;
    }
    EXPECT_EQ(n.LVLFromXP(n.XPFromLVL(20)), 20);
}

// ─────────────────────────────────────────────
// Calculat_Bonus
// ─────────────────────────────────────────────

TEST(NPC_CalculatBonus, FOR_10GivesBonus0) {
    NPC n;
    n.FOR = 10;
    n.Calculat_Bonus("FOR");
    EXPECT_EQ(n.FOR_Bonus, 0);
}

TEST(NPC_CalculatBonus, FOR_8GivesMinus1) {
    NPC n;
    n.FOR = 8;
    n.Calculat_Bonus("FOR");
    EXPECT_EQ(n.FOR_Bonus, -1);
}

TEST(NPC_CalculatBonus, DEX_14GivesPlus2) {
    NPC n;
    n.DEX = 14;
    n.Calculat_Bonus("DEX");
    EXPECT_EQ(n.DEX_Bonus, 2);
}

TEST(NPC_CalculatBonus, ALL_SetsAllBonuses) {
    NPC n;
    n.FOR = 10; n.DEX = 12; n.CON = 14;
    n.INT = 8;  n.SAG = 16; n.CHA = 18;
    n.Calculat_Bonus("ALL");
    EXPECT_EQ(n.FOR_Bonus,  0);
    EXPECT_EQ(n.DEX_Bonus,  1);
    EXPECT_EQ(n.CON_Bonus,  2);
    EXPECT_EQ(n.INT_Bonus, -1);
    EXPECT_EQ(n.SAG_Bonus,  3);
    EXPECT_EQ(n.CHA_Bonus,  4);
}

TEST(NPC_CalculatBonus, UnknownKeyDoesNothing) {
    NPC n;
    n.FOR_Bonus = 99;
    n.Calculat_Bonus("INVALID");
    EXPECT_EQ(n.FOR_Bonus, 99); // unchanged
}

// ─────────────────────────────────────────────
// SizeCategoryfromSize
// ─────────────────────────────────────────────

TEST(NPC_SizeCategory, TinyBoundary) {
    NPC n;
    n.Size = 1;  n.SizeCategoryfromSize(); EXPECT_EQ(n.SizeCategory, "Tiny");
    n.Size = 20; n.SizeCategoryfromSize(); EXPECT_EQ(n.SizeCategory, "Tiny");
}

TEST(NPC_SizeCategory, SmallBoundary) {
    NPC n;
    n.Size = 21;  n.SizeCategoryfromSize(); EXPECT_EQ(n.SizeCategory, "Small");
    n.Size = 100; n.SizeCategoryfromSize(); EXPECT_EQ(n.SizeCategory, "Small");
}

TEST(NPC_SizeCategory, MediumBoundary) {
    NPC n;
    n.Size = 101; n.SizeCategoryfromSize(); EXPECT_EQ(n.SizeCategory, "Medium");
    n.Size = 190; n.SizeCategoryfromSize(); EXPECT_EQ(n.SizeCategory, "Medium");
}

TEST(NPC_SizeCategory, LargeBoundary) {
    NPC n;
    n.Size = 191; n.SizeCategoryfromSize(); EXPECT_EQ(n.SizeCategory, "Large");
    n.Size = 320; n.SizeCategoryfromSize(); EXPECT_EQ(n.SizeCategory, "Large");
}

TEST(NPC_SizeCategory, HugeBoundary) {
    NPC n;
    n.Size = 321; n.SizeCategoryfromSize(); EXPECT_EQ(n.SizeCategory, "Huge");
    n.Size = 640; n.SizeCategoryfromSize(); EXPECT_EQ(n.SizeCategory, "Huge");
}

TEST(NPC_SizeCategory, GargantuanBoundary) {
    NPC n;
    n.Size = 641;   n.SizeCategoryfromSize(); EXPECT_EQ(n.SizeCategory, "Gargantuan");
    n.Size = 99999; n.SizeCategoryfromSize(); EXPECT_EQ(n.SizeCategory, "Gargantuan");
}

// ─────────────────────────────────────────────
// Calculat_CA
// ─────────────────────────────────────────────

TEST(NPC_CalculatCA, BaseACNoModifiers) {
    NPC n;
    n.DEX_Bonus    = 0;
    n.SizeCategory = "Medium";
    n.Natural_Armor = 0;
    n.Armor.Prot   = 0;
    n.Shield.Prot  = 0;
    EXPECT_EQ(n.Calculat_CA(), 10);
}

TEST(NPC_CalculatCA, DEXBonusApplied) {
    NPC n;
    n.DEX_Bonus    = 3;
    n.SizeCategory = "Medium";
    n.Natural_Armor = 0;
    n.Armor.Prot   = 0;
    n.Shield.Prot  = 0;
    EXPECT_EQ(n.Calculat_CA(), 13);
}

TEST(NPC_CalculatCA, TinySizeBonus) {
    NPC n;
    n.DEX_Bonus    = 0;
    n.SizeCategory = "Tiny";
    n.Natural_Armor = 0;
    n.Armor.Prot   = 0;
    n.Shield.Prot  = 0;
    EXPECT_EQ(n.Calculat_CA(), 12); // 10 + 2
}

TEST(NPC_CalculatCA, LargeSizePenalty) {
    NPC n;
    n.DEX_Bonus    = 0;
    n.SizeCategory = "Large";
    n.Natural_Armor = 0;
    n.Armor.Prot   = 0;
    n.Shield.Prot  = 0;
    EXPECT_EQ(n.Calculat_CA(), 9); // 10 - 1
}

TEST(NPC_CalculatCA, HugeSizePenalty) {
    NPC n;
    n.DEX_Bonus    = 0;
    n.SizeCategory = "Huge";
    n.Natural_Armor = 0;
    n.Armor.Prot   = 0;
    n.Shield.Prot  = 0;
    EXPECT_EQ(n.Calculat_CA(), 8); // 10 - 2
}

TEST(NPC_CalculatCA, AllBonusesCombined) {
    NPC n;
    n.DEX_Bonus     = 2;
    n.SizeCategory  = "Small";  // +1
    n.Natural_Armor = 3;
    n.Armor.Prot    = 4;
    n.Shield.Prot   = 2;
    // 10 + 2 + 1 + 3 + 4 + 2 = 22
    EXPECT_EQ(n.Calculat_CA(), 22);
}

// ─────────────────────────────────────────────
// Reset_All_Stats
// ─────────────────────────────────────────────

TEST(NPC_ResetAllStats, ResetsToDefaults) {
    NPC n;
    n.name      = "Aragorn";
    n.FOR       = 18;
    n.level     = 15;
    n.HP        = 200;
    n.CA        = 25;
    n.Reset_All_Stats();

    EXPECT_EQ(n.name,      "");
    EXPECT_EQ(n.LastName,  "");
    EXPECT_EQ(n.FOR,       3);
    EXPECT_EQ(n.DEX,       3);
    EXPECT_EQ(n.CON,       3);
    EXPECT_EQ(n.INT,       3);
    EXPECT_EQ(n.SAG,       3);
    EXPECT_EQ(n.CHA,       3);
    EXPECT_EQ(n.FOR_Bonus, 0);
    EXPECT_EQ(n.level,     1);
    EXPECT_EQ(n.XP,        0);
    EXPECT_EQ(n.HP,        0);
    EXPECT_EQ(n.CA,        10);
    EXPECT_EQ(n.Natural_Armor, 0);
    EXPECT_EQ(n.SizeCategory,  "");
    EXPECT_EQ(n.alignment.alig1, "");
    EXPECT_EQ(n.alignment.alig2, "");
}

// ─────────────────────────────────────────────
// Calculate_Carecteristics  (statistical sanity)
// ─────────────────────────────────────────────

TEST(NPC_CalculateCaracteristics, ResultInRange) {
    NPC n;
    for (int i = 0; i < 1000; ++i) {
        int result = n.Calculate_Carecteristics();
        // Drop lowest of 4d6 → min = 3 (1+1+1), max = 18 (6+6+6)
        EXPECT_GE(result, 3)  << "Roll below minimum on iteration " << i;
        EXPECT_LE(result, 18) << "Roll above maximum on iteration " << i;
    }
}
