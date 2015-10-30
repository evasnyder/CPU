CC = gcc
hello : run.c queue.c pqueue.c
		$(CC) -o hello run.c queue.c pqueue.c -I .