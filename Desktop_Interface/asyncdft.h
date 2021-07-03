#ifndef ASYNCDFT_H
#define ASYNCDFT_H
#include <thread>
#include <QVector>
#include <mutex>
#include <queue>
#include <omp.h>
#include <fftw3.h>

class AsyncDFT
{
public:
    AsyncDFT();
    ~AsyncDFT();
    static const int n_samples = 375000;

    /* Raise exception if not ready yet*/
    QVector<double> getPowerSpectrum();

    /*Add a sample to the time domain samples*/
    void addSample(short sample);
private:
    /*Thread manager method*/
    void threadManager(); //threaded

    /*Shifts left the window by 1*/
    void shift();
public:
    /*Maximum power value obtained from power spectrum*/
    double maximum = -1;
private:
    /*New samples queue*/
    std::queue<short> accumulated_samples;
    /*Time domain window*/
    double window[n_samples];
    /*Thread for managing FFT computing*/
    std::thread manager;

    /*Variable for stopping the main thread execution*/
    bool stopping;
    /*Indicates if dft is available*/
    bool data_valid;
    /*Number of time domain samples accumulated*/
    int samples_count;
    /*To manage access to samples*/
    std::mutex mtx_samples;
    /*FFTW3*/
    fftw_plan plan;
    fftw_complex *out_buffer;

};

#endif // ASYNCDFT_H
