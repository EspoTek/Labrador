#include "uartstyledecoder.h"

uartStyleDecoder::uartStyleDecoder(QObject *parent_in) : QObject(parent_in)
{
    parent = (isoBuffer *) parent_in;

    updateTimer = new QTimer();
    updateTimer->setTimerType(Qt::PreciseTimer);
    updateTimer->start(CONSOLE_UPDATE_TIMER_PERIOD);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateConsole()));

    serialBuffer = new isoBufferBuffer(SERIAL_BUFFER_LENGTH*2);

    if(parent->channel == 1) console = parent->console1;
    else if(parent->channel == 2) console = parent->console2;
    else qFatal("Nonexistant console requested in uartStyleDecoder::serialDecode");
}


void uartStyleDecoder::updateConsole(){
    if(!newUartSymbol) return;
    //qDebug() << numCharsInBuffer;

    console->setPlainText(QString::fromLocal8Bit(serialBuffer->get(numCharsInBuffer), numCharsInBuffer));
    if(parent->serialAutoScroll){
        //http://stackoverflow.com/questions/21059678/how-can-i-set-auto-scroll-for-a-qtgui-qtextedit-in-pyqt4   DANKON
        QTextCursor c =  console->textCursor();
        c.movePosition(QTextCursor::End);
        console->setTextCursor(c);
        // txtedit.ensureCursorVisible(); // you might need this also
    }
    newUartSymbol = false;
    //charPos = 0;
}

void uartStyleDecoder::serialDecode(double baudRate)
{
    /*if(stopDecoding){
        return;
    }*/
    double dist_seconds = (double)serialDistance()/(parent->sampleRate_bit);
    double bitPeriod_seconds = 1/baudRate;

    //Used to check for wire disconnects.  You should get at least one "1" for a stop bit.
    bool allZeroes = true;

    while(dist_seconds > (bitPeriod_seconds + SERIAL_DELAY)){
        //Read next uart bit
        unsigned char uart_bit = getNextUartBit();
        if(uart_bit) allZeroes = false;

        //Process it
        if(uartTransmitting){
            decodeNextUartBit(uart_bit);
        } else{
            uartTransmitting = (uart_bit == 1) ? false : true;  //Uart starts transmitting after start bit (logic low).
            jitterCompensationNeeded = true;
        }
        //Update the pointer, accounting for jitter
        updateSerialPtr(baudRate, uart_bit);
        //Calculate stopping condition
        dist_seconds = (double)serialDistance()/(parent->sampleRate_bit);
    }

    //Not a single stop bit, or idle bit, in the whole stream.  Wire must be disconnected.
    if(allZeroes){
        qDebug() << "Wire Disconnect detected!";
        wireDisconnected(parent->channel);
        parent->stopDecoding = true;
        updateTimer->stop();
    }
}

int uartStyleDecoder::serialDistance()
{
    int back_bit = parent->back * 8;
    int bufferEnd_bit = parent->bufferEnd * 8;
    if(back_bit >= serialPtr_bit){
        return back_bit - serialPtr_bit;
    }else return bufferEnd_bit - serialPtr_bit + back_bit;
}

void uartStyleDecoder::updateSerialPtr(double baudRate, unsigned char current_bit)
{
    if(jitterCompensationNeeded && uartTransmitting){
        jitterCompensationNeeded = jitterCompensationProcedure(baudRate, current_bit);
    }

    int distance_between_bits = (parent->sampleRate_bit)/baudRate;
    if(uartTransmitting){
        serialPtr_bit += distance_between_bits;
    } else serialPtr_bit += (distance_between_bits - 1);  //Less than one baud period so that it will always see that start bit.

    if (serialPtr_bit > (parent->bufferEnd * 8)){
        serialPtr_bit -= (parent->bufferEnd * 8);
    }
}

unsigned char uartStyleDecoder::getNextUartBit(){
    int coord_byte = serialPtr_bit/8;
    int coord_bit = serialPtr_bit - (8*coord_byte);
    unsigned char dataByte = parent->buffer[coord_byte];
    unsigned char mask = (1 << coord_bit);
    return ((dataByte & mask) ? 1 : 0);
}

void uartStyleDecoder::decodeNextUartBit(unsigned char bitValue)
{
    if(dataBit_current == dataBit_max){
        if(numCharsInBuffer<SERIAL_BUFFER_LENGTH) numCharsInBuffer++;
        serialBuffer->add(currentUartSymbol);
        currentUartSymbol = 0;
        dataBit_current = 0;
        uartTransmitting = false;
        newUartSymbol = true;
        return;
    }
    //else
    currentUartSymbol |= (bitValue << dataBit_current);
    dataBit_current++;
}

//This function compensates for jitter by, when the current bit is a "1", and the last bit was a zero, setting the pointer
//to the sample at the midpoint between this bit and the last.
bool uartStyleDecoder::jitterCompensationProcedure(double baudRate, unsigned char current_bit){

    //We only run when the current bit is a "1", to prevent slowdown when there are long breaks between transmissions.
    if(current_bit == 0){
        return true;
    }

    //Can't be bothered dealing with the corner case where the serial pointer is at the very start of the buffer.
    //Just return and try again next time.
    int left_coord = serialPtr_bit - (parent->sampleRate_bit)/baudRate;
    //qDebug() << "left_coord =" << left_coord;
    if (left_coord < 0){
        return true; //Don't want to read out of bounds!!
    }

    //The usual case, when transmitting anyway.
    unsigned char left_byte = (parent->buffer[left_coord/8] & 0xff);
    //Only run when a zero is detected in the leftmost symbol.
    if(left_byte != 255){
        //Step back, one sample at a time, to the 0->1 transition point
        unsigned char temp_bit = 1;
        while(temp_bit){
            temp_bit = getNextUartBit();
            serialPtr_bit--;
        }
        //Jump the pointer forward by half a uart bit period, and return "done!".
        serialPtr_bit += (parent->sampleRate_bit/baudRate)/2;
        return false;
    }

    return true;
}
