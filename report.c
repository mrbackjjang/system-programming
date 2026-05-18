#include "report.h"
#include <stdio.h>

void report_write_summary(const char *filename, const metrics_t *metrics) {
    FILE *f = fopen(filename, "w");
    if (!f) return;

    const char *state_str = "HEALTHY";
    if (metrics->state == STATE_WARNING) state_str = "WARNING";
    if (metrics->state == STATE_CRITICAL) state_str = "CRITICAL";

    fprintf(f, "[System Summary]\n");
    fprintf(f, "State: %s\n", state_str);
    fprintf(f, "Total Logs: %d\n", metrics->total_logs);
    fprintf(f, "Error Ratio: %.2f%%\n", metrics->error_ratio * 100);
    fprintf(f, "- Errors: %d\n", metrics->error_logs);
    fprintf(f, "- Warnings: %d\n", metrics->warn_logs);
    fprintf(f, "- Notices: %d\n", metrics->notice_logs);
    
    fclose(f);
}

void report_write_incident(const char *filename, const incident_t *incident) {
    if (!incident->active) return; // Incident가 발생하지 않았으면 작성 안함

    FILE *f = fopen(filename, "w");
    if (!f) return;

    fprintf(f, "[Incident Report]\n");
    fprintf(f, "Start Time: %s\n", incident->start_time);
    fprintf(f, "Last Update Time: %s\n", incident->end_time);
    fprintf(f, "Logs Analyzed During Incident: %d\n", incident->log_count_in_incident);
    fprintf(f, "Errors During Incident: %d\n", incident->error_count_in_incident);
    fprintf(f, "Initial Error Message: %s\n", incident->first_error_message);
    
    fclose(f);
}
