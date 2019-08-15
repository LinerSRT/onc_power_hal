int sysfs_read(char* path, char* s, int num_bytes);
int sysfs_write(char* path, char* s);

void release_request(int lock_handle);
int perf_hint_enable(int hint_id, int duration);
int perf_hint_enable_with_type(int hint_id, int duration, int type);

long long calc_timespan_us(struct timespec start, struct timespec end);
