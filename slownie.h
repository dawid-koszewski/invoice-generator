#ifndef SLOWNIE_H
#define SLOWNIE_H

#include <string>

class Slownie
{
public:
    static std::string na_slownie(std::string liczebnik);

private:
    static std::string zamiana(std::string ccc_input, std::string nazwa);
};

#endif // SLOWNIE_H
