#ifndef COMMON_H
#define COMMON_H

typedef enum {
    STATE_HEALTHY = 0,
    STATE_WARNING = 1,
    STATE_CRITICAL = 2
} service_state_t;

typedef struct {
    char timestamp[64];
    char level[16];
    char message[256];
} log_entry_t;

typedef struct {
    int total_logs;
    int error_logs;
    int notice_logs;
    int warn_logs;
    double error_ratio;
    service_state_t state;
} metrics_t;

typedef struct {
    int active;
    char start_time[64];
    char end_time[64];
    int log_count_in_incident;
    int error_count_in_incident;
    char first_error_message[256];
} incident_t;

#endif
