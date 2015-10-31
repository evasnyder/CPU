CC = gcc
hello : queue.c pqueue.c switch.c run.c
		$(CC) -o hello pqueue.c queue.c distribution.c switch.c run.c -I.
