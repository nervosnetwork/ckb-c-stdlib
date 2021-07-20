#ifndef CKB_C_STDLIB_CKB_IDENTITY_H_
#define CKB_C_STDLIB_CKB_IDENTITY_H_

#include <blake2b.h>

#include "ckb_consts.h"

#define CKB_IDENTITY_LEN 21
#define RECID_INDEX 64
#define ONE_BATCH_SIZE 32768
#define PUBKEY_SIZE 33
#define MAX_WITNESS_SIZE 32768
#define BLAKE2B_BLOCK_SIZE 32
#define BLAKE160_SIZE 20
#define SECP256K1_SIGNATURE_SIZE 65
#define SECP256K1_MESSAGE_SIZE 32

enum CkbIdentityErrorCode {
  ERROR_IDENTITY_ARGUMENTS_LEN = -1,
  ERROR_IDENTITY_ENCODING = -2,
  ERROR_IDENTITY_SYSCALL = -3,

  // compatible with secp256k1 pubkey hash verification
  ERROR_IDENTITY_SECP_RECOVER_PUBKEY = -11,
  ERROR_IDENTITY_SECP_PARSE_SIGNATURE = -14,
  ERROR_IDENTITY_SECP_SERIALIZE_PUBKEY = -15,
  ERROR_IDENTITY_PUBKEY_BLAKE160_HASH = -31,
  // new error code
  ERROR_IDENTITY_LOCK_SCRIPT_HASH_NOT_FOUND = 70,
  ERROR_IDENTITY_WRONG_ARGS,
};

typedef struct CkbIdentityType {
  uint8_t flags;
  // blake160 (20 bytes) hash of lock script or pubkey
  uint8_t blake160[20];
} CkbIdentityType;

enum IdentityFlagsType {
  IdentityFlagsPubkeyHash = 0,
  IdentityFlagsOwnerLock = 1,
  IdentityFlagsAcp = 2,
};

typedef int (*validate_signature_t)(void *prefilled_data, const uint8_t *sig,
                                    size_t sig_len, const uint8_t *msg,
                                    size_t msg_len, uint8_t *output,
                                    size_t *output_len);

static int extract_witness_lock(uint8_t *witness, uint64_t len,
                                mol_seg_t *lock_bytes_seg) {
  if (len < 20) {
    return ERROR_IDENTITY_ENCODING;
  }
  uint32_t lock_length = *((uint32_t *)(&witness[16]));
  if (len < 20 + lock_length) {
    return ERROR_IDENTITY_ENCODING;
  } else {
    lock_bytes_seg->ptr = &witness[20];
    lock_bytes_seg->size = lock_length;
  }
  return CKB_SUCCESS;
}

int load_and_hash_witness(blake2b_state *ctx, size_t start, size_t index,
                          size_t source, bool hash_length) {
  uint8_t temp[ONE_BATCH_SIZE];
  uint64_t len = ONE_BATCH_SIZE;
  int ret = ckb_load_witness(temp, &len, start, index, source);
  if (ret != CKB_SUCCESS) {
    return ret;
  }
  if (hash_length) {
    blake2b_update(ctx, (char *)&len, sizeof(uint64_t));
  }
  uint64_t offset = (len > ONE_BATCH_SIZE) ? ONE_BATCH_SIZE : len;
  blake2b_update(ctx, temp, offset);
  while (offset < len) {
    uint64_t current_len = ONE_BATCH_SIZE;
    ret = ckb_load_witness(temp, &current_len, start + offset, index, source);
    if (ret != CKB_SUCCESS) {
      return ret;
    }
    uint64_t current_read =
        (current_len > ONE_BATCH_SIZE) ? ONE_BATCH_SIZE : current_len;
    blake2b_update(ctx, temp, current_read);
    offset += current_read;
  }
  return CKB_SUCCESS;
}

int validate_signature_secp256k1(void *prefilled_data, const uint8_t *sig,
                                 size_t sig_len, const uint8_t *msg,
                                 size_t msg_len, uint8_t *output,
                                 size_t *output_len) {
  (void)prefilled_data;
  int ret = 0;
  if (*output_len < BLAKE160_SIZE) {
    return ERROR_IDENTITY_ARGUMENTS_LEN;
  }
  if (sig_len != SECP256K1_SIGNATURE_SIZE) {
    return ERROR_IDENTITY_ARGUMENTS_LEN;
  }
  if (msg_len != SECP256K1_MESSAGE_SIZE) {
    return ERROR_IDENTITY_ARGUMENTS_LEN;
  }

  /* Load signature */
  secp256k1_context context;
  uint8_t secp_data[CKB_SECP256K1_DATA_SIZE];
  ret = ckb_secp256k1_custom_verify_only_initialize(&context, secp_data);
  if (ret != 0) {
    return ret;
  }

  secp256k1_ecdsa_recoverable_signature signature;
  if (secp256k1_ecdsa_recoverable_signature_parse_compact(
          &context, &signature, sig, sig[RECID_INDEX]) == 0) {
    return ERROR_IDENTITY_SECP_PARSE_SIGNATURE;
  }

  /* Recover pubkey */
  secp256k1_pubkey pubkey;
  if (secp256k1_ecdsa_recover(&context, &pubkey, &signature, msg) != 1) {
    return ERROR_IDENTITY_SECP_RECOVER_PUBKEY;
  }

  uint8_t temp[PUBKEY_SIZE];
  size_t pubkey_size = PUBKEY_SIZE;
  if (secp256k1_ec_pubkey_serialize(&context, temp, &pubkey_size, &pubkey,
                                    SECP256K1_EC_COMPRESSED) != 1) {
    return ERROR_IDENTITY_SECP_SERIALIZE_PUBKEY;
  }
  blake2b_state ctx;
  blake2b_init(&ctx, BLAKE2B_BLOCK_SIZE);
  blake2b_update(&ctx, temp, pubkey_size);
  blake2b_final(&ctx, temp, BLAKE2B_BLOCK_SIZE);

  memcpy(output, temp, BLAKE160_SIZE);
  *output_len = BLAKE160_SIZE;

  return ret;
}

int generate_sighash_all(uint8_t *msg, size_t msg_len) {
  int ret;
  uint64_t len = 0;
  unsigned char temp[MAX_WITNESS_SIZE];
  uint64_t read_len = MAX_WITNESS_SIZE;
  uint64_t witness_len = MAX_WITNESS_SIZE;

  if (msg_len < BLAKE2B_BLOCK_SIZE) {
    return ERROR_IDENTITY_ARGUMENTS_LEN;
  }

  /* Load witness of first input */
  ret = ckb_load_witness(temp, &read_len, 0, 0, CKB_SOURCE_GROUP_INPUT);
  if (ret != CKB_SUCCESS) {
    return ERROR_IDENTITY_SYSCALL;
  }
  witness_len = read_len;
  if (read_len > MAX_WITNESS_SIZE) {
    read_len = MAX_WITNESS_SIZE;
  }

  /* load signature */
  mol_seg_t lock_bytes_seg;
  ret = extract_witness_lock(temp, read_len, &lock_bytes_seg);
  if (ret != 0) {
    return ERROR_IDENTITY_ENCODING;
  }

  /* Load tx hash */
  unsigned char tx_hash[BLAKE2B_BLOCK_SIZE];
  len = BLAKE2B_BLOCK_SIZE;
  ret = ckb_load_tx_hash(tx_hash, &len, 0);
  if (ret != CKB_SUCCESS) {
    return ret;
  }
  if (len != BLAKE2B_BLOCK_SIZE) {
    return ERROR_IDENTITY_SYSCALL;
  }

  /* Prepare sign message */
  blake2b_state blake2b_ctx;
  blake2b_init(&blake2b_ctx, BLAKE2B_BLOCK_SIZE);
  blake2b_update(&blake2b_ctx, tx_hash, BLAKE2B_BLOCK_SIZE);

  /* Clear lock field to zero, then digest the first witness
   * lock_bytes_seg.ptr actually points to the memory in temp buffer
   * */
  memset((void *)lock_bytes_seg.ptr, 0, lock_bytes_seg.size);
  blake2b_update(&blake2b_ctx, (char *)&witness_len, sizeof(uint64_t));
  blake2b_update(&blake2b_ctx, temp, read_len);

  // remaining of first witness
  if (read_len < witness_len) {
    ret = load_and_hash_witness(&blake2b_ctx, read_len, 0,
                                CKB_SOURCE_GROUP_INPUT, false);
    if (ret != CKB_SUCCESS) {
      return ERROR_IDENTITY_SYSCALL;
    }
  }

  // Digest same group witnesses
  size_t i = 1;
  while (1) {
    ret =
        load_and_hash_witness(&blake2b_ctx, 0, i, CKB_SOURCE_GROUP_INPUT, true);
    if (ret == CKB_INDEX_OUT_OF_BOUND) {
      break;
    }
    if (ret != CKB_SUCCESS) {
      return ERROR_IDENTITY_SYSCALL;
    }
    i += 1;
  }

  // Digest witnesses that not covered by inputs
  i = (size_t)ckb_calculate_inputs_len();
  while (1) {
    ret = load_and_hash_witness(&blake2b_ctx, 0, i, CKB_SOURCE_INPUT, true);
    if (ret == CKB_INDEX_OUT_OF_BOUND) {
      break;
    }
    if (ret != CKB_SUCCESS) {
      return ERROR_IDENTITY_SYSCALL;
    }
    i += 1;
  }

  blake2b_final(&blake2b_ctx, msg, BLAKE2B_BLOCK_SIZE);

  return 0;
}

int verify_sighash_all(uint8_t *pubkey_hash, uint8_t *sig, uint32_t sig_len,
                       validate_signature_t func) {
  int ret = 0;
  uint8_t msg[BLAKE2B_BLOCK_SIZE];
  ret = generate_sighash_all(msg, sizeof(msg));
  if (ret != 0) {
    return ret;
  }
  uint8_t output_pubkey_hash[BLAKE160_SIZE];
  size_t output_len = BLAKE160_SIZE;
  ret = func(NULL, sig, sig_len, msg, sizeof(msg), output_pubkey_hash,
             &output_len);
  if (ret != 0) {
    return ret;
  }

  if (memcmp(pubkey_hash, output_pubkey_hash, BLAKE160_SIZE) != 0) {
    return ERROR_IDENTITY_PUBKEY_BLAKE160_HASH;
  }

  return 0;
}

bool is_lock_script_hash_present(uint8_t *lock_script_hash) {
  int err = 0;
  size_t i = 0;
  while (true) {
    uint8_t buff[BLAKE2B_BLOCK_SIZE];
    uint64_t len = BLAKE2B_BLOCK_SIZE;
    err = ckb_checked_load_cell_by_field(buff, &len, 0, i, CKB_SOURCE_INPUT,
                                         CKB_CELL_FIELD_LOCK_HASH);
    if (err == CKB_INDEX_OUT_OF_BOUND) {
      break;
    }
    if (err != 0) {
      break;
    }

    if (memcmp(lock_script_hash, buff, BLAKE160_SIZE) == 0) {
      return true;
    }
    i += 1;
  }
  return false;
}

int ckb_verify_identity(CkbIdentityType *id, uint8_t *sig, uint32_t sig_len) {
  if (id->flags == IdentityFlagsPubkeyHash) {
    if (sig == NULL || sig_len != SECP256K1_SIGNATURE_SIZE) {
      return ERROR_IDENTITY_WRONG_ARGS;
    }
    return verify_sighash_all(id->blake160, sig, sig_len,
                              validate_signature_secp256k1);
  } else if (id->flags == IdentityFlagsOwnerLock) {
    if (is_lock_script_hash_present(id->blake160)) {
      return 0;
    } else {
      return ERROR_IDENTITY_LOCK_SCRIPT_HASH_NOT_FOUND;
    }
  } else {
    return CKB_INVALID_DATA;
  }
}
#endif
