#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nabywca.h"
#include "ui_nabywca.h"
#include "odbiorca.h"
#include "ui_odbiorca.h"
#include "ustawienia.h"
#include "ui_ustawienia.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dSumTotal =0;
    typDok =0;

    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setColumnWidth(0, 40);
    ui->tableWidget->setColumnWidth(1, 360);
    ui->tableWidget->setColumnWidth(2, 50);
    ui->tableWidget->setColumnWidth(3, 50);
    ui->tableWidget->setColumnWidth(4, 90);
    ui->tableWidget->setColumnWidth(5, 110);

    ui->dateEdit_12a->setDate(QDate::currentDate());
    ui->dateEdit_12b->setDate(QDate::currentDate());

    loadComboBox_13(); //powiazane z Nabywca
    loadComboBox_14(); //powiazane z Odbiorca
    loadSettings_15();

    loadComboBoxU(ui->comboBox_0, "baza\\mainCombo_0.txt");
    loadComboBoxU(ui->comboBox_3, "baza\\mainCombo_3.txt");
    loadComboBoxU(ui->comboBox_11b, "baza\\mainCombo_11b.txt");
    loadComboBoxU(ui->comboBox_15a, "baza\\mainCombo_15a.txt");
    loadComboBoxU(ui->comboBox_15b, "baza\\mainCombo_15b.txt");

    loadLastSettings();
    ui->comboBox_0->setCurrentIndex(-1);
    ui->comboBox_14->setCurrentIndex(-1);

    view =nullptr;
    page =nullptr;

    grad1.setStart(0, 0);
    grad1.setFinalStop(0, ui->scrollAreaWidgetContents->height());
    grad1.setColorAt(0, QColor(180,240,180));
    grad1.setColorAt(1, QColor(215,240,215));
    palette1.setBrush(QPalette::Window, grad1);
    ui->centralWidget->setPalette(palette1);
}


MainWindow::~MainWindow()
{
    saveLastSettings();

    saveComboBoxU(ui->comboBox_0, "baza\\mainCombo_0.txt", 13);
    saveComboBoxU(ui->comboBox_3, "baza\\mainCombo_3.txt", 5);
    saveComboBoxU(ui->comboBox_11b, "baza\\mainCombo_11b.txt", 5);
    saveComboBoxU(ui->comboBox_15a, "baza\\mainCombo_15a.txt", 5);
    saveComboBoxU(ui->comboBox_15b, "baza\\mainCombo_15b.txt", 5);

    delete view;
    view =nullptr;

    delete page;
    page =nullptr;

    delete ui;
}


Ui::MainWindow* const& MainWindow::getMainUi()
{
    return ui;
}


void MainWindow::setMainNabywcaLines(const QString& n1, const QString& n2, const QString& n3,
                                     const QString& n4, const QString& n5, const QString& n6)
{
    nab1 =n1;
    nab2 =n2;
    nab3 =n3;
    nab4 =n4;
    nab5 =n5;
    nab6 =n6;
}


void MainWindow::setMainOdbiorcaLines(const QString& o1, const QString& o2, const QString& o3,
                                     const QString& o4, const QString& o5, const QString& o6)
{
    odb1 =o1;
    odb2 =o2;
    odb3 =o3;
    odb4 =o4;
    odb5 =o5;
    odb6 =o6;
}


void MainWindow::setMainUstawieniaLines(const QString& u2, const QString& u3, const QString& u4, const QString& u5,
                                        const QString& u6, const QString& u7, const QString& u11, const QString& u12)
{
    sprzed2 =u2;
    sprzed3 =u3;
    sprzed4 =u4;
    sprzed5 =u5;
    sprzed6 =u6;
    sprzed7 =u7;
    typDok =u11.toInt();
    nazwaDok =u12;

    setWybranaNazwaDok();
}


void MainWindow::loadComboBoxU(QComboBox* box, const QString& from)
{
    std::stringstream in;
    std::string stdString;

    File::loadToStream(from, &in);

    while(getline(in, stdString))
    {
        box->addItem(stdString.c_str());
    }
}


void MainWindow::saveComboBoxU(QComboBox* box, const QString& to, const int& c)
{
    std::stringstream out;
    int itemsCount =box->count();
    if (itemsCount> c) itemsCount =c;

    for (int i =0; i< itemsCount; ++i)
    {
        out <<(box->itemText(i)).toStdString() <<"\n";
    }

    File::saveFromStream(to, &out);
}


void MainWindow::reorderComboBoxU(QComboBox* box, const int& index)
{
    QString tmp =box->itemText(index); //==PROMOWANIE NA TOP==
    box->removeItem(index);
    box->insertItem(0, tmp);
    box->setCurrentIndex(0);
}


void MainWindow::loadLastSettings()
{
    std::stringstream in;
    std::string stdString;

    File::loadToStream("baza\\ostatnie.txt", &in);

    QString stringArr[8];
    int i =0;

    while (i< 8 && getline(in, stdString))
    {
        stringArr[i] =stdString.c_str();
        ++i;
    }

    ui->lineEdit_11a->setText(stringArr[0]);
    ui->comboBox_11b->setCurrentIndex(stringArr[1].toInt());
    ui->checkBox_12->setChecked(stringArr[2].toInt());
    ui->comboBox_13->setCurrentIndex(stringArr[3].toInt());
    //ui->comboBox_14->setCurrentIndex(stringArr[4].toInt());
    ui->comboBox_15a->setCurrentIndex(stringArr[5].toInt());
    ui->comboBox_15b->setCurrentIndex(stringArr[6].toInt());
    ui->comboBox_3->setCurrentIndex(stringArr[7].toInt());

    on_checkBox_12_clicked(stringArr[2].toInt());
    on_comboBox_13_activated(stringArr[3].toInt());
    //on_comboBox_14_activated(stringArr[4].toInt());
}


void MainWindow::saveLastSettings()
{
    QString c11b(ui->comboBox_11b->currentText());
    QString c15a(ui->comboBox_15a->currentText());
    QString c15b(ui->comboBox_15b->currentText());
    QString c3(ui->comboBox_3->currentText());

    if (ui->comboBox_11b->findText(c11b, Qt::MatchExactly)< 0 && c11b!="")
    {
        ui->comboBox_11b->insertItem(0, c11b);
    }

    if (ui->comboBox_15a->findText(c15a, Qt::MatchExactly)< 0 && c15a!="")
    {
        ui->comboBox_15a->insertItem(0, c15a);
    }

    if (ui->comboBox_15b->findText(c15b, Qt::MatchExactly)< 0 && c15b!="")
    {
        ui->comboBox_15b->insertItem(0, c15b);
    }

    if (ui->comboBox_3->findText(c3, Qt::MatchExactly)< 0 && c3!="")
    {
        ui->comboBox_3->insertItem(0, c3);
    }

    std::stringstream out;

    out <<(ui->lineEdit_11a->text()).toStdString() <<"\n";
    out <<ui->comboBox_11b->currentIndex() <<"\n";
    out <<ui->checkBox_12->isChecked() <<"\n";
    out <<ui->comboBox_13->currentIndex() <<"\n";
    out <<ui->comboBox_14->currentIndex() <<"\n";
    out <<ui->comboBox_15a->currentIndex() <<"\n";
    out <<ui->comboBox_15b->currentIndex() <<"\n";
    out <<ui->comboBox_3->currentIndex() <<"\n";

    File::saveFromStream("baza\\ostatnie.txt", &out);
}

//=============================================================================================
//=============================================================================================

void MainWindow::on_comboBox_11b_activated(int index)
{
    reorderComboBoxU(ui->comboBox_11b, index); //==PROMOWANIE NA TOP==
}


void MainWindow::on_comboBox_15a_activated(int index)
{
    reorderComboBoxU(ui->comboBox_15a, index); //==PROMOWANIE NA TOP==
}


void MainWindow::on_comboBox_15b_activated(int index)
{
    reorderComboBoxU(ui->comboBox_15b, index); //==PROMOWANIE NA TOP==
}


void MainWindow::on_comboBox_3_activated(int index)
{
    reorderComboBoxU(ui->comboBox_3, index); //==PROMOWANIE NA TOP==
}


void MainWindow::on_checkBox_12_clicked(bool checked)
{
    if (checked==true)
    {
        ui->dateEdit_12a->setCalendarPopup(true);
        ui->dateEdit_12b->setCalendarPopup(true);
    }
    else
    {
        ui->dateEdit_12a->setCalendarPopup(false);
        ui->dateEdit_12b->setCalendarPopup(false);
    }
}

//=============================================================================================
//==QTABLE=====================================================================================

QString MainWindow::recalc_s5(QString *s2, QString *s4)
{
    (*s2).replace(',','.');
    (*s4).replace(',','.');

    double d2 =(*s2).toInt();
    double d4 =floor((*s4).toDouble()*100+0.5)/100;
    double d5 =floor((d2*d4)*100+0.5)/100;

    (*s4) =QString::number(d4, 'f', 2);
    QString s5 =QString::number(d5, 'f', 2);

    (*s2).replace('.',',');
    (*s4).replace('.',',');
    s5.replace('.',',');

    return s5;
}


void MainWindow::on_pushButton_1_clicked()
{
    ui->tableWidget->blockSignals(true); //IMPORTANTE

    int rowCount =ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCount);

    QString s1 =ui->plainTextEdit_1->toPlainText();
    QString s2 =ui->spinBox_2->text();
    QString s4 =ui->lineEdit_4->text();
    QString s5 =recalc_s5(&s2, &s4);

    ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(rowCount+1)+'.'));
    ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(s1));
    ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(s2));
    ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(ui->comboBox_3->currentText()));
    ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(s4));

    ui->tableWidget->blockSignals(false); //IMPORTANTE

    QTableWidgetItem* item5 =nullptr;
    item5 =new QTableWidgetItem;
    item5->setText(s5);
    item5->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled); //blokada edycji #1. sposob
    //item5->setFlags(item5->flags() & ~Qt::ItemIsEditable); //blokada edycji #2. sposob
    ui->tableWidget->setItem(rowCount, 5, item5);

    ui->tableWidget->verticalHeader()->resizeSections(QHeaderView::ResizeToContents);

    //-------------------------------------------
    if (s1!="")
    {
        s1.replace('\n', ' ');

        int found =ui->comboBox_0->findText(s1, Qt::MatchExactly);

        if (found>=0) ui->comboBox_0->removeItem(found); //==PROMOWANIE NA TOP==

        ui->comboBox_0->insertItem(0, s1);
    }

    ui->comboBox_0->setCurrentIndex(-1);
    ui->plainTextEdit_1->clear();
    ui->spinBox_2->setValue(1);
    ui->lineEdit_4->setText("");
    //-------------------------------------------
}


void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    int rowCount =0;
    rowCount =ui->tableWidget->rowCount();

    if (column==2 || column==4)
    {
        QString s2 =ui->tableWidget->item(row, 2)->text();
        QString s4 =ui->tableWidget->item(row, 4)->text();
        QString s5 =recalc_s5(&s2, &s4);

        ui->tableWidget->item(row, 5)->setText(s5);
    }

    if (column==5)
    {
        dSumTotal =0;
        QString s5;
        double d5;

        for (int i =0; i< rowCount; ++i)
        {
            s5 =ui->tableWidget->item(i, 5)->text();
            s5.replace(',','.');
            d5 =s5.toDouble();
            d5 =floor(d5*100+0.5)/100;

            dSumTotal+=d5;
        }

        QString sSumTotal =QString::number(dSumTotal, 'f', 2);
        sSumTotal.replace('.',',');
        ui->lineEdit_6->setText(sSumTotal);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    int rowCount =-1;
    rowCount =ui->tableWidget->rowCount() -1;

    if (rowCount>=0)
    {
        ui->tableWidget->item(rowCount, 5)->setText("0");

        //ui->tableWidget->blockSignals(true);
/*        QTableWidgetItem* temp;

        for (int i =0; i<6; ++i)
        {
            temp =ui->tableWidget->item(rowCount, i);
            delete temp;

            ui->tableWidget->setItem(rowCount, i, nullptr);
        }
*/
        ui->tableWidget->removeRow(rowCount);
        //ui->tableWidget->blockSignals(false);
    }
}


void MainWindow::on_comboBox_0_activated(int index)
{
    ui->plainTextEdit_1->document()->setPlainText(ui->comboBox_0->itemText(index));
    //ui->plainTextEdit_1->clear();
    //ui->plainTextEdit_1->appendPlainText(ui->comboBox_0->itemText(index));
}

//=============================================================================================
//==NABYWCA====================================================================================

void MainWindow::loadComboBox_13()
{
    std::stringstream in;
    std::string stdString;

    File::loadToStream("baza\\nabywcaCombo_0.txt", &in);

    while(getline(in, stdString))
    {
        ui->comboBox_13->addItem(stdString.c_str());
    }
}


void MainWindow::on_pushButton_13_clicked()
{
    if (!nabywcaPtr) nabywcaPtr =new Nabywca;

    nabywcaPtr->show();

    nabywcaPtr->getMainUi()->comboBox_0->setCurrentIndex(ui->comboBox_13->currentIndex());
    nabywcaPtr->setNabywcaFields(nab1, nab2, nab3, nab4, nab5, nab6);
}


void MainWindow::on_comboBox_13_activated(int index) //podobna do Nabywca::on_comboBox_0_activated
{
    std::stringstream in;
    std::string stdString;

    File::loadSelectedToStream("baza\\nabywca.txt", &in, ui->comboBox_13->itemText(index));

    QString stringArr[6];
    int i =0;

    while (i< 6 && getline(in, stdString))
    {
        stringArr[i] =stdString.c_str();
        ++i;
    }

    setMainNabywcaLines(stringArr[0], stringArr[1], stringArr[2], stringArr[3], stringArr[4], stringArr[5]);
}

//=============================================================================================
//==ODBIORCA====================================================================================

void MainWindow::loadComboBox_14()
{
    std::stringstream in;
    std::string stdString;

    File::loadToStream("baza\\odbiorcaCombo_0.txt", &in);

    while(getline(in, stdString))
    {
        ui->comboBox_14->addItem(stdString.c_str());
    }
}


void MainWindow::on_pushButton_14_clicked()
{
    if (!odbiorcaPtr) odbiorcaPtr =new Odbiorca;

    odbiorcaPtr->show();

    odbiorcaPtr->getMainUi()->comboBox_0->setCurrentIndex(ui->comboBox_14->currentIndex());
    odbiorcaPtr->setOdbiorcaFields(odb1, odb2, odb3, odb4, odb5, odb6);
}


void MainWindow::on_comboBox_14_activated(int index) //podobna do Odbiorca::on_comboBox_0_activated
{
    std::stringstream in;
    std::string stdString;

    File::loadSelectedToStream("baza\\odbiorca.txt", &in, ui->comboBox_14->itemText(index));

    QString stringArr[6];
    int i =0;

    while (i< 6 && getline(in, stdString))
    {
        stringArr[i] =stdString.c_str();
        ++i;
    }

    setMainOdbiorcaLines(stringArr[0], stringArr[1], stringArr[2], stringArr[3], stringArr[4], stringArr[5]);
}

//=============================================================================================
//==USTAWIENIA=================================================================================

void MainWindow::loadSettings_15()
{
    std::stringstream in;
    std::string stdString;

    File::loadToStream("baza\\ustawienia.txt", &in);

    QString stringArr[8];
    int i =0;

    while (i< 8 && getline(in, stdString))
    {
        stringArr[i] =stdString.c_str();
        ++i;
    }

    setMainUstawieniaLines(stringArr[0], stringArr[1], stringArr[2], stringArr[3], stringArr[4], stringArr[5], stringArr[6], stringArr[7]);
}


void MainWindow::on_pushButton_15_clicked()
{
    if (!ustawieniaPtr) ustawieniaPtr =new Ustawienia;

    ustawieniaPtr->show();

    ustawieniaPtr->setUstawieniaFields(sprzed2, sprzed3, sprzed4, sprzed5, sprzed6, sprzed7, typDok, nazwaDok);
}


void MainWindow::setWybranaNazwaDok()
{
    if (typDok==0) wybranaNazwaDok ="Faktura nr";
    if (typDok==1) wybranaNazwaDok ="Rachunek nr";
    if (typDok==2) wybranaNazwaDok =nazwaDok;
}

//=============================================================================================
//==NOWY NUMER=================================================================================

bool MainWindow::availableName(const QString& filePath)
{
    QFile check(filePath);
    if (check.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        check.close();
        return false;
    }
    else
    {
        check.close();
        return true;
    }

}


bool MainWindow::normalizeName(QString name)
{
    if (name=="")
    {
        QMessageBox::warning(this, "", "Pole numeru dokumentu jest puste.\n\nZalecany format to:  [  ##  (MM)  yy  ]\n(gdzie:  ## - nr dokumentu, (MM) - opcjonalnie miesiąc, yy - rok).\nNależy wpisać dwie lub trzy grupy cyfr oraz dowolną ilość innych znaków.\n\nPrzykładowe formaty to 99/12/2018 lub nawet FV099A-Bc  18abc, co oznacza dokument numer 99 w roku 18.\n\nWpisz nowy numer dokumentu ręcznie.", "OK", "", "", 0, 0);
        return false;
    }

    name.replace('\\', '-'); //zabronione znaki nazwy pliku w windowsie \ / : * ? " < > |
    name.replace('/', '-');
    name.replace(':', '-');
    name.replace('*', '-');
    name.replace('?', '-');
    name.replace('"', '-');
    name.replace('<', '-');
    name.replace('>', '-');
    name.replace('|', '-');

    //filePathPdf ="archiwum\\"+filename+".pdf";
    //filePathHtml ="archiwum\\"+filename+".html";
    filePathPdf.clear();
    filePathPdf.append("archiwum\\");
    filePathPdf.append(name);
    filePathPdf.append(".pdf");
    filePathHtml.clear();
    filePathHtml.append("archiwum\\");
    filePathHtml.append(name);
    filePathHtml.append(".html");
    filePathTxt.clear();
    filePathTxt.append("archiwum\\");
    filePathTxt.append(name);
    filePathTxt.append(".txt");

    return true;
}


void MainWindow::on_pushButton_11_clicked()
{
    QString invoiceName(ui->lineEdit_11a->text());

    if (!normalizeName(invoiceName)) return;

    QRegularExpression re("([0-9]+)([[:punct:][:alpha:][:space:]]*)([0-9]*)([[:punct:][:alpha:][:space:]]+)([0-9]*)([0-9]{2})");
    QRegularExpressionMatch match =re.match(invoiceName);

    if (match.hasMatch())
    {
        if (availableName(filePathHtml))
        {
            if (QMessageBox::warning(this, "", "Uwaga.\n\nPodany numer dokumentu nie został jeszcze wykorzystany.\n\nCzy zmienić numer mimo to?", "OK", "Anuluj", "", 1, 1)==1) return;
        }

        QString mp =invoiceName.left(match.capturedStart(0));
        QString m1 =match.captured(1); //#i
        QString m2 =match.captured(2); //separator znak punkcyjny, alfabet, spacja/enter
        QString m3 =match.captured(3); //miesiac MM oraz opcjonalne cyfry
        QString m4 =match.captured(4); //separator znak punkcyjny, alfabet, spacja/enter
        QString m5 =match.captured(5); //opcjonalne cyfry
        QString m6 =match.captured(6); //rok YY
        QString ms =invoiceName.right(invoiceName.length()-match.capturedEnd(0));

        int month =ui->dateEdit_12a->date().month();
        int yearLong =ui->dateEdit_12a->date().year();
        int year =yearLong%100;
        QString dateMonth(QString::number(month));
        QString dateYear(QString::number(year));

        int im1 =m1.toInt();

        int m1len =m1.length();
        int m3len =m3.length();


        if (m3len==0)
        {
            if (m6.toInt()==year) ++im1;
            else im1 =1;
            dateMonth ="";
        }
        else if (m3len> 1 && m3.at(m3len-2)=='1') //jesli numer miesiaca faktury 11 lub 12
        {
            if (m3.right(2).toInt()==month && m6.toInt()==year) ++im1;
            else im1 =1;
            m3.remove(m3len-2, 2);
        }
        else
        {
            if (m3.right(1).toInt()==month && m6.toInt()==year) ++im1;
            else im1 =1;
            m3.remove(m3len-1, 1);
        }

        QString am1 =QString::number(im1);
        int am1len =am1.length();
        int am3len =m3.length() +dateMonth.length();

        for (int i =0; i<(m1len -am1len); ++i) am1.prepend('0');

        if ((m3len -am3len)> 0)
        for (int i =0; i<(m3len -am3len); ++i) m3.prepend('0');

        if ((m3len -am3len)< 0)
        for (int i =0; i<(am3len -m3len); ++i) m3.remove(0, 1);


        QString invoiceNewName =mp +am1 +m2 +m3 +dateMonth +m4 +m5 +dateYear +ms;

        ui->lineEdit_11a->setText(invoiceNewName);
    }
    else
    {
        QMessageBox::warning(this, "", "Nazwa dokumentu nie pasuje do formatu.\n\nZalecany format to:  [  ##  (MM)  yy  ]\n(gdzie:  ## - nr dokumentu, (MM) - opcjonalnie miesiąc, yy - rok).\nNależy wpisać dwie lub trzy grupy cyfr oraz dowolną ilość innych znaków.\n\nPrzykładowe formaty to 99/12/2018 lub nawet FV099A-Bc  18abc, co oznacza dokument numer 99 w roku 18.\n\nWpisz nowy numer dokumentu ręcznie.", "OK", "", "", 0, 0);
        return;
    }
}

//=============================================================================================
//==ARCHIWUM===================================================================================

void MainWindow::on_pushButton_12_clicked()
{
    QUrl filePath(QFileDialog::getOpenFileUrl(this, "Otwieranie pliku do edycji", QUrl::fromLocalFile("archiwum\\"), "Wszystkie pliki (*.*);;Pliki do edycji (*.txt);;Dokumenty html (*.html);;Dokumenty PDF (*.pdf)"));

    if (filePath.fileName().right(3)=="txt")
    {
        if (QMessageBox::warning(this, "", "Uwaga.\n\nCzy wczytać do programu dokument "+filePath.fileName()+"?\n\nObecne wartości w głównym oknie programu zostaną podmienione.\nPonadto dane Nabywcy, Odbiorcy oraz Sprzedawcy zostaną chwilowo ustawione na te z otwieranego dokumentu.\nPamiętaj, że jeżeli wejdziesz w okno Ustawienia i naciśniesz OK, to te chwilowe dane z wczytanego dokumentu zostaną zapisane na stałe.\n\nAle poza tym możesz swobodnie wyświetlać podgląd oraz edytować wczytany dokument.", "OK", "Anuluj", "", 1, 1)==1) return;

        loadFieldsData(filePath);
    }
    else
    {
        QDesktopServices::openUrl(filePath);
    }
}

//=============================================================================================
//==PODGLAD====================================================================================

void MainWindow::loadFieldsData(const QUrl& filePath)
{
    std::stringstream in;
    std::string stdString;

    File::loadToStream(filePath.toLocalFile(), &in);

    QString stringArr[25];
    int i =0;

    while (i< 25 && getline(in, stdString))
    {
        stringArr[i] =stdString.c_str();
        ++i;
    }

    ui->comboBox_15a->setCurrentText(stringArr[0]); //#1

    ui->dateEdit_12b->setDate(QDate::fromString(stringArr[1], "dd-MM-yyyy")); //#2
    ui->dateEdit_12a->setDate(QDate::fromString(stringArr[2], "dd-MM-yyyy")); //#3

    typDok =stringArr[3].toInt(); //#4
    nazwaDok =stringArr[4]; //#5
    setWybranaNazwaDok();

    ui->lineEdit_11a->setText(stringArr[5]); //#6

    sprzed2 =stringArr[6]; //#7
    sprzed3 =stringArr[7]; //#8
    sprzed4 =stringArr[8]; //#9
    sprzed5 =stringArr[9]; //#10
    sprzed6 =stringArr[10]; //#11

    nab2 =stringArr[11]; //#12
    nab3 =stringArr[12]; //#13
    nab4 =stringArr[13]; //#14
    nab5 =stringArr[14]; //#15
    nab6 =stringArr[15]; //#16
    ui->comboBox_13->setCurrentIndex(-1);
    nab1 ="";

    ui->checkBox_14->setChecked(stringArr[16].toInt()); //#17
    odb2 =stringArr[17]; //#18
    odb3 =stringArr[18]; //#19
    odb4 =stringArr[19]; //#20
    odb5 =stringArr[20]; //#21
    odb6 =stringArr[21]; //#22
    ui->comboBox_14->setCurrentIndex(-1);
    odb1 ="";

    ui->comboBox_11b->setCurrentText(stringArr[22]); //#23
    ui->comboBox_15b->setCurrentText(stringArr[23]); //#24
    sprzed7 =stringArr[24]; //#25

    int rowCount =0;
    rowCount =ui->tableWidget->rowCount();

    for (int row =rowCount-1; row>=0; --row)
    {
        ui->tableWidget->removeRow(row);
    }

    QString s[5];
    int j =0;

    while (getline(in, stdString))
    {
        if (j> 4)
        {
            ui->tableWidget->blockSignals(true); //IMPORTANTE
            rowCount =ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rowCount);

            for (int k =0; k< 5; ++k)
            {
                ui->tableWidget->setItem(rowCount, k, new QTableWidgetItem(s[k]));
            }

            ui->tableWidget->blockSignals(false); //IMPORTANTE

            QTableWidgetItem* item5 =nullptr;
            item5 =new QTableWidgetItem;
            //item5->setText(recalc_s5(&s[2], &s[4]));
            item5->setText(recalc_s5((s+2), (s+4)));
            item5->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled); //blokada edycji #1. sposob
            ui->tableWidget->setItem(rowCount, 5, item5);

            ui->tableWidget->verticalHeader()->resizeSections(QHeaderView::ResizeToContents);

            j =0;
        }

        s[j] =stdString.c_str();
        ++j;
    }
}


void MainWindow::saveFieldsData()
{
    std::stringstream out;

    int rowCount =ui->tableWidget->rowCount();

    out <<(ui->comboBox_15a->currentText()).toStdString() <<"\n"; //#1

    out <<(ui->dateEdit_12b->date().toString("dd-MM-yyyy")).toStdString() <<"\n"; //#2
    out <<(ui->dateEdit_12a->date().toString("dd-MM-yyyy")).toStdString() <<"\n"; //#3
    out <<typDok <<"\n"; //#4
    out <<(nazwaDok).toStdString() <<"\n"; //#5
    out <<(ui->lineEdit_11a->text()).toStdString() <<"\n"; //#6

    out <<(sprzed2).toStdString() <<"\n"; //#7
    out <<(sprzed3).toStdString() <<"\n"; //#8
    out <<(sprzed4).toStdString() <<"\n"; //#9
    out <<(sprzed5).toStdString() <<"\n"; //#10
    out <<(sprzed6).toStdString() <<"\n"; //#11

    out <<(nab2).toStdString() <<"\n"; //#12
    out <<(nab3).toStdString() <<"\n"; //#13
    out <<(nab4).toStdString() <<"\n"; //#14
    out <<(nab5).toStdString() <<"\n"; //#15
    out <<(nab6).toStdString() <<"\n"; //#16

    //out <<(QString::number(ui->checkBox_14->isChecked())).toStdString() <<"\n"; //#17
    out <<(ui->checkBox_14->isChecked()) <<"\n"; //#17

    if (ui->checkBox_14->isChecked())
    {
        out <<(odb2).toStdString() <<"\n"; //#18
        out <<(odb3).toStdString() <<"\n"; //#19
        out <<(odb4).toStdString() <<"\n"; //#10
        out <<(odb5).toStdString() <<"\n"; //#21
        out <<(odb6).toStdString() <<"\n"; //#22
    }
    else
    {
        out <<"\n\n\n\n\n";
    }

    out <<(ui->comboBox_11b->currentText()).toStdString() <<"\n"; //#23
    out <<(ui->comboBox_15b->currentText()).toStdString() <<"\n"; //#24
    out <<(sprzed7).toStdString() <<"\n"; //#25

    for (int row =0; row< rowCount; ++row)
    {
        out <<(ui->tableWidget->item(row, 0)->text()).toStdString() <<"\n"; //#26

        std::string textField((ui->tableWidget->item(row, 1)->text()).toStdString());
        replaceAll(&textField, "\n", " ");
        out <<textField <<"\n"; //#27

        out <<(ui->tableWidget->item(row, 2)->text()).toStdString() <<"\n"; //#28
        out <<(ui->tableWidget->item(row, 3)->text()).toStdString() <<"\n"; //#29
        out <<(ui->tableWidget->item(row, 4)->text()).toStdString() <<"\n"; //#30
    }

    out <<"0" <<"\n"; //extra linia, zeby za szybko while getline sie nie konczyl

    File::saveFromStream(filePathTxt, &out);
}


void MainWindow::replaceAll(std::string* stdString, const std::string& from, const std::string& to)
{
    std::string::size_type pos =0; //to nie moj algorytm, znaleziony w necie

    while ((pos =(*stdString).find(from, pos))!=std::string::npos)
    {
        (*stdString).replace(pos, from.size(), to);
        pos+=to.size();
    }
}


void MainWindow::replaceLine(std::string* stdString, const int& row)
{
    replaceAll(stdString, "{miejsce}", (ui->comboBox_15a->currentText()).toStdString());
    replaceAll(stdString, "{data_wyst}", (ui->dateEdit_12b->date().toString("dd-MM-yyyy")).toStdString());
    replaceAll(stdString, "{data_sprz}", (ui->dateEdit_12a->date().toString("dd-MM-yyyy")).toStdString());
    replaceAll(stdString, "{nazwa_dok}", (wybranaNazwaDok).toStdString());
    replaceAll(stdString, "{nr_dok}", (ui->lineEdit_11a->text()).toStdString());

    replaceAll(stdString, "{sprzed}", (sprzed2).toStdString());
    replaceAll(stdString, "{sprzed_adres}", (sprzed3+" "+sprzed4+", "+sprzed5).toStdString());
    replaceAll(stdString, "{sprzed_NIP}", (sprzed6).toStdString());

    replaceAll(stdString, "{nab}", (nab2).toStdString());
    replaceAll(stdString, "{nab_adres}", (nab3+" "+nab4+", "+nab5).toStdString());
    replaceAll(stdString, "{nab_NIP}", (nab6).toStdString());

    if (ui->checkBox_14->isChecked())
    {
        if (odb2!="")
        {
            replaceAll(stdString, "{odb_n}", "Odbiorca:");
        }
        else
        {
            replaceAll(stdString, "{odb_n}", "");
        }

        if (odb3!="" || odb4!="" || odb5!="")
        {
            replaceAll(stdString, "{odb_adres_n}", "Adres:");
        }
        else
        {
            replaceAll(stdString, "{odb_adres_n}", "");
        }

        if (odb6!="")
        {
            replaceAll(stdString, "{odb_NIP_n}", "NIP:");
        }
        else
        {
            replaceAll(stdString, "{odb_NIP_n}", "");
        }

        replaceAll(stdString, "{odb}", (odb2).toStdString());
        replaceAll(stdString, "{odb_adres}", (odb3+" "+odb4+", "+odb5).toStdString());
        replaceAll(stdString, "{odb_NIP}", (odb6).toStdString());
    }
    else
    {
        replaceAll(stdString, "{odb_n}", "");
        replaceAll(stdString, "{odb_adres_n}", "");
        replaceAll(stdString, "{odb_NIP_n}", "");
        replaceAll(stdString, "{odb}", "");
        replaceAll(stdString, "{odb_adres}", "");
        replaceAll(stdString, "{odb_NIP}", "");
    }

    int dniDoZaplaty =ui->comboBox_11b->currentText().toInt();
    std::string dniTekst;
    if (dniDoZaplaty==1)
        dniTekst =" dzień do ";
    else
        dniTekst =" dni do ";
    replaceAll(stdString, "{termin}", std::to_string(dniDoZaplaty) +dniTekst+(ui->dateEdit_12b->date().addDays(dniDoZaplaty).toString("dd-MM-yyyy")).toStdString());
    replaceAll(stdString, "{sposob}", (ui->comboBox_15b->currentText()).toStdString());

    if (ui->comboBox_15b->currentText()=="gotówka")
    {
        replaceAll(stdString, "{nr_konta_n}", "");
        replaceAll(stdString, "{nr_konta}", "");
    }
    else
    {
        replaceAll(stdString, "{nr_konta_n}", "Nr konta:");
        replaceAll(stdString, "{nr_konta}", (sprzed7).toStdString());
    }

    if (row>=0) //inaczej sie wysypie
    {
        replaceAll(stdString, "{lp}", (ui->tableWidget->item(row, 0)->text()).toStdString());

        std::string textField((ui->tableWidget->item(row, 1)->text()).toStdString());
        replaceAll(&textField, "\n", "<br>");
        replaceAll(stdString, "{usluga}", textField);

        replaceAll(stdString, "{ilosc}", (ui->tableWidget->item(row, 2)->text()).toStdString());
        replaceAll(stdString, "{miara}", (ui->tableWidget->item(row, 3)->text()).toStdString());
        replaceAll(stdString, "{cena_j}", (ui->tableWidget->item(row, 4)->text()).toStdString());
        replaceAll(stdString, "{cena_c}", (ui->tableWidget->item(row, 5)->text()).toStdString());
    }

    replaceAll(stdString, "{cena_r}", (ui->lineEdit_6->text()).toStdString());
    replaceAll(stdString, "{slownie}", (Slownie::na_slownie((ui->lineEdit_6->text()).toStdString())).c_str());
}


void MainWindow::replaceFields(std::stringstream *in, std::stringstream *out)
{
    std::string stdString;
    int rowCount =ui->tableWidget->rowCount();
    int currLine =0;
    int repeatedLine =0;

    while (getline(*in, stdString))
    {
        if (stdString.find("<tr")!=std::string::npos) ++currLine;
        if (stdString.find("{lp}")!=std::string::npos
                || stdString.find("{usluga}")!=std::string::npos
                || stdString.find("{ilosc}")!=std::string::npos
                || stdString.find("{miara}")!=std::string::npos
                || stdString.find("{cena_j}")!=std::string::npos
                || stdString.find("{cena_c}")!=std::string::npos) repeatedLine =currLine;
    }

    (*in).clear();
    (*in).seekg(0, std::ios::beg);
    currLine =0;

    while (getline(*in, stdString))
    {
        if (stdString.find("<tr")!=std::string::npos) ++currLine;

        if (currLine< repeatedLine)
        {
            replaceLine(&stdString);
            (*out) <<stdString <<"\n";
        }
        else break;
    }

    //std::ios::seekdir cursor =(*in).seekg(0, std::ios::cur);

    for (int row= 0; row< rowCount; ++row)
    {
        (*in).clear();
        (*in).seekg(0, std::ios::beg);
        currLine =0;

        while (getline(*in, stdString))
        {
            if (stdString.find("<tr")!=std::string::npos) ++currLine;

            if (currLine==repeatedLine)
            {
                replaceLine(&stdString, row);
                (*out) <<stdString <<"\n";
            }
        }
    }

    (*in).clear();
    (*in).seekg(0, std::ios::beg);
    currLine =0;

    while (getline(*in, stdString))
    {
        if (stdString.find("<tr")!=std::string::npos) ++currLine;

        if  (currLine> repeatedLine)
        {
            replaceLine(&stdString);
            (*out) <<stdString <<"\n";
        }
    }

    (*in).clear();                  //nie wiem czy potrzeba
    (*in).seekg(0, std::ios::beg);  //nie wiem czy potrzeba
    (*out).clear();                 //nie wiem czy potrzeba
    (*out).seekg(0, std::ios::beg); //nie wiem czy potrzeba
}


void MainWindow::pdfAutoShow()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePathPdf));
}


void MainWindow::pdfAutoPrint()
{
    //view->page()->printToPdf(pdfSaveName, QPageLayout(QPageSize(QPageSize::A4), QPageLayout::Portrait, QMarginsF(20, 20, 20, 20)));

    page->printToPdf(filePathPdf, QPageLayout(QPageSize(QPageSize::A4), QPageLayout::Portrait, QMarginsF(20, 20, 20, 20)));
    connect(page, &QWebEnginePage::pdfPrintingFinished, this, &MainWindow::pdfAutoShow);
}


void MainWindow::on_pushButton_3_clicked()
{
    QString invoiceName(ui->lineEdit_11a->text());

    if (!normalizeName(invoiceName)) return;

    if (!availableName(filePathPdf))
    {
        if (QMessageBox::warning(this, "", "Uwaga.\n\nDokument PDF o podanym numerze już istnieje.\n\nZastąpić?", "OK", "Anuluj", "", 1, 1)==1) return;
    }

    //-----------------------------------------------------------------------
    //if (!view) view =new QWebEngineView();
    //view->load(QUrl(QStringLiteral("qrc:/template.html")));
    //view->resize(1024, 750);
    //view->show();

    delete page; //BRZYDKIE ROZWIAZANIE..., ale inaczej nie chce tworzyc zmienionych plikow pdf
    page =nullptr;

    if (!page) page =new QWebEnginePage();

    std::stringstream in;
    std::stringstream out;

    File::loadToStream("baza\\template_utf-8.html", &in);

    replaceFields(&in, &out);

    page->setHtml(out.str().c_str());
    connect(page, &QWebEnginePage::loadFinished, this, &MainWindow::pdfAutoPrint);

    out.clear();                  //nie wiem czy potrzeba
    out.seekg(0, std::ios::beg);  //nie wiem czy potrzeba

    File::saveFromStream(filePathHtml, &out);


/*
    std::ifstream in("baza\\template_utf-8.html");
    std::stringstream out;
    std::ofstream fileOut(filePathHtml.toStdString());

    if (!in.good())
    {
        QMessageBox::warning(0, "", "Nie można otworzyć pliku ze wzorcem druku.", "OK", "", "", 0, 0);
        return;
    }

    if (!fileOut.good())
    {
        QMessageBox::warning(0, "", "Nie można zapisać pliku wydruku.", "OK", "", "", 0, 0);
        return;
    }

    //-----------------------------------------------------------------------
    replaceFields(&in, &out);

    page->setHtml(out.str().c_str());
    connect(page, &QWebEnginePage::loadFinished, this, &MainWindow::pdfAutoPrint);

    out.clear();                  //nie wiem czy potrzeba
    out.seekg(0, std::ios::beg);  //nie wiem czy potrzeba

    fileOut <<out.str();

    in.close();
    fileOut.flush();
    fileOut.close();
*/

    saveFieldsData();
}


void MainWindow::alternativePreview()
{
    QString invoiceName(ui->lineEdit_11a->text());

    if (!normalizeName(invoiceName)) return;

    if (!availableName(filePathHtml))
    {
        if (QMessageBox::warning(this, "", "Uwaga.\n\nDokument HTML o podanym numerze już istnieje.\n\nZastąpić?", "OK", "Anuluj", "", 1, 1)==1) return;
    }

    //-----------------------------------------------------------------------
    std::stringstream in;
    std::stringstream out;

    File::loadToStream("baza\\template_utf-8.html", &in);

    replaceFields(&in, &out);

    (out).clear();                  //nie wiem czy potrzeba
    (out).seekg(0, std::ios::beg);  //nie wiem czy potrzeba

    File::saveFromStream(filePathHtml, &out);

/*
    std::ifstream in("baza\\template_utf-8.html");
    std::stringstream out;
    std::ofstream fileOut(filePathHtml.toStdString());

    if (!in.good())
    {
        QMessageBox::warning(0, "", "Nie można otworzyć pliku ze wzorcem druku.", "OK", "", "", 0, 0);
        return;
    }

    if (!fileOut.good())
    {
        QMessageBox::warning(0, "", "Nie można zapisać pliku wydruku.", "OK", "", "", 0, 0);
        return;
    }

    //-----------------------------------------------------------------------
    replaceFields(&in, &out);

    fileOut <<out.str();

    in.close();
    fileOut.flush();
    fileOut.close();
*/

    QDesktopServices::openUrl(QUrl::fromLocalFile(filePathHtml));

    saveFieldsData();
}

//=============================================================================================
//==MAIN MENU==================================================================================

void MainWindow::on_actionNowy_numer_dokumentu_triggered()
{
    on_pushButton_11_clicked();
}


void MainWindow::on_actionPodglad_wydruku_triggered()
{
    on_pushButton_3_clicked();
}


void MainWindow::on_actionAlternatywny_podglad_triggered()
{
    alternativePreview();
}


void MainWindow::on_actionZakoncz_triggered()
{
    if (ui->tableWidget->rowCount()> 0)
    {
        if (QMessageBox::warning(this, "", "Czy na pewno zakończyć pracę programu?", "OK", "Anuluj", "", 1, 1)==1)
        {
            return;
        }
    }

    this->destroy();
}


void MainWindow::on_actionQt_triggered()
{
    QMessageBox::aboutQt(this);
}


void MainWindow::on_actionInformacje_o_programie_triggered()
{
    QMessageBox::about(this, "Informacje o programie", "Program został napisany w oparciu o bibliotekę Qt 5.9.3");
}


void MainWindow::closeEvent(QCloseEvent* event)
{
    if (ui->tableWidget->rowCount()> 0)
    {
        if (QMessageBox::warning(this, "", "Czy na pewno zakończyć pracę programu?", "OK", "Anuluj", "", 1, 1)==1)
        {
            event->ignore();
            return;
        }
    }

    event->accept();
}






//=============================================================================================
//=============================================================================================
/*
//must be in a header, otherwise moc gets confused with missing vtable
class DeleteHighlightedItemWhenShiftDelPressedEventFilter : public QObject
{
     Q_OBJECT
protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

bool DeleteHighlightedItemWhenShiftDelPressedEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key::Key_Delete && keyEvent->modifiers() == Qt::ShiftModifier)
        {
            auto combobox = dynamic_cast<QComboBox *>(obj);
            if (combobox){
                combobox->removeItem(combobox->currentIndex());
                return true;
            }
        }
    }
    // standard event processing
    return QObject::eventFilter(obj, event);
}

myQComboBox->installEventFilter(new DeleteHighlightedItemWhenShiftDelPressedEventFilter);
*/


/*
    //popup menu do usuwania elementow z listy comboboxa - nie wiem jak to zrobic zeby dzialalo
    //==w KONSTRUKTORZE============================================================================================
    //ui->comboBox_0->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->comboBox_0->setContextMenuPolicy(Qt::CustomContextMenu);

    m_deleteAction = new QAction(tr("Delete item"), this);
    connect(m_deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));
    connect(ui->comboBox_0, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));


void MainWindow::contextMenuRequest(QPoint pnt)
{
    QMenu* menu = ui->comboBox_0->lineEdit()->createStandardContextMenu();
    menu->addSeparator();
    menu->addAction(m_deleteAction);
    menu->popup(pnt); //podobno tak nie dziala w widows vista
    //menu->popup(QCursor::pos()); //a tak dziala w windows vista
    connect(menu, SIGNAL(aboutToHide()), menu, SLOT(deleteLater()));
}
*/



