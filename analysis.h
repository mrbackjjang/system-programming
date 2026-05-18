#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "common.h"

void analysis_init(metrics_t *metrics, incident_t *incident);
void analysis_update(metrics_t *metrics, incident_t *incident, const log_entry_t *entry);
service_state_t analysis_get_state(const metrics_t *metrics);

#endif
