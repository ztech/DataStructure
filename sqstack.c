/*
 * sqstack.c
 * This is Sequence Stack Data Structure Reference Implementation which written
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

#define MAX_SIZE 50
#define ElemType int

typedef struct {
	ElemType data[MAX_SIZE];
	int top;
} SqStack;

/* Basic Operation */

void init_stack(SqStack *st)
{
	st->top = -1;
}

bool pop(SqStack *st, ElemType *x)
{
	if (st->top == -1) return false;
	*x = st->data[st->top--];
	return true;
}

bool push(SqStack *st, ElemType x)
{
	if (st->top == MAX_SIZE - 1) return false;
	st->data[++st->top] = x;
	return true;
}

bool is_empty(SqStack st)
{
	return st.top == -1;
}


void print_stack(SqStack st)
{
	SqStack p = st;
	int i = 1, x;
	while (pop(&p, &x)) {
		printf("%d\t", x);
		if (i++ % 10 == 0) printf("\n");
	}
	if (i % 10 != 1) printf("\n");
}

int main(int argc, char **argv)
{
	printf("Sequence Stack Test\n");
	
	SqStack st;
	init_stack(&st);
	printf("Is Stack Empty? %s\n", is_empty(st) ? "true" : "false");
	for (int i = 20; i > 0; i--) push(&st, i);
	print_stack(st);
	printf("Is Stack Empty? %s\n", is_empty(st) ? "true" : "false");

	return 0;
}
