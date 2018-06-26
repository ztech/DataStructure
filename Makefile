CC = clang
CFLAGS = -g -o
BIN = sqlist llist dllist sqstack lstack squeue lqueue string matrix
.DEFAULT_GOAL = all
sqlist: sqlist.c
	$(CC) sqlist.c $(CFLAGS) sqlist
llist: llist.c
	$(CC) llist.c $(CFLAGS) llist
dllist: dllist.c
	$(CC) dllist.c $(CFLAGS) dllist
sqstack: sqstack.c
	$(CC) sqstack.c $(CFLAGS) sqstack
lstack: lstack.c
	$(CC) lstack.c $(CFLAGS) lstack
squeue: squeue.c
	$(CC) squeue.c $(CFLAGS) squeue
lqueue: lqueue.c
	$(CC) lqueue.c $(CFLAGS) lqueue
string: string.c
	$(CC) string.c $(CFLAGS) string
matrix: matrix.c
	$(CC) matrix.c $(CFLAGS) matrix
.PHONY: all
all: $(BIN)
.PHONY: clean
clean:
	rm $(BIN)
