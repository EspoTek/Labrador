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

#include "espocombobox.h"

espoComboBox::espoComboBox(QWidget *parent) : QComboBox(parent)
{

}


void espoComboBox::readWaveformList(void)
{
    //This code gets the name of the current directory, regardless of platform.
    //This is so the interface knows where to find the waveform data
    //QDir *dir = new QDir();
    //qDebug() << dir->currentPath();
#ifdef PLATFORM_ANDROID
    QFile qt_list("assets:/waveforms/_list.wfl");
    bool success = qt_list.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!success){
        qFatal("Could not load _list.wfl");
    }

    char nameBuffer[255];
    QStringList *newNames = new QStringList();

    while (!qt_list.atEnd()) {
        QByteArray line = qt_list.readLine();
        strcpy(nameBuffer, line.data());
        strtok(nameBuffer, "\n\r");
        newNames->append(nameBuffer);
        qDebug() << nameBuffer;
    }
    this->addItems(*(newNames));
    delete newNames;
    qt_list.close();
#else
    QString dirString = QCoreApplication::applicationDirPath();
    dirString.append("/waveforms/_list.wfl");
    QByteArray array = dirString.toLocal8Bit();
    char* buffer = array.data();
    //qDebug() << buffer;

    qDebug() << "Attempting to open" << dirString;

    FILE *listPtr = fopen(buffer, "r");
    QStringList *newNames = new QStringList();
    char nameBuffer[255];

    if(listPtr == NULL){
        qFatal("Could not load _list.wfl");
    }

    while (fgets(nameBuffer,256,listPtr) !=NULL){
        qDebug() << "nameBuffer = " << nameBuffer;
        strtok(nameBuffer, "\n\r");
        newNames->append(nameBuffer);
    }
    this->addItems(*(newNames));
    delete newNames;

    fclose(listPtr);
#endif
    qDebug() << "List loaded!!";
}
