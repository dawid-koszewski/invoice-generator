#include <QApplication>
#include "mainwindow.h"
#include "nabywca.h"
#include "odbiorca.h"
#include "ustawienia.h"

MainWindow* mainWindowPtr =nullptr;
Nabywca* nabywcaPtr =nullptr;
Odbiorca* odbiorcaPtr =nullptr;
Ustawienia* ustawieniaPtr =nullptr;


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    //QTextCodec::setCodecForLocale(QTextCodec::codecForUtfText("UTF-8"));
    //QTextCodec::setCodecForLocale(QTextCodec::codecForHtml("UTF-8"));
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));


    mainWindowPtr =new MainWindow; //mainWindowPtr->setAttribute(Qt::WA_DeleteOnClose);
    mainWindowPtr->show();



    int ret =a.exec();

    delete nabywcaPtr;
    nabywcaPtr =nullptr;

    delete odbiorcaPtr;
    odbiorcaPtr =nullptr;

    delete ustawieniaPtr;
    ustawieniaPtr =nullptr;

    delete mainWindowPtr;
    mainWindowPtr =nullptr;


    return ret;
}
