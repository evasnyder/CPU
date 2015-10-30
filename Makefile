CC = gcc
hello : run.c queue.c pqueue.c
		$(CC) -o hello pqueue.c queue.c run.c -I.