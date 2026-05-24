#include "report.h"
#include <stdio.h>

void report_write_summary(const char *filepath, metrics_t *m) {
    FILE *f = fopen(filepath, "w"); // 요약은 항상 최신 상태로 덮어쓰기
    if (!f) return;
    
    fprintf(f, "--- Log Analysis Summary ---\n");
    fprintf(f, "Total Logs: %d\n", m->total_logs);
    fprintf(f, "Errors: %d\n", m->error_count);
    fprintf(f, "Warnings: %d\n", m->warn_count);
    fprintf(f, "Notices: %d\n", m->notice_count);
    
    fclose(f);
}

void report_write_incident(const char *filepath, log_entry_t *entry, const char *status_msg) {
    FILE *f = fopen(filepath, "a"); // 히스토리 누적을 위해 a 모드(Append) 사용
    if (!f) return;

    // 파싱된 이벤트 시간(Event Time)을 기준으로 기록
    fprintf(f, "[%s] %s (Level: %s)\n", entry->timestamp, status_msg, entry->level);
    
    fclose(f);
}