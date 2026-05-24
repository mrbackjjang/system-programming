#include "parser.h"
#include <string.h>

int parser_parse_line(const char *line, log_entry_t *entry) {
    memset(entry, 0, sizeof(log_entry_t));
    
    // 시간 파싱: 첫 번째 '['와 ']' 사이 문자열 추출
    const char *t_start = strchr(line, '[');
    if (t_start) {
        const char *t_end = strchr(t_start + 1, ']');
        if (t_end && (t_end - t_start - 1 < sizeof(entry->timestamp))) {
            strncpy(entry->timestamp, t_start + 1, t_end - t_start - 1);
            entry->timestamp[t_end - t_start - 1] = '\0';
        }
    } else {
        strcpy(entry->timestamp, "Unknown Time");
    }

    // 로그 레벨 파싱
    if (strstr(line, "[error]")) strcpy(entry->level, "error");
    else if (strstr(line, "[warn]")) strcpy(entry->level, "warn");
    else if (strstr(line, "[notice]")) strcpy(entry->level, "notice");
    else strcpy(entry->level, "info");

    return 1;
}