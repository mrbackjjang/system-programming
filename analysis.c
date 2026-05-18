#include "analysis.h"
#include <string.h>

void analysis_init(metrics_t *metrics, incident_t *incident) {
    memset(metrics, 0, sizeof(metrics_t));
    memset(incident, 0, sizeof(incident_t));
}

void analysis_update(metrics_t *metrics, incident_t *incident, const log_entry_t *entry) {
    metrics->total_logs++;
    
    if (strstr(entry->level, "error") != NULL) {
        metrics->error_logs++;
    } else if (strstr(entry->level, "notice") != NULL) {
        metrics->notice_logs++;
    } else if (strstr(entry->level, "warn") != NULL) {
        metrics->warn_logs++;
    }

    metrics->error_ratio = (double)metrics->error_logs / metrics->total_logs;

    if (metrics->error_ratio >= 0.3) {
        metrics->state = STATE_CRITICAL;
    } else if (metrics->error_ratio >= 0.1) {
        metrics->state = STATE_WARNING;
    } else {
        metrics->state = STATE_HEALTHY;
    }

    // Incident 시작 조건
    if (metrics->state == STATE_CRITICAL && !incident->active) {
        incident->active = 1;
        strcpy(incident->start_time, entry->timestamp);
        strcpy(incident->first_error_message, entry->message);
    }

    // Incident 진행 중 누적
    if (incident->active) {
        incident->log_count_in_incident++;
        if (strstr(entry->level, "error") != NULL) {
            incident->error_count_in_incident++;
        }
        strcpy(incident->end_time, entry->timestamp);
    }
}

service_state_t analysis_get_state(const metrics_t *metrics) {
    return metrics->state;
}
