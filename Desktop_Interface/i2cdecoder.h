#ifndef I2CDECODER_H
#define I2CDECODER_H

#include "isobuffer.h"
#include "isobufferbuffer.h"

#include <QObject>
#include <QTimer>
#include <mutex>

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
constexpr uint8_t dataBitStreamLength = 9;
constexpr uint32_t I2C_BUFFER_LENGTH = 4096;

class i2cDecoder : public QObject
{
    Q_OBJECT
public:
    explicit i2cDecoder(isoBuffer* sda_in, isoBuffer* scl_in, QPlainTextEdit* console_in);
    ~i2cDecoder();
	// misc
    isoBuffer* sda;
	isoBuffer* scl;
    QPlainTextEdit* console;
    isoBufferBuffer* serialBuffer = nullptr;
    std::mutex mutex;
    QTimer *updateTimer;

	// State vars
	uint8_t currentSdaValue = 0;
	uint8_t previousSdaValue = 0;
	uint8_t currentSclValue = 0;
	uint8_t previousSclValue = 0;
    uint64_t serialPtr_bit = 0;
	transmissionState state = transmissionState::unknown;
    bool consoleStateInvalid;

	// Data Transmission
	uint8_t currentBitIndex = 0;
    uint16_t currentBitStream;

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
    void reset();
signals:
public slots:
    void updateConsole();
};

} // Namespace i2c

#endif // UARTSTYLEDECODER_H
