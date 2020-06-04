#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <sstream>


class File
{
public:
    static void copyExcept(const QString& from, const QString& to, const QString& except ="");

    static bool remCompany(bool atn, const QString& toRemove, const QString& origin, const QString& tmpNew, const QString& tmpNewCopy);

    static bool addCompany(bool atn, const QString& t1, const QString& t2, const QString& t3, const QString& t4,
                           const QString& t5, const QString& t6, const QString& t7, const QString& origin, const QString& tmpNew);

    static void loadToStream(const QString& from, std::stringstream* in); // FROM taking IN>> | TO sending OUT<<

    static void saveFromStream(const QString& to, std::stringstream* out); // FROM taking IN>> | TO sending OUT<<

    static void loadSelectedToStream(const QString& from, std::stringstream* in, const QString& selected);
};

#endif // FILE_H
