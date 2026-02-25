#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <yaml-cpp/yaml.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class DND_GM_Helper;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    YAML::Node config;
private slots:
    void on_Racetxtin_editingFinished();
    void on_pushButton_clicked();
    void on_butPrintNPCinfo_clicked();
    void on_Classtxtin_editingFinished();
    void on_pushButton_2_clicked();
    void on_Nametxtin_editingFinished();
    void on_pushButton_3_clicked();
    void on_LastNametxtin_editingFinished();
    void on_pushButton_4_clicked();
    void on_butMale_clicked();
    void on_pushButton_6_clicked();
    void on_butnonbinary_clicked();
    void on_Sexetxtin_editingFinished();
    void on_Sizetxtin_editingFinished();
    void on_butRandsize_clicked();
    void on_agetxtin_editingFinished();
    void on_pushButton_5_clicked();
    void on_butCOmandlinemode_clicked();
    void on_leveltxtin_editingFinished();
    void on_xptxtin_editingFinished();
    void on_butrandlevel_clicked();
    void on_butRandXP_clicked();
    void on_HPtxtin_editingFinished();
    void on_butCalculatehp_clicked();
    void on_ddAlimetin_activated(int index);
    void on_pushButton_7_clicked();
    void on_ddDivinity_activated(int index);  // NEW

    void on_butRandDivinity_clicked();

    void on_butDivinitybyaliment_clicked();

private:
    Ui::DND_GM_Helper *ui;
};
#endif // WIDGET_H
