#ifndef HEADER_CKB_C_STDLIB_STDLIB_H_
#define HEADER_CKB_C_STDLIB_STDLIB_H_
#include <stddef.h>

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
typedef int (*cmpfun)(const void *, const void *);
void qsort(void *base, size_t nel, size_t width, cmpfun cmp);
int rand(void);

#endif
