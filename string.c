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
#include <malloc.h>
#define dbgprintf(format,...) \
	printf("["__FILE__":%d]: "format"\n", __LINE__, ##__VA_ARGS__)  
#else
#define dbgprintf(format,...)
#endif

#define MAX_SIZE 50

typedef struct {
	char str[MAX_SIZE+1];
	int length;
} StaticString; // Only ADT

typedef struct {
	char *ch;
	int length;
} String;

/* Basic Operation */

int str_len(char *ch)
{
	int len = 0;
	while(*ch) {
		++len;
		++ch;
	}
	dbgprintf("String Length: %d", len);
	return len;
}

int strlength(String str)
{
	return str.length;
}

static inline void str_cpy(char *src, char *dst)
{
	while(*src) *dst++ = *src++;
}

static inline void str_ncpy(char *src, char *dst, int len)
{
	for (int i = 0; i < len; i++) *dst++ = *src++;
}

bool str_assign(String *str, char* ch)
{
	if (str->ch) free(str->ch);

	if (!*ch) {
		str->ch = NULL;
		str->length = 0;
	} else {
		str->length = str_len(ch);
		dbgprintf("str->length = %d", str->length);
		str->ch = malloc(sizeof(char) * (str->length + 1));
		if (!str->ch) return false;
		dbgprintf("String size: %ld", malloc_usable_size(str->ch));
		str_cpy(ch, str->ch);
		str->ch[str->length] = '\0'; // Add end flag 
	}
	return true;
}

int str_cmp(String s1, String s2)
{
	for (int i = 0; i < s1.length && i < s2.length; i++)
		if (s1.ch[i] != s2.ch[i]) return s1.ch[i] - s2.ch[i];

	return s1.length - s2.length;
}

bool concat(String *str, String str1, String str2)
{
	if (str->ch) free(str->ch);

	str->length = str1.length + str2.length;
	str->ch = malloc(sizeof(char) * (str->length + 1));
	if (!str->ch) return false;

	str_cpy(str1.ch, str->ch);
	str_cpy(str2.ch, str->ch + str1.length);
	str->ch[str->length] = '\0';
	return true;
}

bool substring(String *substr, String str, int pos, int len)
{
	if (pos < 0 || len < 0 || pos >= str.length || pos + len >= str.length)
		return false;

	if (substr->ch) free(substr->ch);

	if (!len) {
		substr->ch = NULL;
		substr->length = 0;
	} else {
		substr->ch = malloc(sizeof(char) * (len + 1));
		str_ncpy(str.ch + pos, substr->ch, len);
		substr->ch[len] = '\0';
		substr->length = len;
	}
	return true;
		
}

bool clearstring(String *str)
{
	if(str->ch) {
		free(str->ch);
		str->ch = NULL;
	}

	str->length = 0;
	return true;
}

/* Pattern Matching */

int str_index(String str, String substr)
{
	int i = 0, j = 0;
	while (i < str.length && j < substr.length) {
		dbgprintf("Current Str : %d", i);
		if (str.ch[i] == substr.ch[j]) {
			++i;
			++j;
		} else {
			i -= j - 1;
			j = 0;
		}
	}

	if (j == substr.length) return i - j;
	return -1;
}

void getnext(String substr, int next[])
{
	int i = 0, j = -1;
	next[0] = -1;
	while (i < substr.length -1) {
		dbgprintf("Next Status : i = %d, j = %d, ch[i] = %c, ch[j] = %c", i, j, \
				substr.ch[i], j < 0 ? '\0' : substr.ch[j]);
		if (j == -1 || substr.ch[i] == substr.ch[j]) {
			++i;
			++j;
			next[i] = j;
		} else {
			j = next[j];
		}
	}
	for (i = 0; i < substr.length; i++) dbgprintf("next[%d] = %d", i, next[i]);
}

void getnextval(String substr, int nextval[])
{
	int i = 0, j = -1;
	nextval[0] = -1;
	bool e = false;
	while (i < substr.length - 1) {
		if (j == -1 || e) {
			++i;
			++j;
			e = substr.ch[i] == substr.ch[j];
			if (e) nextval[i] = nextval[j];
			else nextval[i] = j;
		} else {
			j = nextval[j];
		}
	}
}

int str_kmp(String str, String substr)
{
	int *next = malloc(sizeof(int) * substr.length);
	// getnext(substr, next);
	getnextval(substr, next);
	int i = 0, j = 0;
	while (i < str.length && j < substr.length) {
		if (j == -1 || str.ch[i] == substr.ch[j]) {
			++i;
			++j;
		} else {
			j = next[j];
		}
	}
	free(next);
	if (j == substr.length) return i - j;
	return -1;
}

int main(int argc, char **argv)
{
	printf("String Test\n");
	
	String str = {NULL, 0};
	str_assign(&str, "Hello, world!");
	printf("String Assign : %s\n", str.ch);

	String str2 = {NULL, 0};
	str_assign(&str2, " By Zombie");

	String str3 = {NULL, 0};
	concat(&str3, str, str2);
	printf("String Concatenate : %s\n", str3.ch);


	String str4 = {NULL, 0};
	str_assign(&str4, "abcdefgh");
	String str5 = {NULL, 0};
	substring(&str5, str4, 2, 3);
	printf("SubString : %s\n", str5.ch);


	String str6 = {NULL, 0};
	str_assign(&str6, "ABABACAABABCABABABABBABACAB");
	String str7 = {NULL, 0};
	str_assign(&str7, "ABABABB");
	int index = str_index(str6, str7);
	printf("String Index : %d\n", index);
	index = str_kmp(str6, str7);
	printf("String KMP Index : %d\n", index);

	clearstring(&str);
	return 0;
}
