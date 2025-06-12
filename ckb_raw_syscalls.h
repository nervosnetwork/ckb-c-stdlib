#ifndef CKB_C_STDLIB_CKB_RAW_SYSCALLS_H_
#define CKB_C_STDLIB_CKB_RAW_SYSCALLS_H_

#include "ckb_consts.h"
#include "ckb_syscall_apis.h"

#ifndef CKB_STDLIB_NO_SYSCALL_IMPL

/*
 * From
 * https://git.musl-libc.org/cgit/musl/tree/src/include/features.h?id=86373b4999bfd9a9379bc4a3ca877b1c80a2a340#n8
 */
#ifndef weak_alias
#define weak_alias(old, new) \
  extern __typeof(old) new __attribute__((__weak__, __alias__(#old)))
#endif

#define memory_barrier() asm volatile("fence" ::: "memory")

long default_internal_syscall(long n, long _a0, long _a1, long _a2, long _a3,
                              long _a4, long _a5) {
  register long a0 asm("a0") = _a0;
  register long a1 asm("a1") = _a1;
  register long a2 asm("a2") = _a2;
  register long a3 asm("a3") = _a3;
  register long a4 asm("a4") = _a4;
  register long a5 asm("a5") = _a5;

#ifdef __riscv_32e
  register long syscall_id asm("t0") = n;
#else
  register long syscall_id asm("a7") = n;
#endif

  asm volatile("scall"
               : "+r"(a0)
               : "r"(a1), "r"(a2), "r"(a3), "r"(a4), "r"(a5), "r"(syscall_id));
  /*
   * Syscalls might modify memory sent as pointer, adding a barrier here ensures
   * gcc won't do incorrect optimization.
   */
  memory_barrier();

  return a0;
}
weak_alias(default_internal_syscall, __internal_syscall);

#define syscall(n, a, b, c, d, e, f)                                           \
  __internal_syscall(n, (long)(a), (long)(b), (long)(c), (long)(d), (long)(e), \
                     (long)(f))

int default_ckb_exit(int8_t code) {
  return syscall(SYS_exit, code, 0, 0, 0, 0, 0);
}
weak_alias(default_ckb_exit, ckb_exit);

int default_ckb_load_tx_hash(void* addr, uint64_t* len, size_t offset) {
  volatile uint64_t inner_len = *len;
  int ret = syscall(SYS_ckb_load_tx_hash, addr, &inner_len, offset, 0, 0, 0);
  *len = inner_len;
  return ret;
}
weak_alias(default_ckb_load_tx_hash, ckb_load_tx_hash);

int default_ckb_load_script_hash(void* addr, uint64_t* len, size_t offset) {
  volatile uint64_t inner_len = *len;
  int ret =
      syscall(SYS_ckb_load_script_hash, addr, &inner_len, offset, 0, 0, 0);
  *len = inner_len;
  return ret;
}
weak_alias(default_ckb_load_script_hash, ckb_load_script_hash);

int default_ckb_load_cell(void* addr, uint64_t* len, size_t offset,
                          size_t index, size_t source) {
  volatile uint64_t inner_len = *len;
  int ret =
      syscall(SYS_ckb_load_cell, addr, &inner_len, offset, index, source, 0);
  *len = inner_len;
  return ret;
}
weak_alias(default_ckb_load_cell, ckb_load_cell);

int default_ckb_load_input(void* addr, uint64_t* len, size_t offset,
                           size_t index, size_t source) {
  volatile uint64_t inner_len = *len;
  int ret =
      syscall(SYS_ckb_load_input, addr, &inner_len, offset, index, source, 0);
  *len = inner_len;
  return ret;
}
weak_alias(default_ckb_load_input, ckb_load_input);

int default_ckb_load_header(void* addr, uint64_t* len, size_t offset,
                            size_t index, size_t source) {
  volatile uint64_t inner_len = *len;
  int ret =
      syscall(SYS_ckb_load_header, addr, &inner_len, offset, index, source, 0);
  *len = inner_len;
  return ret;
}
weak_alias(default_ckb_load_header, ckb_load_header);

int default_ckb_load_witness(void* addr, uint64_t* len, size_t offset,
                             size_t index, size_t source) {
  volatile uint64_t inner_len = *len;
  int ret =
      syscall(SYS_ckb_load_witness, addr, &inner_len, offset, index, source, 0);
  *len = inner_len;
  return ret;
}
weak_alias(default_ckb_load_witness, ckb_load_witness);

int default_ckb_load_script(void* addr, uint64_t* len, size_t offset) {
  volatile uint64_t inner_len = *len;
  int ret = syscall(SYS_ckb_load_script, addr, &inner_len, offset, 0, 0, 0);
  *len = inner_len;
  return ret;
}
weak_alias(default_ckb_load_script, ckb_load_script);

int default_ckb_load_transaction(void* addr, uint64_t* len, size_t offset) {
  volatile uint64_t inner_len = *len;
  int ret =
      syscall(SYS_ckb_load_transaction, addr, &inner_len, offset, 0, 0, 0);
  *len = inner_len;
  return ret;
}
weak_alias(default_ckb_load_transaction, ckb_load_transaction);

int default_ckb_load_cell_by_field(void* addr, uint64_t* len, size_t offset,
                                   size_t index, size_t source, size_t field) {
  volatile uint64_t inner_len = *len;
  int ret = syscall(SYS_ckb_load_cell_by_field, addr, &inner_len, offset, index,
                    source, field);
  *len = inner_len;
  return ret;
}
weak_alias(default_ckb_load_cell_by_field, ckb_load_cell_by_field);

int default_ckb_load_header_by_field(void* addr, uint64_t* len, size_t offset,
                                     size_t index, size_t source,
                                     size_t field) {
  volatile uint64_t inner_len = *len;
  int ret = syscall(SYS_ckb_load_header_by_field, addr, &inner_len, offset,
                    index, source, field);
  *len = inner_len;
  return ret;
}
weak_alias(default_ckb_load_header_by_field, ckb_load_header_by_field);

int default_ckb_load_input_by_field(void* addr, uint64_t* len, size_t offset,
                                    size_t index, size_t source, size_t field) {
  volatile uint64_t inner_len = *len;
  int ret = syscall(SYS_ckb_load_input_by_field, addr, &inner_len, offset,
                    index, source, field);
  *len = inner_len;
  return ret;
}
weak_alias(default_ckb_load_input_by_field, ckb_load_input_by_field);

int default_ckb_load_cell_data(void* addr, uint64_t* len, size_t offset,
                               size_t index, size_t source) {
  volatile uint64_t inner_len = *len;
  int ret = syscall(SYS_ckb_load_cell_data, addr, &inner_len, offset, index,
                    source, 0);
  *len = inner_len;
  return ret;
}
weak_alias(default_ckb_load_cell_data, ckb_load_cell_data);

int default_ckb_load_cell_data_as_code(void* addr, size_t memory_size,
                                       size_t content_offset,
                                       size_t content_size, size_t index,
                                       size_t source) {
  return syscall(SYS_ckb_load_cell_data_as_code, addr, memory_size,
                 content_offset, content_size, index, source);
}
weak_alias(default_ckb_load_cell_data_as_code, ckb_load_cell_data_as_code);

int default_ckb_debug(const char* s) {
  return syscall(SYS_ckb_debug, s, 0, 0, 0, 0, 0);
}
weak_alias(default_ckb_debug, ckb_debug);

int default_ckb_vm_version() {
  return syscall(SYS_ckb_vm_version, 0, 0, 0, 0, 0, 0);
}
weak_alias(default_ckb_vm_version, ckb_vm_version);

uint64_t default_ckb_current_cycles() {
  return syscall(SYS_ckb_current_cycles, 0, 0, 0, 0, 0, 0);
}
weak_alias(default_ckb_current_cycles, ckb_current_cycles);

int default_ckb_exec(size_t index, size_t source, size_t place, size_t bounds,
                     int argc, const char* argv[]) {
  return syscall(SYS_ckb_exec, index, source, place, bounds, argc, argv);
}
weak_alias(default_ckb_exec, ckb_exec);

int default_ckb_spawn(size_t index, size_t source, size_t place, size_t bounds,
                      spawn_args_t* spawn_args) {
  return syscall(SYS_ckb_spawn, index, source, place, bounds, spawn_args, 0);
}
weak_alias(default_ckb_spawn, ckb_spawn);

int default_ckb_wait(uint64_t pid, int8_t* exit_code) {
  return syscall(SYS_ckb_wait, pid, exit_code, 0, 0, 0, 0);
}
weak_alias(default_ckb_wait, ckb_wait);

uint64_t default_ckb_process_id() {
  return syscall(SYS_ckb_process_id, 0, 0, 0, 0, 0, 0);
}
weak_alias(default_ckb_process_id, ckb_process_id);

int default_ckb_pipe(uint64_t fds[2]) {
  return syscall(SYS_ckb_pipe, fds, 0, 0, 0, 0, 0);
}
weak_alias(default_ckb_pipe, ckb_pipe);

int default_ckb_read(uint64_t fd, void* buffer, size_t* length) {
  volatile size_t l = *length;
  int ret = syscall(SYS_ckb_read, fd, buffer, &l, 0, 0, 0);
  *length = l;
  return ret;
}
weak_alias(default_ckb_read, ckb_read);

int default_ckb_write(uint64_t fd, const void* buffer, size_t* length) {
  volatile size_t l = *length;
  int ret = syscall(SYS_ckb_write, fd, buffer, &l, 0, 0, 0);
  *length = l;
  return ret;
}
weak_alias(default_ckb_write, ckb_write);

int default_ckb_load_block_extension(void* addr, uint64_t* len, size_t offset,
                                     size_t index, size_t source) {
  return syscall(SYS_ckb_load_block_extension, addr, len, offset, index, source,
                 0);
}
weak_alias(default_ckb_load_block_extension, ckb_load_block_extension);

int default_ckb_inherited_fds(uint64_t* fds, size_t* length) {
  volatile size_t l = *length;
  int ret = syscall(SYS_ckb_inherited_fds, fds, &l, 0, 0, 0, 0);
  *length = l;
  return ret;
}
weak_alias(default_ckb_inherited_fds, ckb_inherited_fds);

int default_ckb_close(uint64_t fd) {
  return syscall(SYS_ckb_close, fd, 0, 0, 0, 0, 0);
}
weak_alias(default_ckb_close, ckb_close);

#endif /* CKB_STDLIB_NO_SYSCALL_IMPL */

#endif /* CKB_C_STDLIB_CKB_RAW_SYSCALLS_H_ */
