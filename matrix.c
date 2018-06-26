/*
 * string.c
 * This is String Data Structure Reference Implementation which written
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
#include <malloc.h>
#define dbgprintf(format,...) \
	printf("["__FILE__":%d]: "format"\n", __LINE__, ##__VA_ARGS__)  
#else
#define dbgprintf(format,...)
#endif

#define MAX_SIZE 50

#define MAT_M 4
#define MAT_N 5

/* Basic Operation */

void trans_mat(int *A, int *B, int m, int n)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			*(B + m * j + i) = *(A + n * i + j);
}

void print_mat(int *A, int m, int n)
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) printf("%d\t", *(A + n * i + j));
		printf("\n");
	}
}

int main(int argc, char **argv)
{
	printf("Matrix Test\n");
	
	int A[MAT_M][MAT_N] = { { 1,  2,  3,  4,  5}, \
				{ 6,  7,  8,  9, 10}, \
				{11, 12, 13, 14, 15}, \
				{16, 17, 18, 19, 20} };
	int B[MAT_N][MAT_N];
	trans_mat((int *)A, (int *)B, MAT_M, MAT_N);
	printf("A:\n");
	print_mat((int *)A, MAT_M, MAT_N);
	printf("Transformed A:\n");
	print_mat((int *)B, MAT_N, MAT_M);

	return 0;
}
