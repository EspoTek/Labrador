#ifndef I2CDECODER_H
#define I2CDECODER_H

#include <QObject>
#include "isobuffer.h"

namespace i2c
{

enum class transmissionState: uint8_t
{
	unknown,
	idle,
	address,
	data	
};

enum class edge: uint8_t
{
	rising,
	falling,
	held_high,
	held_low
};

class i2cDecoder : public QObject
{
    Q_OBJECT
public:
    explicit i2cDecoder(isoBuffer* sda_in, isoBuffer* scl_in, uint32_t clockRate);
private:
	// misc
    isoBuffer* sda;
	isoBuffer* scl;
	uint32_t stepSize;

	// State vars
	uint8_t currentSdaValue;
	uint8_t previousSdaValue;
	uint8_t currentSclValue;
	uint8_t previousSclValue;
    uint64_t serialPtr_bit = 0;
	transmissionState state = transmissionState::unknown;

	// Data Transmission
	uint8_t currentBitIndex;
	uint16_t address;
	uint8_t currentDataByte;
	std::vector<uint8_t> dataBytes;

	// Member functions
	void updateBitValues();
	void setStepSize(uint32_t clockRate);
	void runStateMachine();
    void run(); 
    int serialDistance(isoBuffer* buffer);
	edge edgeDetection(uint8_t current, uint8_t prev);
	void decodeAddress(edge sdaEdge, edge sclEdge);
	void decodeData(edge sdaEdge, edge sclEdge);
signals:
public slots:

};

} // Namespace i2c

#endif // UARTSTYLEDECODER_H
