#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int replayer_run(const char *source_path, const char *ip, int port, useconds_t delay_us) {
    FILE *src = fopen(source_path, "r");
    if (!src) {
        perror("Failed to open source log");
        return 0;
    }

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port);

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("Connect error");
        fclose(src);
        return 0;
    }

    char line[512];
    while (fgets(line, sizeof(line), src)) {
        send(sock, line, strlen(line), 0);
        usleep(delay_us);
    }

    close(sock);
    fclose(src);
    return 1;
}

int main() {
    replayer_run("sample_apache.log", "127.0.0.1", 8080, 100000);
    printf("Replay finished.\n");
    return 0;
}