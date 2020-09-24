#ifndef CKB_C_STDLIB_STDLIB_H_
#define CKB_C_STDLIB_STDLIB_H_
#include <entry.h>
#include <internal/types.h>

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
typedef int (*cmpfun)(const void *, const void *);
void qsort(void *base, size_t nel, size_t width, cmpfun cmp);
int rand(void);
typedef int (*cmp_func_t)(const void *a, const void *b);
void *bsearch(const void *key, const void *base, size_t num, size_t size,
              cmp_func_t cmp);

#endif /* CKB_C_STDLIB_STDLIB_H_ */
