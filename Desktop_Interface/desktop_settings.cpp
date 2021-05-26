#include "desktop_settings.h"

//USB iso stuff
int MAX_TRANSFER_SIZE = 1023;
int MAX_PENDING_TRANSFERS = 512;
int MAX_PENDING_IO = 16;

//Plot settings
// this should be int GRAPH_SAMPLES = 375000 * 10; to avoid downsampling
int GRAPH_SAMPLES = 8192;
int TIMER_PERIOD = 17;
int ISO_RECOVERY_TIME = (200);
int MAX_WINDOW_SIZE = 10;
int TICK_SEPARATION = 96;

//Multimeter settings
int MULTIMETER_PERIOD = 500;

double SERIAL_DELAY = 0.01;  //100 baud?

QMutex tcBlockMutex;
QMutex unixDriverDeleteMutex;

unsigned char expected_variant;

#ifndef PLATFORM_WINDOWS
struct timeval tv;
#endif

