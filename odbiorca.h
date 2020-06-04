#ifndef ODBIORCA_H
#define ODBIORCA_H

#include <QWidget>
#include <QMessageBox>
#include <sstream>
#include "file.h"

namespace Ui {
class Odbiorca;
}

class Odbiorca : public QWidget
{
    Q_OBJECT

public:
    explicit Odbiorca(QWidget *parent = 0);
    ~Odbiorca();

    Ui::Odbiorca* const& getMainUi();

    void setOdbiorcaFields(const QString& o1, const QString& o2, const QString& o3,
                           const QString& o4, const QString& o5, const QString& o6);

private slots:
    void on_lineEdit_1_textEdited();
    void on_lineEdit_2_textEdited();
    void on_lineEdit_3_textEdited();
    void on_lineEdit_4_textEdited();
    void on_lineEdit_5_textEdited();
    void on_lineEdit_6_textEdited();

    void on_pushButton_0_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void closeEvent(QCloseEvent* event);

    void on_comboBox_0_activated(int index);

private:
    Ui::Odbiorca *ui;

    bool activeTmpNew;
    bool fieldsChanged;
    bool saveCancelled;

    void clearFields();

    void loadComboBox_0();
    void saveComboBox_0();

    void remComp(const int& indexToDel);
    void addComp(const QString& toAdd);

    QLinearGradient grad1;
    QPalette palette1;
};

extern Odbiorca* odbiorcaPtr;

#endif // ODBIORCA_H
