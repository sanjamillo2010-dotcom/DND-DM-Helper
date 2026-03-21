#include "mainmenu.h"
#include "widget.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent)
    : QToolBox(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_butNPCCreatorin_clicked()
{
    Widget *widget = new Widget();
    widget->show();
    this->close();
}
