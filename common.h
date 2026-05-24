#ifndef COMMON_H
#define COMMON_H

typedef struct {
    char timestamp[64];
    char level[16];
    char message[256];
} log_entry_t;

typedef struct {
    int total_logs;
    int error_count;
    int warn_count;
    int notice_count;
} metrics_t;

typedef struct {
    int is_critical;
} incident_t;

#endif