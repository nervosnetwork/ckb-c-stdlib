/*
utils.h

Defines basic utility functions.
*/

#ifndef CKB_C_STDLIB_CKB_UTILS_H_
#define CKB_C_STDLIB_CKB_UTILS_H_

#include "stddef.h"

/* a and b are since value,
 return 0 if a is equals to b,
 return -1 if a is less than b,
 return 1 if a is greater than b */
int ckb_epoch_number_with_fraction_cmp(uint64_t a, uint64_t b) {
  static const size_t NUMBER_OFFSET = 0;
  static const size_t NUMBER_BITS = 24;
  static const uint64_t NUMBER_MAXIMUM_VALUE = (1 << NUMBER_BITS);
  static const uint64_t NUMBER_MASK = (NUMBER_MAXIMUM_VALUE - 1);
  static const size_t INDEX_OFFSET = NUMBER_BITS;
  static const size_t INDEX_BITS = 16;
  static const uint64_t INDEX_MAXIMUM_VALUE = (1 << INDEX_BITS);
  static const uint64_t INDEX_MASK = (INDEX_MAXIMUM_VALUE - 1);
  static const size_t LENGTH_OFFSET = NUMBER_BITS + INDEX_BITS;
  static const size_t LENGTH_BITS = 16;
  static const uint64_t LENGTH_MAXIMUM_VALUE = (1 << LENGTH_BITS);
  static const uint64_t LENGTH_MASK = (LENGTH_MAXIMUM_VALUE - 1);

  /* extract a epoch */
  uint64_t a_epoch = (a >> NUMBER_OFFSET) & NUMBER_MASK;
  uint64_t a_index = (a >> INDEX_OFFSET) & INDEX_MASK;
  uint64_t a_len = (a >> LENGTH_OFFSET) & LENGTH_MASK;

  /* extract b epoch */
  uint64_t b_epoch = (b >> NUMBER_OFFSET) & NUMBER_MASK;
  uint64_t b_index = (b >> INDEX_OFFSET) & INDEX_MASK;
  uint64_t b_len = (b >> LENGTH_OFFSET) & LENGTH_MASK;

  if (a_epoch < b_epoch) {
    return -1;
  } else if (a_epoch > b_epoch) {
    return 1;
  } else {
    /* a and b is in the same epoch,
       compare a_index / a_len <=> b_index / b_len
     */
    uint64_t a_block = a_index * b_len;
    uint64_t b_block = b_index * a_len;
    /* compare block */
    if (a_block < b_block) {
      return -1;
    } else if (a_block > b_block) {
      return 1;
    } else {
      return 0;
    }
  }
}

#define CKB_SINCE_VALUE_BITS 56
#define CKB_SINCE_VALUE_MASK 0x00ffffffffffffff
#define CKB_SINCE_FLAG_METRIC_MASK 0b01100000
#define CKB_SINCE_EPOCH_FRACTION_FLAG 0b00100000

/*
 * Compare since, comparable is set to 1 when the
 * a and b since values have the same flags, otherwise comparable is set to 0.
 *
 * Return value only has meaning when the comparable is set to 1:
 * return 0 if a is equals to b,
 * return -1 if a is less than b,
 * return 1 if a is greater than b
 */
int ckb_since_cmp(uint64_t a, uint64_t b, int *comparable) {
  uint8_t a_flag = a >> CKB_SINCE_VALUE_BITS;
  uint8_t b_flag = b >> CKB_SINCE_VALUE_BITS;
  if (a_flag != b_flag) {
    *comparable = 0;
    return 0;
  }
  *comparable = 1;
  if ((a_flag & CKB_SINCE_FLAG_METRIC_MASK) == CKB_SINCE_EPOCH_FRACTION_FLAG) {
    return ckb_epoch_number_with_fraction_cmp(a, b);
  } else {
    uint64_t a_value = a & CKB_SINCE_VALUE_MASK;
    uint64_t b_value = b & CKB_SINCE_VALUE_MASK;
    if (a_value < b_value) {
      return -1;
    } else if (a_value > b_value) {
      return 1;
    } else {
      return 0;
    }
  }
}

#endif /* CKB_C_STDLIB_CKB_UTILS_H_ */
