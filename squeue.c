/*
 * squeue.c
 * This is Sequence Queue Data Structure Reference Implementation which written
 * purely in C Language.
 * Copyright 2018 Zombie<teng@tenglog.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// #define __DEBUG__

#ifdef __DEBUG__
#define dbgprintf(format,...) \
	printf("["__FILE__":%d]: "format"\n", __LINE__, ##__VA_ARGS__)  
#else
#define dbgprintf(format,...)
#endif

#define MAX_SIZE 50
#define ElemType int

typedef struct {
	ElemType data[MAX_SIZE];
	int front;
	int rear;
} SqQueue;

/* Basic Operation */

void init_queue(SqQueue *qu)
{
	qu->front = qu->rear = 0;
}

bool is_empty(SqQueue qu)
{
	return qu.front == qu.rear;
}

bool enqueue(SqQueue *qu, ElemType x)
{
	if ((qu->rear + 1) % MAX_SIZE == qu->front) return false;
	qu->rear = ++qu->rear % MAX_SIZE;
	qu->data[qu->rear] = x;
	dbgprintf("Current Queue Front = %d, Rear = %d", qu->front, qu->rear);
	return true;
}

bool dequeue(SqQueue *qu, ElemType *x)
{
	if (qu->rear == qu->front) return false;
	qu->front = ++qu->front % MAX_SIZE;
	*x = qu->data[qu->front];
	return true;
}

void print_queue(SqQueue qu)
{
	ElemType x;
	int counter;
	for (counter = 1; dequeue(&qu, &x); counter++) {
		printf("%d\t", x);
		if (!(counter % 10)) printf("\n");
	}
	if (counter % 10 != 1) printf("\n");
}

int main(int argc, char **argv)
{
	printf("Sequence Queue Test\n");
	
	SqQueue qu;
	init_queue(&qu);
	int x;
	for (int i = 1; i < 37; i++) enqueue(&qu, i);
	for (int i = 0; i < 10; i++) dequeue(&qu, &x);
	for (int i = 37; i < 80; i++) enqueue(&qu, i);
	print_queue(qu);

	return 0;
}
