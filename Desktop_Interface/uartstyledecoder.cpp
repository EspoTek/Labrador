#include "uartstyledecoder.h"

uartStyleDecoder::uartStyleDecoder(QObject *parent_in) : QObject(parent_in)
{
    qDebug() << "uartStyleDecoder() checkpoint 1";
    parent = (isoBuffer *) parent_in;

    qDebug() << "uartStyleDecoder() checkpoint 2";
    updateTimer = new QTimer();
    updateTimer->setTimerType(Qt::PreciseTimer);
    updateTimer->start(CONSOLE_UPDATE_TIMER_PERIOD);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateConsole()));

    qDebug() << "uartStyleDecoder() checkpoint 3";
    serialBuffer = new isoBufferBuffer(SERIAL_BUFFER_LENGTH*2);
}


void uartStyleDecoder::updateConsole(){
    if(!newUartSymbol) return;
    qDebug() << numCharsInBuffer;

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
    double dist_seconds = (double)serialDistance()/(parent->sampleRate_bit);
    double bitPeriod_seconds = 1/baudRate;

    if(parent->channel == 1) console = parent->console1;
    else if(parent->channel == 2) console = parent->console2;
    else qFatal("Nonexistant console requested in uartStyleDecoder::serialDecode");


    while(dist_seconds > (bitPeriod_seconds + SERIAL_DELAY)){
        //Read next uart bit
        unsigned char uart_bit = getNextUartBit();
        //Process it
        if(uartTransmitting){
            decodeNextUartBit(uart_bit);
            //qDebug() << "uart_bit = " << uart_bit;
        } else{
            uartTransmitting = (uart_bit==1) ? false : true;
            jitterCompensationNeeded = true;
            //if(uartTransmitting)  qDebug() << "Decoding symbol!";
        }
        //Update the pointer, accounting for jitter
        updateSerialPtr(baudRate, uart_bit);
        //Calculate stopping condition
        dist_seconds = (double)serialDistance()/(parent->sampleRate_bit);
    }
    //qDebug() << "\n\n\n\n\n";
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
        //qDebug() << "JitterCompensation Needed?" << jitterCompensationNeeded;
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

bool uartStyleDecoder::jitterCompensationProcedure(double baudRate, unsigned char current_bit){

    if(current_bit !=0){
        //qDebug() << "Current bit not zero!!";
        return true;
    }

    int left_coord = serialPtr_bit - (parent->sampleRate_bit)/baudRate;
    if (left_coord < 0){
        return true; //Don't want to read out of bounds!!
    }

    unsigned char left_byte = (parent->buffer[left_coord/8] & 0xff);
    //qDebug() << "current_bit" << current_bit;
    //qDebug() << "left_byte" << left_byte;

    if(left_byte > 0){
        //qDebug() << "Recalibration Opportunity";
        unsigned char temp_bit = 0;
        //Go back to 1-0 transition point
        while(!temp_bit){
            temp_bit = getNextUartBit();
            serialPtr_bit--;
        }
        //Jump by half a uart bit period.
        serialPtr_bit += (parent->sampleRate_bit/baudRate)/2;
        return false;
    }

    return true;
}
