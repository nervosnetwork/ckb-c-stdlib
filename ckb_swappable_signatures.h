#ifndef CKB_C_STDLIB_CKB_SWAPPABLE_SIGNATURES_H_
#define CKB_C_STDLIB_CKB_SWAPPABLE_SIGNATURES_H_

#include "ckb_dlfcn.h"

#ifdef CKB_SWAPPABLE_SIGNATURES_DEBUG
#define DEBUG(s) ckb_debug(s)
#else
#define DEBUG(s)
#endif /* CKB_SWAPPABLE_SIGNATURES_DEBUG */

typedef int (*verify_function)(void *, const uint8_t *, size_t, const uint8_t *,
                               size_t, uint8_t *, size_t *);

typedef struct {
  uint8_t *code_buffer;
  uint64_t code_buffer_size;
  uint8_t *prefilled_data_buffer;
  size_t prefilled_buffer_size;
  verify_function verify_func;
} CkbSwappableSignatureInstance;

int ckb_initialize_swappable_signature(
    const uint8_t *code_hash, uint8_t hash_type,
    CkbSwappableSignatureInstance *instance) {
  void *handle = NULL;
  size_t consumed_size = 0;
  int ret = ckb_dlopen2(code_hash, hash_type, instance->code_buffer,
                        instance->code_buffer_size, &handle, &consumed_size);
  if (ret != CKB_SUCCESS) {
    return ret;
  }
  instance->code_buffer_size = consumed_size;
  int (*load_prefilled_data_func)(void *, size_t *);
  *(void **)(&load_prefilled_data_func) =
      ckb_dlsym(handle, "load_prefilled_data");
  if (load_prefilled_data_func == NULL) {
    DEBUG("Error loading load prefilled data func!");
    return CKB_INVALID_DATA;
  }
  ret = load_prefilled_data_func(instance->prefilled_data_buffer,
                                 &instance->prefilled_buffer_size);
  if (ret != CKB_SUCCESS) {
    DEBUG("Error loading prefilled data!");
    return ret;
  }
  *(void **)(&instance->verify_func) = ckb_dlsym(handle, "validate_signature");
  if (instance->verify_func == NULL) {
    DEBUG("Error loading validate signature func!");
    return CKB_INVALID_DATA;
  }
  return CKB_SUCCESS;
}

#endif /* CKB_C_STDLIB_CKB_SWAPPABLE_SIGNATURES_H_ */
