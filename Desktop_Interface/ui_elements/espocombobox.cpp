#include "espocombobox.h"

espoComboBox::espoComboBox(QWidget *parent) : QComboBox(parent)
{

}

void espoComboBox::readWaveformList(void)
{
#ifdef PLATFORM_ANDROID
    QFile file("assets:/waveforms/_list.wfl");
#else
    QString path = QCoreApplication::applicationDirPath();
    QFile file(path.append("/waveforms/_list.wfl"));
#endif

    qDebug() << "opening" << file.fileName();
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qFatal("could not open %s", qUtf8Printable(file.fileName()));

    QStringList newNames;
    while (!file.atEnd())
        newNames.append(file.readLine().trimmed());
    this->addItems(newNames);
    file.close();
}
