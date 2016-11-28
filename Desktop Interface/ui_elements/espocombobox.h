#ifndef ESPOCOMBOBOX_H
#define ESPOCOMBOBOX_H

#include <QWidget>
#include <QComboBox>
#include <QDebug>
#include <QDir>
#include <QFile>
#include "platformspecific.h"

//espoComboBox is a combo box that reads its contents externally from the waveforms file.

class espoComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit espoComboBox(QWidget *parent = 0);
    void readWaveformList(void);
private:
signals:

public slots:
};

#endif // ESPOCOMBOBOX_H
