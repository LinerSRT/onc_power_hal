#define AOSP_DELTA (0x1200)
#define NUM_HINTS (POWER_HINT_DISABLE_TOUCH + 1)

struct hint_handles {
    int handle;
    int ref_count;
};

struct hint_data {
    unsigned long hint_id;
    unsigned long perflock_handle;
};
