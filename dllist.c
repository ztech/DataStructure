/*
 * dlist.c
 * This is Dual Link List Data Structure Reference Implementation which written
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

typedef struct DLNode {
	ElemType data;
	struct DLNode *prior;
	struct DLNode *next;
} DLNode, *DualLinkList;

/* Basic Operation */

bool create_list_end(DualLinkList *L, ElemType e[], int n)
{
	*L = (DualLinkList)malloc(sizeof(DLNode));
	(*L)->prior = NULL;
	(*L)->next = NULL;
	DualLinkList r = *L;
	for (int i = 0; i < n; i++) {
		DualLinkList p = (DualLinkList)malloc(sizeof(DLNode));
		p->data = e[i];
		r->next = p;
		p->prior = r;
		r = p;
	}
	r->next = NULL;
	return true;
}

bool create_list_front(DualLinkList *L, ElemType e[], int n)
{
	*L = (DualLinkList)malloc(sizeof(DLNode));
	(*L)->prior = NULL;
	(*L)->next = NULL;
	DualLinkList r = *L;
	for (int i = 0; i < n; i++) {
		DualLinkList p = (DualLinkList)malloc(sizeof(DLNode));
		p->data = e[i];
        p->prior = (*L);
		p->next = (*L)->next;
        if ((*L)->next) (*L)->next->prior = p;
        (*L)->next = p;
	}
	return true;
}

void print_list(DualLinkList L)
{
	int counter = 1;
	for (L = L->next; L != NULL; L = L->next) { // Ignore first head pointer
		printf("%d\t", L->data);
		if (counter % 10 == 0 && L->next != NULL) printf("\n");
		counter++;
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	printf("Dual Link List Test\n");
	DualLinkList L;
	int a[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	create_list_front(&L, a, 20);
	print_list(L);

	return 0;
}
