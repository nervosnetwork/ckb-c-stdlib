#ifndef CKB_C_STDLIB_CKB_SYSCALLS_H_
#define CKB_C_STDLIB_CKB_SYSCALLS_H_

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "ckb_consts.h"
#include "ckb_syscall_apis.h"

int ckb_checked_load_tx_hash(void* addr, uint64_t* len, size_t offset) {
  uint64_t old_len = *len;
  int ret = ckb_load_tx_hash(addr, len, offset);
  if (ret == CKB_SUCCESS && (*len) > old_len) {
    ret = CKB_LENGTH_NOT_ENOUGH;
  }
  return ret;
}

int ckb_checked_load_script_hash(void* addr, uint64_t* len, size_t offset) {
  uint64_t old_len = *len;
  int ret = ckb_load_script_hash(addr, len, offset);
  if (ret == CKB_SUCCESS && (*len) > old_len) {
    ret = CKB_LENGTH_NOT_ENOUGH;
  }
  return ret;
}

int ckb_checked_load_cell(void* addr, uint64_t* len, size_t offset,
                          size_t index, size_t source) {
  uint64_t old_len = *len;
  int ret = ckb_load_cell(addr, len, offset, index, source);
  if (ret == CKB_SUCCESS && (*len) > old_len) {
    ret = CKB_LENGTH_NOT_ENOUGH;
  }
  return ret;
}

int ckb_checked_load_input(void* addr, uint64_t* len, size_t offset,
                           size_t index, size_t source) {
  uint64_t old_len = *len;
  int ret = ckb_load_input(addr, len, offset, index, source);
  if (ret == CKB_SUCCESS && (*len) > old_len) {
    ret = CKB_LENGTH_NOT_ENOUGH;
  }
  return ret;
}

int ckb_checked_load_header(void* addr, uint64_t* len, size_t offset,
                            size_t index, size_t source) {
  uint64_t old_len = *len;
  int ret = ckb_load_header(addr, len, offset, index, source);
  if (ret == CKB_SUCCESS && (*len) > old_len) {
    ret = CKB_LENGTH_NOT_ENOUGH;
  }
  return ret;
}

int ckb_checked_load_witness(void* addr, uint64_t* len, size_t offset,
                             size_t index, size_t source) {
  uint64_t old_len = *len;
  int ret = ckb_load_witness(addr, len, offset, index, source);
  if (ret == CKB_SUCCESS && (*len) > old_len) {
    ret = CKB_LENGTH_NOT_ENOUGH;
  }
  return ret;
}

int ckb_checked_load_script(void* addr, uint64_t* len, size_t offset) {
  uint64_t old_len = *len;
  int ret = ckb_load_script(addr, len, offset);
  if (ret == CKB_SUCCESS && (*len) > old_len) {
    ret = CKB_LENGTH_NOT_ENOUGH;
  }
  return ret;
}

int ckb_checked_load_transaction(void* addr, uint64_t* len, size_t offset) {
  uint64_t old_len = *len;
  int ret = ckb_load_transaction(addr, len, offset);
  if (ret == CKB_SUCCESS && (*len) > old_len) {
    ret = CKB_LENGTH_NOT_ENOUGH;
  }
  return ret;
}

int ckb_checked_load_cell_by_field(void* addr, uint64_t* len, size_t offset,
                                   size_t index, size_t source, size_t field) {
  uint64_t old_len = *len;
  int ret = ckb_load_cell_by_field(addr, len, offset, index, source, field);
  if (ret == CKB_SUCCESS && (*len) > old_len) {
    ret = CKB_LENGTH_NOT_ENOUGH;
  }
  return ret;
}

int ckb_checked_load_header_by_field(void* addr, uint64_t* len, size_t offset,
                                     size_t index, size_t source,
                                     size_t field) {
  uint64_t old_len = *len;
  int ret = ckb_load_header_by_field(addr, len, offset, index, source, field);
  if (ret == CKB_SUCCESS && (*len) > old_len) {
    ret = CKB_LENGTH_NOT_ENOUGH;
  }
  return ret;
}

int ckb_checked_load_input_by_field(void* addr, uint64_t* len, size_t offset,
                                    size_t index, size_t source, size_t field) {
  uint64_t old_len = *len;
  int ret = ckb_load_input_by_field(addr, len, offset, index, source, field);
  if (ret == CKB_SUCCESS && (*len) > old_len) {
    ret = CKB_LENGTH_NOT_ENOUGH;
  }
  return ret;
}

int ckb_checked_load_cell_data(void* addr, uint64_t* len, size_t offset,
                               size_t index, size_t source) {
  uint64_t old_len = *len;
  int ret = ckb_load_cell_data(addr, len, offset, index, source);
  if (ret == CKB_SUCCESS && (*len) > old_len) {
    ret = CKB_LENGTH_NOT_ENOUGH;
  }
  return ret;
}

/* load the actual witness for the current type verify group.
   use this instead of ckb_load_witness if type contract needs args to verify
   input/output.
 */
int ckb_load_actual_type_witness(uint8_t* buf, uint64_t* len, size_t index,
                                 size_t* type_source) {
  *type_source = CKB_SOURCE_GROUP_INPUT;
  uint64_t tmp_len = 0;
  if (ckb_load_cell_by_field(NULL, &tmp_len, 0, 0, CKB_SOURCE_GROUP_INPUT,
                             CKB_CELL_FIELD_CAPACITY) ==
      CKB_INDEX_OUT_OF_BOUND) {
    *type_source = CKB_SOURCE_GROUP_OUTPUT;
  }

  return ckb_checked_load_witness(buf, len, 0, index, *type_source);
}

/* calculate inputs length */
int ckb_calculate_inputs_len() {
  uint64_t len = 0;
  /* lower bound, at least tx has one input */
  int lo = 0;
  /* higher bound */
  int hi = 4;
  int ret;
  /* try to load input until failing to increase lo and hi */
  while (1) {
    ret = ckb_load_input_by_field(NULL, &len, 0, hi, CKB_SOURCE_INPUT,
                                  CKB_INPUT_FIELD_SINCE);
    if (ret == CKB_SUCCESS) {
      lo = hi;
      hi *= 2;
    } else {
      break;
    }
  }

  /* now we get our lower bound and higher bound,
   count number of inputs by binary search */
  int i;
  while (lo + 1 != hi) {
    i = (lo + hi) / 2;
    ret = ckb_load_input_by_field(NULL, &len, 0, i, CKB_SOURCE_INPUT,
                                  CKB_INPUT_FIELD_SINCE);
    if (ret == CKB_SUCCESS) {
      lo = i;
    } else {
      hi = i;
    }
  }
  /* now lo is last input index and hi is length of inputs */
  return hi;
}

/*
 * Look for a dep cell with specific code hash, code_hash should be a buffer
 * with 32 bytes.
 */
int ckb_look_for_dep_with_hash2(const uint8_t* code_hash, uint8_t hash_type,
                                size_t* index) {
  size_t current = 0;
  size_t field =
      (hash_type == 1) ? CKB_CELL_FIELD_TYPE_HASH : CKB_CELL_FIELD_DATA_HASH;
  while (current < SIZE_MAX) {
    uint64_t len = 32;
    uint8_t hash[32];

    int ret = ckb_load_cell_by_field(hash, &len, 0, current,
                                     CKB_SOURCE_CELL_DEP, field);
    switch (ret) {
      case CKB_ITEM_MISSING:
        break;
      case CKB_SUCCESS:
        if (memcmp(code_hash, hash, 32) == 0) {
          /* Found a match */
          *index = current;
          return CKB_SUCCESS;
        }
        break;
      default:
        return CKB_INDEX_OUT_OF_BOUND;
    }
    current++;
  }
  return CKB_INDEX_OUT_OF_BOUND;
}

int ckb_look_for_dep_with_hash(const uint8_t* data_hash, size_t* index) {
  return ckb_look_for_dep_with_hash2(data_hash, 0, index);
}

#ifndef CKB_STDLIB_NO_SYSCALL_IMPL

#define memory_barrier() asm volatile("fence" ::: "memory")

static inline long __internal_syscall(long n, long _a0, long _a1, long _a2,
                                      long _a3, long _a4, long _a5) {
  register long a0 asm("a0") = _a0;
  register long a1 asm("a1") = _a1;
  register long a2 asm("a2") = _a2;
  register long a3 asm("a3") = _a3;
  register long a4 asm("a4") = _a4;
  register long a5 asm("a5") = _a5;

#ifdef __riscv_32e
  register long syscall_id asm("t0") = n;
#else
  register long syscall_id asm("a7") = n;
#endif

  asm volatile("scall"
               : "+r"(a0)
               : "r"(a1), "r"(a2), "r"(a3), "r"(a4), "r"(a5), "r"(syscall_id));
  /*
   * Syscalls might modify memory sent as pointer, adding a barrier here ensures
   * gcc won't do incorrect optimization.
   */
  memory_barrier();

  return a0;
}

#define syscall(n, a, b, c, d, e, f)                                           \
  __internal_syscall(n, (long)(a), (long)(b), (long)(c), (long)(d), (long)(e), \
                     (long)(f))

int ckb_exit(int8_t code) { return syscall(SYS_exit, code, 0, 0, 0, 0, 0); }

int ckb_load_tx_hash(void* addr, uint64_t* len, size_t offset) {
  volatile uint64_t inner_len = *len;
  int ret = syscall(SYS_ckb_load_tx_hash, addr, &inner_len, offset, 0, 0, 0);
  *len = inner_len;
  return ret;
}

int ckb_load_script_hash(void* addr, uint64_t* len, size_t offset) {
  volatile uint64_t inner_len = *len;
  int ret =
      syscall(SYS_ckb_load_script_hash, addr, &inner_len, offset, 0, 0, 0);
  *len = inner_len;
  return ret;
}

int ckb_load_cell(void* addr, uint64_t* len, size_t offset, size_t index,
                  size_t source) {
  volatile uint64_t inner_len = *len;
  int ret =
      syscall(SYS_ckb_load_cell, addr, &inner_len, offset, index, source, 0);
  *len = inner_len;
  return ret;
}

int ckb_load_input(void* addr, uint64_t* len, size_t offset, size_t index,
                   size_t source) {
  volatile uint64_t inner_len = *len;
  int ret =
      syscall(SYS_ckb_load_input, addr, &inner_len, offset, index, source, 0);
  *len = inner_len;
  return ret;
}

int ckb_load_header(void* addr, uint64_t* len, size_t offset, size_t index,
                    size_t source) {
  volatile uint64_t inner_len = *len;
  int ret =
      syscall(SYS_ckb_load_header, addr, &inner_len, offset, index, source, 0);
  *len = inner_len;
  return ret;
}

int ckb_load_witness(void* addr, uint64_t* len, size_t offset, size_t index,
                     size_t source) {
  volatile uint64_t inner_len = *len;
  int ret =
      syscall(SYS_ckb_load_witness, addr, &inner_len, offset, index, source, 0);
  *len = inner_len;
  return ret;
}

int ckb_load_script(void* addr, uint64_t* len, size_t offset) {
  volatile uint64_t inner_len = *len;
  int ret = syscall(SYS_ckb_load_script, addr, &inner_len, offset, 0, 0, 0);
  *len = inner_len;
  return ret;
}

int ckb_load_transaction(void* addr, uint64_t* len, size_t offset) {
  volatile uint64_t inner_len = *len;
  int ret =
      syscall(SYS_ckb_load_transaction, addr, &inner_len, offset, 0, 0, 0);
  *len = inner_len;
  return ret;
}

int ckb_load_cell_by_field(void* addr, uint64_t* len, size_t offset,
                           size_t index, size_t source, size_t field) {
  volatile uint64_t inner_len = *len;
  int ret = syscall(SYS_ckb_load_cell_by_field, addr, &inner_len, offset, index,
                    source, field);
  *len = inner_len;
  return ret;
}

int ckb_load_header_by_field(void* addr, uint64_t* len, size_t offset,
                             size_t index, size_t source, size_t field) {
  volatile uint64_t inner_len = *len;
  int ret = syscall(SYS_ckb_load_header_by_field, addr, &inner_len, offset,
                    index, source, field);
  *len = inner_len;
  return ret;
}

int ckb_load_input_by_field(void* addr, uint64_t* len, size_t offset,
                            size_t index, size_t source, size_t field) {
  volatile uint64_t inner_len = *len;
  int ret = syscall(SYS_ckb_load_input_by_field, addr, &inner_len, offset,
                    index, source, field);
  *len = inner_len;
  return ret;
}

int ckb_load_cell_data(void* addr, uint64_t* len, size_t offset, size_t index,
                       size_t source) {
  volatile uint64_t inner_len = *len;
  int ret = syscall(SYS_ckb_load_cell_data, addr, &inner_len, offset, index,
                    source, 0);
  *len = inner_len;
  return ret;
}

int ckb_debug(const char* s) {
  return syscall(SYS_ckb_debug, s, 0, 0, 0, 0, 0);
}

#endif /* CKB_STDLIB_NO_SYSCALL_IMPL */

#endif /* CKB_C_STDLIB_CKB_SYSCALLS_H_ */
