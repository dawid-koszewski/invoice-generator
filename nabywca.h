#ifndef NABYWCA_H
#define NABYWCA_H

#include <QWidget>
#include <QMessageBox>
#include <sstream>
#include "file.h"

namespace Ui {
class Nabywca;
}

class Nabywca : public QWidget
{
    Q_OBJECT

public:
    explicit Nabywca(QWidget *parent = 0);
    ~Nabywca();

    Ui::Nabywca* const& getMainUi();

    void setNabywcaFields(const QString& n1, const QString& n2, const QString& n3,
                          const QString& n4, const QString& n5, const QString& n6);

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
    Ui::Nabywca *ui;

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

extern Nabywca* nabywcaPtr;

#endif // NABYWCA_H
