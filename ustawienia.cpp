#include "ustawienia.h"
#include "ui_ustawienia.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


Ustawienia::Ustawienia(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ustawienia)
{
    ui->setupUi(this);

    fieldsChanged =false;
    typDok =0;

    grad1.setStart(0, 0);
    grad1.setFinalStop(0, ui->scrollAreaWidgetContents->height());
    grad1.setColorAt(0, QColor(240,180,180));
    grad1.setColorAt(1, QColor(240,215,215));
    palette1.setBrush(QPalette::Window, grad1);
    ui->scrollArea->setPalette(palette1);
}

Ustawienia::~Ustawienia()
{
    delete ui;
}


Ui::Ustawienia* const& Ustawienia::getMainUi()
{
    return ui;
}


void Ustawienia::setUstawieniaFields(const QString& u2, const QString& u3, const QString& u4, const QString& u5,
                                     const QString& u6, const QString& u7, const int& u11, const QString& u12)
{
    ui->lineEdit_2->setText(u2);
    ui->lineEdit_3->setText(u3);
    ui->lineEdit_4->setText(u4);
    ui->lineEdit_5->setText(u5);
    ui->lineEdit_6->setText(u6);
    ui->lineEdit_7->setText(u7);
    typDok =u11;
    ui->lineEdit_11a_3->setText(u12);

    if (typDok==0) ui->radioButton_11a_1->setChecked(true);
    if (typDok==1) ui->radioButton_11a_2->setChecked(true);
    if (typDok==2) ui->radioButton_11a_3->setChecked(true);
}

//=============================================================================================
//=============================================================================================

void Ustawienia::clearCheckBoxes()
{
    ui->checkBox_0->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_11b->setChecked(false);
    ui->checkBox_15a->setChecked(false);
    ui->checkBox_15b->setChecked(false);
}


void Ustawienia::on_pushButton_12_clicked()
{
    if (ui->checkBox_0->isChecked()) mainWindowPtr->getMainUi()->comboBox_0->clear();
    if (ui->checkBox_3->isChecked()) mainWindowPtr->getMainUi()->comboBox_3->clear();
    if (ui->checkBox_11b->isChecked()) mainWindowPtr->getMainUi()->comboBox_11b->clear();
    if (ui->checkBox_15a->isChecked()) mainWindowPtr->getMainUi()->comboBox_15a->clear();
    if (ui->checkBox_15b->isChecked()) mainWindowPtr->getMainUi()->comboBox_15b->clear();
    clearCheckBoxes();
}


void Ustawienia::on_lineEdit_2_textEdited()
{
    if (fieldsChanged==false) fieldsChanged =true;
}


void Ustawienia::on_lineEdit_3_textEdited()
{
    if (fieldsChanged==false) fieldsChanged =true;
}


void Ustawienia::on_lineEdit_4_textEdited()
{
    if (fieldsChanged==false) fieldsChanged =true;
}


void Ustawienia::on_lineEdit_5_textEdited()
{
    if (fieldsChanged==false) fieldsChanged =true;
}


void Ustawienia::on_lineEdit_6_textEdited()
{
   if (fieldsChanged==false) fieldsChanged =true;
}


void Ustawienia::on_lineEdit_7_textEdited()
{
    if (fieldsChanged==false) fieldsChanged =true;
}


void Ustawienia::on_lineEdit_11a_3_textEdited()
{
    if (fieldsChanged==false) fieldsChanged =true;
}


//=============================================================================================
//==MAINWINDOW=================================================================================

void Ustawienia::on_pushButton_4_clicked()
{
    if (fieldsChanged==true)
    {
        if (QMessageBox::warning(this, "", "Uwaga.\n\nCzy na pewno zmienić ustawienia?", "OK", "Anuluj", "", 1, 1)==1)
        {
            this->hide();
            return;
        }
    }

    std::stringstream out;

    out <<(ui->lineEdit_2->text()).toStdString() <<"\n";
    out <<(ui->lineEdit_3->text()).toStdString() <<"\n";
    out <<(ui->lineEdit_4->text()).toStdString() <<"\n";
    out <<(ui->lineEdit_5->text()).toStdString() <<"\n";
    out <<(ui->lineEdit_6->text()).toStdString() <<"\n";
    out <<(ui->lineEdit_7->text()).toStdString() <<"\n";
    out <<(QString::number(typDok)).toStdString() <<"\n";
    out <<(ui->lineEdit_11a_3->text()).toStdString() <<"\n";

    File::saveFromStream("baza\\ustawienia.txt", &out);


    mainWindowPtr->setMainUstawieniaLines(ui->lineEdit_2->text(), ui->lineEdit_3->text(), ui->lineEdit_4->text(), ui->lineEdit_5->text(),
                                          ui->lineEdit_6->text(), ui->lineEdit_7->text(), QString::number(typDok), ui->lineEdit_11a_3->text());

    fieldsChanged =false;
    this->hide();
}

//=============================================================================================
//=============================================================================================

void Ustawienia::on_pushButton_5_clicked()
{
    fieldsChanged =false;
    this->hide();
}


void Ustawienia::closeEvent(QCloseEvent* event)
{
    if (fieldsChanged==true)
    {
        if (QMessageBox::warning(this, "", "Zamknąć okno bez zapisywania?", "OK", "Anuluj", "", 1, 1)==1)
        {
            event->ignore();
            return;
        }
    }

    fieldsChanged =false;
    event->accept();
}

//=============================================================================================
//==NAZWA_DOKUMENTU============================================================================

void Ustawienia::on_radioButton_11a_1_clicked()
{
    typDok =0;
    if (fieldsChanged==false) fieldsChanged =true;
}


void Ustawienia::on_radioButton_11a_2_clicked()
{
    typDok =1;
    if (fieldsChanged==false) fieldsChanged =true;
}


void Ustawienia::on_radioButton_11a_3_clicked()
{
    typDok =2;
    if (fieldsChanged==false) fieldsChanged =true;
}

