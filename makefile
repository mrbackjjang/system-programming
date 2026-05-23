CC = gcc
CFLAGS = -Wall -Wextra -g

all: log_replayer log_tracker

log_replayer: log_replayer.c
	$(CC) $(CFLAGS) -o log_replayer log_replayer.c

log_tracker: log_tracker.c parser.c analysis.c report.c
	$(CC) $(CFLAGS) -o log_tracker log_tracker.c parser.c analysis.c report.c -lpthread

clean:
	rm -f log_replayer log_tracker live.log summary.txt incident.txt