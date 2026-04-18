#include "../include/Export/pdfexporter.h"
#include <QtPrintSupport/QPrinter>
#include <QPrinter>
#include <QTextDocument>
#include <QFileInfo>
#include <QFileDialog>
#include <QDir>

namespace DND_GM_Helper_N {
namespace Export_N {

PdfExporter::PdfExporter() {}

bool PdfExporter::exportNpcToPdf(const DND_GM_Helper_N::NPC_N::NPC& npc, const QString& filePath)
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    printer.setPageSize(QPageSize::A4);
    printer.setPageMargins(QMarginsF(10, 10, 10, 10), QPageLayout::Millimeter);

    // Helper lambda for stat bonus display
    auto bonus = [](int b) -> QString {
        return (b >= 0) ? QString("+%1").arg(b) : QString::number(b);
    };

    // Build item rows
    QString itemRows = "";
    if (npc.itemVector.empty()) {
        itemRows = "<tr><td colspan='5' style='color:#888;font-style:italic;padding:4px;'>No items</td></tr>";
    } else {
        for (int i = 0; i < (int)npc.itemVector.size(); i++) {
            QString bg = (i % 2 == 0) ? "#f5ecd7" : "#fdf6e3";
            itemRows += QString("<tr style=\"background:%1;\">"
                                "<td>%2</td><td>%3</td>"
                                "<td style='color:#555;font-size:9px;'>%4</td>"
                                "<td align='right'>%5 gp</td>"
                                "<td align='right'>%6 g</td></tr>")
                            .arg(bg)
                            .arg(i + 1)
                            .arg(QString::fromStdString(npc.itemVector[i]->name))
                            .arg(QString::fromStdString(npc.itemVector[i]->description))
                            .arg(npc.itemVector[i]->Prix)
                            .arg(npc.itemVector[i]->Poids);
        }
    }

    // Calculate total inventory weight (items + armor + weapons)
    int totalPoids = 0;
    for (int i = 0; i < (int)npc.itemVector.size(); i++) {
        totalPoids += npc.itemVector[i]->Poids;
    }
    totalPoids += npc.Armor.Poids;
    totalPoids += npc.Shield.Poids;
    totalPoids += npc.Weapon1.Poids;
    totalPoids += npc.Weapon2.Poids;
    totalPoids += npc.Weapon3.Poids;
    totalPoids += npc.Weapon4.Poids;
    totalPoids += npc.Weapon5.Poids;

    // Build weapon rows — only non-empty weapons, with damage dice
    struct WeaponRef {
        const DND_GM_Helper_N::Inventory_N::Weapon* w;
    };
    std::vector<WeaponRef> weapons = {
        {&npc.Weapon1}, {&npc.Weapon2}, {&npc.Weapon3},
        {&npc.Weapon4}, {&npc.Weapon5}
    };
    QString weaponRows = "";
    int wi = 0;
    for (const auto& wr : weapons) {
        if (wr.w->Name.empty()) continue;
        QString bg = (wi % 2 == 0) ? "#fdf6e3" : "#f5ecd7";
        QString dice = QString("%1d%2")
                           .arg(wr.w->Attack.Num_of_Dice)
                           .arg(wr.w->Attack.Dice_Value);
        weaponRows += QString("<tr style=\"background:%1;\">"
                              "<td>%2</td>"
                              "<td style='font-size:10px;color:#555;'>%3</td>"
                              "<td align='center'><b>%4</b></td>"
                              "</tr>")
                          .arg(bg)
                          .arg(QString::fromStdString(wr.w->Name))
                          .arg(QString::fromStdString(wr.w->Type))
                          .arg(dice);
        wi++;
    }
    if (weaponRows.isEmpty()) {
        weaponRows = "<tr><td colspan='3' style='color:#888;font-style:italic;padding:4px;'>No weapons</td></tr>";
    }

    // Build HP checkboxes — one per HP point, max 50
    QString hpBoxes = "";
    int maxBoxes = qMin(npc.HP, 50);
    for (int i = 0; i < maxBoxes; i++) {
        hpBoxes += "&#9744; ";
        if ((i + 1) % 10 == 0) hpBoxes += "<br/>";
    }
    if (npc.HP > 50) {
        hpBoxes += QString("<span style='font-size:9px;color:#888;'>... +%1 more</span>")
                       .arg(npc.HP - 50);
    }

    QString html = QString(R"(
<html>
<body style="font-family: 'Georgia', serif; background-color: #fdf6e3; color: #1a0a00; margin:0; padding:0;">

<!-- TITLE BANNER -->
<table width="100%" cellpadding="4" cellspacing="0"
       style="background:#7b2d00; border:2px solid #3b1500; margin-bottom:6px;">
    <tr>
        <td align="center" style="color:#f5e6c8; font-size:20px; font-weight:bold; letter-spacing:2px;">
            &#9876; D&amp;D 3.5 &mdash; NPC SHEET &#9876;
        </td>
    </tr>
</table>

<!-- NAME BAR -->
<table width="100%" cellpadding="4" cellspacing="0"
       style="background:#f5ecd7; border:2px solid #7b2d00; margin-bottom:6px;">
    <tr>
        <td style="font-size:18px; font-weight:bold; color:#7b2d00;">%1 %2</td>
        <td align="right" style="font-size:8px; color:#555;">
            <b>Race:</b> %3 &nbsp;|&nbsp; <b>Class:</b> %4 &nbsp;|&nbsp;
            <b>Alignment:</b> %14 &nbsp;|&nbsp; <b>Deity:</b> %15
        </td>
    </tr>
</table>

<!-- ROW 1: BASIC INFO + ABILITY SCORES -->
<table width="100%" cellpadding="0" cellspacing="6" style="margin-bottom:6px;">
<tr valign="top">

    <!-- LEFT: Basic Info -->
    <td width="48%">
        <table width="100%" cellpadding="4" cellspacing="0"
               style="border:2px solid #7b2d00; background:#fdf6e3;">
            <tr style="background:#7b2d00;">
                <td colspan="4" style="color:#f5e6c8; font-weight:bold; font-size:11px;
                    letter-spacing:1px; padding:3px 6px;">CHARACTER INFO</td>
            </tr>
            <tr style="background:#f5ecd7;">
                <td width="30%"><b>Sex</b></td><td>%5</td>
                <td width="30%"><b>Age</b></td><td>%6</td>
            </tr>
            <tr>
                <td><b>Size</b></td><td>%11</td>
                <td><b>Category</b></td><td>%12</td>
            </tr>
            <tr style="background:#f5ecd7;">
                <td><b>Level</b></td><td>%7</td>
                <td><b>XP</b></td><td>%8</td>
            </tr>
            <tr>
                <td><b>Max HP</b></td><td>%9</td>
                <td><b>AC</b></td><td>%10</td>
            </tr>
            <tr style="background:#f5ecd7;">
                <td><b>Natural Armor</b></td><td>%13</td>
                <td></td><td></td>
            </tr>
        </table>
    </td>

    <td width="4%"></td>

    <!-- RIGHT: Ability Scores -->
    <td width="48%">
        <table width="100%" cellpadding="4" cellspacing="0"
               style="border:2px solid #7b2d00; background:#fdf6e3;">
            <tr style="background:#7b2d00;">
                <td colspan="3" style="color:#f5e6c8; font-weight:bold; font-size:11px;
                    letter-spacing:1px; padding:3px 6px;">ABILITY SCORES</td>
            </tr>
            <tr style="background:#f5ecd7; text-align:center;">
                <td><b>Ability</b></td><td><b>Score</b></td><td><b>Modifier</b></td>
            </tr>
            <tr style="text-align:center;">
                <td><b>STR</b></td><td>%16</td><td>%17</td>
            </tr>
            <tr style="background:#f5ecd7; text-align:center;">
                <td><b>DEX</b></td><td>%18</td><td>%19</td>
            </tr>
            <tr style="text-align:center;">
                <td><b>CON</b></td><td>%20</td><td>%21</td>
            </tr>
            <tr style="background:#f5ecd7; text-align:center;">
                <td><b>INT</b></td><td>%22</td><td>%23</td>
            </tr>
            <tr style="text-align:center;">
                <td><b>WIS</b></td><td>%24</td><td>%25</td>
            </tr>
            <tr style="background:#f5ecd7; text-align:center;">
                <td><b>CHA</b></td><td>%26</td><td>%27</td>
            </tr>
        </table>
    </td>

</tr>
</table>

<!-- HP TRACKING -->
<table width="100%" cellpadding="4" cellspacing="0"
       style="border:2px solid #7b2d00; background:#fdf6e3; margin-bottom:6px;">
    <tr style="background:#7b2d00;">
        <td colspan="2" style="color:#f5e6c8; font-weight:bold; font-size:11px;
            letter-spacing:1px; padding:3px 6px;">HIT POINT TRACKING</td>
    </tr>
    <tr valign="top">
        <td width="35%" style="padding:6px;">
            <table width="100%" cellpadding="6" cellspacing="0"
                   style="border:1px solid #c9a96e; text-align:center;">
                <tr style="background:#f5ecd7;">
                    <td><b>Max HP</b></td>
                    <td><b>Current HP</b></td>
                    <td><b>Temp HP</b></td>
                </tr>
                <tr style="font-size:15px;">
                    <td><b>%9</b></td>
                    <td style="border-bottom:2px solid #7b2d00;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
                    <td style="border-bottom:2px solid #7b2d00;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
                </tr>
            </table>
        </td>
        <td style="padding:6px; font-size:11px; line-height:1.8;">
            <b style="font-size:10px;">Damage taken (tick one box per point of damage):</b><br/>
            %28
        </td>
    </tr>
</table>

<!-- ROW 2: ARMOR + WEAPONS -->
<table width="100%" cellpadding="0" cellspacing="6" style="margin-bottom:6px;">
<tr valign="top">

    <!-- LEFT: Armor & Shield -->
    <td width="48%">
        <table width="100%" cellpadding="4" cellspacing="0"
               style="border:2px solid #7b2d00; background:#fdf6e3;">
            <tr style="background:#7b2d00;">
                <td colspan="3" style="color:#f5e6c8; font-weight:bold; font-size:11px;
                    letter-spacing:1px; padding:3px 6px;">ARMOR &amp; SHIELD</td>
            </tr>
            <tr style="background:#f5ecd7; font-size:10px;">
                <td><b>Slot</b></td><td><b>Name</b></td><td><b>Protection</b></td>
            </tr>
            <tr>
                <td><b>Armor</b></td>
                <td>%29<br/><span style="font-size:9px;color:#555;">%32 | Max Dex Bonus: %31</span></td>
                <td align="center">%30</td>
            </tr>
            <tr style="background:#f5ecd7;">
                <td><b>Shield</b></td>
                <td>%33<br/><span style="font-size:9px;color:#555;">%35</span></td>
                <td align="center">%34</td>
            </tr>
        </table>
    </td>

    <td width="4%"></td>

    <!-- RIGHT: Weapons -->
    <td width="48%">
        <table width="100%" cellpadding="4" cellspacing="0"
               style="border:2px solid #7b2d00; background:#fdf6e3;">
            <tr style="background:#7b2d00;">
                <td colspan="3" style="color:#f5e6c8; font-weight:bold; font-size:11px;
                    letter-spacing:1px; padding:3px 6px;">WEAPONS</td>
            </tr>
            <tr style="background:#f5ecd7; font-size:10px;">
                <td><b>Name</b></td><td><b>Type</b></td><td align="center"><b>Damage</b></td>
            </tr>
            %36
        </table>
    </td>

</tr>
</table>

<!-- ITEMS -->
<table width="100%" cellpadding="4" cellspacing="0"
       style="border:2px solid #7b2d00; background:#fdf6e3; margin-bottom:6px;">
    <tr style="background:#7b2d00;">
        <td colspan="5" style="color:#f5e6c8; font-weight:bold; font-size:11px;
            letter-spacing:1px; padding:3px 6px;">INVENTORY</td>
    </tr>
    <tr style="background:#f5ecd7; font-size:10px;">
        <td width="5%"><b>#</b></td>
        <td width="25%"><b>Name</b></td>
        <td><b>Description</b></td>
        <td width="12%" align="right"><b>Value</b></td>
        <td width="12%" align="right"><b>Weight</b></td>
    </tr>
    %37
    <tr style="background:#7b2d00;">
        <td colspan="4" align="right"
            style="color:#f5e6c8; font-weight:bold; font-size:10px; padding:3px 6px;">
            TOTAL WEIGHT (items + armor + weapons):
        </td>
        <td align="right"
            style="color:#f5e6c8; font-weight:bold; font-size:10px; padding:3px 6px;">
            %38 g
        </td>
    </tr>
</table>

<!-- FOOTER -->
<table width="100%" cellpadding="2" cellspacing="0" style="margin-top:6px;">
    <tr>
        <td align="center" style="font-size:8px; color:#999; border-top:1px solid #c9a96e;">
            Generated by DND-DM-Helper &middot; D&amp;D 3.5e NPC Sheet
        </td>
    </tr>
</table>

</body></html>
    )")
                       .arg(QString::fromStdString(npc.name),                                         // %1
                            QString::fromStdString(npc.LastName),                                     // %2
                            QString::fromStdString(npc.race.name),                                    // %3
                            QString::fromStdString(npc.classtype.name))                               // %4
                       .arg(QString::fromStdString(npc.Sexe))                                         // %5
                       .arg(npc.Age)                                                                  // %6
                       .arg(npc.level)                                                                // %7
                       .arg(npc.XP)                                                                   // %8
                       .arg(npc.HP)                                                                   // %9
                       .arg(npc.CA)                                                                   // %10
                       .arg(npc.Size)                                                                 // %11
                       .arg(QString::fromStdString(npc.SizeCategory))                                 // %12
                       .arg(npc.Natural_Armor)                                                        // %13
                       .arg(QString::fromStdString(npc.alignment.alig1 + " " + npc.alignment.alig2)) // %14
                       .arg(QString::fromStdString(npc.divinity.name))                                // %15
                       .arg(npc.FOR).arg(bonus(npc.FOR_Bonus))                                        // %16 %17
                       .arg(npc.DEX).arg(bonus(npc.DEX_Bonus))                                        // %18 %19
                       .arg(npc.CON).arg(bonus(npc.CON_Bonus))                                        // %20 %21
                       .arg(npc.INT).arg(bonus(npc.INT_Bonus))                                        // %22 %23
                       .arg(npc.SAG).arg(bonus(npc.SAG_Bonus))                                        // %24 %25
                       .arg(npc.CHA).arg(bonus(npc.CHA_Bonus))                                        // %26 %27
                       .arg(hpBoxes)                                                                  // %28
                       .arg(QString::fromStdString(npc.Armor.Name))                                   // %29
                       .arg(npc.Armor.Prot)                                                           // %30
                       .arg(npc.Armor.MaxDEX_Bonus)                                                   // %31
                       .arg(QString::fromStdString(npc.Armor.Type))                                   // %32
                       .arg(QString::fromStdString(npc.Shield.Name))                                  // %33
                       .arg(npc.Shield.Prot)                                                          // %34
                       .arg(QString::fromStdString(npc.Shield.Type))                                  // %35
                       .arg(weaponRows)                                                               // %36
                       .arg(itemRows)                                                                 // %37
                       .arg(totalPoids);                                                              // %38

    QTextDocument doc;
    doc.setHtml(html);
    doc.setPageSize(printer.pageRect(QPrinter::Point).size());
    doc.print(&printer);

    return QFileInfo::exists(filePath);
}

} // Export_N
} // DND_GM_Helper_N
