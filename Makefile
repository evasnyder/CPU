CC = gcc
hello : run.c queue.c pqueue.c switch.c
		$(CC) -o hello pqueue.c queue.c run.c distribution.c switch.c -I.
