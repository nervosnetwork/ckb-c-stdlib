#ifndef CKB_C_STDLIB_CKB_SYSCALL_APIS_H_
#define CKB_C_STDLIB_CKB_SYSCALL_APIS_H_

/*
 * Syscall related APIs that will be shared and used in all CKB
 * smart contract environments
 */

#include <stddef.h>
#include <stdint.h>

int ckb_exit(int8_t code);
int ckb_load_tx_hash(void* addr, uint64_t* len, size_t offset);
int ckb_load_transaction(void* addr, uint64_t* len, size_t offset);
int ckb_load_script_hash(void* addr, uint64_t* len, size_t offset);
int ckb_load_script(void* addr, uint64_t* len, size_t offset);
int ckb_debug(const char* s);

int ckb_load_cell(void* addr, uint64_t* len, size_t offset, size_t index,
                  size_t source);
int ckb_load_input(void* addr, uint64_t* len, size_t offset, size_t index,
                   size_t source);
int ckb_load_header(void* addr, uint64_t* len, size_t offset, size_t index,
                    size_t source);
int ckb_load_witness(void* addr, uint64_t* len, size_t offset, size_t index,
                     size_t source);
int ckb_load_cell_by_field(void* addr, uint64_t* len, size_t offset,
                           size_t index, size_t source, size_t field);
int ckb_load_header_by_field(void* addr, uint64_t* len, size_t offset,
                             size_t index, size_t source, size_t field);
int ckb_load_input_by_field(void* addr, uint64_t* len, size_t offset,
                            size_t index, size_t source, size_t field);
int ckb_load_cell_data(void* addr, uint64_t* len, size_t offset, size_t index,
                       size_t source);
int ckb_vm_version();
uint64_t ckb_current_cycles();
int ckb_exec_cell(const uint8_t* code_hash, uint8_t hash_type, uint32_t offset,
                  uint32_t length, int argc, const char* argv[]);

int ckb_dlopen2(const uint8_t* dep_cell_hash, uint8_t hash_type,
                uint8_t* aligned_addr, size_t aligned_size, void** handle,
                size_t* consumed_size);
void* ckb_dlsym(void* handle, const char* symbol);

#endif /* CKB_C_STDLIB_CKB_SYSCALL_APIS_H_ */
