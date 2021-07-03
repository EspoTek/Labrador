#ifndef ASYNCDFT_H
#define ASYNCDFT_H
#include "sliding_dft.hpp"
#include <thread>
#include <QVector>
#include <mutex>
#include <queue>

class AsyncDFT
{
public:
    AsyncDFT();
    ~AsyncDFT();
    static const int n_samples = 350000;

    /* Raise exception if not ready yet*/
    QVector<double> getPowerSpectrum();

    void addSample(short sample);

private:
    SlidingDFT<double, n_samples> dft;
    std::thread dft_computing;
    std::queue<short> waiting_jobs;

    int pending_jobs;
    std::mutex dft_mutex;

    std::thread manager;
    bool stopping;
    void threadManager(); //threaded
    void updateDFT(); //threaded

};

#endif // ASYNCDFT_H
