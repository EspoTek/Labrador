#ifndef ESPOCOMBOBOX_H
#define ESPOCOMBOBOX_H

#include <QWidget>
#include <QComboBox>
#include <QDebug>
#include <QDir>
#include <QFile>

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
