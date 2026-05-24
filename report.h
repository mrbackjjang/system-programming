#ifndef REPORT_H
#define REPORT_H
#include "common.h"

void report_write_summary(const char *filepath, metrics_t *m);
void report_write_incident(const char *filepath, log_entry_t *entry, const char *status_msg);

#endif