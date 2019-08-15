#define NODE_MAX (64)

#define SCALING_GOVERNOR_PATH "/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor"
#define DCVS_CPU0_SLACK_MAX_NODE "/sys/module/msm_dcvs/cores/cpu0/slack_time_max_us"
#define DCVS_CPU0_SLACK_MIN_NODE "/sys/module/msm_dcvs/cores/cpu0/slack_time_min_us"
#define MPDECISION_SLACK_MAX_NODE "/sys/module/msm_mpdecision/slack_time_max_us"
#define MPDECISION_SLACK_MIN_NODE "/sys/module/msm_mpdecision/slack_time_min_us"
#define SCALING_MIN_FREQ "/sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq"
#define ONDEMAND_GOVERNOR "ondemand"
#define INTERACTIVE_GOVERNOR "interactive"
#define MSMDCVS_GOVERNOR "msm-dcvs"

#define HINT_HANDLED (0)
#define HINT_NONE (-1)

#define INPUT_EVENT_WAKUP_MODE_OFF 4
#define INPUT_EVENT_WAKUP_MODE_ON 5

#define CHECK_HANDLE(x) ((x) > 0)

enum CPU_GOV_CHECK {
    CPU0 = 0,
    CPU1 = 1,
    CPU2 = 2,
    CPU3 = 3
};
