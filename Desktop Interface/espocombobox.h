#ifndef ESPOCOMBOBOX_H
#define ESPOCOMBOBOX_H

#include <QWidget>
#include <QComboBox>
#include <QDebug>

class espoComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit espoComboBox(QWidget *parent = 0);
    void readWaveformList(void);
signals:

public slots:
};

#endif // ESPOCOMBOBOX_H
