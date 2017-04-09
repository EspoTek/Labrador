#ifndef BUFFERCONTROL_H
#define BUFFERCONTROL_H

#include <QWidget>
#include <QLabel>
#include <QDebug>

//bufferControl is a controller object that allocates and deallocates bandwidth depending on what devices are active.

class bufferControl : public QLabel
{
    Q_OBJECT
public:
    explicit bufferControl(QWidget *parent = 0);
    void refreshImage(void);
private:
    QPixmap bufferImage;
    int numBuffers = 1;
    bool scopeState_CH1 = true;
    bool scopeState_CH2 = false;
    bool scopeDsrState = false;
    //bool signalGenState = false;
    bool busSnifferState_CH1 = false;
    bool busSnifferState_CH2 = false;
    bool multimeterState = false;
    unsigned char digState = 0x00;

    void updateBuffer(bool increment, int amount);
    void updateMode(void);

signals:
    void scopeOut_CH1(bool state);
    void scopeOut_CH2(bool state);
    void scopeUncheck(bool state);
    void scopeDsrOut(bool state);
    void scopeDsrUncheck(bool state);
    void signalGenOut(bool state);
    void busSnifferOut_CH1(bool state);
    void busSnifferOut_CH2(bool state);
    void busSnifferUncheck(bool state);
    void multimeterOut(bool state);
    void updateDig(int digMask);
    void modeChange(int newMode);
public slots:
    void scopeIn_CH1(bool state);
    void scopeIn_CH2(bool state);
    void scopeDsrIn(bool state);
    //void signalGenIn(bool state);
    void busSnifferIn_CH1(bool state);
    void busSnifferIn_CH2(bool state);
    void multimeterIn(bool state);
    void digIn_CH1(bool state);
    void digIn_CH2(bool state);
    void digIn_CH3(bool state);
    void digIn_CH4(bool state);
    void poke(void);
};

#endif // BUFFERCONTROL_H
