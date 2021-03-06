//===- llvm/Support/StringSaver.h -------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_SUPPORT_STRINGSAVER_H
#define LLVM_SUPPORT_STRINGSAVER_H

#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/Twine.h"
#include "llvm/Support/Allocator.h"

namespace llvm {

/// \brief Saves strings in the inheritor's stable storage and returns a stable
/// raw character pointer.
class StringSaver final {
  BumpPtrAllocator &Alloc;

public:
  StringSaver(BumpPtrAllocator &Alloc) : Alloc(Alloc) {}
  StringRef save(const char *S) { return save(StringRef(S)); }
  StringRef save(StringRef S);
  StringRef save(const Twine &S) { return save(StringRef(S.str())); }
  StringRef save(std::string &S) { return save(StringRef(S)); }
};
}
#endif
