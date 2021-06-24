#ifndef SIPRINT_H
#define SIPRINT_H

#include <string.h>
#include <QDebug>

//siprint just prints values with their SI prefix.
//For example, it would print the number 1000 and unit V as "1kV".
class siprint
{
public:
    siprint(const char *unitsInit, double valInit);
    char* printVal();
    char units[6];
    double value;
private:
    char printString[160];
};

#endif // SIPRINT_H
