/*
 * lqueue.c
 * This is Link Queue Data Structure Reference Implementation which written
 * purely in C Language.
 * Copyright 2018 Zombie<teng@tenglog.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
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

#define __DEBUG__

#ifdef __DEBUG__
#define dbgprintf(format,...) \
	printf("["__FILE__":%d]: "format"\n", __LINE__, ##__VA_ARGS__)  
#else
#define dbgprintf(format,...)
#endif

#define ElemType int

typedef struct QNode {
	ElemType data;
	struct QNode *next;
} QNode;

typedef struct {
	QNode *front;
	QNode *rear;
} LinkQueue;

/* Basic Operation */

void init_queue(LinkQueue *lqu)
{
	lqu->front = lqu->rear = NULL;
}

bool is_empty(LinkQueue lqu)
{
	return lqu.rear == NULL || lqu.front == NULL;
}

void enqueue(LinkQueue *lqu, ElemType x)
{
	QNode *p = malloc(sizeof(QNode));
	p->data = x;
	p->next = NULL;
	if (lqu->rear == NULL) {
		lqu->rear = lqu->front = p;
	} else {
		lqu->rear->next = p;
		lqu->rear = p;
	}
}

bool dequeue(LinkQueue *lqu, ElemType *x)
{
	if (lqu->front == NULL) return false;
	QNode *p = lqu->front;
	lqu->front = lqu->front->next;
	if (lqu->front == NULL) lqu->rear = NULL;
	*x = p->data;
	free(p);
	return true;
}

void print_queue(LinkQueue lqu)
{
	int counter = 1;
	ElemType x;
	for(; dequeue(&lqu, &x); counter++) {
		printf("%d\t", x);
		if (counter % 10 == 0 && !is_empty(lqu)) printf("\n");
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	printf("Link Queue Test\n");
	LinkQueue lqu;
	init_queue(&lqu);
	for (int i = 1; i < 191; i++) enqueue(&lqu, i);
	print_queue(lqu);

	return 0;
}
