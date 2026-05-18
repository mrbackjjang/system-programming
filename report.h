#ifndef REPORT_H
#define REPORT_H

#include "common.h"

void report_write_summary(const char *filename, const metrics_t *metrics);
void report_write_incident(const char *filename, const incident_t *incident);

#endif
