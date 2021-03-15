
#ifndef _BLOCKCHAIN_API2_H_
#define _BLOCKCHAIN_API2_H_

#define MOLECULEC2_VERSION 6001
#define MOLECULE2_API_VERSION_MIN 5000

#include "molecule2_reader.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ----forward declaration--------
struct Uint32Type;
struct Uint32VTable;
struct Uint32VTable *GetUint32VTable(void);
struct Uint32Type make_Uint32(mol2_cursor_t *cur);
uint32_t Uint32_len_impl(struct Uint32Type *);
uint8_t Uint32_get_impl(struct Uint32Type *, uint32_t, bool *);
struct Uint64Type;
struct Uint64VTable;
struct Uint64VTable *GetUint64VTable(void);
struct Uint64Type make_Uint64(mol2_cursor_t *cur);
uint32_t Uint64_len_impl(struct Uint64Type *);
uint8_t Uint64_get_impl(struct Uint64Type *, uint32_t, bool *);
struct Uint128Type;
struct Uint128VTable;
struct Uint128VTable *GetUint128VTable(void);
struct Uint128Type make_Uint128(mol2_cursor_t *cur);
uint32_t Uint128_len_impl(struct Uint128Type *);
uint8_t Uint128_get_impl(struct Uint128Type *, uint32_t, bool *);
struct Byte32Type;
struct Byte32VTable;
struct Byte32VTable *GetByte32VTable(void);
struct Byte32Type make_Byte32(mol2_cursor_t *cur);
uint32_t Byte32_len_impl(struct Byte32Type *);
uint8_t Byte32_get_impl(struct Byte32Type *, uint32_t, bool *);
struct Uint256Type;
struct Uint256VTable;
struct Uint256VTable *GetUint256VTable(void);
struct Uint256Type make_Uint256(mol2_cursor_t *cur);
uint32_t Uint256_len_impl(struct Uint256Type *);
uint8_t Uint256_get_impl(struct Uint256Type *, uint32_t, bool *);
struct BytesType;
struct BytesVTable;
struct BytesVTable *GetBytesVTable(void);
struct BytesType make_Bytes(mol2_cursor_t *cur);
uint32_t Bytes_len_impl(struct BytesType *);
uint8_t Bytes_get_impl(struct BytesType *, uint32_t, bool *);
struct BytesOptType;
struct BytesOptVTable;
struct BytesOptVTable *GetBytesOptVTable(void);
struct BytesOptType make_BytesOpt(mol2_cursor_t *cur);
bool BytesOpt_is_none_impl(struct BytesOptType *);
bool BytesOpt_is_some_impl(struct BytesOptType *);
mol2_cursor_t BytesOpt_unwrap_impl(struct BytesOptType *);
struct BytesVecType;
struct BytesVecVTable;
struct BytesVecVTable *GetBytesVecVTable(void);
struct BytesVecType make_BytesVec(mol2_cursor_t *cur);
uint32_t BytesVec_len_impl(struct BytesVecType *);
mol2_cursor_t BytesVec_get_impl(struct BytesVecType *, uint32_t, bool *);
struct Byte32VecType;
struct Byte32VecVTable;
struct Byte32VecVTable *GetByte32VecVTable(void);
struct Byte32VecType make_Byte32Vec(mol2_cursor_t *cur);
uint32_t Byte32Vec_len_impl(struct Byte32VecType *);
mol2_cursor_t Byte32Vec_get_impl(struct Byte32VecType *, uint32_t, bool *);
struct ScriptOptType;
struct ScriptOptVTable;
struct ScriptOptVTable *GetScriptOptVTable(void);
struct ScriptOptType make_ScriptOpt(mol2_cursor_t *cur);
bool ScriptOpt_is_none_impl(struct ScriptOptType *);
bool ScriptOpt_is_some_impl(struct ScriptOptType *);
struct ScriptType ScriptOpt_unwrap_impl(struct ScriptOptType *);
struct ProposalShortIdType;
struct ProposalShortIdVTable;
struct ProposalShortIdVTable *GetProposalShortIdVTable(void);
struct ProposalShortIdType make_ProposalShortId(mol2_cursor_t *cur);
uint32_t ProposalShortId_len_impl(struct ProposalShortIdType *);
uint8_t ProposalShortId_get_impl(struct ProposalShortIdType *, uint32_t,
                                 bool *);
struct UncleBlockVecType;
struct UncleBlockVecVTable;
struct UncleBlockVecVTable *GetUncleBlockVecVTable(void);
struct UncleBlockVecType make_UncleBlockVec(mol2_cursor_t *cur);
uint32_t UncleBlockVec_len_impl(struct UncleBlockVecType *);
struct UncleBlockType UncleBlockVec_get_impl(struct UncleBlockVecType *,
                                             uint32_t, bool *);
struct TransactionVecType;
struct TransactionVecVTable;
struct TransactionVecVTable *GetTransactionVecVTable(void);
struct TransactionVecType make_TransactionVec(mol2_cursor_t *cur);
uint32_t TransactionVec_len_impl(struct TransactionVecType *);
struct TransactionType TransactionVec_get_impl(struct TransactionVecType *,
                                               uint32_t, bool *);
struct ProposalShortIdVecType;
struct ProposalShortIdVecVTable;
struct ProposalShortIdVecVTable *GetProposalShortIdVecVTable(void);
struct ProposalShortIdVecType make_ProposalShortIdVec(mol2_cursor_t *cur);
uint32_t ProposalShortIdVec_len_impl(struct ProposalShortIdVecType *);
mol2_cursor_t ProposalShortIdVec_get_impl(struct ProposalShortIdVecType *,
                                          uint32_t, bool *);
struct CellDepVecType;
struct CellDepVecVTable;
struct CellDepVecVTable *GetCellDepVecVTable(void);
struct CellDepVecType make_CellDepVec(mol2_cursor_t *cur);
uint32_t CellDepVec_len_impl(struct CellDepVecType *);
struct CellDepType CellDepVec_get_impl(struct CellDepVecType *, uint32_t,
                                       bool *);
struct CellInputVecType;
struct CellInputVecVTable;
struct CellInputVecVTable *GetCellInputVecVTable(void);
struct CellInputVecType make_CellInputVec(mol2_cursor_t *cur);
uint32_t CellInputVec_len_impl(struct CellInputVecType *);
struct CellInputType CellInputVec_get_impl(struct CellInputVecType *, uint32_t,
                                           bool *);
struct CellOutputVecType;
struct CellOutputVecVTable;
struct CellOutputVecVTable *GetCellOutputVecVTable(void);
struct CellOutputVecType make_CellOutputVec(mol2_cursor_t *cur);
uint32_t CellOutputVec_len_impl(struct CellOutputVecType *);
struct CellOutputType CellOutputVec_get_impl(struct CellOutputVecType *,
                                             uint32_t, bool *);
struct ScriptType;
struct ScriptVTable;
struct ScriptVTable *GetScriptVTable(void);
struct ScriptType make_Script(mol2_cursor_t *cur);
mol2_cursor_t Script_get_code_hash_impl(struct ScriptType *);
uint8_t Script_get_hash_type_impl(struct ScriptType *);
mol2_cursor_t Script_get_args_impl(struct ScriptType *);
struct OutPointType;
struct OutPointVTable;
struct OutPointVTable *GetOutPointVTable(void);
struct OutPointType make_OutPoint(mol2_cursor_t *cur);
mol2_cursor_t OutPoint_get_tx_hash_impl(struct OutPointType *);
uint32_t OutPoint_get_index_impl(struct OutPointType *);
struct CellInputType;
struct CellInputVTable;
struct CellInputVTable *GetCellInputVTable(void);
struct CellInputType make_CellInput(mol2_cursor_t *cur);
uint64_t CellInput_get_since_impl(struct CellInputType *);
struct OutPointType CellInput_get_previous_output_impl(struct CellInputType *);
struct CellOutputType;
struct CellOutputVTable;
struct CellOutputVTable *GetCellOutputVTable(void);
struct CellOutputType make_CellOutput(mol2_cursor_t *cur);
uint64_t CellOutput_get_capacity_impl(struct CellOutputType *);
struct ScriptType CellOutput_get_lock_impl(struct CellOutputType *);
struct ScriptOptType CellOutput_get_type__impl(struct CellOutputType *);
struct CellDepType;
struct CellDepVTable;
struct CellDepVTable *GetCellDepVTable(void);
struct CellDepType make_CellDep(mol2_cursor_t *cur);
struct OutPointType CellDep_get_out_point_impl(struct CellDepType *);
uint8_t CellDep_get_dep_type_impl(struct CellDepType *);
struct RawTransactionType;
struct RawTransactionVTable;
struct RawTransactionVTable *GetRawTransactionVTable(void);
struct RawTransactionType make_RawTransaction(mol2_cursor_t *cur);
uint32_t RawTransaction_get_version_impl(struct RawTransactionType *);
struct CellDepVecType RawTransaction_get_cell_deps_impl(
    struct RawTransactionType *);
struct Byte32VecType RawTransaction_get_header_deps_impl(
    struct RawTransactionType *);
struct CellInputVecType RawTransaction_get_inputs_impl(
    struct RawTransactionType *);
struct CellOutputVecType RawTransaction_get_outputs_impl(
    struct RawTransactionType *);
struct BytesVecType RawTransaction_get_outputs_data_impl(
    struct RawTransactionType *);
struct TransactionType;
struct TransactionVTable;
struct TransactionVTable *GetTransactionVTable(void);
struct TransactionType make_Transaction(mol2_cursor_t *cur);
struct RawTransactionType Transaction_get_raw_impl(struct TransactionType *);
struct BytesVecType Transaction_get_witnesses_impl(struct TransactionType *);
struct RawHeaderType;
struct RawHeaderVTable;
struct RawHeaderVTable *GetRawHeaderVTable(void);
struct RawHeaderType make_RawHeader(mol2_cursor_t *cur);
uint32_t RawHeader_get_version_impl(struct RawHeaderType *);
uint32_t RawHeader_get_compact_target_impl(struct RawHeaderType *);
uint64_t RawHeader_get_timestamp_impl(struct RawHeaderType *);
uint64_t RawHeader_get_number_impl(struct RawHeaderType *);
uint64_t RawHeader_get_epoch_impl(struct RawHeaderType *);
mol2_cursor_t RawHeader_get_parent_hash_impl(struct RawHeaderType *);
mol2_cursor_t RawHeader_get_transactions_root_impl(struct RawHeaderType *);
mol2_cursor_t RawHeader_get_proposals_hash_impl(struct RawHeaderType *);
mol2_cursor_t RawHeader_get_uncles_hash_impl(struct RawHeaderType *);
mol2_cursor_t RawHeader_get_dao_impl(struct RawHeaderType *);
struct HeaderType;
struct HeaderVTable;
struct HeaderVTable *GetHeaderVTable(void);
struct HeaderType make_Header(mol2_cursor_t *cur);
struct RawHeaderType Header_get_raw_impl(struct HeaderType *);
mol2_cursor_t Header_get_nonce_impl(struct HeaderType *);
struct UncleBlockType;
struct UncleBlockVTable;
struct UncleBlockVTable *GetUncleBlockVTable(void);
struct UncleBlockType make_UncleBlock(mol2_cursor_t *cur);
struct HeaderType UncleBlock_get_header_impl(struct UncleBlockType *);
struct ProposalShortIdVecType UncleBlock_get_proposals_impl(
    struct UncleBlockType *);
struct BlockType;
struct BlockVTable;
struct BlockVTable *GetBlockVTable(void);
struct BlockType make_Block(mol2_cursor_t *cur);
struct HeaderType Block_get_header_impl(struct BlockType *);
struct UncleBlockVecType Block_get_uncles_impl(struct BlockType *);
struct TransactionVecType Block_get_transactions_impl(struct BlockType *);
struct ProposalShortIdVecType Block_get_proposals_impl(struct BlockType *);
struct CellbaseWitnessType;
struct CellbaseWitnessVTable;
struct CellbaseWitnessVTable *GetCellbaseWitnessVTable(void);
struct CellbaseWitnessType make_CellbaseWitness(mol2_cursor_t *cur);
struct ScriptType CellbaseWitness_get_lock_impl(struct CellbaseWitnessType *);
mol2_cursor_t CellbaseWitness_get_message_impl(struct CellbaseWitnessType *);
struct WitnessArgsType;
struct WitnessArgsVTable;
struct WitnessArgsVTable *GetWitnessArgsVTable(void);
struct WitnessArgsType make_WitnessArgs(mol2_cursor_t *cur);
struct BytesOptType WitnessArgs_get_lock_impl(struct WitnessArgsType *);
struct BytesOptType WitnessArgs_get_input_type_impl(struct WitnessArgsType *);
struct BytesOptType WitnessArgs_get_output_type_impl(struct WitnessArgsType *);

// ----definition-----------------
typedef struct Uint32VTable {
  uint32_t (*len)(struct Uint32Type *);
  uint8_t (*get)(struct Uint32Type *, uint32_t, bool *);
} Uint32VTable;
typedef struct Uint32Type {
  mol2_cursor_t cur;
  Uint32VTable *t;
} Uint32Type;

typedef struct Uint64VTable {
  uint32_t (*len)(struct Uint64Type *);
  uint8_t (*get)(struct Uint64Type *, uint32_t, bool *);
} Uint64VTable;
typedef struct Uint64Type {
  mol2_cursor_t cur;
  Uint64VTable *t;
} Uint64Type;

typedef struct Uint128VTable {
  uint32_t (*len)(struct Uint128Type *);
  uint8_t (*get)(struct Uint128Type *, uint32_t, bool *);
} Uint128VTable;
typedef struct Uint128Type {
  mol2_cursor_t cur;
  Uint128VTable *t;
} Uint128Type;

typedef struct Byte32VTable {
  uint32_t (*len)(struct Byte32Type *);
  uint8_t (*get)(struct Byte32Type *, uint32_t, bool *);
} Byte32VTable;
typedef struct Byte32Type {
  mol2_cursor_t cur;
  Byte32VTable *t;
} Byte32Type;

typedef struct Uint256VTable {
  uint32_t (*len)(struct Uint256Type *);
  uint8_t (*get)(struct Uint256Type *, uint32_t, bool *);
} Uint256VTable;
typedef struct Uint256Type {
  mol2_cursor_t cur;
  Uint256VTable *t;
} Uint256Type;

typedef struct BytesVTable {
  uint32_t (*len)(struct BytesType *);
  uint8_t (*get)(struct BytesType *, uint32_t, bool *);
} BytesVTable;
typedef struct BytesType {
  mol2_cursor_t cur;
  BytesVTable *t;
} BytesType;

typedef struct BytesOptVTable {
  bool (*is_none)(struct BytesOptType *);
  bool (*is_some)(struct BytesOptType *);
  mol2_cursor_t (*unwrap)(struct BytesOptType *);
} BytesOptVTable;
typedef struct BytesOptType {
  mol2_cursor_t cur;
  BytesOptVTable *t;
} BytesOptType;

typedef struct BytesVecVTable {
  uint32_t (*len)(struct BytesVecType *);
  mol2_cursor_t (*get)(struct BytesVecType *, uint32_t, bool *);
} BytesVecVTable;
typedef struct BytesVecType {
  mol2_cursor_t cur;
  BytesVecVTable *t;
} BytesVecType;

typedef struct Byte32VecVTable {
  uint32_t (*len)(struct Byte32VecType *);
  mol2_cursor_t (*get)(struct Byte32VecType *, uint32_t, bool *);
} Byte32VecVTable;
typedef struct Byte32VecType {
  mol2_cursor_t cur;
  Byte32VecVTable *t;
} Byte32VecType;

typedef struct ScriptOptVTable {
  bool (*is_none)(struct ScriptOptType *);
  bool (*is_some)(struct ScriptOptType *);
  struct ScriptType (*unwrap)(struct ScriptOptType *);
} ScriptOptVTable;
typedef struct ScriptOptType {
  mol2_cursor_t cur;
  ScriptOptVTable *t;
} ScriptOptType;

typedef struct ProposalShortIdVTable {
  uint32_t (*len)(struct ProposalShortIdType *);
  uint8_t (*get)(struct ProposalShortIdType *, uint32_t, bool *);
} ProposalShortIdVTable;
typedef struct ProposalShortIdType {
  mol2_cursor_t cur;
  ProposalShortIdVTable *t;
} ProposalShortIdType;

typedef struct UncleBlockVecVTable {
  uint32_t (*len)(struct UncleBlockVecType *);
  struct UncleBlockType (*get)(struct UncleBlockVecType *, uint32_t, bool *);
} UncleBlockVecVTable;
typedef struct UncleBlockVecType {
  mol2_cursor_t cur;
  UncleBlockVecVTable *t;
} UncleBlockVecType;

typedef struct TransactionVecVTable {
  uint32_t (*len)(struct TransactionVecType *);
  struct TransactionType (*get)(struct TransactionVecType *, uint32_t, bool *);
} TransactionVecVTable;
typedef struct TransactionVecType {
  mol2_cursor_t cur;
  TransactionVecVTable *t;
} TransactionVecType;

typedef struct ProposalShortIdVecVTable {
  uint32_t (*len)(struct ProposalShortIdVecType *);
  mol2_cursor_t (*get)(struct ProposalShortIdVecType *, uint32_t, bool *);
} ProposalShortIdVecVTable;
typedef struct ProposalShortIdVecType {
  mol2_cursor_t cur;
  ProposalShortIdVecVTable *t;
} ProposalShortIdVecType;

typedef struct CellDepVecVTable {
  uint32_t (*len)(struct CellDepVecType *);
  struct CellDepType (*get)(struct CellDepVecType *, uint32_t, bool *);
} CellDepVecVTable;
typedef struct CellDepVecType {
  mol2_cursor_t cur;
  CellDepVecVTable *t;
} CellDepVecType;

typedef struct CellInputVecVTable {
  uint32_t (*len)(struct CellInputVecType *);
  struct CellInputType (*get)(struct CellInputVecType *, uint32_t, bool *);
} CellInputVecVTable;
typedef struct CellInputVecType {
  mol2_cursor_t cur;
  CellInputVecVTable *t;
} CellInputVecType;

typedef struct CellOutputVecVTable {
  uint32_t (*len)(struct CellOutputVecType *);
  struct CellOutputType (*get)(struct CellOutputVecType *, uint32_t, bool *);
} CellOutputVecVTable;
typedef struct CellOutputVecType {
  mol2_cursor_t cur;
  CellOutputVecVTable *t;
} CellOutputVecType;

typedef struct ScriptVTable {
  mol2_cursor_t (*code_hash)(struct ScriptType *);
  uint8_t (*hash_type)(struct ScriptType *);
  mol2_cursor_t (*args)(struct ScriptType *);
} ScriptVTable;
typedef struct ScriptType {
  mol2_cursor_t cur;
  ScriptVTable *t;
} ScriptType;

typedef struct OutPointVTable {
  mol2_cursor_t (*tx_hash)(struct OutPointType *);
  uint32_t (*index)(struct OutPointType *);
} OutPointVTable;
typedef struct OutPointType {
  mol2_cursor_t cur;
  OutPointVTable *t;
} OutPointType;

typedef struct CellInputVTable {
  uint64_t (*since)(struct CellInputType *);
  struct OutPointType (*previous_output)(struct CellInputType *);
} CellInputVTable;
typedef struct CellInputType {
  mol2_cursor_t cur;
  CellInputVTable *t;
} CellInputType;

typedef struct CellOutputVTable {
  uint64_t (*capacity)(struct CellOutputType *);
  struct ScriptType (*lock)(struct CellOutputType *);
  struct ScriptOptType (*type_)(struct CellOutputType *);
} CellOutputVTable;
typedef struct CellOutputType {
  mol2_cursor_t cur;
  CellOutputVTable *t;
} CellOutputType;

typedef struct CellDepVTable {
  struct OutPointType (*out_point)(struct CellDepType *);
  uint8_t (*dep_type)(struct CellDepType *);
} CellDepVTable;
typedef struct CellDepType {
  mol2_cursor_t cur;
  CellDepVTable *t;
} CellDepType;

typedef struct RawTransactionVTable {
  uint32_t (*version)(struct RawTransactionType *);
  struct CellDepVecType (*cell_deps)(struct RawTransactionType *);
  struct Byte32VecType (*header_deps)(struct RawTransactionType *);
  struct CellInputVecType (*inputs)(struct RawTransactionType *);
  struct CellOutputVecType (*outputs)(struct RawTransactionType *);
  struct BytesVecType (*outputs_data)(struct RawTransactionType *);
} RawTransactionVTable;
typedef struct RawTransactionType {
  mol2_cursor_t cur;
  RawTransactionVTable *t;
} RawTransactionType;

typedef struct TransactionVTable {
  struct RawTransactionType (*raw)(struct TransactionType *);
  struct BytesVecType (*witnesses)(struct TransactionType *);
} TransactionVTable;
typedef struct TransactionType {
  mol2_cursor_t cur;
  TransactionVTable *t;
} TransactionType;

typedef struct RawHeaderVTable {
  uint32_t (*version)(struct RawHeaderType *);
  uint32_t (*compact_target)(struct RawHeaderType *);
  uint64_t (*timestamp)(struct RawHeaderType *);
  uint64_t (*number)(struct RawHeaderType *);
  uint64_t (*epoch)(struct RawHeaderType *);
  mol2_cursor_t (*parent_hash)(struct RawHeaderType *);
  mol2_cursor_t (*transactions_root)(struct RawHeaderType *);
  mol2_cursor_t (*proposals_hash)(struct RawHeaderType *);
  mol2_cursor_t (*uncles_hash)(struct RawHeaderType *);
  mol2_cursor_t (*dao)(struct RawHeaderType *);
} RawHeaderVTable;
typedef struct RawHeaderType {
  mol2_cursor_t cur;
  RawHeaderVTable *t;
} RawHeaderType;

typedef struct HeaderVTable {
  struct RawHeaderType (*raw)(struct HeaderType *);
  mol2_cursor_t (*nonce)(struct HeaderType *);
} HeaderVTable;
typedef struct HeaderType {
  mol2_cursor_t cur;
  HeaderVTable *t;
} HeaderType;

typedef struct UncleBlockVTable {
  struct HeaderType (*header)(struct UncleBlockType *);
  struct ProposalShortIdVecType (*proposals)(struct UncleBlockType *);
} UncleBlockVTable;
typedef struct UncleBlockType {
  mol2_cursor_t cur;
  UncleBlockVTable *t;
} UncleBlockType;

typedef struct BlockVTable {
  struct HeaderType (*header)(struct BlockType *);
  struct UncleBlockVecType (*uncles)(struct BlockType *);
  struct TransactionVecType (*transactions)(struct BlockType *);
  struct ProposalShortIdVecType (*proposals)(struct BlockType *);
} BlockVTable;
typedef struct BlockType {
  mol2_cursor_t cur;
  BlockVTable *t;
} BlockType;

typedef struct CellbaseWitnessVTable {
  struct ScriptType (*lock)(struct CellbaseWitnessType *);
  mol2_cursor_t (*message)(struct CellbaseWitnessType *);
} CellbaseWitnessVTable;
typedef struct CellbaseWitnessType {
  mol2_cursor_t cur;
  CellbaseWitnessVTable *t;
} CellbaseWitnessType;

typedef struct WitnessArgsVTable {
  struct BytesOptType (*lock)(struct WitnessArgsType *);
  struct BytesOptType (*input_type)(struct WitnessArgsType *);
  struct BytesOptType (*output_type)(struct WitnessArgsType *);
} WitnessArgsVTable;
typedef struct WitnessArgsType {
  mol2_cursor_t cur;
  WitnessArgsVTable *t;
} WitnessArgsType;

#ifndef MOLECULEC_C2_DECLARATION_ONLY

// ----implementation-------------
struct Uint32Type make_Uint32(mol2_cursor_t *cur) {
  Uint32Type ret;
  ret.cur = *cur;
  ret.t = GetUint32VTable();
  return ret;
}
struct Uint32VTable *GetUint32VTable(void) {
  static Uint32VTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.len = Uint32_len_impl;
  s_vtable.get = Uint32_get_impl;
  return &s_vtable;
}
uint32_t Uint32_len_impl(Uint32Type *this) { return 4; }
uint8_t Uint32_get_impl(Uint32Type *this, uint32_t index, bool *existing) {
  uint8_t ret = {0};
  mol2_cursor_res_t res = mol2_slice_by_offset2(&this->cur, 1 * index, 1);
  if (res.errno != MOL2_OK) {
    *existing = false;
    return ret;
  } else {
    *existing = true;
  }
  ret = convert_to_Uint8(&res.cur);
  return ret;
}
struct Uint64Type make_Uint64(mol2_cursor_t *cur) {
  Uint64Type ret;
  ret.cur = *cur;
  ret.t = GetUint64VTable();
  return ret;
}
struct Uint64VTable *GetUint64VTable(void) {
  static Uint64VTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.len = Uint64_len_impl;
  s_vtable.get = Uint64_get_impl;
  return &s_vtable;
}
uint32_t Uint64_len_impl(Uint64Type *this) { return 8; }
uint8_t Uint64_get_impl(Uint64Type *this, uint32_t index, bool *existing) {
  uint8_t ret = {0};
  mol2_cursor_res_t res = mol2_slice_by_offset2(&this->cur, 1 * index, 1);
  if (res.errno != MOL2_OK) {
    *existing = false;
    return ret;
  } else {
    *existing = true;
  }
  ret = convert_to_Uint8(&res.cur);
  return ret;
}
struct Uint128Type make_Uint128(mol2_cursor_t *cur) {
  Uint128Type ret;
  ret.cur = *cur;
  ret.t = GetUint128VTable();
  return ret;
}
struct Uint128VTable *GetUint128VTable(void) {
  static Uint128VTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.len = Uint128_len_impl;
  s_vtable.get = Uint128_get_impl;
  return &s_vtable;
}
uint32_t Uint128_len_impl(Uint128Type *this) { return 16; }
uint8_t Uint128_get_impl(Uint128Type *this, uint32_t index, bool *existing) {
  uint8_t ret = {0};
  mol2_cursor_res_t res = mol2_slice_by_offset2(&this->cur, 1 * index, 1);
  if (res.errno != MOL2_OK) {
    *existing = false;
    return ret;
  } else {
    *existing = true;
  }
  ret = convert_to_Uint8(&res.cur);
  return ret;
}
struct Byte32Type make_Byte32(mol2_cursor_t *cur) {
  Byte32Type ret;
  ret.cur = *cur;
  ret.t = GetByte32VTable();
  return ret;
}
struct Byte32VTable *GetByte32VTable(void) {
  static Byte32VTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.len = Byte32_len_impl;
  s_vtable.get = Byte32_get_impl;
  return &s_vtable;
}
uint32_t Byte32_len_impl(Byte32Type *this) { return 32; }
uint8_t Byte32_get_impl(Byte32Type *this, uint32_t index, bool *existing) {
  uint8_t ret = {0};
  mol2_cursor_res_t res = mol2_slice_by_offset2(&this->cur, 1 * index, 1);
  if (res.errno != MOL2_OK) {
    *existing = false;
    return ret;
  } else {
    *existing = true;
  }
  ret = convert_to_Uint8(&res.cur);
  return ret;
}
struct Uint256Type make_Uint256(mol2_cursor_t *cur) {
  Uint256Type ret;
  ret.cur = *cur;
  ret.t = GetUint256VTable();
  return ret;
}
struct Uint256VTable *GetUint256VTable(void) {
  static Uint256VTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.len = Uint256_len_impl;
  s_vtable.get = Uint256_get_impl;
  return &s_vtable;
}
uint32_t Uint256_len_impl(Uint256Type *this) { return 32; }
uint8_t Uint256_get_impl(Uint256Type *this, uint32_t index, bool *existing) {
  uint8_t ret = {0};
  mol2_cursor_res_t res = mol2_slice_by_offset2(&this->cur, 1 * index, 1);
  if (res.errno != MOL2_OK) {
    *existing = false;
    return ret;
  } else {
    *existing = true;
  }
  ret = convert_to_Uint8(&res.cur);
  return ret;
}
struct BytesType make_Bytes(mol2_cursor_t *cur) {
  BytesType ret;
  ret.cur = *cur;
  ret.t = GetBytesVTable();
  return ret;
}
struct BytesVTable *GetBytesVTable(void) {
  static BytesVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.len = Bytes_len_impl;
  s_vtable.get = Bytes_get_impl;
  return &s_vtable;
}
uint32_t Bytes_len_impl(BytesType *this) {
  return mol2_fixvec_length(&this->cur);
}
uint8_t Bytes_get_impl(BytesType *this, uint32_t index, bool *existing) {
  uint8_t ret = {0};
  mol2_cursor_res_t res = mol2_fixvec_slice_by_index(&this->cur, 1, index);
  if (res.errno != MOL2_OK) {
    *existing = false;
    return ret;
  } else {
    *existing = true;
  }
  ret = convert_to_Uint8(&res.cur);
  return ret;
}
struct BytesOptType make_BytesOpt(mol2_cursor_t *cur) {
  BytesOptType ret;
  ret.cur = *cur;
  ret.t = GetBytesOptVTable();
  return ret;
}
struct BytesOptVTable *GetBytesOptVTable(void) {
  static BytesOptVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.is_none = BytesOpt_is_none_impl;
  s_vtable.is_some = BytesOpt_is_some_impl;
  s_vtable.unwrap = BytesOpt_unwrap_impl;
  return &s_vtable;
}
bool BytesOpt_is_none_impl(BytesOptType *this) {
  return mol2_option_is_none(&this->cur);
}
bool BytesOpt_is_some_impl(BytesOptType *this) {
  return !mol2_option_is_none(&this->cur);
}
mol2_cursor_t BytesOpt_unwrap_impl(BytesOptType *this) {
  mol2_cursor_t ret;
  ret = convert_to_rawbytes(&this->cur);
  return ret;
}
struct BytesVecType make_BytesVec(mol2_cursor_t *cur) {
  BytesVecType ret;
  ret.cur = *cur;
  ret.t = GetBytesVecVTable();
  return ret;
}
struct BytesVecVTable *GetBytesVecVTable(void) {
  static BytesVecVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.len = BytesVec_len_impl;
  s_vtable.get = BytesVec_get_impl;
  return &s_vtable;
}
uint32_t BytesVec_len_impl(BytesVecType *this) {
  return mol2_dynvec_length(&this->cur);
}
mol2_cursor_t BytesVec_get_impl(BytesVecType *this, uint32_t index,
                                bool *existing) {
  mol2_cursor_t ret = {0};
  mol2_cursor_res_t res = mol2_dynvec_slice_by_index(&this->cur, index);
  if (res.errno != MOL2_OK) {
    *existing = false;
    return ret;
  } else {
    *existing = true;
  }
  return convert_to_rawbytes(&res.cur);
}
struct Byte32VecType make_Byte32Vec(mol2_cursor_t *cur) {
  Byte32VecType ret;
  ret.cur = *cur;
  ret.t = GetByte32VecVTable();
  return ret;
}
struct Byte32VecVTable *GetByte32VecVTable(void) {
  static Byte32VecVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.len = Byte32Vec_len_impl;
  s_vtable.get = Byte32Vec_get_impl;
  return &s_vtable;
}
uint32_t Byte32Vec_len_impl(Byte32VecType *this) {
  return mol2_fixvec_length(&this->cur);
}
mol2_cursor_t Byte32Vec_get_impl(Byte32VecType *this, uint32_t index,
                                 bool *existing) {
  mol2_cursor_t ret = {0};
  mol2_cursor_res_t res = mol2_fixvec_slice_by_index(&this->cur, 32, index);
  if (res.errno != MOL2_OK) {
    *existing = false;
    return ret;
  } else {
    *existing = true;
  }
  ret = convert_to_array(&res.cur);
  return ret;
}
struct ScriptOptType make_ScriptOpt(mol2_cursor_t *cur) {
  ScriptOptType ret;
  ret.cur = *cur;
  ret.t = GetScriptOptVTable();
  return ret;
}
struct ScriptOptVTable *GetScriptOptVTable(void) {
  static ScriptOptVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.is_none = ScriptOpt_is_none_impl;
  s_vtable.is_some = ScriptOpt_is_some_impl;
  s_vtable.unwrap = ScriptOpt_unwrap_impl;
  return &s_vtable;
}
bool ScriptOpt_is_none_impl(ScriptOptType *this) {
  return mol2_option_is_none(&this->cur);
}
bool ScriptOpt_is_some_impl(ScriptOptType *this) {
  return !mol2_option_is_none(&this->cur);
}
ScriptType ScriptOpt_unwrap_impl(ScriptOptType *this) {
  ScriptType ret;
  mol2_cursor_t cur = this->cur;
  ret.cur = cur;
  ret.t = GetScriptVTable();
  return ret;
}
struct ProposalShortIdType make_ProposalShortId(mol2_cursor_t *cur) {
  ProposalShortIdType ret;
  ret.cur = *cur;
  ret.t = GetProposalShortIdVTable();
  return ret;
}
struct ProposalShortIdVTable *GetProposalShortIdVTable(void) {
  static ProposalShortIdVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.len = ProposalShortId_len_impl;
  s_vtable.get = ProposalShortId_get_impl;
  return &s_vtable;
}
uint32_t ProposalShortId_len_impl(ProposalShortIdType *this) { return 10; }
uint8_t ProposalShortId_get_impl(ProposalShortIdType *this, uint32_t index,
                                 bool *existing) {
  uint8_t ret = {0};
  mol2_cursor_res_t res = mol2_slice_by_offset2(&this->cur, 1 * index, 1);
  if (res.errno != MOL2_OK) {
    *existing = false;
    return ret;
  } else {
    *existing = true;
  }
  ret = convert_to_Uint8(&res.cur);
  return ret;
}
struct UncleBlockVecType make_UncleBlockVec(mol2_cursor_t *cur) {
  UncleBlockVecType ret;
  ret.cur = *cur;
  ret.t = GetUncleBlockVecVTable();
  return ret;
}
struct UncleBlockVecVTable *GetUncleBlockVecVTable(void) {
  static UncleBlockVecVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.len = UncleBlockVec_len_impl;
  s_vtable.get = UncleBlockVec_get_impl;
  return &s_vtable;
}
uint32_t UncleBlockVec_len_impl(UncleBlockVecType *this) {
  return mol2_dynvec_length(&this->cur);
}
UncleBlockType UncleBlockVec_get_impl(UncleBlockVecType *this, uint32_t index,
                                      bool *existing) {
  UncleBlockType ret = {0};
  mol2_cursor_res_t res = mol2_dynvec_slice_by_index(&this->cur, index);
  if (res.errno != MOL2_OK) {
    *existing = false;
    return ret;
  } else {
    *existing = true;
  }
  ret.cur = res.cur;
  ret.t = GetUncleBlockVTable();
  return ret;
}
struct TransactionVecType make_TransactionVec(mol2_cursor_t *cur) {
  TransactionVecType ret;
  ret.cur = *cur;
  ret.t = GetTransactionVecVTable();
  return ret;
}
struct TransactionVecVTable *GetTransactionVecVTable(void) {
  static TransactionVecVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.len = TransactionVec_len_impl;
  s_vtable.get = TransactionVec_get_impl;
  return &s_vtable;
}
uint32_t TransactionVec_len_impl(TransactionVecType *this) {
  return mol2_dynvec_length(&this->cur);
}
TransactionType TransactionVec_get_impl(TransactionVecType *this,
                                        uint32_t index, bool *existing) {
  TransactionType ret = {0};
  mol2_cursor_res_t res = mol2_dynvec_slice_by_index(&this->cur, index);
  if (res.errno != MOL2_OK) {
    *existing = false;
    return ret;
  } else {
    *existing = true;
  }
  ret.cur = res.cur;
  ret.t = GetTransactionVTable();
  return ret;
}
struct ProposalShortIdVecType make_ProposalShortIdVec(mol2_cursor_t *cur) {
  ProposalShortIdVecType ret;
  ret.cur = *cur;
  ret.t = GetProposalShortIdVecVTable();
  return ret;
}
struct ProposalShortIdVecVTable *GetProposalShortIdVecVTable(void) {
  static ProposalShortIdVecVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.len = ProposalShortIdVec_len_impl;
  s_vtable.get = ProposalShortIdVec_get_impl;
  return &s_vtable;
}
uint32_t ProposalShortIdVec_len_impl(ProposalShortIdVecType *this) {
  return mol2_fixvec_length(&this->cur);
}
mol2_cursor_t ProposalShortIdVec_get_impl(ProposalShortIdVecType *this,
                                          uint32_t index, bool *existing) {
  mol2_cursor_t ret = {0};
  mol2_cursor_res_t res = mol2_fixvec_slice_by_index(&this->cur, 10, index);
  if (res.errno != MOL2_OK) {
    *existing = false;
    return ret;
  } else {
    *existing = true;
  }
  ret = convert_to_array(&res.cur);
  return ret;
}
struct CellDepVecType make_CellDepVec(mol2_cursor_t *cur) {
  CellDepVecType ret;
  ret.cur = *cur;
  ret.t = GetCellDepVecVTable();
  return ret;
}
struct CellDepVecVTable *GetCellDepVecVTable(void) {
  static CellDepVecVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.len = CellDepVec_len_impl;
  s_vtable.get = CellDepVec_get_impl;
  return &s_vtable;
}
uint32_t CellDepVec_len_impl(CellDepVecType *this) {
  return mol2_fixvec_length(&this->cur);
}
CellDepType CellDepVec_get_impl(CellDepVecType *this, uint32_t index,
                                bool *existing) {
  CellDepType ret = {0};
  mol2_cursor_res_t res = mol2_fixvec_slice_by_index(&this->cur, 37, index);
  if (res.errno != MOL2_OK) {
    *existing = false;
    return ret;
  } else {
    *existing = true;
  }
  ret.cur = res.cur;
  ret.t = GetCellDepVTable();
  return ret;
}
struct CellInputVecType make_CellInputVec(mol2_cursor_t *cur) {
  CellInputVecType ret;
  ret.cur = *cur;
  ret.t = GetCellInputVecVTable();
  return ret;
}
struct CellInputVecVTable *GetCellInputVecVTable(void) {
  static CellInputVecVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.len = CellInputVec_len_impl;
  s_vtable.get = CellInputVec_get_impl;
  return &s_vtable;
}
uint32_t CellInputVec_len_impl(CellInputVecType *this) {
  return mol2_fixvec_length(&this->cur);
}
CellInputType CellInputVec_get_impl(CellInputVecType *this, uint32_t index,
                                    bool *existing) {
  CellInputType ret = {0};
  mol2_cursor_res_t res = mol2_fixvec_slice_by_index(&this->cur, 44, index);
  if (res.errno != MOL2_OK) {
    *existing = false;
    return ret;
  } else {
    *existing = true;
  }
  ret.cur = res.cur;
  ret.t = GetCellInputVTable();
  return ret;
}
struct CellOutputVecType make_CellOutputVec(mol2_cursor_t *cur) {
  CellOutputVecType ret;
  ret.cur = *cur;
  ret.t = GetCellOutputVecVTable();
  return ret;
}
struct CellOutputVecVTable *GetCellOutputVecVTable(void) {
  static CellOutputVecVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.len = CellOutputVec_len_impl;
  s_vtable.get = CellOutputVec_get_impl;
  return &s_vtable;
}
uint32_t CellOutputVec_len_impl(CellOutputVecType *this) {
  return mol2_dynvec_length(&this->cur);
}
CellOutputType CellOutputVec_get_impl(CellOutputVecType *this, uint32_t index,
                                      bool *existing) {
  CellOutputType ret = {0};
  mol2_cursor_res_t res = mol2_dynvec_slice_by_index(&this->cur, index);
  if (res.errno != MOL2_OK) {
    *existing = false;
    return ret;
  } else {
    *existing = true;
  }
  ret.cur = res.cur;
  ret.t = GetCellOutputVTable();
  return ret;
}
struct ScriptType make_Script(mol2_cursor_t *cur) {
  ScriptType ret;
  ret.cur = *cur;
  ret.t = GetScriptVTable();
  return ret;
}
struct ScriptVTable *GetScriptVTable(void) {
  static ScriptVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.code_hash = Script_get_code_hash_impl;
  s_vtable.hash_type = Script_get_hash_type_impl;
  s_vtable.args = Script_get_args_impl;
  return &s_vtable;
}
mol2_cursor_t Script_get_code_hash_impl(ScriptType *this) {
  mol2_cursor_t ret;
  mol2_cursor_t ret2 = mol2_table_slice_by_index(&this->cur, 0);
  ret = convert_to_array(&ret2);
  return ret;
}
uint8_t Script_get_hash_type_impl(ScriptType *this) {
  uint8_t ret;
  mol2_cursor_t ret2 = mol2_table_slice_by_index(&this->cur, 1);
  ret = convert_to_Uint8(&ret2);
  return ret;
}
mol2_cursor_t Script_get_args_impl(ScriptType *this) {
  mol2_cursor_t ret;
  mol2_cursor_t re2 = mol2_table_slice_by_index(&this->cur, 2);
  ret = convert_to_rawbytes(&re2);
  return ret;
}
struct OutPointType make_OutPoint(mol2_cursor_t *cur) {
  OutPointType ret;
  ret.cur = *cur;
  ret.t = GetOutPointVTable();
  return ret;
}
struct OutPointVTable *GetOutPointVTable(void) {
  static OutPointVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.tx_hash = OutPoint_get_tx_hash_impl;
  s_vtable.index = OutPoint_get_index_impl;
  return &s_vtable;
}
mol2_cursor_t OutPoint_get_tx_hash_impl(OutPointType *this) {
  mol2_cursor_t ret;
  mol2_cursor_t ret2 = mol2_slice_by_offset(&this->cur, 0, 32);
  ret = convert_to_array(&ret2);
  return ret;
}
uint32_t OutPoint_get_index_impl(OutPointType *this) {
  uint32_t ret;
  mol2_cursor_t ret2 = mol2_slice_by_offset(&this->cur, 32, 4);
  ret = convert_to_Uint32(&ret2);
  return ret;
}
struct CellInputType make_CellInput(mol2_cursor_t *cur) {
  CellInputType ret;
  ret.cur = *cur;
  ret.t = GetCellInputVTable();
  return ret;
}
struct CellInputVTable *GetCellInputVTable(void) {
  static CellInputVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.since = CellInput_get_since_impl;
  s_vtable.previous_output = CellInput_get_previous_output_impl;
  return &s_vtable;
}
uint64_t CellInput_get_since_impl(CellInputType *this) {
  uint64_t ret;
  mol2_cursor_t ret2 = mol2_slice_by_offset(&this->cur, 0, 8);
  ret = convert_to_Uint64(&ret2);
  return ret;
}
OutPointType CellInput_get_previous_output_impl(CellInputType *this) {
  OutPointType ret;
  mol2_cursor_t cur = mol2_slice_by_offset(&this->cur, 8, 36);
  ret.cur = cur;
  ret.t = GetOutPointVTable();
  return ret;
}
struct CellOutputType make_CellOutput(mol2_cursor_t *cur) {
  CellOutputType ret;
  ret.cur = *cur;
  ret.t = GetCellOutputVTable();
  return ret;
}
struct CellOutputVTable *GetCellOutputVTable(void) {
  static CellOutputVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.capacity = CellOutput_get_capacity_impl;
  s_vtable.lock = CellOutput_get_lock_impl;
  s_vtable.type_ = CellOutput_get_type__impl;
  return &s_vtable;
}
uint64_t CellOutput_get_capacity_impl(CellOutputType *this) {
  uint64_t ret;
  mol2_cursor_t ret2 = mol2_table_slice_by_index(&this->cur, 0);
  ret = convert_to_Uint64(&ret2);
  return ret;
}
ScriptType CellOutput_get_lock_impl(CellOutputType *this) {
  ScriptType ret;
  mol2_cursor_t cur = mol2_table_slice_by_index(&this->cur, 1);
  ret.cur = cur;
  ret.t = GetScriptVTable();
  return ret;
}
ScriptOptType CellOutput_get_type__impl(CellOutputType *this) {
  ScriptOptType ret;
  mol2_cursor_t cur = mol2_table_slice_by_index(&this->cur, 2);
  ret.cur = cur;
  ret.t = GetScriptOptVTable();
  return ret;
}
struct CellDepType make_CellDep(mol2_cursor_t *cur) {
  CellDepType ret;
  ret.cur = *cur;
  ret.t = GetCellDepVTable();
  return ret;
}
struct CellDepVTable *GetCellDepVTable(void) {
  static CellDepVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.out_point = CellDep_get_out_point_impl;
  s_vtable.dep_type = CellDep_get_dep_type_impl;
  return &s_vtable;
}
OutPointType CellDep_get_out_point_impl(CellDepType *this) {
  OutPointType ret;
  mol2_cursor_t cur = mol2_slice_by_offset(&this->cur, 0, 36);
  ret.cur = cur;
  ret.t = GetOutPointVTable();
  return ret;
}
uint8_t CellDep_get_dep_type_impl(CellDepType *this) {
  uint8_t ret;
  mol2_cursor_t ret2 = mol2_slice_by_offset(&this->cur, 36, 1);
  ret = convert_to_Uint8(&ret2);
  return ret;
}
struct RawTransactionType make_RawTransaction(mol2_cursor_t *cur) {
  RawTransactionType ret;
  ret.cur = *cur;
  ret.t = GetRawTransactionVTable();
  return ret;
}
struct RawTransactionVTable *GetRawTransactionVTable(void) {
  static RawTransactionVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.version = RawTransaction_get_version_impl;
  s_vtable.cell_deps = RawTransaction_get_cell_deps_impl;
  s_vtable.header_deps = RawTransaction_get_header_deps_impl;
  s_vtable.inputs = RawTransaction_get_inputs_impl;
  s_vtable.outputs = RawTransaction_get_outputs_impl;
  s_vtable.outputs_data = RawTransaction_get_outputs_data_impl;
  return &s_vtable;
}
uint32_t RawTransaction_get_version_impl(RawTransactionType *this) {
  uint32_t ret;
  mol2_cursor_t ret2 = mol2_table_slice_by_index(&this->cur, 0);
  ret = convert_to_Uint32(&ret2);
  return ret;
}
CellDepVecType RawTransaction_get_cell_deps_impl(RawTransactionType *this) {
  CellDepVecType ret;
  mol2_cursor_t cur = mol2_table_slice_by_index(&this->cur, 1);
  ret.cur = cur;
  ret.t = GetCellDepVecVTable();
  return ret;
}
Byte32VecType RawTransaction_get_header_deps_impl(RawTransactionType *this) {
  Byte32VecType ret;
  mol2_cursor_t cur = mol2_table_slice_by_index(&this->cur, 2);
  ret.cur = cur;
  ret.t = GetByte32VecVTable();
  return ret;
}
CellInputVecType RawTransaction_get_inputs_impl(RawTransactionType *this) {
  CellInputVecType ret;
  mol2_cursor_t cur = mol2_table_slice_by_index(&this->cur, 3);
  ret.cur = cur;
  ret.t = GetCellInputVecVTable();
  return ret;
}
CellOutputVecType RawTransaction_get_outputs_impl(RawTransactionType *this) {
  CellOutputVecType ret;
  mol2_cursor_t cur = mol2_table_slice_by_index(&this->cur, 4);
  ret.cur = cur;
  ret.t = GetCellOutputVecVTable();
  return ret;
}
BytesVecType RawTransaction_get_outputs_data_impl(RawTransactionType *this) {
  BytesVecType ret;
  mol2_cursor_t cur = mol2_table_slice_by_index(&this->cur, 5);
  ret.cur = cur;
  ret.t = GetBytesVecVTable();
  return ret;
}
struct TransactionType make_Transaction(mol2_cursor_t *cur) {
  TransactionType ret;
  ret.cur = *cur;
  ret.t = GetTransactionVTable();
  return ret;
}
struct TransactionVTable *GetTransactionVTable(void) {
  static TransactionVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.raw = Transaction_get_raw_impl;
  s_vtable.witnesses = Transaction_get_witnesses_impl;
  return &s_vtable;
}
RawTransactionType Transaction_get_raw_impl(TransactionType *this) {
  RawTransactionType ret;
  mol2_cursor_t cur = mol2_table_slice_by_index(&this->cur, 0);
  ret.cur = cur;
  ret.t = GetRawTransactionVTable();
  return ret;
}
BytesVecType Transaction_get_witnesses_impl(TransactionType *this) {
  BytesVecType ret;
  mol2_cursor_t cur = mol2_table_slice_by_index(&this->cur, 1);
  ret.cur = cur;
  ret.t = GetBytesVecVTable();
  return ret;
}
struct RawHeaderType make_RawHeader(mol2_cursor_t *cur) {
  RawHeaderType ret;
  ret.cur = *cur;
  ret.t = GetRawHeaderVTable();
  return ret;
}
struct RawHeaderVTable *GetRawHeaderVTable(void) {
  static RawHeaderVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.version = RawHeader_get_version_impl;
  s_vtable.compact_target = RawHeader_get_compact_target_impl;
  s_vtable.timestamp = RawHeader_get_timestamp_impl;
  s_vtable.number = RawHeader_get_number_impl;
  s_vtable.epoch = RawHeader_get_epoch_impl;
  s_vtable.parent_hash = RawHeader_get_parent_hash_impl;
  s_vtable.transactions_root = RawHeader_get_transactions_root_impl;
  s_vtable.proposals_hash = RawHeader_get_proposals_hash_impl;
  s_vtable.uncles_hash = RawHeader_get_uncles_hash_impl;
  s_vtable.dao = RawHeader_get_dao_impl;
  return &s_vtable;
}
uint32_t RawHeader_get_version_impl(RawHeaderType *this) {
  uint32_t ret;
  mol2_cursor_t ret2 = mol2_slice_by_offset(&this->cur, 0, 4);
  ret = convert_to_Uint32(&ret2);
  return ret;
}
uint32_t RawHeader_get_compact_target_impl(RawHeaderType *this) {
  uint32_t ret;
  mol2_cursor_t ret2 = mol2_slice_by_offset(&this->cur, 4, 4);
  ret = convert_to_Uint32(&ret2);
  return ret;
}
uint64_t RawHeader_get_timestamp_impl(RawHeaderType *this) {
  uint64_t ret;
  mol2_cursor_t ret2 = mol2_slice_by_offset(&this->cur, 8, 8);
  ret = convert_to_Uint64(&ret2);
  return ret;
}
uint64_t RawHeader_get_number_impl(RawHeaderType *this) {
  uint64_t ret;
  mol2_cursor_t ret2 = mol2_slice_by_offset(&this->cur, 16, 8);
  ret = convert_to_Uint64(&ret2);
  return ret;
}
uint64_t RawHeader_get_epoch_impl(RawHeaderType *this) {
  uint64_t ret;
  mol2_cursor_t ret2 = mol2_slice_by_offset(&this->cur, 24, 8);
  ret = convert_to_Uint64(&ret2);
  return ret;
}
mol2_cursor_t RawHeader_get_parent_hash_impl(RawHeaderType *this) {
  mol2_cursor_t ret;
  mol2_cursor_t ret2 = mol2_slice_by_offset(&this->cur, 32, 32);
  ret = convert_to_array(&ret2);
  return ret;
}
mol2_cursor_t RawHeader_get_transactions_root_impl(RawHeaderType *this) {
  mol2_cursor_t ret;
  mol2_cursor_t ret2 = mol2_slice_by_offset(&this->cur, 64, 32);
  ret = convert_to_array(&ret2);
  return ret;
}
mol2_cursor_t RawHeader_get_proposals_hash_impl(RawHeaderType *this) {
  mol2_cursor_t ret;
  mol2_cursor_t ret2 = mol2_slice_by_offset(&this->cur, 96, 32);
  ret = convert_to_array(&ret2);
  return ret;
}
mol2_cursor_t RawHeader_get_uncles_hash_impl(RawHeaderType *this) {
  mol2_cursor_t ret;
  mol2_cursor_t ret2 = mol2_slice_by_offset(&this->cur, 128, 32);
  ret = convert_to_array(&ret2);
  return ret;
}
mol2_cursor_t RawHeader_get_dao_impl(RawHeaderType *this) {
  mol2_cursor_t ret;
  mol2_cursor_t ret2 = mol2_slice_by_offset(&this->cur, 160, 32);
  ret = convert_to_array(&ret2);
  return ret;
}
struct HeaderType make_Header(mol2_cursor_t *cur) {
  HeaderType ret;
  ret.cur = *cur;
  ret.t = GetHeaderVTable();
  return ret;
}
struct HeaderVTable *GetHeaderVTable(void) {
  static HeaderVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.raw = Header_get_raw_impl;
  s_vtable.nonce = Header_get_nonce_impl;
  return &s_vtable;
}
RawHeaderType Header_get_raw_impl(HeaderType *this) {
  RawHeaderType ret;
  mol2_cursor_t cur = mol2_slice_by_offset(&this->cur, 0, 192);
  ret.cur = cur;
  ret.t = GetRawHeaderVTable();
  return ret;
}
mol2_cursor_t Header_get_nonce_impl(HeaderType *this) {
  mol2_cursor_t ret;
  mol2_cursor_t ret2 = mol2_slice_by_offset(&this->cur, 192, 16);
  ret = convert_to_array(&ret2);
  return ret;
}
struct UncleBlockType make_UncleBlock(mol2_cursor_t *cur) {
  UncleBlockType ret;
  ret.cur = *cur;
  ret.t = GetUncleBlockVTable();
  return ret;
}
struct UncleBlockVTable *GetUncleBlockVTable(void) {
  static UncleBlockVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.header = UncleBlock_get_header_impl;
  s_vtable.proposals = UncleBlock_get_proposals_impl;
  return &s_vtable;
}
HeaderType UncleBlock_get_header_impl(UncleBlockType *this) {
  HeaderType ret;
  mol2_cursor_t cur = mol2_table_slice_by_index(&this->cur, 0);
  ret.cur = cur;
  ret.t = GetHeaderVTable();
  return ret;
}
ProposalShortIdVecType UncleBlock_get_proposals_impl(UncleBlockType *this) {
  ProposalShortIdVecType ret;
  mol2_cursor_t cur = mol2_table_slice_by_index(&this->cur, 1);
  ret.cur = cur;
  ret.t = GetProposalShortIdVecVTable();
  return ret;
}
struct BlockType make_Block(mol2_cursor_t *cur) {
  BlockType ret;
  ret.cur = *cur;
  ret.t = GetBlockVTable();
  return ret;
}
struct BlockVTable *GetBlockVTable(void) {
  static BlockVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.header = Block_get_header_impl;
  s_vtable.uncles = Block_get_uncles_impl;
  s_vtable.transactions = Block_get_transactions_impl;
  s_vtable.proposals = Block_get_proposals_impl;
  return &s_vtable;
}
HeaderType Block_get_header_impl(BlockType *this) {
  HeaderType ret;
  mol2_cursor_t cur = mol2_table_slice_by_index(&this->cur, 0);
  ret.cur = cur;
  ret.t = GetHeaderVTable();
  return ret;
}
UncleBlockVecType Block_get_uncles_impl(BlockType *this) {
  UncleBlockVecType ret;
  mol2_cursor_t cur = mol2_table_slice_by_index(&this->cur, 1);
  ret.cur = cur;
  ret.t = GetUncleBlockVecVTable();
  return ret;
}
TransactionVecType Block_get_transactions_impl(BlockType *this) {
  TransactionVecType ret;
  mol2_cursor_t cur = mol2_table_slice_by_index(&this->cur, 2);
  ret.cur = cur;
  ret.t = GetTransactionVecVTable();
  return ret;
}
ProposalShortIdVecType Block_get_proposals_impl(BlockType *this) {
  ProposalShortIdVecType ret;
  mol2_cursor_t cur = mol2_table_slice_by_index(&this->cur, 3);
  ret.cur = cur;
  ret.t = GetProposalShortIdVecVTable();
  return ret;
}
struct CellbaseWitnessType make_CellbaseWitness(mol2_cursor_t *cur) {
  CellbaseWitnessType ret;
  ret.cur = *cur;
  ret.t = GetCellbaseWitnessVTable();
  return ret;
}
struct CellbaseWitnessVTable *GetCellbaseWitnessVTable(void) {
  static CellbaseWitnessVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.lock = CellbaseWitness_get_lock_impl;
  s_vtable.message = CellbaseWitness_get_message_impl;
  return &s_vtable;
}
ScriptType CellbaseWitness_get_lock_impl(CellbaseWitnessType *this) {
  ScriptType ret;
  mol2_cursor_t cur = mol2_table_slice_by_index(&this->cur, 0);
  ret.cur = cur;
  ret.t = GetScriptVTable();
  return ret;
}
mol2_cursor_t CellbaseWitness_get_message_impl(CellbaseWitnessType *this) {
  mol2_cursor_t ret;
  mol2_cursor_t re2 = mol2_table_slice_by_index(&this->cur, 1);
  ret = convert_to_rawbytes(&re2);
  return ret;
}
struct WitnessArgsType make_WitnessArgs(mol2_cursor_t *cur) {
  WitnessArgsType ret;
  ret.cur = *cur;
  ret.t = GetWitnessArgsVTable();
  return ret;
}
struct WitnessArgsVTable *GetWitnessArgsVTable(void) {
  static WitnessArgsVTable s_vtable;
  static int inited = 0;
  if (inited) return &s_vtable;
  s_vtable.lock = WitnessArgs_get_lock_impl;
  s_vtable.input_type = WitnessArgs_get_input_type_impl;
  s_vtable.output_type = WitnessArgs_get_output_type_impl;
  return &s_vtable;
}
BytesOptType WitnessArgs_get_lock_impl(WitnessArgsType *this) {
  BytesOptType ret;
  mol2_cursor_t cur = mol2_table_slice_by_index(&this->cur, 0);
  ret.cur = cur;
  ret.t = GetBytesOptVTable();
  return ret;
}
BytesOptType WitnessArgs_get_input_type_impl(WitnessArgsType *this) {
  BytesOptType ret;
  mol2_cursor_t cur = mol2_table_slice_by_index(&this->cur, 1);
  ret.cur = cur;
  ret.t = GetBytesOptVTable();
  return ret;
}
BytesOptType WitnessArgs_get_output_type_impl(WitnessArgsType *this) {
  BytesOptType ret;
  mol2_cursor_t cur = mol2_table_slice_by_index(&this->cur, 2);
  ret.cur = cur;
  ret.t = GetBytesOptVTable();
  return ret;
}
#endif  // MOLECULEC_C2_DECLARATION_ONLY

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  // _BLOCKCHAIN_API2_H_
