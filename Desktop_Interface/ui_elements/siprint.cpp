#include "siprint.h"

siprint::siprint(const char *unitsInit, double valInit)
: value(valInit)
{
    strncpy(units, unitsInit, 6);
}

char* siprint::printVal(){
    std::string suffix;
    bool negative = (value < 0);

    char* tempStringPtr = printString;
    if (negative)
    {
        printString[0] = '-';
        tempStringPtr++;
    }

    if (abs(value) >= 1000000000000000000)
    {
        sprintf(tempStringPtr, "Inf %s", units);
    }
    else if (abs(value) >= 1000000)
    {
        sprintf(tempStringPtr, "%.2fM%s", abs(value)/1000000, units);
    }
    else if (abs(value) >= 1000)
    {
        sprintf(tempStringPtr, "%.2fk%s",  abs(value)/1000, units);
    }
    else if (abs(value) >= 1)
    {
        sprintf(tempStringPtr, "%.2f%s",  abs(value), units);
    }
    else if (abs(value) >= 0.001)
    {
        sprintf(tempStringPtr, "%.2fm%s", abs(value)*1000, units);
    }
    else if (abs(value) >= 0.000001)
    {
        sprintf(tempStringPtr, "%.2fu%s",  abs(value)*1000000, units);
    }
    else if (abs(value) >= 0.000000001)
    {
        sprintf(tempStringPtr, "%.2fn%s",  abs(value)*1000000000, units);
    }
    else if (abs(value) >= 0.000000000001)
    {
        sprintf(tempStringPtr, "%.2fp%s",  abs(value)*1000000000000, units);
    }
    else if (abs(value) >= 1)
    {
        sprintf(tempStringPtr, "%.2f%s",  abs(value), units);
    }

    return printString;
}
