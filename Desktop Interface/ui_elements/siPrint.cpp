#include "siprint.h"

siprint::siprint(char *unitsInit, double valInit)
{
    strncpy(units, unitsInit, 6);
    value = valInit;
}

char* siprint::printVal(){
    double tempValue = value;
    bool negative = false;

    if (tempValue == 0){
        sprintf(printString, "0%s", units);
        return printString;
    }
    if (value < 0){
        negative = true;
        tempValue *= -1;
    }
    if (tempValue >= 1000000000000000000){
        sprintf(printString, "Inf %s", units);
        return printString;
    }


    if (tempValue >= 1000000){
        sprintf(printString, "%c%.2fM%s", (negative ? '-':' '), tempValue/1000000, units);
        return printString;
    }

    if (tempValue >= 1000){
        sprintf(printString, "%c%.2fk%s", (negative ? '-':' '), tempValue/1000, units);
        return printString;
    }

    if (tempValue >= 1){
        sprintf(printString, "%c%.2f%s", (negative ? '-':' '), tempValue, units);
        return printString;
    }

    if (tempValue >= 0.001){
        sprintf(printString, "%c%.2fm%s", (negative ? '-' : ' '), tempValue*1000, units);
        return printString;
    }

    if (tempValue >= 0.000001){
        sprintf(printString, "%c%.2fu%s", (negative ? '-':' '), tempValue*1000000, units);
        return printString;
    }

    if (tempValue >= 0.000000001){
        sprintf(printString, "%c%.2fn%s", (negative ? '-':' '), tempValue*1000000000, units);
        return printString;
    }

    if (tempValue >= 0.000000000001){
        sprintf(printString, "%c%.2fp%s", (negative ? '-':' '), tempValue*1000000000000, units);
        return printString;
    }


    sprintf(printString, "0%s", units);
    return printString;
}
