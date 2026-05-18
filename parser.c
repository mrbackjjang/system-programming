#include "parser.h"
#include <stdio.h>

int parser_parse_line(const char *line, log_entry_t *entry) {
    // [Thu Jun 09 06:07:05 2005] [error] message... 형식을 파싱
    if (sscanf(line, "[%63[^]]] [%15[^]]] %255[^\n]", entry->timestamp, entry->level, entry->message) == 3) {
        return 1; // 성공
    }
    return 0; // 실패
}
