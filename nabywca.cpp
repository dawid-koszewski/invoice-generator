#include "nabywca.h"
#include "ui_nabywca.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


Nabywca::Nabywca(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Nabywca)
{
    ui->setupUi(this);

    activeTmpNew =false;
    fieldsChanged =false;
    saveCancelled =false;

    loadComboBox_0();
    ui->comboBox_0->setCurrentIndex(-1);

    grad1.setStart(0, 0);
    grad1.setFinalStop(0, ui->scrollAreaWidgetContents->height());
    grad1.setColorAt(0, QColor(180,180,240));
    grad1.setColorAt(1, QColor(215,215,240));
    palette1.setBrush(QPalette::Window, grad1);
    ui->scrollArea->setPalette(palette1);
}


Nabywca::~Nabywca()
{
    delete ui;
}


Ui::Nabywca* const& Nabywca::getMainUi()
{
    return ui;
}


void Nabywca::setNabywcaFields(const QString& n1, const QString& n2, const QString& n3,
                               const QString& n4, const QString& n5, const QString& n6)
{
    ui->lineEdit_1->setText(n1);
    ui->lineEdit_2->setText(n2);
    ui->lineEdit_3->setText(n3);
    ui->lineEdit_4->setText(n4);
    ui->lineEdit_5->setText(n5);
    ui->lineEdit_6->setText(n6);
}

//=============================================================================================
//=============================================================================================

void Nabywca::on_lineEdit_1_textEdited()
{
    if (fieldsChanged==false) fieldsChanged =true;
}


void Nabywca::on_lineEdit_2_textEdited()
{
    if (fieldsChanged==false) fieldsChanged =true;
}


void Nabywca::on_lineEdit_3_textEdited()
{
    if (fieldsChanged==false) fieldsChanged =true;
}


void Nabywca::on_lineEdit_4_textEdited()
{
    if (fieldsChanged==false) fieldsChanged =true;
}


void Nabywca::on_lineEdit_5_textEdited()
{
    if (fieldsChanged==false) fieldsChanged =true;
}


void Nabywca::on_lineEdit_6_textEdited()
{
   if (fieldsChanged==false) fieldsChanged =true;
}


void Nabywca::clearFields()
{
    ui->lineEdit_1->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
}


void Nabywca::loadComboBox_0()
{
    std::stringstream tmpStream;
    std::string stdString;

    File::loadToStream("baza\\nabywcaCombo_0.txt", &tmpStream);

    while(getline(tmpStream, stdString))
    {
        ui->comboBox_0->addItem(stdString.c_str());
    }
}


void Nabywca::saveComboBox_0()
{
    std::stringstream tmpStream;
    int itemsCount =ui->comboBox_0->count();

    for (int i =0; i< itemsCount; ++i)
    {
        tmpStream <<(ui->comboBox_0->itemText(i)).toStdString() <<"\n";
    }

    File::saveFromStream("baza\\nabywcaCombo_0.txt", &tmpStream);
}


void Nabywca::remComp(const int& indexToDel)
{
    activeTmpNew =File::remCompany(activeTmpNew, ui->comboBox_0->itemText(indexToDel), "baza\\nabywca.txt", "baza\\nabywcaTmpNew.txt", "baza\\nabywcaTmpNewCopy.txt");

    ui->comboBox_0->removeItem(indexToDel);
}


void Nabywca::addComp(const QString& toAdd)
{
    activeTmpNew =File::addCompany(activeTmpNew, ui->lineEdit_1->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text(), ui->lineEdit_4->text(),
                                   ui->lineEdit_5->text(), ui->lineEdit_6->text(), "-------", "baza\\nabywca.txt", "baza\\nabywcaTmpNew.txt");

    ui->comboBox_0->insertItem(0, toAdd);
    ui->comboBox_0->setCurrentIndex(0);
    ui->comboBox_0->model()->sort(0); //==SORTOWANIE ALFABETYCZNE==
}


void Nabywca::on_pushButton_0_clicked()
{
    clearFields();
}


void Nabywca::on_pushButton_1_clicked()
{
    QString toAdd =ui->lineEdit_1->text();

    if (toAdd=="")
    {
        QMessageBox::warning(this, "", "Pole skrót nabywcy jest puste.", "OK", "", "", 0, 0);
        saveCancelled =true;
        return;
    }

    int found =-1;
    if (toAdd==ui->comboBox_0->currentText()) found =ui->comboBox_0->currentIndex();
    else found =ui->comboBox_0->findText(toAdd, Qt::MatchExactly);

    if (found>=0)
    {
        if (QMessageBox::warning(this, "", "Uwaga.\n\nNabywca o podanym skrócie już istnieje w bazie.\n\nZamienić?", "OK", "Anuluj", "", 1, 1)==0)
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


void Nabywca::on_pushButton_2_clicked()
{   
    if (QMessageBox::warning(this, "", "Uwaga.\n\nCzy na pewno usunąć tego nabywcę?", "OK", "Anuluj", "", 1, 1)==1) return;

    remComp(ui->comboBox_0->currentIndex());
    ui->comboBox_0->setCurrentIndex(-1);
    clearFields();
    fieldsChanged =false;
}


void Nabywca::on_pushButton_3_clicked()
{   
    int indexToDel =ui->comboBox_0->currentIndex();

    if (fieldsChanged==true && indexToDel>=0)
    {
        if (QMessageBox::warning(this, "", "Uwaga.\n\nCzy na pewno zmienić dane tego nabywcy?", "OK", "Anuluj", "", 1, 1)==1) return;

        remComp(indexToDel);
        addComp(ui->lineEdit_1->text());
        fieldsChanged =false;
    }
}

//=============================================================================================
//==MAINWINDOW=================================================================================

void Nabywca::on_comboBox_0_activated(int index)
{
    QString fileFrom("baza\\nabywca.txt");
    if (activeTmpNew==true) fileFrom ="baza\\nabywcaTmpNew.txt";

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

    setNabywcaFields(stringArr[0], stringArr[1], stringArr[2], stringArr[3], stringArr[4], stringArr[5]);

    fieldsChanged =false;
}


void Nabywca::on_pushButton_4_clicked()
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
        File::copyExcept("baza\\nabywcaTmpNew.txt", "baza\\nabywca.txt");

        saveComboBox_0();

        mainWindowPtr->getMainUi()->comboBox_13->clear();
        mainWindowPtr->loadComboBox_13();
    }

    mainWindowPtr->getMainUi()->comboBox_13->setCurrentIndex(ui->comboBox_0->currentIndex());
    mainWindowPtr->setMainNabywcaLines(ui->lineEdit_1->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text(),
                                       ui->lineEdit_4->text(), ui->lineEdit_5->text(), ui->lineEdit_6->text());

    fieldsChanged =false;
    this->hide();
}

//=============================================================================================
//=============================================================================================

void Nabywca::on_pushButton_5_clicked()
{
    ui->comboBox_0->setCurrentIndex(-1);
    clearFields();
    activeTmpNew =false;

    fieldsChanged =false;
    this->hide();
}


void Nabywca::closeEvent(QCloseEvent* event)
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





//=============================================================================================
//=============================================================================================
/*
void Nabywca::on_comboBox_0_activated(int index)
{
    QFile fileTmpNew("baza\\nabywcaTmpNew.txt");
    if (!fileTmpNew.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Nie można otworzyć bazy danych.", fileTmpNew.errorString());
        return;
    }

    QTextStream in (&fileTmpNew);

    QString selected =ui->comboBox_0->itemText(index);
    QString lineIn;
    int linia =0;

    while (!in.atEnd())
    {
        lineIn =in.readLine();
        ++linia;

        if (linia%7==1 && lineIn==selected)
        {
            ui->lineEdit_1->setText(lineIn);
            ui->lineEdit_2->setText(in.readLine());
            ui->lineEdit_3->setText(in.readLine());
            ui->lineEdit_4->setText(in.readLine());
            ui->lineEdit_5->setText(in.readLine());
            ui->lineEdit_6->setText(in.readLine());
            linia+=5;
        }
    }

    fileTmpNew.close();
    fieldsChanged =false;
}
*/




/*
//--------------------------------
//#0------------------------------
    out <<sStream.str().c_str();
//--------------------------------
//#1A--CLASSIC--isStream----------
    char *line = new char [1024];

    while(sStream.getline(line, 1024))
    {
        stdString =line;
        out <<stdString.c_str() <<"\n";
    }
//--------------------------------
//#1B--MODERN--string-------------
    while(getline(sStream, stdString))
    {
        out <<stdString.c_str() <<"\n";
    }
//--------------------------------
//posredni cuteString z ".fromStdString()" drukuje puste pliki, a z ".c_str()" dziala dobrze
//--------------------------------
*/




//===============================================================================================//
//wersja, ktora dotyczyla kopiowania plikow, majac liste z ktorej zostalo usunietych kilka wpisow//
//===============================================================================================//
/*
    int itemCount =ui->comboBox_0->count();
    QStringList itemsToCompare;

    for (int i =0; i< itemCount; ++i)
    {
        itemsToCompare <<ui->comboBox_0->itemText(i);
    }

    std::sort(itemsToCompare.begin(), itemsToCompare.end(), [](const QString &s1, const QString &s2){return s1.toLower() < s2.toLower();});


    QString lineIn;
    int linia =0;
    bool itemExisting =false;

    while (!in.atEnd())
    {
        lineIn =in.readLine();

        if (linia%7==0)
        {
            itemExisting =std::binary_search(itemsToCompare.begin(), itemsToCompare.end(), lineIn);

            if (itemExisting==true)
            {
                out <<lineIn <<endl;

                for (int i =0; i< 6; ++i)
                {
                    out <<in.readLine() <<endl;
                    ++linia;
                }
            }
        }

        ++linia;
    }

    //-----------------------------------

    toAddList.append(toAdd);
    if (!toAddList.removeOne(toDel)) toDelList.append(toDel);
*/

