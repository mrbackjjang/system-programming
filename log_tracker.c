#include "common.h"
#include "parser.h"
#include "analysis.h"
#include "report.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int tracker_run(const char *live_log_path) {
    metrics_t metrics;
    incident_t incident;
    analysis_init(&metrics, &incident);

    long last_pos = 0;
    char line[512];
    log_entry_t entry;

    while (1) {
        FILE *f = fopen(live_log_path, "r");
        if (f) {
            fseek(f, last_pos, SEEK_SET);
            
            while (fgets(line, sizeof(line), f)) {
                if (strchr(line, '\n') == NULL) break;
                
                if (parser_parse_line(line, &entry)) {
                    analysis_update(&metrics, &incident, &entry);
                }
                last_pos = ftell(f);
            }
            fclose(f);
            
            report_write_summary("summary.txt", &metrics);
            report_write_incident("incident.txt", &incident);
        }
        usleep(500000);
    }
    return 1;
}

int main() {
    tracker_run("live.log");
    return 0;
}