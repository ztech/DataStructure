/*
 * sqlist.c
 * This is Sequence List Data Structure Reference Implementation which written
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
	int length;
} SqList;

/* Basic Operation */

void init_list(SqList *L)
{
	L->length = 0;
}

bool add_elem(SqList *L, ElemType e)
{
	if (L->length >= MAX_SIZE) return false;
	dbgprintf("Current Length : %d", L->length);
	L->data[L->length] = e;
	L->length++;
	dbgprintf("Current data[1] = %d", L->data[1]);
	return true;
}

void print_list(SqList L)
{
	for (int i = 0; i < L.length / 10 + 1; i++) {
		int num = i + 10 > L.length ? L.length : i + 10;
		for (int j = i; j < num; j++) printf("%d\t", L.data[j]);
		printf("\n");
	}
}

int main(int argc, char **argv)
{
	printf("Sequence List Test\n");
	
	SqList L;
	init_list(&L);
	dbgprintf("Current L.length = %d", L.length);
	add_elem(&L, 1);
	add_elem(&L, 2);
	print_list(L);

	return 0;
}
