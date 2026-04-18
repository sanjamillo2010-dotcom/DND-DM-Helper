#ifndef PDFEXPORTER_H
#define PDFEXPORTER_H

#include <QString>
#include "../include/NPC/NPC.h"

namespace DND_GM_Helper_N {
namespace Export_N {

class PdfExporter
{
public:
    PdfExporter();
    static bool exportNpcToPdf(const DND_GM_Helper_N::NPC_N::NPC& npc, const QString& filePath);
};

}//Export_N
}//DND_GM_Helper_N

#endif // PDFEXPORTER_H
