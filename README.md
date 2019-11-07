# ckb-c-stdlib

[![Build Status](https://travis-ci.com/nervosnetwork/ckb-c-stdlib.svg?branch=master)](https://travis-ci.com/nervosnetwork/ckb-c-stdlib)

In the development of CKB scripts, we discovered many use-cases and patterns that could be really useful in writing CKB scripts. This repo serves as a commonplace for all those useful scripts. This could include but aren't limit to:

* CKB's data structure definitions
* Utilities for interacting with CKB via syscalls
* A shimmed libc, notice the libc here is tailored for CKB's special needs, implementing everything in POSIX's standard is never a goal. If you do have special requirements, using a more complete libc is always a better choice

Notice while this repo would focus on C code, it it not limited to scripts written in C. A Rust script might use FFI to leverage the C code here, a higher level language can also use certain glues to use the code here.
