#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QComboBox>
#include <QRegExp>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QWebEngineView>
#include <sstream>
//#include <fstream>
#include "file.h"
#include "slownie.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow* const& getMainUi();

    void setMainNabywcaLines(const QString& n1, const QString& n2, const QString& n3,
                             const QString& n4, const QString& n5, const QString& n6);

    void setMainOdbiorcaLines(const QString& o1, const QString& o2, const QString& o3,
                              const QString& o4, const QString& o5, const QString& o6);

    void setMainUstawieniaLines(const QString& u2, const QString& u3, const QString& u4, const QString& u5,
                                const QString& u6, const QString& u7, const QString& u11, const QString &u12);

    void loadComboBox_13(); //powiazane z Nabywca
    void loadComboBox_14(); //powiazane z Odbiorca
    void loadSettings_15(); //powiazane z Ustawienia

private slots:
    void on_comboBox_11b_activated(int index);
    void on_comboBox_15a_activated(int index);
    void on_comboBox_15b_activated(int index);
    void on_comboBox_3_activated(int index);

    void on_checkBox_12_clicked(bool checked);

    //--Table--------------------------------------
    void on_pushButton_1_clicked();
    void on_tableWidget_cellChanged(int row, int column);
    void on_pushButton_2_clicked();
    void on_comboBox_0_activated(int index);

    //--Nowa---------------------------------------
    void on_pushButton_11_clicked();

    //--Archiwum-----------------------------------
    void on_pushButton_12_clicked();

    //--Nabywca------------------------------------
    void on_pushButton_13_clicked();
    void on_comboBox_13_activated(int index);

    //--Odbiorca-----------------------------------
    void on_pushButton_14_clicked();
    void on_comboBox_14_activated(int index);

    //--Ustawienia---------------------------------
    void on_pushButton_15_clicked();
    void setWybranaNazwaDok();

    //--Drukuj-------------------------------------
    void on_pushButton_3_clicked();

    //--Menu---------------------------------------
    void on_actionNowy_numer_dokumentu_triggered();
    void on_actionPodglad_wydruku_triggered();
    void on_actionAlternatywny_podglad_triggered();
    void on_actionZakoncz_triggered();
    void on_actionQt_triggered();
    void on_actionInformacje_o_programie_triggered();
    void closeEvent(QCloseEvent* event);

private:
    Ui::MainWindow *ui;

    QWebEngineView* view;
    QWebEnginePage* page;
    QString filePathPdf;
    QString filePathHtml;
    QString filePathTxt;

    //--Nabywca------------------------------------
    QString nab1;
    QString nab2;
    QString nab3;
    QString nab4;
    QString nab5;
    QString nab6;

    //--Odbiorca-----------------------------------
    QString odb1;
    QString odb2;
    QString odb3;
    QString odb4;
    QString odb5;
    QString odb6;

    //--Ustawienia---------------------------------
    QString sprzed2;
    QString sprzed3;
    QString sprzed4;
    QString sprzed5;
    QString sprzed6;
    QString sprzed7;
    int typDok;
    QString nazwaDok;
    QString wybranaNazwaDok;

    //--Universal----------------------------------
    void loadComboBoxU(QComboBox* box, const QString& from);
    void saveComboBoxU(QComboBox* box, const QString& to, const int& c);
    void reorderComboBoxU(QComboBox* box, const int& index);
    void loadLastSettings();
    void saveLastSettings();

    //--Table--------------------------------------
    double dSumTotal;
    QString recalc_s5(QString *s2, QString *s4);

    //--Nowy numer---------------------------------
    bool availableName(const QString& filePath);
    bool normalizeName(QString name);

    //--Print--------------------------------------
    void loadFieldsData(const QUrl& filePath);
    void saveFieldsData();
    void replaceAll(std::string* stdString, const std::string& from, const std::string& to);
    void replaceLine(std::string* stdString, const int& row =-1);
    void replaceFields(std::stringstream *in, std::stringstream *out);

    void pdfAutoShow();
    void pdfAutoPrint();

    void alternativePreview();

    QLinearGradient grad1;
    QPalette palette1;
};

extern MainWindow* mainWindowPtr;

#endif // MAINWINDOW_H
