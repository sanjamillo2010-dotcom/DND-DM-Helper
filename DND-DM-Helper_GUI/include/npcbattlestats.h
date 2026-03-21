#ifndef NPCBATTLESTATS_H
#define NPCBATTLESTATS_H

#include <QWidget>

namespace Ui {
class NPCbattlestats;
}

class NPCbattlestats : public QWidget
{
    Q_OBJECT

public:
    explicit NPCbattlestats(QWidget *parent = nullptr);
    ~NPCbattlestats();

private slots:
    void on_txtStrin_textChanged(const QString &arg1);

    void on_butBackin_clicked();

    void on_txtDexin_textChanged(const QString &arg1);

    void on_TxtConin_textChanged(const QString &arg1);

    void on_txtIntin_textChanged(const QString &arg1);

    void on_txtWisin_textChanged(const QString &arg1);

    void on_txtChain_textChanged(const QString &arg1);

    void on_butbonusin_clicked();

    void on_butaddstrin_clicked();

    void on_butsubstrin_clicked();

    void on_butadddexin_clicked();

    void on_butsubdexin_clicked();

    void on_butaddconin_clicked();

    void on_butsubconin_clicked();

    void on_butaddintin_clicked();

    void on_butsubintin_clicked();

    void on_butaddwisin_clicked();

    void on_butsubwisin_clicked();

    void on_butaddchain_clicked();

    void on_butsubchain_clicked();

    void on_butRandabilityin_clicked();


    void on_txtcain_textChanged(const QString &arg1);

    void on_butsubACin_clicked();

    void on_butaddACin_clicked();

    void on_butrandcain_clicked();

    void on_butCalCAin_clicked();

    void on_butResetallstatsin_clicked();

    void on_txtNAin_textChanged(const QString &arg1);

    void on_butsubNAin_clicked();

    void on_butaddNAin_clicked();

    void on_butrandNAin_clicked();

    void on_DDArmorin_activated(int index);

    void on_DDShieldin_activated(int index);

    void on_ddWeapons1_activated(int index);

    void on_ddWeapons2_activated(int index);

    void on_ddWeapons3_activated(int index);

    void on_ddWeapons4_activated(int index);

    void on_ddWeapons5_activated(int index);

private:
    Ui::NPCbattlestats *ui;
};

#endif // NPCBATTLESTATS_H
