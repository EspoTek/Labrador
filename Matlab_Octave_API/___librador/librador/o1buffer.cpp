#include "o1buffer.h"
#include <stdio.h>
#include <stdlib.h>


//o1buffer is an object that has o(1) access times for its elements.
//At the moment it's basically an array, but I'm keeping it as an object so it can be changed to something more memory efficient later.
//See isobuffer in github.com/espotek/labrador for an example of a much more compact (RAM-wise) buffer.
o1buffer::o1buffer()
{
    buffer = (int *) (malloc(sizeof(int)*NUM_SAMPLES_PER_CHANNEL));
}

o1buffer::~o1buffer(){
    free(buffer);
}


void o1buffer::add(int value, int address){
    //Ensure that the address is not too high.
    if(address >= NUM_SAMPLES_PER_CHANNEL){
        address = address % NUM_SAMPLES_PER_CHANNEL;
    }
    if(address<0){
        fprintf(stderr, "ERROR: o1buffer::add was given a negative address\n");
    }
    //Assign the value
    buffer[address] = value;
    updateMostRecentAddress(address);
}

int o1buffer::addVector(int *firstElement, int numElements){
    int currentAddress = mostRecentAddress;

    for(int i=0; i< numElements; i++){
        add(firstElement[i], currentAddress);
        currentAddress = (currentAddress + 1) % NUM_SAMPLES_PER_CHANNEL;
    }
    return 0;
}

int o1buffer::addVector(unsigned char *firstElement, int numElements){
    int currentAddress = mostRecentAddress;

    for(int i=0; i< numElements; i++){
        add(firstElement[i], currentAddress);
        currentAddress = (currentAddress + 1) % NUM_SAMPLES_PER_CHANNEL;
    }
    return 0;
}


int o1buffer::get(int address){
    //Ensure that the address is not too high.
    if(address >= NUM_SAMPLES_PER_CHANNEL){
        address = address % NUM_SAMPLES_PER_CHANNEL;
    }
    if(address<0){
        fprintf(stderr, "ERROR: o1buffer::get was given a negative address\n");
    }
    //Return the value
    return buffer[address];
}

inline void o1buffer::updateMostRecentAddress(int newAddress){
    mostRecentAddress = newAddress;
}

//This function places samples in a buffer than can be plotted on the streamingDisplay.
//A small delay, is added in case the packets arrive out of order.
std::vector<double> *o1buffer::getMany_double(int numToGet, int interval_samples, int delay_samples, int filter_mode){
    //Resize the vector
    convertedStream_double.resize(numToGet);

    //Copy raw samples out.
    int tempAddress;
    for(int i=0;i<numToGet;i++){
        tempAddress = mostRecentAddress - delay_samples - (interval_samples * i);
        if(tempAddress < 0){
            tempAddress += NUM_SAMPLES_PER_CHANNEL;
        }
        double *data = convertedStream_double.data();
        data[i] = get_filtered_sample(tempAddress, filter_mode, interval_samples);
        //convertedStream_double.replace(i, buffer[tempAddress]);
    }
    return &convertedStream_double;
}

std::vector<double> *o1buffer::getSinceLast(int feasible_window_begin, int feasible_window_end, int interval_samples, int filter_mode){

    //Calculate what sample the feasible window begins at
    //printf_debugging("o1buffer::getSinceLast()\n")
    int feasible_start_point = mostRecentAddress - feasible_window_begin;
    if(feasible_start_point < 0){
        feasible_start_point += NUM_SAMPLES_PER_CHANNEL;
    }

    //Work out whether or not we're starting from the feasible window or the last point
    int actual_start_point;
    if(distanceFromMostRecentAddress(feasible_start_point) > distanceFromMostRecentAddress(stream_index_at_last_call + interval_samples)){
        actual_start_point = stream_index_at_last_call + interval_samples;
    } else {
        actual_start_point = feasible_start_point;
    }

    //Work out how much we're copying
    int actual_sample_distance = distanceFromMostRecentAddress(actual_start_point) - distanceFromMostRecentAddress(mostRecentAddress - feasible_window_end);
    int numToGet = actual_sample_distance/interval_samples;
    //printf_debugging("Fetching %d samples, starting at index %d with interval %d\n", numToGet, actual_start_point, interval_samples);

    //Set up the buffer
    convertedStream_double.resize(numToGet);

    //Copy raw samples out.
    int tempAddress = stream_index_at_last_call;
    for(int i=0;i<numToGet;i++){
        tempAddress = actual_start_point + (interval_samples * i);
        if(tempAddress >= NUM_SAMPLES_PER_CHANNEL){
            tempAddress -= NUM_SAMPLES_PER_CHANNEL;
        }
        double *data = convertedStream_double.data();
        data[numToGet-1-i] = get_filtered_sample(tempAddress, filter_mode, interval_samples);
        //convertedStream_double.replace(i, buffer[tempAddress]);
    }

    //update stream_index_at_last_call for next call
    stream_index_at_last_call = tempAddress;

    return &convertedStream_double;
}

int o1buffer::distanceFromMostRecentAddress(int index){
    //Standard case.  buffer[NUM_SAMPLES_PER_CHANNEL] not crossed between most recent and index's sample writes.
    if(index < mostRecentAddress){
        return mostRecentAddress - index;
    }

    //Corner case.  buffer[NUM_SAMPLES_PER_CHANNEL] boundary has been crossed.
    if(index > mostRecentAddress){
        //Two areas.  0 to mostRecentAddress, and index to the end of the buffer.
        return mostRecentAddress + (NUM_SAMPLES_PER_CHANNEL - index);
    }

    //I guess the other corner case is when the addresses are the same.
    return 0;
}

//replace with get_filtered_sample
double o1buffer::get_filtered_sample(int index, int filter_type, int filter_size){
    double accum = 0;
    int currentPos = index - (filter_size / 2);
    int end = currentPos + filter_size;

    switch(filter_type){
        case 0: //No filter
            return buffer[index];
        case 1: //Moving Average filter
            if(currentPos < 0){
                currentPos += NUM_SAMPLES_PER_CHANNEL;
            }
            if(end >= NUM_SAMPLES_PER_CHANNEL){
                end -= NUM_SAMPLES_PER_CHANNEL;
            }
            while(currentPos != end){
                accum += buffer[currentPos];
                currentPos = (currentPos + 1) % NUM_SAMPLES_PER_CHANNEL;
            }
            return accum/((double)filter_size);
        break;
        default: //Default to "no filter"
            return buffer[index];
    }
}
