#ifndef CKB_C_STDLIB_CKB_SYSCALL_UTILS_H_
#define CKB_C_STDLIB_CKB_SYSCALL_UTILS_H_

#include <string.h>

#include "ckb_consts.h"
#include "ckb_syscall_apis.h"

#ifndef CKB_STDLIB_NO_SYSCALL_IMPL

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

int ckb_exec_cell(const uint8_t* code_hash, uint8_t hash_type, uint32_t offset,
                  uint32_t length, int argc, const char* argv[]) {
  size_t index = SIZE_MAX;
  int ret = ckb_look_for_dep_with_hash2(code_hash, hash_type, &index);
  if (ret != CKB_SUCCESS) {
    return ret;
  }
  size_t bounds = ((size_t)offset << 32) | length;
  return ckb_exec(index, CKB_SOURCE_CELL_DEP, 0, bounds, argc, argv);
}

int ckb_spawn_cell(const uint8_t* code_hash, uint8_t hash_type, uint32_t offset,
                   uint32_t length, spawn_args_t* spawn_args) {
  size_t index = SIZE_MAX;
  int ret = ckb_look_for_dep_with_hash2(code_hash, hash_type, &index);
  if (ret != CKB_SUCCESS) {
    return ret;
  }
  size_t bounds = ((size_t)offset << 32) | length;
  return ckb_spawn(index, CKB_SOURCE_CELL_DEP, 0, bounds, spawn_args);
}

#endif /* CKB_STDLIB_NO_SYSCALL_IMPL */

#endif /* CKB_C_STDLIB_CKB_SYSCALL_UTILS_H_ */
