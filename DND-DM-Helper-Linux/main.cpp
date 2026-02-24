#include "widget.h"
#include "NPC.h"

#include <QApplication>
#include <yaml-cpp/yaml.h>
NPC npc;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
