// Copyright (C) 2017, 2018, 2019, 2020, 2021 Christopher Paul Esposito
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
