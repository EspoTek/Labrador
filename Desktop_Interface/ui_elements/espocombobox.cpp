#include "espocombobox.h"

espoComboBox::espoComboBox(QWidget *parent) : QComboBox(parent)
{

}


void espoComboBox::readWaveformList()
{
    const QStringList potentialDirs = {
#ifdef PLATFORM_ANDROID
        "assets:",
#else
       QCoreApplication::applicationDirPath(),
#endif
       ":/", // fall back to builtin
    };

    QString filename;
    for (const QString &dir : potentialDirs) {
        const QString potential = dir + "/waveforms/_list.wfl";
        if (QFileInfo::exists(potential)) {
            filename = potential;
            break;
        }
    }
    if (filename.isEmpty()) {
        qWarning() << "Failed to find a waveform list!";
        return;
    }

    QFile qt_list(filename);
    bool success = qt_list.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!success){
        qWarning("Could not load _list.wfl");
        return;
    }

    QStringList newNames;

    while (!qt_list.atEnd()) {
        this->addItem(qt_list.readLine().trimmed());
    }
    qt_list.close();

    qDebug() << "List loaded!!";
}
