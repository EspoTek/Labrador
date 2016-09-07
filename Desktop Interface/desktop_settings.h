#ifndef DESKTOP_SETTINGS_H
#define DESKTOP_SETTINGS_H

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

#endif // DESKTOP_SETTINGS_H

