#include <cutils/properties.h>

int sysfs_read(char *path, char *s, int num_bytes);
int sysfs_write(char *path, char *s);
int get_scaling_governor(char governor[], int size);
int get_scaling_governor_check_cores(char governor[], int size,int core_num);
int is_interactive_governor(char*);

void vote_ondemand_io_busy_off();
void unvote_ondemand_io_busy_off();
void vote_ondemand_sdf_low();
void unvote_ondemand_sdf_low();
void perform_hint_action(int hint_id, int resource_values[],
    int num_resources);
void undo_hint_action(int hint_id);
void release_request(int lock_handle);
int interaction_with_handle(int lock_handle, int duration, int num_args, int opt_list[]);
int perf_hint_enable(int hint_id, int duration);
int perf_hint_enable_with_type(int hint_id, int duration, int type);

long long calc_timespan_us(struct timespec start, struct timespec end);
