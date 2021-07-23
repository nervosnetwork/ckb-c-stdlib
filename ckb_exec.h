#ifndef _CBK_C_STDLIB_CKB_EXEC_H_
#define _CBK_C_STDLIB_CKB_EXEC_H_
#include <stdint.h>
#include <string.h>

#ifndef CKB_EXEC_MAX_ARGS_COUNT
#define CKB_EXEC_MAX_ARGS_COUNT 64
#endif

#ifndef CKB_EXEC_MAX_BUFF_LEN
#define CKB_EXEC_MAX_BUFF_LEN (32 * 1024)
#endif

enum CkbExecErrorCodeType {
  ERROR_EXEC_OUT_OF_BOUNDS = 30,
  ERROR_EXEC_INVALID_HEX,
};

typedef struct CkbBinaryArgsType {
  uint32_t argc;
  uint16_t len[CKB_EXEC_MAX_ARGS_COUNT];
  uint8_t* args[CKB_EXEC_MAX_ARGS_COUNT];

  uint32_t used_buff;
  uint8_t buff[CKB_EXEC_MAX_BUFF_LEN];
} CkbBinaryArgsType;

typedef struct CkbHexArgsType {
  uint32_t argc;
  char* argv[CKB_EXEC_MAX_ARGS_COUNT];

  uint32_t used_buff;
  char buff[CKB_EXEC_MAX_BUFF_LEN];
} CkbHexArgsType;

static int _exec_getbin(uint8_t x, uint8_t* out) {
  if (x >= '0' && x <= '9') {
    *out = x - '0';
  } else if (x >= 'A' && x <= 'F') {
    *out = x - 'A' + 10;
  } else if (x >= 'a' && x <= 'f') {
    *out = x - 'a' + 10;
  } else {
    return ERROR_EXEC_INVALID_HEX;
  }
  return 0;
}

static void _exec_gethex(uint8_t x, char* out) {
  static char s_mapping[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                             '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  out[0] = s_mapping[(x >> 4) & 0x0F];
  out[1] = s_mapping[x & 0x0F];
}

int _exec_safe_strlen(const char* s, uint32_t limit, uint32_t* length) {
  if (s == NULL) return ERROR_EXEC_OUT_OF_BOUNDS;

  uint32_t count = 0;
  for (; *s; s++) {
    count++;
    if (count > limit) return ERROR_EXEC_OUT_OF_BOUNDS;
  }
  *length = count;
  return 0;
}

// the string length of "hex" should be no more than bin_len*2
// "length" returns the bytes count written in "bin"
static int _exec_hex2bin(const char* hex, uint8_t* bin, uint32_t bin_len,
                         uint32_t* length) {
  uint32_t limit = 2 * bin_len;
  uint32_t hex_len;
  int err = _exec_safe_strlen(hex, limit, &hex_len);
  if (err != 0) return err;
  if (hex_len % 2 != 0) return ERROR_EXEC_INVALID_HEX;
  *length = hex_len / 2;
  if (*length > bin_len) {
    return ERROR_EXEC_OUT_OF_BOUNDS;
  }
  for (uint32_t i = 0; i < *length; i++) {
    uint8_t high, low;
    err = _exec_getbin(hex[i * 2], &high);
    if (err != 0) return err;
    err = _exec_getbin(hex[i * 2 + 1], &low);
    if (err != 0) return err;
    bin[i] = high << 4 | low;
  }
  return 0;
}

static int _exec_bin2hex(const uint8_t* bin, uint32_t bin_len, char* hex,
                         uint32_t hex_len, uint32_t* length) {
  if (hex_len < (bin_len * 2 + 1)) {
    return ERROR_EXEC_OUT_OF_BOUNDS;
  }
  for (uint32_t i = 0; i < bin_len; i++) {
    _exec_gethex(bin[i], hex + 2 * i);
  }
  // NULL terminated
  *(hex + bin_len * 2) = 0;

  *length = 2 * bin_len + 1;
  return 0;
}

// encode argc, argv passed from main function, into CkbBinaryArgsType struct.
int ckb_exec_decode(int argc, char* argv[], CkbBinaryArgsType* args) {
  int err = 0;
  if (argc > CKB_EXEC_MAX_ARGS_COUNT) {
    return ERROR_EXEC_OUT_OF_BOUNDS;
  }

  args->argc = argc;
  args->used_buff = 0;

  for (int i = 0; i < argc; i++) {
    uint32_t length;
    err = _exec_hex2bin(argv[i], args->buff + args->used_buff,
                        CKB_EXEC_MAX_BUFF_LEN - args->used_buff, &length);
    if (err != 0) return err;
    args->len[i] = length;
    args->args[i] = args->buff + args->used_buff;

    args->used_buff += length;
    if (args->used_buff > CKB_EXEC_MAX_BUFF_LEN)
      return ERROR_EXEC_OUT_OF_BOUNDS;
  }

  return 0;
}

// use ckb_exec_reset and ckb_exec_append to generate CkbBinaryArgsType from
// scratch
void ckb_exec_reset(CkbBinaryArgsType* args) {
  args->argc = 0;
  args->used_buff = 0;
}

int ckb_exec_append(CkbBinaryArgsType* args, uint8_t* data, uint8_t len) {
  if (args->argc >= CKB_EXEC_MAX_ARGS_COUNT) {
    return ERROR_EXEC_INVALID_HEX;
  }
  uint8_t* p = args->buff + args->used_buff;
  args->used_buff += len;
  if (args->used_buff > CKB_EXEC_MAX_BUFF_LEN) {
    return ERROR_EXEC_OUT_OF_BOUNDS;
  }

  memcpy(p, data, len);
  args->args[args->argc] = p;
  args->len[args->argc] = len;

  args->argc++;

  return 0;
}

// convert binary format to hex format.
// the fields argc, argv in CkbHexArgsType can be used directly in exec
int ckb_exec_encode(CkbBinaryArgsType* in, CkbHexArgsType* out) {
  int err = 0;

  if (in->argc > CKB_EXEC_MAX_ARGS_COUNT) {
    return ERROR_EXEC_OUT_OF_BOUNDS;
  }

  out->argc = in->argc;
  out->used_buff = 0;

  for (uint32_t i = 0; i < in->argc; i++) {
    uint8_t* p = in->args[i];
    uint32_t len = in->len[i];
    uint32_t length;
    if (out->used_buff >= CKB_EXEC_MAX_BUFF_LEN) {
      return ERROR_EXEC_OUT_OF_BOUNDS;
    }
    err = _exec_bin2hex(p, len, out->buff + out->used_buff,
                        CKB_EXEC_MAX_BUFF_LEN - out->used_buff, &length);
    if (err != 0) return err;
    out->argv[i] = out->buff + out->used_buff;

    out->used_buff += length;
  }

  return 0;
}

#endif  // _CBK_C_STDLIB_CKB_EXEC_H_
