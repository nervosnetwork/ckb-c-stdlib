#ifndef CKB_C_STDLIB_CKB_STREAMING_H_
#define CKB_C_STDLIB_CKB_STREAMING_H_

#ifndef CKB_ONE_BATCH_SIZE
#define CKB_ONE_BATCH_SIZE 16384
#endif /* CKB_ONE_BATCH_SIZE */

#include "blake2b.h"
#include "ckb_syscalls.h"

typedef int (*load_function)(void *, uint64_t *, size_t, size_t, size_t);

int ckb_load_and_hash(blake2b_state *ctx, size_t start, size_t index,
                      size_t source, load_function f) {
  uint8_t temp[CKB_ONE_BATCH_SIZE];
  uint64_t len = CKB_ONE_BATCH_SIZE;
  int ret = f(temp, &len, start, index, source);
  if (ret != CKB_SUCCESS) {
    return ret;
  }
  blake2b_update(ctx, (char *)&len, sizeof(uint64_t));
  uint64_t offset = (len > CKB_ONE_BATCH_SIZE) ? CKB_ONE_BATCH_SIZE : len;
  blake2b_update(ctx, temp, offset);
  while (offset < len) {
    uint64_t current_len = CKB_ONE_BATCH_SIZE;
    ret = f(temp, &current_len, start + offset, index, source);
    if (ret != CKB_SUCCESS) {
      return ret;
    }
    uint64_t current_read =
        (current_len > CKB_ONE_BATCH_SIZE) ? CKB_ONE_BATCH_SIZE : current_len;
    blake2b_update(ctx, temp, current_read);
    offset += current_read;
  }
  return CKB_SUCCESS;
}

int ckb_hash_cell(blake2b_state *ctx, size_t index_code, size_t source) {
  return ckb_load_and_hash(ctx, 0, index_code, source, ckb_load_cell);
}

int ckb_hash_input(blake2b_state *ctx, size_t index_code, size_t source) {
  return ckb_load_and_hash(ctx, 0, index_code, source, ckb_load_input);
}

#endif /* CKB_C_STDLIB_CKB_STREAMING_H_ */
