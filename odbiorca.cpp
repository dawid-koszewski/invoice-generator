#include "odbiorca.h"
#include "ui_odbiorca.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


Odbiorca::Odbiorca(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Odbiorca)
{
    ui->setupUi(this);

    activeTmpNew =false;
    fieldsChanged =false;
    saveCancelled =false;

    loadComboBox_0();
    ui->comboBox_0->setCurrentIndex(-1);

    grad1.setStart(0, 0);
    grad1.setFinalStop(0, ui->scrollAreaWidgetContents->height());
    grad1.setColorAt(0, QColor(240,240,180));
    grad1.setColorAt(1, QColor(240,240,215));
    palette1.setBrush(QPalette::Window, grad1);
    ui->scrollArea->setPalette(palette1);
}


Odbiorca::~Odbiorca()
{
    delete ui;
}


Ui::Odbiorca* const& Odbiorca::getMainUi()
{
    return ui;
}


void Odbiorca::setOdbiorcaFields(const QString& o1, const QString& o2, const QString& o3,
                                 const QString& o4, const QString& o5, const QString& o6)
{
    ui->lineEdit_1->setText(o1);
    ui->lineEdit_2->setText(o2);
    ui->lineEdit_3->setText(o3);
    ui->lineEdit_4->setText(o4);
    ui->lineEdit_5->setText(o5);
    ui->lineEdit_6->setText(o6);
}

//=============================================================================================
//=============================================================================================

void Odbiorca::on_lineEdit_1_textEdited()
{
    if (fieldsChanged==false) fieldsChanged =true;
}


void Odbiorca::on_lineEdit_2_textEdited()
{
    if (fieldsChanged==false) fieldsChanged =true;
}


void Odbiorca::on_lineEdit_3_textEdited()
{
    if (fieldsChanged==false) fieldsChanged =true;
}


void Odbiorca::on_lineEdit_4_textEdited()
{
    if (fieldsChanged==false) fieldsChanged =true;
}


void Odbiorca::on_lineEdit_5_textEdited()
{
    if (fieldsChanged==false) fieldsChanged =true;
}


void Odbiorca::on_lineEdit_6_textEdited()
{
   if (fieldsChanged==false) fieldsChanged =true;
}


void Odbiorca::clearFields()
{
    ui->lineEdit_1->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
}


void Odbiorca::loadComboBox_0()
{
    std::stringstream tmpStream;
    std::string stdString;

    File::loadToStream("baza\\odbiorcaCombo_0.txt", &tmpStream);

    while(getline(tmpStream, stdString))
    {
        ui->comboBox_0->addItem(stdString.c_str());
    }
}


void Odbiorca::saveComboBox_0()
{
    std::stringstream tmpStream;
    int itemsCount =ui->comboBox_0->count();

    for (int i =0; i< itemsCount; ++i)
    {
        tmpStream <<(ui->comboBox_0->itemText(i)).toStdString() <<"\n";
    }

    File::saveFromStream("baza\\odbiorcaCombo_0.txt", &tmpStream);
}


void Odbiorca::remComp(const int& indexToDel)
{
    activeTmpNew =File::remCompany(activeTmpNew, ui->comboBox_0->itemText(indexToDel), "baza\\odbiorca.txt", "baza\\odbiorcaTmpNew.txt", "baza\\odbiorcaTmpNewCopy.txt");

    ui->comboBox_0->removeItem(indexToDel);
}


void Odbiorca::addComp(const QString& toAdd)
{
    activeTmpNew =File::addCompany(activeTmpNew, ui->lineEdit_1->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text(), ui->lineEdit_4->text(),
                                   ui->lineEdit_5->text(), ui->lineEdit_6->text(), "-------", "baza\\odbiorca.txt", "baza\\odbiorcaTmpNew.txt");

    ui->comboBox_0->insertItem(0, toAdd);
    ui->comboBox_0->setCurrentIndex(0);
    ui->comboBox_0->model()->sort(0); //==SORTOWANIE ALFABETYCZNE==
}


void Odbiorca::on_pushButton_0_clicked()
{
    clearFields();
}


void Odbiorca::on_pushButton_1_clicked()
{
    QString toAdd =ui->lineEdit_1->text();

    if (toAdd=="")
    {
        QMessageBox::warning(this, "", "Pole skrót odbiorcy jest puste.", "OK", "", "", 0, 0);
        saveCancelled =true;
        return;
    }

    int found =-1;
    if (toAdd==ui->comboBox_0->currentText()) found =ui->comboBox_0->currentIndex();
    else found =ui->comboBox_0->findText(toAdd, Qt::MatchExactly);

    if (found>=0)
    {
        if (QMessageBox::warning(this, "", "Uwaga.\n\nOdbiorca o podanym skrócie już istnieje w bazie.\n\nZamienić?", "OK", "Anuluj", "", 1, 1)==0)
        {
            remComp(found);
            addComp(toAdd);
            fieldsChanged =false;
        }
        else saveCancelled =true;
    }
    else
    {
        addComp(toAdd);
        fieldsChanged =false;
    }
}


void Odbiorca::on_pushButton_2_clicked()
{
    if (QMessageBox::warning(this, "", "Uwaga.\n\nCzy na pewno usunąć tego odbiorcę?", "OK", "Anuluj", "", 1, 1)==1) return;

    remComp(ui->comboBox_0->currentIndex());
    ui->comboBox_0->setCurrentIndex(-1);
    clearFields();
    fieldsChanged =false;
}


void Odbiorca::on_pushButton_3_clicked()
{
    int indexToDel =ui->comboBox_0->currentIndex();

    if (fieldsChanged==true && indexToDel>=0)
    {
        if (QMessageBox::warning(this, "", "Uwaga.\n\nCzy na pewno zmienić dane tego odbiorcy?", "OK", "Anuluj", "", 1, 1)==1) return;

        remComp(indexToDel);
        addComp(ui->lineEdit_1->text());
        fieldsChanged =false;
    }
}

//=============================================================================================
//==MAINWINDOW=================================================================================

void Odbiorca::on_comboBox_0_activated(int index)
{
    QString fileFrom("baza\\odbiorca.txt");
    if (activeTmpNew==true) fileFrom ="baza\\odbiorcaTmpNew.txt";

    std::stringstream tmpStream;
    std::string stdString;

    File::loadSelectedToStream(fileFrom, &tmpStream, ui->comboBox_0->itemText(index));

    QString stringArr[6];
    int i =0;

    while (i< 6 && getline(tmpStream, stdString))
    {
        stringArr[i] =stdString.c_str();
        ++i;
    }

    setOdbiorcaFields(stringArr[0], stringArr[1], stringArr[2], stringArr[3], stringArr[4], stringArr[5]);

    fieldsChanged =false;
}


void Odbiorca::on_pushButton_4_clicked()
{
    if (fieldsChanged==true)
    {
        on_pushButton_1_clicked();

        if (saveCancelled==true)
        {
            saveCancelled =false;
            return;
        }
    }

    if (activeTmpNew==true)
    {
        File::copyExcept("baza\\odbiorcaTmpNew.txt", "baza\\odbiorca.txt");

        saveComboBox_0();

        mainWindowPtr->getMainUi()->comboBox_14->clear();
        mainWindowPtr->loadComboBox_14();
    }

    mainWindowPtr->getMainUi()->comboBox_14->setCurrentIndex(ui->comboBox_0->currentIndex());
    mainWindowPtr->setMainOdbiorcaLines(ui->lineEdit_1->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text(),
                                        ui->lineEdit_4->text(), ui->lineEdit_5->text(), ui->lineEdit_6->text());

    fieldsChanged =false;
    this->hide();
}

//=============================================================================================
//=============================================================================================

void Odbiorca::on_pushButton_5_clicked()
{
    ui->comboBox_0->setCurrentIndex(-1);
    clearFields();
    activeTmpNew =false;

    fieldsChanged =false;
    this->hide();
}


void Odbiorca::closeEvent(QCloseEvent* event)
{
    if (fieldsChanged==true || activeTmpNew==true)
    {
        if (QMessageBox::warning(this, "", "Zamknąć okno bez zapisywania?", "OK", "Anuluj", "", 1, 1)==1)
        {
            event->ignore();
            return;
        }
    }

    ui->comboBox_0->setCurrentIndex(-1);
    clearFields();
    activeTmpNew =false;

    fieldsChanged =false;
    event->accept();
}

