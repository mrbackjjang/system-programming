#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int replayer_run(const char *source_path, const char *live_path, useconds_t delay_us) {
    FILE *src = fopen(source_path, "r");
    if (!src) {
        perror("Failed to open source log");
        return 0;
    }

    FILE *live = fopen(live_path, "a");
    if (!live) {
        perror("Failed to open live log");
        fclose(src);
        return 0;
    }

    char line[512];
    while (fgets(line, sizeof(line), src)) {
        fputs(line, live);
        fflush(live);
        usleep(delay_us);
    }

    fclose(src);
    fclose(live);
    return 1;
}

int main() {
    replayer_run("sample_apache.log", "live.log", 100000);
    printf("Replay finished.\n");
    return 0;
}