#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

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

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
