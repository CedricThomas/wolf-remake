#include <string.h>
#include <time.h>
#include <math.h>

#include "wolf.h"

unsigned long millis() {
    struct timespec _t;
    clock_gettime(CLOCK_REALTIME, &_t);
    return _t.tv_sec * 1000 + lround(_t.tv_nsec / 1.0e6);
}

time_tracker_t time_tracker_create(unsigned long interval) {
    time_tracker_t tracker;
    memset(&tracker, 0, sizeof(time_tracker_t));
    tracker.interval = interval;
    tracker.last_time = millis();
    return tracker;
}

int time_tracker_update(time_tracker_t *tracker) {
    unsigned long current_time = millis();
    if (current_time < tracker->last_time + tracker->interval) {
        return 0;
    }
    tracker->last_time = current_time;
    return 1;
}
