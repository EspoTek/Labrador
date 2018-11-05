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

constexpr uint8_t addressBitStreamLength = 9;

class i2cDecoder : public QObject
{
    Q_OBJECT
public:
    explicit i2cDecoder(isoBuffer* sda_in, isoBuffer* scl_in);
	// misc
    isoBuffer* sda;
	isoBuffer* scl;

	// State vars
	uint8_t currentSdaValue = 0;
	uint8_t previousSdaValue = 0;
	uint8_t currentSclValue = 0;
	uint8_t previousSclValue = 0;
    uint64_t serialPtr_bit = 0;
	transmissionState state = transmissionState::unknown;

	// Data Transmission
	uint8_t currentBitIndex = 0;
    uint16_t addressBitStream;
	uint8_t currentDataByte = 0;

	// Member functions
	void updateBitValues();
	void runStateMachine();
    void run(); 
    int serialDistance(isoBuffer* buffer);
	edge edgeDetection(uint8_t current, uint8_t prev);
	void decodeAddress(edge sdaEdge, edge sclEdge);
	void decodeData(edge sdaEdge, edge sclEdge);
	void startCondition();
	void stopCondition();
	void dataByteCompleted(uint8_t byte, bool ACKed);	
    void reset();

signals:
public slots:

};

} // Namespace i2c

#endif // UARTSTYLEDECODER_H
