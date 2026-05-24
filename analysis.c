#include "analysis.h"
#include <string.h>

void analysis_init(metrics_t *m, incident_t *i) {
    m->total_logs = 0;
    m->error_count = 0;
    m->warn_count = 0;
    m->notice_count = 0;
    i->is_critical = 0;
}

void analysis_update(metrics_t *m, incident_t *i, log_entry_t *entry) {
    m->total_logs++;
    
    if (strcmp(entry->level, "error") == 0) m->error_count++;
    else if (strcmp(entry->level, "warn") == 0) m->warn_count++;
    else if (strcmp(entry->level, "notice") == 0) m->notice_count++;

    double error_rate = (double)m->error_count / m->total_logs;
    
    if (error_rate >= 0.3 && m->total_logs > 10) {
        i->is_critical = 1;
    } else {
        i->is_critical = 0;
    }
}