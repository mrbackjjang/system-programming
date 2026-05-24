#ifndef ANALYSIS_H
#define ANALYSIS_H
#include "common.h"

void analysis_init(metrics_t *m, incident_t *i);
void analysis_update(metrics_t *m, incident_t *i, log_entry_t *entry);

#endif