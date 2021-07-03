#include "asyncdft.h"
#include <iostream>

#define DBG 1

AsyncDFT::AsyncDFT()
{
    /*Creating the main thread, which will manage everything*/
    stopping = false;
    manager = std::thread(&AsyncDFT::threadManager, this);
}

AsyncDFT::~AsyncDFT()
{
    stopping = true;
    dft_mutex.unlock();
    while (!manager.joinable());
    manager.join();
#if DBG
    std::cout << "Joined manager thread [DESTRUCTOR]" << std::endl;
#endif
}

void AsyncDFT::threadManager()
{
    while(stopping == false) {
            dft_mutex.lock();
            std::thread t = std::thread(&AsyncDFT::updateDFT, this);
#if DBG
            std::cout << "Starting new thread [MANAGER]" << std::endl;
#endif
            while(!t.joinable());
            t.join();
#if DBG
            std::cout << "Joined a thread [MANAGER]" << std::endl;
#endif
    }
}

void AsyncDFT::updateDFT()
{
#if DBG
    std::cout << "Im a thread and i gained lock, now calculating [THREAD]" << std::endl;
#endif
    if (!waiting_jobs.empty()) {
        short sample = waiting_jobs.front();
        waiting_jobs.pop();
        dft.update(sample);
    }
#if DBG
    std::cout << "Im a thread and i released lock, exiting [THREAD]" << std::endl;
#endif
}

void AsyncDFT::addSample(short sample)
{
    /*Adding to the waiting jobs the sample*/
    waiting_jobs.push(sample);
    dft_mutex.unlock();
}

QVector<double> AsyncDFT::getPowerSpectrum()
{
    /*Before doing anything, check if sliding DFT is computable*/
    if (!dft.is_data_valid()) {
        throw std::exception();
    }

    QVector<double> pow_spectr(n_samples, 0);
    double maximum = -1;

    /*Computing Power Spectrum*/
    for (int i = 0; i < n_samples; i++) {
        pow_spectr[i] = sqrt(dft.dft[i].real()*dft.dft[i].real() +
                             dft.dft[i].imag()*dft.dft[i].imag());

        if (pow_spectr[i] > maximum) {
            maximum = pow_spectr[i];
        }
    }

    for (int i = 0; i < n_samples; i++) {
        pow_spectr[i] /= maximum;
        pow_spectr[i] *= 100;
    }

    /*Returning normalized spectrum*/
    return pow_spectr;
}
