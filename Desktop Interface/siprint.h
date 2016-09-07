#ifndef SIPRINT_H
#define SIPRINT_H

#include <string.h>
#include <QDebug>

class siprint
{
public:
    siprint(char *unitsInit, double valInit);
    char* printVal();
    char units[6];
    double value;
private:
    char printString[160];

};

#endif // SIPRINT_H
