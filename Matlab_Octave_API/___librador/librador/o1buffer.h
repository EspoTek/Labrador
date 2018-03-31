#ifndef O1BUFFER_H
#define O1BUFFER_H

#include <vector>

#define NUM_SAMPLES_PER_CHANNEL 7500000


class o1buffer
{
public:
    explicit o1buffer();
    ~o1buffer();
    void add(int value, int address);
    int addVector(int *firstElement, int numElements);
    int addVector(unsigned char *firstElement, int numElements);
    int get(int address);
    int mostRecentAddress = 0;
    int stream_index_at_last_call = 0;
    int distanceFromMostRecentAddress(int index);
    std::vector<double> *getMany_double(int numToGet, int interval_samples, int delay_sample, int filter_mode);
    std::vector<double> *getSinceLast(int feasible_window_begin, int feasible_window_end, int interval_samples, int filter_mode);
private:
    int *buffer;
    std::vector<double> convertedStream_double;
    void updateMostRecentAddress(int newAddress);
    double get_filtered_sample(int index, int filter_type, int filter_size);
};

#endif // O1BUFFER_H
