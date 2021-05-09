#include "buffercontrol.h"

bufferControl::bufferControl(QWidget *parent) : QLabel(parent)
{
    //refreshImage();
}

void bufferControl::refreshImage(void){
    //qDebug() << "Trying to show bitmap " << numBuffers;

    switch(numBuffers){
    case 0:
        bufferImage = QPixmap(":/bitmap/buffer_0.bmp");
        break;
    case 1:
        bufferImage = QPixmap(":/bitmap/buffer_1.bmp");
        break;
    case 2:
        bufferImage = QPixmap(":/bitmap/buffer_2.bmp");
        break;
    }

    if(bufferImage.isNull()) qFatal("Resource not found\n");

    this->setPixmap(bufferImage);
    //qDebug() << this->text();
    this->show();
    return;
}

void bufferControl::scopeIn_CH1(bool state){  //What about DSR!?
    scopeState_CH1 = state;

    if (scopeState_CH2){ //Implicitly state is false
        scopeState_CH2 = false;
        //updateBuffer(0);  -  Causes issues because the uncheck below called scopeIn_CH2 (but only when toggle)!!!
        emit scopeUncheck(false);
    }

    //Turn off the DSR when CH1 is disabled.
    if(!state && !scopeDsrDisableOverride){
        emit scopeDsrUncheck(false);
    }

    emit scopeDsrOut(state);
    emit scopeOut_CH2(state);

    updateBuffer(state,1); // Do this last to ensure anything accidentally enabled is immediately switched off
    qDebug() << "scopeIn_CH1" << state;
    updateMode();
}

void bufferControl::scopeIn_CH2(bool state){
    scopeState_CH2 = state;

    updateBuffer(state,1);
    qDebug() << "scopeIn_CH2" << state;
    updateMode();
}

void bufferControl::scopeDsrIn(bool state){
    scopeDsrState = state;

    updateBuffer(state,1);
    qDebug() << "scopeDsrIn" << state;
    updateMode();
}

void bufferControl::busSnifferIn_CH1(bool state){
    busSnifferState_CH1 = state;

    if (busSnifferState_CH2){ //Implicitly state is false
        busSnifferState_CH2 = false;
        //updateBuffer(0);  -  Causes issues because the uncheck below called scopeIn_CH2 (but only when toggle)!!!
        emit busSnifferUncheck(false);
    }

    //Signal Gen CH2 doesn't work with bus sniffer.
    emit signalGenOut(!state);

    emit busSnifferOut_CH2(state);

    updateBuffer(state,1);
    qDebug() << "busSnifferIn_CH1" << state;
    updateMode();
}

void bufferControl::busSnifferIn_CH2(bool state){
    busSnifferState_CH2 = state;

    updateBuffer(state,1);
    qDebug() << "busSnifferIn_CH2" << state;
    updateMode();
}

void bufferControl::multimeterIn(bool state){
    multimeterState = state;

    updateBuffer(state,2);
    qDebug() << "multimeterIn" << state;
    updateMode();
}



void bufferControl::updateBuffer(bool decrement, int amount){
    if(decrement){
        numBuffers-=amount;
    }
    else{
        numBuffers+=amount;
    }
    refreshImage();

    //Write new state
    switch(numBuffers){
        case 0:
            if(scopeState_CH1 == false) emit scopeOut_CH1(false);
            if(scopeState_CH2 == false) emit scopeOut_CH2(false);
            if(scopeDsrState == false) emit scopeDsrOut(false);
            //if(signalGenState == false) signalGenOut(0);
            if(busSnifferState_CH1 == false) emit busSnifferOut_CH1(false);
            if(busSnifferState_CH2 == false) emit busSnifferOut_CH2(false);
            if(multimeterState == false) emit multimeterOut(false);
            break;
        case 1:
            emit scopeOut_CH1(true);
            if(scopeState_CH1 == true){
                emit scopeDsrOut(true);
                emit scopeOut_CH2(true);
            }
            //signalGenOut(1);
            emit busSnifferOut_CH1(true);
            if(busSnifferState_CH1 == true){
                emit busSnifferOut_CH2(true);
            }

            //busSnifferOut_CH2(1);
            emit multimeterOut(false);
        break;
        case 2:
            emit scopeOut_CH1(true);
            //scopeOut_CH2(1);
            if(scopeState_CH1 == true) emit scopeDsrOut(true);
            //signalGenOut(1);
            emit busSnifferOut_CH1(true);
            //busSnifferOut_CH2(1);
            emit multimeterOut(true);
            break;
    default:
        qFatal("numBuffers is not equal to 0, 1 or 2");
    }

    if(scopeDsrDisableOverride){
        emit scopeDsrOut(false);
    }
}

void bufferControl::digIn_CH1(bool state){
    unsigned char mask = 0x01;
    if(state){
        digState |= mask;
    }
    else{
        digState &= (unsigned char) 0xff - mask;
    }
    emit updateDig(digState);
}

void bufferControl::digIn_CH2(bool state){
    unsigned char mask = 0x02;
    if(state){
        digState |= mask;
    }
    else{
        digState &= (unsigned char) 0xff - mask;
    }    emit updateDig(digState);
}

void bufferControl::digIn_CH3(bool state){
    unsigned char mask = 0x04;
    if(state){
        digState |= mask;
    }
    else{
        digState &= (unsigned char) 0xff - mask;
    }    emit updateDig(digState);
}

void bufferControl::digIn_CH4(bool state){
    unsigned char mask = 0x08;
    if(state){
        digState |= mask;
    }
    else{
        digState &= (unsigned char) 0xff - mask;
    }    emit updateDig(digState);
}

void bufferControl::updateMode(void){
    if(multimeterState){
        emit modeChange(7);
        qDebug() << "Changed to mode 7";
        return;
    }
    if(scopeDsrState){
        emit modeChange(6);
        qDebug() << "Changed to mode 6";
        return;
    }

    if (busSnifferState_CH2){
        emit modeChange(4);
        qDebug() << "Changed to mode 4";
        return;
    }
    if(busSnifferState_CH1 && scopeState_CH1){
        emit modeChange(1);
        qDebug() << "Changed to mode 1";
        return;
    }
    if (scopeState_CH2){
        emit modeChange(2);
        qDebug() << "Changed to mode 2";
        return;
    }
    if(busSnifferState_CH1){
        emit modeChange(3);
        qDebug() << "Changed to mode 3";
        return;
    }
    if(scopeState_CH1){
        emit modeChange(0);
        qDebug() << "Changed to mode 0";
        return;
    }

    emit modeChange(5);
    qDebug() << "Changed to mode 5";
    return;

}

void bufferControl::poke(void){
    emit updateDig(digState);
    updateMode();
    updateBuffer(false,0);
}

