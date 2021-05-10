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

#ifndef SIPRINT_H
#define SIPRINT_H

#include <string.h>
#include <QDebug>

//siprint just prints values with their SI prefix.
//For example, it would print the number 1000 and unit V as "1kV".
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
