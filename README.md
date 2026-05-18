# Log-based Incident Tracker

## 1. 개요
Apache 서버의 에러 로그를 실시간으로 모니터링하고, 에러 비율에 따라 시스템 상태(HEALTHY, WARNING, CRITICAL)를 판정하여 리포트를 생성하는 시스템 프로그래밍 프로젝트입니다.

## 2. 빌드 및 실행 방법
1. `make` 명령어로 컴파일
2. 터미널 1: `./log_tracker` 실행 (실시간 감시 시작)
3. 터미널 2: `./log_replayer` 실행 (로그 전송 시작)

## 3. 결과물
* `summary.txt`: 실시간 로그 통계 및 현재 시스템 상태
* `incident.txt`: CRITICAL 상태 진입 시 생성되는 사건 보고서