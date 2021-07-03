#include "asyncdft.h"
#include <iostream>
#include <math.h>
#define DBG 0

AsyncDFT::AsyncDFT()
{
    /*Creating the main thread, which will manage everything*/
    stopping = false;
    /*Data is not valid until we get n_samples into the window*/
    data_valid = false;
    /*Samples counter*/
    samples_count=0;
    /*Initializing time domain window to 0s*/
    /*FFTW3 inits*/
    fftw_init_threads();
    fftw_plan_with_nthreads(omp_get_max_threads());
#if DBG
    std::cout << "Starting with " << omp_get_max_threads() << "threads" << std::endl;
#endif
    out_buffer = fftw_alloc_complex(n_samples);
    plan = fftw_plan_dft_r2c_1d(n_samples,window, out_buffer,0);
    /*Starting manager*/
    manager = std::thread(&AsyncDFT::threadManager, this);
}

AsyncDFT::~AsyncDFT()
{
    stopping = true;
    mtx_samples.unlock();   //Unlock thread manager if blocked and waiting for more samples
    while (!manager.joinable());
    manager.join();
#if DBG
    std::cout << "Joined manager thread [DESTRUCTOR]" << std::endl;
#endif
}

void AsyncDFT::threadManager()
{
    while(stopping == false) {
        /*Calculating DFT if there are new samples, otherwise DFT would be the same*/
        mtx_samples.lock();
        /*Data is now valid*/
        data_valid = true;
        /*Shifting window by 1*/
        shift();
    }
}


void AsyncDFT::addSample(short sample)
{
    /*Adding to the waiting jobs the sample*/
    accumulated_samples.push(sample);
    if (samples_count >= n_samples) {
        /*Add the last sample to the window*/
        short oldest_sample = accumulated_samples.front();
        window[n_samples-1] = oldest_sample;
        accumulated_samples.pop();
        mtx_samples.unlock(); //unlock the thread Manager for computing DFT
    } else {
        /*Fill the window*/
        window[samples_count] = sample;
    }
    /*Updating the number of samples*/
    samples_count++;
}

QVector<double> AsyncDFT::getPowerSpectrum()
{
    /*Before doing anything, check if sliding DFT is computable*/
    if (data_valid == false) {
        throw std::exception();
    }

    /*Zero-padding for better resolution of DFT*/
    QVector<double> amplitude(n_samples/2+1,0);
    static int count = 100;
    double cur_maximum = -1;

    /*Executing FFTW plan*/
    fftw_execute(plan);
    amplitude[0] = sqrt(out_buffer[0][0]*out_buffer[0][0] + out_buffer[0][1]*out_buffer[0][1]);  /* DC component */

    cur_maximum = (amplitude[0] > cur_maximum ) ? amplitude[0] : cur_maximum;

    for (int k = 1; k < (n_samples+1)/2; ++k) {  /* (k < N/2 rounded up) */
         amplitude[k] = sqrt(out_buffer[k][0]*out_buffer[k][0] + out_buffer[k][1]*out_buffer[k][1]);

         cur_maximum = (amplitude[k] > cur_maximum ) ? amplitude[k] : cur_maximum;
    }
    if (n_samples % 2 == 0) { /* N is even */
         amplitude[n_samples/2] = sqrt(out_buffer[n_samples/2][0]*out_buffer[n_samples/2][0]);  /* Nyquist freq. */

         cur_maximum = (amplitude[n_samples/2] > cur_maximum ) ? amplitude[n_samples/2] : cur_maximum;

    }

    if (cur_maximum < maximum) {
        count--;
    } else {
        /*current maximum is higher resetting count to 10*/
        maximum = cur_maximum;
        count = 100;
    }

    if (count == 0) {
        /*current maximum is lower for 10 consecutive samples*/
        maximum = cur_maximum;
        count = 100;
    }

    std::cout << "Cur Maximum: " << cur_maximum << std::endl;
    return amplitude;
}

void AsyncDFT::shift()
{
#if DBG
    std::cout << "Shifting [S]" << std::endl;
#endif
    for(int i = 0; i+1 < n_samples; i++) {
        window[i] = window[i+1];
    }
#if DBG
    std::cout << "Shifting [E]" << std::endl;
#endif
}
