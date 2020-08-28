#ifndef HEADER_CKB_C_STDLIB_STDARG_H_
#define HEADER_CKB_C_STDLIB_STDARG_H_

#define va_start(v, l) __builtin_va_start(v, l)
#define va_end(v) __builtin_va_end(v)
#define va_arg(v, l) __builtin_va_arg(v, l)
#define __va_copy(d, s) __builtin_va_copy(d, s)
#define va_list __builtin_va_list

#endif
