#ifndef CKB_C_STDLIB_CKB_DLFCN_H_
#define CKB_C_STDLIB_CKB_DLFCN_H_

#include "ckb_syscalls.h"

int ckb_dlopen(const uint8_t *dep_cell_data_hash, uint8_t *aligned_addr,
               size_t aligned_size, void **handle, size_t *consumed_size) {
  return ckb_dlopen2(dep_cell_data_hash, 0, aligned_addr, aligned_size, handle,
                     consumed_size);
}

#ifndef CKB_STDLIB_NO_SYSCALL_IMPL

int _ckb_load_cell_code(void *addr, size_t memory_size, size_t content_offset,
                        size_t content_size, size_t index, size_t source) {
  return syscall(SYS_ckb_load_cell_data_as_code, addr, memory_size,
                 content_offset, content_size, index, source);
}

/*
 * The ELF parsing code here is inspired from
 * https://github.com/riscv/riscv-pk/blob/master/pk/elf.h, original code is in
 * BSD license.
 */

typedef struct {
  uint8_t e_ident[16];
  uint16_t e_type;
  uint16_t e_machine;
  uint32_t e_version;
  uint64_t e_entry;
  uint64_t e_phoff;
  uint64_t e_shoff;
  uint32_t e_flags;
  uint16_t e_ehsize;
  uint16_t e_phentsize;
  uint16_t e_phnum;
  uint16_t e_shentsize;
  uint16_t e_shnum;
  uint16_t e_shstrndx;
} Elf64_Ehdr;

#define SHT_STRTAB 3
#define SHT_RELA 4
#define SHT_DYNSYM 11

typedef struct {
  uint32_t sh_name;
  uint32_t sh_type;
  uint64_t sh_flags;
  uint64_t sh_addr;
  uint64_t sh_offset;
  uint64_t sh_size;
  uint32_t sh_link;
  uint32_t sh_info;
  uint64_t sh_addralign;
  uint64_t sh_entsize;
} Elf64_Shdr;

#define PT_LOAD 1
#define PF_X 1

typedef struct {
  uint32_t p_type;
  uint32_t p_flags;
  uint64_t p_offset;
  uint64_t p_vaddr;
  uint64_t p_paddr;
  uint64_t p_filesz;
  uint64_t p_memsz;
  uint64_t p_align;
} Elf64_Phdr;

typedef struct {
  uint32_t st_name;
  uint8_t st_info;
  uint8_t st_other;
  uint16_t st_shndx;
  uint64_t st_value;
  uint64_t st_size;
} Elf64_Sym;

#define R_RISCV_RELATIVE 3

typedef struct {
  uint64_t r_offset;
  uint64_t r_info;
  int64_t r_addend;
} Elf64_Rela;

#define RISCV_PGSIZE 4096

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#define ERROR_CONTEXT_FAILURE -21
#define ERROR_INVALID_ELF -22
#define ERROR_MEMORY_NOT_ENOUGH -23
#define ERROR_OUT_OF_BOUND -24
#define ERROR_INVALID_ARGS -25

typedef struct {
  Elf64_Sym *dynsyms;
  const char *dynstr;
  size_t dynsym_size;
  uint8_t *base_addr;
  size_t size;
} CkbDlfcnContext;

int check_in_range(const void *p, const CkbDlfcnContext *context) {
  uint64_t end;

  void *begin = context->base_addr;
  if (__builtin_uaddl_overflow((uint64_t)context->base_addr, context->size,
                               &end)) {
    return 0;
  }
  if (begin <= p && p < (void *)end) {
    return 1;
  } else {
    return 0;
  }
}

int roundup(uint64_t a, uint64_t b, uint64_t *value) {
  if (a == 0) {
    *value = 0;
    return 0;
  }
  uint64_t d = (a - 1) / b;
  return __builtin_umull_overflow(d + 1, b, value);
}

uint8_t *addr_offset_checked(uint8_t *aligned_addr, uint64_t aligned_size,
                             uint64_t offset) {
  uint64_t target = 0;
  if (offset < aligned_size) {
    if (__builtin_uaddl_overflow((uint64_t)aligned_addr, offset, &target)) {
      return 0;
    } else {
      return (uint8_t *)target;
    }
  } else {
    return 0;
  }
}

void *addr_offset_with_context(const void *addr, uint64_t offset,
                               const CkbDlfcnContext *context) {
  uint64_t target = 0;
  if (__builtin_uaddl_overflow((uint64_t)addr, offset, &target)) {
    return 0;
  } else {
    if (!check_in_range((const void *)target, context)) {
      return 0;
    } else {
      return (void *)target;
    }
  }
}

int ckb_dlopen2(const uint8_t *dep_cell_hash, uint8_t hash_type,
                uint8_t *aligned_addr, size_t aligned_size, void **handle,
                size_t *consumed_size) {
  if (sizeof(CkbDlfcnContext) > RISCV_PGSIZE || aligned_size < RISCV_PGSIZE) {
    return ERROR_CONTEXT_FAILURE;
  }
  if (((uint64_t)aligned_addr) < 8) {
    return ERROR_CONTEXT_FAILURE;
  }

  if (dep_cell_hash == 0 || aligned_size == 0 || aligned_addr == 0 ||
      handle == 0 || consumed_size == 0) {
    return ERROR_INVALID_ARGS;
  }
  uint64_t _end = 0;
  if (__builtin_uaddl_overflow((uint64_t)aligned_addr, aligned_size, &_end)) {
    return ERROR_OUT_OF_BOUND;
  }

  CkbDlfcnContext *context = (CkbDlfcnContext *)aligned_addr;
  memset(context, 0, sizeof(CkbDlfcnContext));
  aligned_addr += RISCV_PGSIZE;
  aligned_size -= RISCV_PGSIZE;
  context->base_addr = aligned_addr;
  context->size = aligned_size;

  size_t index = SIZE_MAX;
  int ret = ckb_look_for_dep_with_hash2(dep_cell_hash, hash_type, &index);
  if (ret != CKB_SUCCESS) {
    return ret;
  }

  /* Basic ELF header parsing */
  Elf64_Ehdr header;
  uint64_t len = sizeof(header);
  ret =
      ckb_load_cell_data((void *)&header, &len, 0, index, CKB_SOURCE_CELL_DEP);
  if (ret != CKB_SUCCESS) {
    return ret;
  }
  if (len < sizeof(header)) {
    return ERROR_INVALID_ELF;
  }
  if ((header.e_phentsize != sizeof(Elf64_Phdr)) ||
      (header.e_shentsize != sizeof(Elf64_Shdr)) || (header.e_phnum > 16) ||
      (header.e_shnum > 32)) {
    return ERROR_INVALID_ELF;
  }
  /* Parse program headers and load relevant parts */
  Elf64_Phdr program_headers[16];
  len = sizeof(Elf64_Phdr) * header.e_phnum;
  ret = ckb_load_cell_data((void *)program_headers, &len, header.e_phoff, index,
                           CKB_SOURCE_CELL_DEP);
  if (ret != CKB_SUCCESS) {
    return ret;
  }
  if (len < sizeof(Elf64_Phdr) * header.e_phnum) {
    return ERROR_INVALID_ELF;
  }
  uint64_t max_consumed_size = 0;
  for (int i = 0; i < header.e_phnum; i++) {
    const Elf64_Phdr *ph = &program_headers[i];
    if (ph->p_type == PT_LOAD && ph->p_memsz > 0) {
      if ((ph->p_flags & PF_X) != 0) {
        uint64_t prepad = ph->p_vaddr % RISCV_PGSIZE;
        uint64_t vaddr = ph->p_vaddr - prepad;
        uint64_t memsz = 0;
        if (roundup(prepad + ph->p_memsz, RISCV_PGSIZE, &memsz)) {
          return ERROR_INVALID_ELF;
        }
        unsigned long size = 0;
        if (__builtin_uaddl_overflow(vaddr, memsz, &size)) {
          return ERROR_INVALID_ELF;
        }
        if (size > aligned_size) {
          return ERROR_MEMORY_NOT_ENOUGH;
        }
        uint8_t *addr2 = addr_offset_checked(aligned_addr, aligned_size, vaddr);
        if (addr2 == 0) {
          return ERROR_INVALID_ELF;
        }
        ret = _ckb_load_cell_code(addr2, memsz, ph->p_offset, ph->p_filesz,
                                  index, CKB_SOURCE_CELL_DEP);
        if (ret != CKB_SUCCESS) {
          return ret;
        }
        max_consumed_size = MAX(max_consumed_size, vaddr + memsz);
      } else {
        uint64_t filesz = ph->p_filesz;
        uint64_t memsz = ph->p_memsz;
        uint64_t size = 0;
        uint64_t gap_len = 0;
        if (filesz > memsz) {
          return ERROR_INVALID_ELF;
        }
        gap_len = memsz - filesz;

        if (__builtin_uaddl_overflow(ph->p_vaddr, memsz, &size)) {
          return ERROR_INVALID_ELF;
        }
        uint64_t consumed_end = 0;
        if (roundup(size, RISCV_PGSIZE, &consumed_end)) {
          return ERROR_INVALID_ELF;
        }
        if (consumed_end > aligned_size) {
          return ERROR_MEMORY_NOT_ENOUGH;
        }
        uint8_t *addr2 =
            addr_offset_checked(aligned_addr, aligned_size, ph->p_vaddr);
        if (addr2 == 0) {
          return ERROR_INVALID_ELF;
        }
        uint64_t read_len = filesz;
        ret = ckb_load_cell_data(addr2, &read_len, ph->p_offset, index,
                                 CKB_SOURCE_CELL_DEP);
        if (ret != CKB_SUCCESS) {
          return ret;
        }
        if (read_len < filesz) {
          return ERROR_INVALID_ELF;
        }
        if (gap_len > 0) {
          uint8_t *addr3 = addr_offset_with_context(addr2, filesz, context);
          uint8_t *addr4 =
              addr_offset_with_context(addr3, gap_len - 1, context);
          if (addr3 != 0 && addr4 != 0) {
            memset(addr3, 0, gap_len);
          } else {
            return ERROR_INVALID_ELF;
          }
        }
        max_consumed_size = MAX(max_consumed_size, consumed_end);
      }
    }
  }
  /*
   * Parse sectioin header & relocation headers,
   * Perform necessary relocations.
   */
  Elf64_Shdr section_headers[32];
  len = sizeof(Elf64_Shdr) * header.e_shnum;
  ret = ckb_load_cell_data((void *)section_headers, &len, header.e_shoff, index,
                           CKB_SOURCE_CELL_DEP);
  if (ret != CKB_SUCCESS) {
    return ret;
  }
  if (len < sizeof(Elf64_Shdr) * header.e_shnum) {
    return ERROR_INVALID_ELF;
  }
  if (header.e_shstrndx >= 32 || header.e_shstrndx >= header.e_shnum) {
    return ERROR_INVALID_ELF;
  }
  /*
   * First load shstrtab tab, this is temporary code only needed in ELF loading
   * phase here.
   */
  Elf64_Shdr *shshrtab = &section_headers[header.e_shstrndx];
  char shrtab[4096];
  if (shshrtab->sh_size > 4096) {
    return ERROR_INVALID_ELF;
  }
  uint64_t shrtab_len = shshrtab->sh_size;
  ret = ckb_load_cell_data((void *)shrtab, &shrtab_len, shshrtab->sh_offset,
                           index, CKB_SOURCE_CELL_DEP);
  if (ret != CKB_SUCCESS) {
    return ret;
  }
  if (shrtab_len < shshrtab->sh_size) {
    return ERROR_INVALID_ELF;
  }
  for (int i = 0; i < header.e_shnum; i++) {
    const Elf64_Shdr *sh = &section_headers[i];
    if (sh->sh_type == SHT_RELA) {
      if (sh->sh_entsize != sizeof(Elf64_Rela)) {
        return ERROR_INVALID_ELF;
      }
      size_t relocation_size = sh->sh_size / sh->sh_entsize;
      uint64_t current_offset = sh->sh_offset;
      while (relocation_size > 0) {
        Elf64_Rela relocations[64];
        size_t load_size = MIN(relocation_size, 64);
        uint64_t load_length = load_size * sizeof(Elf64_Rela);
        ret = ckb_load_cell_data((void *)relocations, &load_length,
                                 current_offset, index, CKB_SOURCE_CELL_DEP);
        if (ret != CKB_SUCCESS) {
          return ret;
        }
        if (load_length < load_size * sizeof(Elf64_Rela)) {
          return ERROR_INVALID_ELF;
        }
        relocation_size -= load_size;
        current_offset += load_size * sizeof(Elf64_Rela);
        for (size_t j = 0; j < load_size; j++) {
          Elf64_Rela *r = &relocations[j];
          if (r->r_info != R_RISCV_RELATIVE) {
            /* Only relative relocation is supported now, we might add more
             * later */
            return ERROR_INVALID_ELF;
          }
          if (r->r_offset >= (aligned_size - sizeof(uint64_t)) ||
              r->r_addend >= (int64_t)(aligned_size) || r->r_addend < 0) {
            return ERROR_INVALID_ELF;
          }
          uint64_t temp = (uint64_t)(aligned_addr + r->r_addend);
          memcpy(aligned_addr + r->r_offset, &temp, sizeof(uint64_t));
        }
      }
    } else if (sh->sh_type == SHT_DYNSYM) {
      /* We assume one ELF file only has one DYNSYM section now */
      if (sh->sh_entsize != sizeof(Elf64_Sym)) {
        return ERROR_INVALID_ELF;
      }
      uint8_t *addr2 =
          addr_offset_checked(aligned_addr, aligned_size, sh->sh_offset);
      if (addr2 == 0) {
        return ERROR_INVALID_ELF;
      }
      context->dynsyms = (Elf64_Sym *)addr2;
      context->dynsym_size = sh->sh_size / sh->sh_entsize;

      uint8_t *addr3 = addr_offset_with_context(addr2, sh->sh_size, context);
      if (addr3 == 0) {
        return ERROR_INVALID_ELF;
      }
    } else if (sh->sh_type == SHT_STRTAB) {
      static char DYNSTR[] = ".dynstr";
      if (sh->sh_name < (4096 - sizeof(DYNSTR)) &&
          shshrtab->sh_size >= sizeof(DYNSTR) &&
          sh->sh_name < (shshrtab->sh_size - sizeof(DYNSTR))) {
        const char *current_str = shrtab + sh->sh_name;
        if (strcmp(DYNSTR, current_str) == 0) {
          const uint8_t *addr2 =
              addr_offset_checked(aligned_addr, aligned_size, sh->sh_offset);
          if (addr2 == 0) {
            return ERROR_INVALID_ELF;
          }
          context->dynstr = (const char *)addr2;
        }
      }
    }
  }
  if (context->dynsyms == NULL || context->dynstr == NULL) {
    return ERROR_INVALID_ELF;
  }
  *handle = (void *)context;
  *consumed_size = max_consumed_size + RISCV_PGSIZE;
  return CKB_SUCCESS;
}

void *ckb_dlsym(void *handle, const char *symbol) {
  if (handle == NULL || symbol == NULL) {
    return NULL;
  }
  CkbDlfcnContext *context = (CkbDlfcnContext *)handle;

  if (context->base_addr == NULL || context->size == 0 ||
      context->dynstr == NULL || context->dynsym_size == 0 ||
      context->dynsyms == NULL) {
    return NULL;
  }
  if (!check_in_range(context->dynstr, context)) {
    return NULL;
  }
  uint64_t _end = 0;
  if (__builtin_uaddl_overflow((uint64_t)context->base_addr, context->size,
                               &_end)) {
    return NULL;
  }

  for (uint64_t i = 0; i < context->dynsym_size; i++) {
    Elf64_Sym *sym = &context->dynsyms[i];
    const char *str =
        addr_offset_with_context(context->dynstr, sym->st_name, context);
    const void *str_end =
        addr_offset_with_context(str, strlen(symbol), context);
    if ((str == 0) || (str_end == 0)) return NULL;
    if (strcmp(str, symbol) == 0) {
      void *p =
          addr_offset_with_context(context->base_addr, sym->st_value, context);
      if (p == 0) {
        return 0;
      } else {
        return p;
      }
    }
  }

  return NULL;
}

#endif /* CKB_STDLIB_NO_SYSCALL_IMPL */

#endif /* CKB_C_STDLIB_CKB_DLFCN_H_ */
