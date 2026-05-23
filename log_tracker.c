#include "common.h"
#include "parser.h"
#include "analysis.h"
#include "report.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define QUEUE_SIZE 100

metrics_t metrics;
incident_t incident;

char log_queue[QUEUE_SIZE][512];
int q_front = 0, q_rear = 0, q_count = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *receive_thread(void *arg) {
    int clnt_sock = *((int*)arg);
    FILE *f = fdopen(clnt_sock, "r");
    char line[512];

    while (fgets(line, sizeof(line), f)) {
        pthread_mutex_lock(&lock);
        if (q_count < QUEUE_SIZE) {
            strcpy(log_queue[q_rear], line);
            q_rear = (q_rear + 1) % QUEUE_SIZE;
            q_count++;
            pthread_cond_signal(&cond); // 데이터가 들어왔음을 알림
        }
        pthread_mutex_unlock(&lock);
    }
    fclose(f);
    return NULL;
}

void *analysis_thread(void *arg) {
    log_entry_t entry;
    char line[512];

    while (1) {
        pthread_mutex_lock(&lock);
        while (q_count == 0) {
            pthread_cond_wait(&cond, &lock); // 데이터가 들어올 때까지 대기
        }
        strcpy(line, log_queue[q_front]);
        q_front = (q_front + 1) % QUEUE_SIZE;
        q_count--;
        pthread_mutex_unlock(&lock);

        if (parser_parse_line(line, &entry)) {
            analysis_update(&metrics, &incident, &entry);
            report_write_summary("summary.txt", &metrics);
            report_write_incident("incident.txt", &incident);
        }
    }
    return NULL;
}

int main() {
    analysis_init(&metrics, &incident);

    int serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(8080);

    // 포트 재사용 옵션 (테스트 시 포트 바인딩 에러 방지)
    int opt_val = 1;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val));

    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(serv_sock, 5);

    printf("Waiting for log_replayer connection...\n");
    int clnt_sock = accept(serv_sock, NULL, NULL);
    printf("Connected!\n");

    pthread_t rcv_tid, ana_tid;
    pthread_create(&rcv_tid, NULL, receive_thread, (void*)&clnt_sock);
    pthread_create(&ana_tid, NULL, analysis_thread, NULL);

    pthread_join(rcv_tid, NULL);
    pthread_cancel(ana_tid); // 수신이 끝나면 분석 쓰레드도 종료
    
    close(serv_sock);
    return 0;
}