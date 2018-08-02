#ifndef I2CDECODER_H
#define I2CDECODER_H

#include <QObject>
#include "isobuffer.h"

class i2cDecoder : public QObject
{
    Q_OBJECT
public:
    explicit i2cDecoder(isoBuffer* sda_in, isoBuffer* scl_in, uint32_t clockRate);
private:
    isoBuffer* sda;
	isoBuffer* scl;
	uint8_t currentSdaValue;
	uint8_t currentSclValue;
    uint64_t serialPtr_bit = 0;
	void updateBitValues();
	uint32_t stepSize;
	void setStepSize(uint32_t clockRate);
	void runStateMachine();
    void run(); 
    int serialDistance(isoBuffer* buffer);
signals:
public slots:
};

#endif // UARTSTYLEDECODER_H
