#ifndef DESKTOP_SETTINGS_H
#define DESKTOP_SETTINGS_H

#include <QMutex>

//Just a whole lot of variables not directly related to xmega.

//USB iso stuff
extern int MAX_TRANSFER_SIZE;
extern int MAX_PENDING_TRANSFERS;
extern int MAX_PENDING_IO;

//Plot settings
extern int GRAPH_SAMPLES;
extern int TIMER_PERIOD;
extern int ISO_RECOVERY_TIME;
extern int MAX_WINDOW_SIZE;
extern int TICK_SEPARATION;
#define TRIGGER_COUNT_THRESH (7 + log10(window))  //Is this the right number?

//Multimeter settings
extern int MULTIMETER_PERIOD;

extern double SERIAL_DELAY;

extern QMutex tcBlockMutex;

#define DEBUG_SETTINGSDOTSET

#define USB_RECONNECT_PERIOD 420

#define VALID_DATA_PER_375 375

#define VALID_DATA_PER_750 750

#define COLUMN_BREAK VALID_DATA_PER_750

//#define MAX_CONSOLE_BLOCK_COUNT 512
#define SERIAL_BUFFER_LENGTH 2048

#endif // DESKTOP_SETTINGS_H

