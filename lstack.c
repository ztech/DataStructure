/*
 * lstack.c
 * This is Link Stack Data Structure Reference Implementation which written
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

// #define __DEBUG__

#ifdef __DEBUG__
#define dbgprintf(format,...) \
	printf("["__FILE__":%d]: "format"\n", __LINE__, ##__VA_ARGS__)  
#else
#define dbgprintf(format,...)
#endif

#define ElemType int

typedef struct LNode {
	ElemType data;
	struct LNode *next;
} LNode, *LinkStack;


/* Basic Operation */

void init_stack(LinkStack *lst)
{
	*lst = (LinkStack)malloc(sizeof(LNode));
	(*lst)->next = NULL;
}

void push(LinkStack lst, ElemType x)
{
	LinkStack p = (LinkStack)malloc(sizeof(LNode));
	p->next = NULL;
	p->data = x;
	p->next = lst->next;
	lst->next = p;
}

bool pop(LinkStack lst, ElemType *x)
{
	if (lst->next == NULL) return false;
	LinkStack p = lst->next;
	*x = p->data;
	lst->next =p->next;
	free(p);
	return true;
}

bool is_empty(LinkStack lst)
{
	dbgprintf("Is Empty? %s", lst->next == NULL ? "true" : "fasle");
	return lst->next == NULL;
}

void print_stack(LinkStack lst)
{
	LinkStack p; // Use temporary stack
	init_stack(&p);

	int counter = 1, x = 0;
	while (pop(lst, &x)) {
		printf("%d\t", x);
		push(p, x);
		if (!(counter++ % 10) && !is_empty(lst)) printf("\n");
	}
	printf("\n");

	while (pop(p, &x)) push(lst, x); // Restore original stack
}

int main(int argc, char **argv)
{
	printf("Link Stack Test\n");
	LinkStack lst;
	init_stack(&lst);

	for (int i = 1; i < 37; i++) push(lst, i);
	print_stack(lst);

	return 0;
}
