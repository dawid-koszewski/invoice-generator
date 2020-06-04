#ifndef USTAWIENIA_H
#define USTAWIENIA_H

#include <QWidget>
#include <QMessageBox>
#include <sstream>
#include "file.h"

namespace Ui {
class Ustawienia;
}

class Ustawienia : public QWidget
{
    Q_OBJECT

public:
    explicit Ustawienia(QWidget *parent = 0);
    ~Ustawienia();

    Ui::Ustawienia* const& getMainUi();

    void setUstawieniaFields(const QString& u2, const QString& u3, const QString& u4, const QString& u5,
                             const QString& u6, const QString& u7, const int& u11, const QString& u12);

private slots:
    void on_pushButton_12_clicked();

    void on_lineEdit_2_textEdited();
    void on_lineEdit_3_textEdited();
    void on_lineEdit_4_textEdited();
    void on_lineEdit_5_textEdited();
    void on_lineEdit_6_textEdited();
    void on_lineEdit_7_textEdited();
    void on_lineEdit_11a_3_textEdited();

    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void closeEvent(QCloseEvent* event);

    void on_radioButton_11a_1_clicked();
    void on_radioButton_11a_2_clicked();
    void on_radioButton_11a_3_clicked();

private:
    Ui::Ustawienia *ui;

    bool fieldsChanged;
    int typDok;

    void clearCheckBoxes();

    QLinearGradient grad1;
    QPalette palette1;
};

extern Ustawienia* ustawieniaPtr;

#endif // USTAWIENIA_H
