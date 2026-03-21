#ifndef MAINMENU_H
#define MAINMENU_H

#include <QToolBox>

namespace Ui {
class MainMenu;
}

class MainMenu : public QToolBox
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:

    void on_butNPCCreatorin_clicked();

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H
