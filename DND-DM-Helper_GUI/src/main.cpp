#include "../include/NPC.h"
#include "../include/widget.h"

#include <QApplication>
#include <yaml-cpp/yaml.h>
DND_GM_Helper_N::NPC_N::NPC npc;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
