#ifndef I2CDECODER_H
#define I2CDECODER_H

#include <QObject>
#include "isobuffer.h"

class i2cDecoder : public QObject
{
    Q_OBJECT
public:
    explicit i2cDecoder(isoBuffer* sda_in, isoBuffer* scl_in);
    void run(); 
    int serialDistance(isoBuffer* buffer);
private:
    isoBuffer* sda;
	isoBuffer* scl;
	uint8_t currentSdaValue;
	uint8_t currentSclValue;
    int serialPtr_bit = 0;
	void updateBitValues();
signals:
public slots:
};

#endif // UARTSTYLEDECODER_H
