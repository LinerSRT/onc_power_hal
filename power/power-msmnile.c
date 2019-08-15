#define LOG_NIDEBUG 0

#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define LOG_TAG "QTI PowerHAL"
#include <hardware/hardware.h>
#include <hardware/power.h>
#include <log/log.h>
#include <time.h>

#include "performance.h"
#include "power-common.h"
#include "utils.h"

const int kMaxLaunchDuration = 5000;
const int kMaxInteractiveDuration = 5000;
const int kMinInteractiveDuration = 100;

static int process_activity_launch_hint(void* data __unused) {
    static int launch_handle = -1;
    static int launch_mode = 0;

    if (!data) {
        if (CHECK_HANDLE(launch_handle)) {
            release_request(launch_handle);
            launch_handle = -1;
        }
        launch_mode = 0;
        return HINT_HANDLED;
    }

    launch_handle = perf_hint_enable_with_type(VENDOR_HINT_LAUNCH_BOOST, kMaxLaunchDuration,
                                               LAUNCH_BOOST_V1);
    if (!CHECK_HANDLE(launch_handle)) {
        ALOGE("Failed to perform launch boost");
        return HINT_NONE;
    }
    launch_mode = 1;

    return HINT_HANDLED;
}

static int process_interaction_hint(void* data) {
    static struct timespec s_previous_boost_timespec;
    static int s_previous_duration = 0;

    struct timespec cur_boost_timespec;
    long long elapsed_time;
    int duration = kMinInteractiveDuration;

    if (data) {
        int input_duration = *((int*)data);
        if (input_duration > duration) {
            duration = (input_duration > kMaxInteractiveDuration) ? kMaxInteractiveDuration
                                                                  : input_duration;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &cur_boost_timespec);

    elapsed_time = calc_timespan_us(s_previous_boost_timespec, cur_boost_timespec);
    if ((s_previous_duration * 1000) > (elapsed_time + duration * 1000)) {
        return HINT_HANDLED;
    }
    s_previous_boost_timespec = cur_boost_timespec;
    s_previous_duration = duration;

    perf_hint_enable_with_type(VENDOR_HINT_SCROLL_BOOST, duration, SCROLL_VERTICAL);

    return HINT_HANDLED;
}

int power_hint_override(struct power_module* module __unused, power_hint_t hint,
                        void* data __unused) {
    int ret_val = HINT_NONE;
    switch (hint) {
        case POWER_HINT_INTERACTION:
            ret_val = process_interaction_hint(data);
            break;
        case POWER_HINT_LAUNCH:
            ret_val = process_activity_launch_hint(data);
            break;
        default:
            break;
    }
    return ret_val;
}
