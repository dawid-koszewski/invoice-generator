#include "file.h"


void File::copyExcept(const QString& from, const QString& to, const QString& except)
{
    QFile fileFrom(from);
    if (!fileFrom.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(0, "", "Nie można otworzyć pliku bazy danych:\n\n"+from, "OK", "", "", 0, 0);
        return;
    }

    QFile fileTo(to);
    if (!fileTo.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(0, "", "Nie można zapisać pliku bazy danych:\n\n"+to, "OK", "", "", 0, 0);
        return;
    }

    QTextStream in (&fileFrom);
    in.setCodec("UTF-8");

    QTextStream out (&fileTo);
    out.setCodec("UTF-8");
    //-----------------------------------------------
    if (except=="")
    {
        out <<in.readAll();
    }
    else
    {
        QString lineIn;
        int linia =0;

        while (!in.atEnd())
        {
            lineIn =in.readLine();
            ++linia;

            if (linia%7==1 && lineIn==except)
            {
                for (int i =0; i< 6; ++i)
                {
                    in.readLine();
                    ++linia;
                }
            }
            else out <<lineIn <<endl;
        }
    }
    //-----------------------------------------------
    fileFrom.close();
    fileTo.flush();
    fileTo.close();
}


bool File::remCompany(bool atn, const QString& toRemove, const QString& origin, const QString& tmpNew, const QString& tmpNewCopy)
{
    if (atn==false)
    {
        copyExcept(origin, tmpNewCopy);
    }
    else
    {
        copyExcept(tmpNew, tmpNewCopy);
    }

    copyExcept(tmpNewCopy, tmpNew, toRemove);

    return true;
}


bool File::addCompany(bool atn, const QString& t1, const QString& t2, const QString& t3, const QString& t4,
                      const QString& t5, const QString& t6, const QString& t7, const QString& origin, const QString& tmpNew)
{
    if (atn==false)
    {
        copyExcept(origin, tmpNew);
    }

    QFile fileTo(tmpNew);
    if (!fileTo.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        QMessageBox::warning(0, "", "Nie można zapisać pliku bazy danych:\n\n"+tmpNew, "OK", "", "", 0, 0);
        return true; //bo tmpNew jest juz utworzony, chwilowo nie mozna go otworzyc... false spowoduje nadpisanie ewentualnych wczesniejszych zmian
    }

    QTextStream out (&fileTo);
    out.setCodec("UTF-8"); //QTextStream konwertuje Latin1->Unicode->Latin1 - czyli bez zmian

    out <<t1 <<endl;
    out <<t2 <<endl;
    out <<t3 <<endl;
    out <<t4 <<endl;
    out <<t5 <<endl;
    out <<t6 <<endl;
    out <<t7 <<endl;

    fileTo.flush();
    fileTo.close();

    return true;
}


void File::loadToStream(const QString& from, std::stringstream* in) // FROM taking IN>> | TO sending OUT<<
{
    QFile fileFrom(from);
    if (!fileFrom.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(0, "", "Nie można otworzyć pliku bazy danych:\n\n"+from, "OK", "", "", 0, 0);
        return;
    }

    QTextStream tmpIn (&fileFrom);
    tmpIn.setCodec("UTF-8");

    (*in) <<tmpIn.readAll().toStdString();

    fileFrom.close();
}


void File::saveFromStream(const QString& to, std::stringstream* out) // FROM taking IN>> | TO sending OUT<<
{
    QFile fileTo(to);
    if (!fileTo.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(0, "", "Nie można zapisać pliku bazy danych:\n\n"+to, "OK", "", "", 0, 0);
        return;
    }

    QTextStream tmpOut (&fileTo);
    tmpOut.setCodec("Latin1"); //QTextStream konwertuje Latin1->Unicode->Latin1 - czyli bez zmian

    tmpOut <<(*out).str().c_str();

    fileTo.flush();
    fileTo.close();
}


void File::loadSelectedToStream(const QString& from, std::stringstream* in, const QString& selected) // FROM taking IN>> | TO sending OUT<<
{
    QFile fileFrom(from);
    if (!fileFrom.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(0, "", "Nie można otworzyć pliku bazy danych:\n\n"+from, "OK", "", "", 0, 0);
        return;
    }

    QTextStream tmpIn (&fileFrom);
    tmpIn.setCodec("UTF-8");

    QString lineIn;
    int linia =0;

    while (!tmpIn.atEnd())
    {
        lineIn =tmpIn.readLine();
        ++linia;

        if (linia%7==1 && lineIn==selected)
        {
            (*in) <<lineIn.toStdString() <<"\n";

            for (int i =0; i< 5; ++i)
            {
                (*in) <<tmpIn.readLine().toStdString() <<"\n";
                ++linia;
            }

            fileFrom.close();
            return;
        }
    }

    fileFrom.close();
}
