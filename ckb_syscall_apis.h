#ifndef CKB_C_STDLIB_CKB_SYSCALL_APIS_H_
#define CKB_C_STDLIB_CKB_SYSCALL_APIS_H_

/*
 * Syscall related APIs that will be shared and used in all CKB
 * smart contract environments
 */

#include <stddef.h>
#include <stdint.h>

/* Raw APIs */

/* VM version 0 APIs */
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
int ckb_load_cell_data_as_code(void* addr, size_t memory_size,
                               size_t content_offset, size_t content_size,
                               size_t index, size_t source);

/* VM version 1 APIs */
int ckb_vm_version();
uint64_t ckb_current_cycles();
int ckb_exec(size_t index, size_t source, size_t place, size_t bounds, int argc,
             const char* argv[]);

/* VM version 2 APIs */
typedef struct spawn_args_t {
  size_t argc;
  const char** argv;
  /* Spawned VM process ID */
  uint64_t* process_id;
  /* A list of file descriptor, 0 indicates end of array */
  const uint64_t* inherited_fds;
} spawn_args_t;

int ckb_spawn(size_t index, size_t source, size_t place, size_t bounds,
              spawn_args_t* spawn_args);

int ckb_wait(uint64_t pid, int8_t* exit_code);

uint64_t ckb_process_id();

int ckb_pipe(uint64_t fds[2]);

int ckb_read(uint64_t fd, void* buffer, size_t* length);

int ckb_write(uint64_t fd, const void* buffer, size_t* length);

int ckb_inherited_fds(uint64_t* fds, size_t* length);

int ckb_close(uint64_t fd);

int ckb_load_block_extension(void* addr, uint64_t* len, size_t offset,
                             size_t index, size_t source);

/* Handy utilities */
int ckb_exec_cell(const uint8_t* code_hash, uint8_t hash_type, uint32_t offset,
                  uint32_t length, int argc, const char* argv[]);
int ckb_spawn_cell(const uint8_t* code_hash, uint8_t hash_type, uint32_t offset,
                   uint32_t length, spawn_args_t* spawn_args);
int ckb_checked_load_tx_hash(void* addr, uint64_t* len, size_t offset);
int ckb_checked_load_script_hash(void* addr, uint64_t* len, size_t offset);
int ckb_checked_load_cell(void* addr, uint64_t* len, size_t offset,
                          size_t index, size_t source);
int ckb_checked_load_input(void* addr, uint64_t* len, size_t offset,
                           size_t index, size_t source);
int ckb_checked_load_header(void* addr, uint64_t* len, size_t offset,
                            size_t index, size_t source);
int ckb_checked_load_witness(void* addr, uint64_t* len, size_t offset,
                             size_t index, size_t source);
int ckb_checked_load_script(void* addr, uint64_t* len, size_t offset);
int ckb_checked_load_transaction(void* addr, uint64_t* len, size_t offset);
int ckb_checked_load_cell_by_field(void* addr, uint64_t* len, size_t offset,
                                   size_t index, size_t source, size_t field);
int ckb_checked_load_header_by_field(void* addr, uint64_t* len, size_t offset,
                                     size_t index, size_t source, size_t field);
int ckb_checked_load_input_by_field(void* addr, uint64_t* len, size_t offset,
                                    size_t index, size_t source, size_t field);
int ckb_checked_load_cell_data(void* addr, uint64_t* len, size_t offset,
                               size_t index, size_t source);
/* load the actual witness for the current type verify group.
   use this instead of ckb_load_witness if type contract needs args to verify
   input/output.
 */
int ckb_load_actual_type_witness(uint8_t* buf, uint64_t* len, size_t index,
                                 size_t* type_source);
/* calculate inputs length */
int ckb_calculate_inputs_len();
/*
 * Look for a dep cell with specific code hash, code_hash should be a buffer
 * with 32 bytes.
 */
int ckb_look_for_dep_with_hash2(const uint8_t* code_hash, uint8_t hash_type,
                                size_t* index);
/*
 * Deprecated, please use ckb_look_for_dep_with_hash2 instead.
 */
int ckb_look_for_dep_with_hash(const uint8_t* data_hash, size_t* index);

/*
 * Those 2 are in fact implemented by ckb_dlfcn.h, which is not a direct
 * CKB syscall(or simple wrapper on a syscall), but rather a whole dynamic
 * linking solution. However for compatibility reasons, we are still keeping
 * those APIs in this file so as not to break existing code.
 */
int ckb_dlopen2(const uint8_t* dep_cell_hash, uint8_t hash_type,
                uint8_t* aligned_addr, size_t aligned_size, void** handle,
                size_t* consumed_size);
void* ckb_dlsym(void* handle, const char* symbol);

#endif /* CKB_C_STDLIB_CKB_SYSCALL_APIS_H_ */
