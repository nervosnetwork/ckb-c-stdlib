#ifndef MOLECULE2_READER_H
#define MOLECULE2_READER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef mol2_printf
#define mol2_printf printf
#endif
#ifndef MOL2_EXIT
#define MOL2_EXIT exit
#endif

#ifndef MOL2_PANIC
#define MOL2_PANIC(err)                                   \
  do {                                                    \
    mol2_printf("Error at %s: %d\n", __FILE__, __LINE__); \
    MOL2_EXIT(err);                                       \
  } while (0)
#endif

/*
 * This part is not for normal users.
 */
//
// referenced API or macros
//
#ifndef ASSERT
#define ASSERT(s) ((void)0)
#endif

#ifndef MIN
#define MIN(a, b) ((a > b) ? (b) : (a))
#endif
#ifndef MAX
#define MAX(a, b) ((a > b) ? (a) : (b))
#endif

typedef uint32_t mol2_num_t;  // Item Id
typedef uint8_t mol2_errno;   // Error Number
#define MOL2_NUM_T_SIZE 4

// predefined type
// If the types defined in schema is fundamental type:
// 1. dynvec of byte(<byte>) or
// 2. array([byte; N])
// They will be converted to the type mol2_cursor_t automatically
// 3. byte
// it will be converted to uint8_t.

// predefined type
// If the types defined in schema:
// 1. the name is same as below (case insensitive)
// 2. the type is matched (e.g. Uint32 should have type with [byte; 4])
// they will be converted to the corresponding types automatically instead of
// just returning raw byte array.
//
typedef uint64_t Uint64;  // [byte; 8]
typedef int64_t Int64;    // [byte; 8]
typedef uint32_t Uint32;  // [byte; 4]
typedef int32_t Int32;    // [byte; 4]
typedef uint16_t Uint16;  // [byte; 2]
typedef int16_t Int16;    // [byte; 2]
typedef uint8_t Uint8;    // [byte; 1]
typedef int8_t Int8;      // [byte; 1]

/* Error Numbers */

#define MOL2_OK 0x00
#define MOL2_ERR 0xff

#define MOL2_ERR_TOTAL_SIZE 0x01
#define MOL2_ERR_HEADER 0x02
#define MOL2_ERR_OFFSET 0x03
#define MOL2_ERR_UNKNOWN_ITEM 0x04
#define MOL2_ERR_INDEX_OUT_OF_BOUNDS 0x05
#define MOL2_ERR_FIELD_COUNT 0x06
#define MOL2_ERR_DATA 0x07
#define MOL2_ERR_OVERFLOW 0x08

// converting function
// format: convert_to_${Type}
#define SWAP(a, b, t) \
  {                   \
    (t) = (a);        \
    (a) = (b);        \
    (b) = (t);        \
  }
#define is_le2()      \
  ((union {           \
     uint16_t i;      \
     unsigned char c; \
   }){.i = 1}         \
       .c)

void change_endian(uint8_t *ptr, int size);
/**
 * read from a data source, with offset, up to "len" bytes into ptr.
 * the memory size of "ptr" is "len".
 *
 * Return the length actually written. It may be smaller than "len".
 *
 * The "args" will be passed into "read" function as the first argument.
 */
typedef uint32_t (*mol2_source_t)(uintptr_t arg[], uint8_t *ptr, uint32_t len,
                                  uint32_t offset);

#define MAX_CACHE_SIZE 2048
#define MIN_CACHE_SIZE 64

// data source with cache support
typedef struct mol2_data_source_t {
  // function "read" might have more arguments
  uintptr_t args[4];
  // total size of the data source. It is always true:
  // offset+size <= total_size
  uint32_t total_size;

  mol2_source_t read;
  // start point of the cache
  // if [offset, size) is in [start_point, start_point+cache_size), it returns
  // memory in cache directly otherwise, it will try to load first (like cache
  // miss)
  uint32_t start_point;
  uint32_t cache_size;
  // it's normally same as MAX_CACHE_SIZE.
  // modify it for testing purpose
  uint32_t max_cache_size;
  // variable length structure
  // it's true length is calculated by "MOL2_DATA_SOURCE_LEN".
  uint8_t cache[];
} mol2_data_source_t;

#define MOL2_DATA_SOURCE_LEN(cache_size) \
  (sizeof(mol2_data_source_t) + (cache_size))

#define DEFAULT_DATA_SOURCE_LENGTH (sizeof(mol2_data_source_t) + MAX_CACHE_SIZE)

/**
 * --------------- MUST READ ----------------------
 * This is the most important data struct in this file, MUST READ!
 * The data_source is to fetch data from external, like memory, disk, or some
 * others. It is with cache support. You can get an idea how to implement one
 * from functions: "mol2_source_memory" and "mol2_make_cursor_from_memory".
 *
 * The offset and size, is an "view"/"slice" of the data source.
 *
 * When a new cursor is generated from an old one,
 * the "data_source" must be copied. The offset and size can be different.
 * Currently, there is no way to convert one data source to another.
 *
 */
typedef struct mol2_cursor_t {
  uint32_t offset;  // offset of slice
  uint32_t size;    // size of slice
  mol2_data_source_t *data_source;
} mol2_cursor_t;

// a sample source over memory
uint32_t mol2_source_memory(uintptr_t args[], uint8_t *ptr, uint32_t len,
                            uint32_t offset);
mol2_cursor_t mol2_make_cursor_from_memory(const void *memory, uint32_t size);

uint32_t mol2_read_at(const mol2_cursor_t *cur, uint8_t *buff,
                      uint32_t buff_len);

// Bytes segment.
typedef struct {
  uint8_t *ptr;     // Pointer
  mol2_num_t size;  // Full size
} mol2_seg_t;

// Unpacked Union
typedef struct {
  mol2_num_t item_id;    // Item Id
  mol2_cursor_t cursor;  // Cursor
} mol2_union_t;

// Result for returning segment.
typedef struct {
  mol2_errno errno;   // Error Number
  mol2_cursor_t cur;  // Cursor
} mol2_cursor_res_t;

void mol2_add_offset(mol2_cursor_t *cur, uint32_t offset);
void mol2_sub_size(mol2_cursor_t *cur, uint32_t shrinked_size);
void mol2_validate(const mol2_cursor_t *cur);

mol2_num_t mol2_unpack_number(const mol2_cursor_t *cursor);

mol2_errno mol2_verify_fixed_size(const mol2_cursor_t *input,
                                  mol2_num_t total_size);

mol2_errno mol2_fixvec_verify(const mol2_cursor_t *input, mol2_num_t item_size);

bool mol2_option_is_none(const mol2_cursor_t *input);
mol2_union_t mol2_union_unpack(const mol2_cursor_t *input);
mol2_num_t mol2_fixvec_length(const mol2_cursor_t *input);
mol2_num_t mol2_dynvec_length(const mol2_cursor_t *input);
mol2_num_t mol2_table_actual_field_count(const mol2_cursor_t *input);
bool mol2_table_has_extra_fields(const mol2_cursor_t *input,
                                 mol2_num_t field_count);
mol2_cursor_t mol2_slice_by_offset(const mol2_cursor_t *input,
                                   mol2_num_t offset, mol2_num_t size);

mol2_cursor_res_t mol2_fixvec_slice_by_index(const mol2_cursor_t *input,
                                             mol2_num_t item_size,
                                             mol2_num_t item_index);

mol2_cursor_res_t mol2_dynvec_slice_by_index(const mol2_cursor_t *input,
                                             mol2_num_t item_index);

mol2_cursor_t mol2_table_slice_by_index(const mol2_cursor_t *input,
                                        mol2_num_t field_index);

mol2_cursor_t mol2_fixvec_slice_raw_bytes(const mol2_cursor_t *input);
Uint64 convert_to_Uint64(mol2_cursor_t *cur);
Int64 convert_to_Int64(mol2_cursor_t *cur);
Uint32 convert_to_Uint32(mol2_cursor_t *cur);
Int32 convert_to_Int32(mol2_cursor_t *cur);
Uint16 convert_to_Uint16(mol2_cursor_t *cur);
Int16 convert_to_Int16(mol2_cursor_t *cur);
Uint8 convert_to_Uint8(mol2_cursor_t *cur);
Int8 convert_to_Int8(mol2_cursor_t *cur);
mol2_cursor_t convert_to_array(mol2_cursor_t *cur);
mol2_cursor_t convert_to_rawbytes(mol2_cursor_t *cur);

#ifndef MOLECULEC_C2_DECLARATION_ONLY

// cur->offset = cur->offset + offset
void mol2_add_offset(mol2_cursor_t *cur, uint32_t offset) {
  uint32_t res;
  if (__builtin_add_overflow(cur->offset, offset, &res)) {
    MOL2_PANIC(MOL2_ERR_OVERFLOW);
  }
  cur->offset = res;
}

// cur->size = cur->size - shrinked_size
void mol2_sub_size(mol2_cursor_t *cur, uint32_t shrinked_size) {
  uint32_t res;
  if (__builtin_sub_overflow(cur->size, shrinked_size, &res)) {
    MOL2_PANIC(MOL2_ERR_OVERFLOW);
  }
  cur->size = res;
}

// mol2_unpack_number(cur) / 4 - 1
uint32_t mol2_get_item_count(mol2_cursor_t *cur) {
  uint32_t count = mol2_unpack_number(cur) / 4;
  if (count == 0) {
    MOL2_PANIC(MOL2_ERR_OVERFLOW);
  }
  return count - 1;
}
// item_size * item_count + offset
uint32_t mol2_calculate_offset(uint32_t item_size, uint32_t item_count,
                               uint32_t offset) {
  uint32_t mul_res;
  if (__builtin_mul_overflow(item_size, item_count, &mul_res)) {
    MOL2_PANIC(MOL2_ERR_OVERFLOW);
  }
  uint32_t sum_res;
  if (__builtin_add_overflow(mul_res, offset, &sum_res)) {
    MOL2_PANIC(MOL2_ERR_OVERFLOW);
  }
  return sum_res;
}

void mol2_validate(const mol2_cursor_t *cur) {
  uint32_t res;
  if (__builtin_add_overflow(cur->offset, cur->size, &res)) {
    MOL2_PANIC(MOL2_ERR_OVERFLOW);
  }
  if (res > cur->data_source->total_size) {
    mol2_printf("total_size(%d) > offset(%d) + size(%d)\n",
                cur->data_source->total_size, cur->offset, cur->size);
    MOL2_PANIC(MOL2_ERR_INDEX_OUT_OF_BOUNDS);
  }
}

mol2_errno mol2_verify_fixed_size(const mol2_cursor_t *input,
                                  mol2_num_t total_size) {
  return input->size == total_size ? MOL2_OK : MOL2_ERR_TOTAL_SIZE;
}

mol2_errno mol2_fixvec_verify(const mol2_cursor_t *input,
                              mol2_num_t item_size) {
  if (input->size < MOL2_NUM_T_SIZE) {
    return MOL2_ERR_HEADER;
  }
  mol2_num_t item_count = mol2_unpack_number(input);
  if (item_count == 0) {
    return input->size == MOL2_NUM_T_SIZE ? MOL2_OK : MOL2_ERR_TOTAL_SIZE;
  }
  // mol2_num_t total_size = mol2_NUM_T_SIZE + item_size * item_count;
  mol2_num_t total_size =
      mol2_calculate_offset(item_size, item_count, MOL2_NUM_T_SIZE);
  return input->size == total_size ? MOL2_OK : MOL2_ERR_TOTAL_SIZE;
}

bool mol2_option_is_none(const mol2_cursor_t *input) {
  return input->size == 0;
}

mol2_union_t mol2_union_unpack(const mol2_cursor_t *input) {
  mol2_union_t ret;
  ret.item_id = mol2_unpack_number(input);
  ret.cursor = *input;  // must copy
  //   ret.cursor.offset = input->offset + mol2_NUM_T_SIZE;
  //   ret.cursor.size = input->size - mol2_NUM_T_SIZE;
  mol2_add_offset(&ret.cursor, MOL2_NUM_T_SIZE);
  mol2_sub_size(&ret.cursor, MOL2_NUM_T_SIZE);
  mol2_validate(&ret.cursor);
  return ret;
}

mol2_num_t mol2_fixvec_length(const mol2_cursor_t *input) {
  return mol2_unpack_number(input);
}

mol2_num_t mol2_dynvec_length(const mol2_cursor_t *input) {
  if (input->size == MOL2_NUM_T_SIZE) {
    return 0;
  } else {
    mol2_cursor_t cur = *input;
    mol2_add_offset(&cur, MOL2_NUM_T_SIZE);
    mol2_sub_size(&cur, MOL2_NUM_T_SIZE);
    mol2_validate(&cur);
    // return (mol2_unpack_number(&cur) / 4) - 1;
    return mol2_get_item_count(&cur);
  }
}

mol2_num_t mol2_table_actual_field_count(const mol2_cursor_t *input) {
  return mol2_dynvec_length(input);
}

bool mol2_table_has_extra_fields(const mol2_cursor_t *input,
                                 mol2_num_t field_count) {
  return mol2_table_actual_field_count(input) > field_count;
}

mol2_cursor_t mol2_slice_by_offset(const mol2_cursor_t *input,
                                   mol2_num_t offset, mol2_num_t size) {
  mol2_cursor_t cur = *input;

  //  cur.offset = input->offset + offset;
  mol2_add_offset(&cur, offset);
  cur.size = size;
  mol2_validate(&cur);
  return cur;
}

mol2_cursor_res_t mol2_slice_by_offset2(const mol2_cursor_t *input,
                                        mol2_num_t offset, mol2_num_t size) {
  mol2_cursor_t cur = *input;

  //  cur.offset = input->offset + offset;
  mol2_add_offset(&cur, offset);
  cur.size = size;
  mol2_validate(&cur);

  mol2_cursor_res_t res;
  res.errno = MOL2_OK;
  res.cur = cur;
  return res;
}

mol2_cursor_res_t mol2_fixvec_slice_by_index(const mol2_cursor_t *input,
                                             mol2_num_t item_size,
                                             mol2_num_t item_index) {
  mol2_cursor_res_t res;
  res.cur = *input;
  mol2_num_t item_count = mol2_unpack_number(input);
  if (item_index >= item_count) {
    res.errno = MOL2_ERR_INDEX_OUT_OF_BOUNDS;
  } else {
    res.errno = MOL2_OK;
    //    res.cur.offset = input->offset + mol2_NUM_T_SIZE + item_size *
    //    item_index;
    uint32_t offset =
        mol2_calculate_offset(item_size, item_index, MOL2_NUM_T_SIZE);
    mol2_add_offset(&res.cur, offset);
    res.cur.size = item_size;
    mol2_validate(&res.cur);
  }
  return res;
}

mol2_cursor_res_t mol2_dynvec_slice_by_index(const mol2_cursor_t *input,
                                             mol2_num_t item_index) {
  mol2_cursor_res_t res;
  res.cur = *input;
  struct mol2_cursor_t temp = *input;

  mol2_num_t total_size = mol2_unpack_number(input);
  if (total_size == MOL2_NUM_T_SIZE) {
    res.errno = MOL2_ERR_INDEX_OUT_OF_BOUNDS;
  } else {
    // temp.offset = input->offset + mol2_NUM_T_SIZE;
    mol2_add_offset(&temp, MOL2_NUM_T_SIZE);
    // mol2_num_t item_count = (mol2_unpack_number(&temp) / 4) - 1;
    mol2_num_t item_count = mol2_get_item_count(&temp);

    if (item_index >= item_count) {
      res.errno = MOL2_ERR_INDEX_OUT_OF_BOUNDS;
    } else {
      temp.offset = input->offset;
      uint32_t temp_offset =
          mol2_calculate_offset(MOL2_NUM_T_SIZE, item_index + 1, 0);
      mol2_add_offset(&temp, temp_offset);

      mol2_num_t item_start = mol2_unpack_number(&temp);
      if (item_index + 1 == item_count) {
        res.errno = MOL2_OK;
        res.cur.offset = input->offset;
        mol2_add_offset(&res.cur, item_start);
        res.cur.size = total_size;
        mol2_sub_size(&res.cur, item_start);
      } else {
        temp.offset = input->offset;
        uint32_t calc_offset =
            mol2_calculate_offset(MOL2_NUM_T_SIZE, item_index + 2, 0);
        mol2_add_offset(&temp, calc_offset);

        mol2_num_t item_end = mol2_unpack_number(&temp);
        res.errno = MOL2_OK;
        res.cur.offset = input->offset;
        mol2_add_offset(&res.cur, item_start);
        res.cur.size = item_end;
        mol2_sub_size(&res.cur, item_start);
      }
    }
  }
  if (res.errno == MOL2_OK) {
    mol2_validate(&res.cur);
  }
  return res;
}

mol2_cursor_t mol2_table_slice_by_index(const mol2_cursor_t *input,
                                        mol2_num_t field_index) {
  mol2_cursor_res_t res = mol2_dynvec_slice_by_index(input, field_index);
  ASSERT(res.errno == 0);
  return res.cur;
}

mol2_cursor_t mol2_fixvec_slice_raw_bytes(const mol2_cursor_t *input) {
  mol2_cursor_t cur = *input;
  mol2_add_offset(&cur, MOL2_NUM_T_SIZE);
  cur.size = mol2_unpack_number(input);
  mol2_validate(&cur);
  return cur;
}

Uint64 convert_to_Uint64(mol2_cursor_t *cur) {
  uint64_t ret;
  uint32_t len = mol2_read_at(cur, (uint8_t *)&ret, sizeof(ret));
  if (len != sizeof(ret)) {
    MOL2_PANIC(MOL2_ERR_DATA);
  }
  change_endian((uint8_t *)&ret, sizeof(ret));
  return ret;
}

Int64 convert_to_Int64(mol2_cursor_t *cur) {
  int64_t ret;
  uint32_t len = mol2_read_at(cur, (uint8_t *)&ret, sizeof(ret));
  if (len != sizeof(ret)) {
    MOL2_PANIC(MOL2_ERR_DATA);
  }
  change_endian((uint8_t *)&ret, sizeof(ret));
  return ret;
}

Uint32 convert_to_Uint32(mol2_cursor_t *cur) {
  uint32_t ret;
  uint32_t len = mol2_read_at(cur, (uint8_t *)&ret, sizeof(ret));
  if (len != sizeof(ret)) {
    MOL2_PANIC(MOL2_ERR_DATA);
  }
  change_endian((uint8_t *)&ret, sizeof(ret));
  return ret;
}

Int32 convert_to_Int32(mol2_cursor_t *cur) {
  int32_t ret;
  uint32_t len = mol2_read_at(cur, (uint8_t *)&ret, sizeof(ret));
  if (len != sizeof(ret)) {
    MOL2_PANIC(MOL2_ERR_DATA);
  }
  change_endian((uint8_t *)&ret, sizeof(ret));
  return ret;
}

Uint16 convert_to_Uint16(mol2_cursor_t *cur) {
  uint16_t ret;
  uint32_t len = mol2_read_at(cur, (uint8_t *)&ret, sizeof(ret));
  if (len != sizeof(ret)) {
    MOL2_PANIC(MOL2_ERR_DATA);
  }
  change_endian((uint8_t *)&ret, sizeof(ret));
  return ret;
}

Int16 convert_to_Int16(mol2_cursor_t *cur) {
  int16_t ret;
  uint32_t len = mol2_read_at(cur, (uint8_t *)&ret, sizeof(ret));
  ASSERT(len == sizeof(ret));
  if (len != sizeof(ret)) {
    MOL2_PANIC(MOL2_ERR_DATA);
  }
  return ret;
}

Uint8 convert_to_Uint8(mol2_cursor_t *cur) {
  uint8_t ret;
  uint32_t len = mol2_read_at(cur, (uint8_t *)&ret, sizeof(ret));
  if (len != sizeof(ret)) {
    MOL2_PANIC(MOL2_ERR_DATA);
  }
  change_endian((uint8_t *)&ret, sizeof(ret));
  return ret;
}

Int8 convert_to_Int8(mol2_cursor_t *cur) {
  int8_t ret;
  uint32_t len = mol2_read_at(cur, (uint8_t *)&ret, sizeof(ret));
  if (len != sizeof(ret)) {
    MOL2_PANIC(MOL2_ERR_DATA);
  }
  change_endian((uint8_t *)&ret, sizeof(ret));
  return ret;
}

mol2_cursor_t convert_to_array(mol2_cursor_t *cur) { return *cur; }

mol2_cursor_t convert_to_rawbytes(mol2_cursor_t *cur) {
  return mol2_fixvec_slice_raw_bytes(cur);
}

void change_endian(uint8_t *ptr, int size) {
  if (is_le2()) return;
  if (size == 0) return;

  if (size % 2 != 0) {
    MOL2_PANIC(MOL2_ERR_DATA);
  }
  uint8_t t = 0;
  for (int i = 0; i < size / 2; i++) {
    SWAP(ptr[i], ptr[size - 1 - i], t);
  }
}

// this is a sample implementation over memory
uint32_t mol2_source_memory(uintptr_t args[], uint8_t *ptr, uint32_t len,
                            uint32_t offset) {
  uint32_t mem_len = (uint32_t)args[1];
  ASSERT(offset < mem_len);
  uint32_t remaining_len = mem_len - offset;

  uint32_t min_len = MIN(remaining_len, len);
  uint8_t *start_mem = (uint8_t *)args[0];
  ASSERT((offset + min_len) <= mem_len);
  memcpy(ptr, start_mem + offset, min_len);
  return min_len;
}

// this is a sample implementation over memory
mol2_cursor_t mol2_make_cursor_from_memory(const void *memory, uint32_t size) {
  mol2_cursor_t cur;
  cur.offset = 0;
  cur.size = size;
  // init data source
  static mol2_data_source_t s_data_source = {0};

  s_data_source.read = mol2_source_memory;
  s_data_source.total_size = size;
  s_data_source.args[0] = (uintptr_t)memory;
  s_data_source.args[1] = (uintptr_t)size;

  s_data_source.cache_size = 0;
  s_data_source.start_point = 0;
  s_data_source.max_cache_size = MAX_CACHE_SIZE;
  cur.data_source = &s_data_source;
  return cur;
}

/**
 * mol2_read_at reads MIN(cur->size, buff_len) bytes from data source
 * "cur" into buff. It returns that number.
 *
 * If the return number is smaller than MIN(cur->size, buff_len), the data
 * source might encounter problem. There are some reasons:
 * 1. The data in data source is not consistent with molecule file (too
 * small).
 * 2. I/O error. It's impossible for memory data source or Syscall
 *
 * If a cache miss is triggered: use "read" to load from data source to the
 * the cache. Then use copy from cache to "buff".
 **/
uint32_t mol2_read_at(const mol2_cursor_t *cur, uint8_t *buff,
                      uint32_t buff_len) {
  uint32_t read_len = MIN(cur->size, buff_len);

  mol2_data_source_t *ds = cur->data_source;
  // beyond cache size, "read" it directly.
  if (read_len > ds->max_cache_size) {
    return ds->read(ds->args, buff, read_len, cur->offset);
  }

  // cache miss
  if (cur->offset < ds->start_point ||
      ((cur->offset + read_len) > ds->start_point + ds->cache_size)) {
    uint32_t size =
        ds->read(ds->args, ds->cache, ds->max_cache_size, cur->offset);
    if (size < read_len) {
      MOL2_PANIC(MOL2_ERR_DATA);
      return 0;
    }
    // update cache setting
    ds->cache_size = size;
    ds->start_point = cur->offset;
    if (ds->cache_size > ds->max_cache_size) {
      MOL2_PANIC(MOL2_ERR_OVERFLOW);
      return 0;
    }
  }
  // cache hit
  if (cur->offset < ds->start_point ||
      (cur->offset - ds->start_point) > ds->max_cache_size) {
    MOL2_PANIC(MOL2_ERR_OVERFLOW);
    return 0;
  }
  uint8_t *read_point = ds->cache + cur->offset - ds->start_point;
  if ((read_point + read_len) > (ds->cache + ds->cache_size)) {
    MOL2_PANIC(MOL2_ERR_OVERFLOW);
    return 0;
  }

  memcpy(buff, read_point, read_len);
  return read_len;
}

mol2_num_t mol2_unpack_number(const mol2_cursor_t *cursor) {
  uint8_t src[4];
  uint32_t len = mol2_read_at(cursor, src, 4);
  if (len != 4) {
    MOL2_PANIC(MOL2_ERR_DATA);
  }
  if (is_le2()) {
    return *(const uint32_t *)src;
  } else {
    uint32_t output = 0;
    uint8_t *dst = (uint8_t *)&output;
    dst[3] = src[0];
    dst[2] = src[1];
    dst[1] = src[2];
    dst[0] = src[3];
    return output;
  }
}

#endif  // MOLECULEC_C2_DECLARATION_ONLY

/*
 * Undef macros which are internal use only.
 */

#undef is_le2

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MOLECULE2_READER_H */
