// RUN: %clang_cc1 -triple aarch64-windows-msvc -w -fdump-record-layouts-simple \
// RUN:            -foverride-record-layout=%S/Inputs/override-layout-aligned-base.layout %s \
// RUN:   | FileCheck %s
// RUN: %clang_cc1 -triple arm64ec-windows-msvc -w -fdump-record-layouts-simple \
// RUN:            -foverride-record-layout=%S/Inputs/override-layout-aligned-base.layout %s \
// RUN:   | FileCheck %s
// RUN: %clang_cc1 -triple x86_64-windows-msvc -w -fdump-record-layouts-simple \
// RUN:            -foverride-record-layout=%S/Inputs/override-layout-aligned-base.layout %s \
// RUN:   | FileCheck %s

// An external layout source (such as LLDB reading DWARF) supplies a record's
// alignment directly; the over-alignment is not recoverable from an alignas
// attribute because no such attribute exists in the AST.  A derived class must
// still pick up the externally supplied alignment of its base.

// CHECK: Type: struct AlignedBase
// CHECK:   Size:64
// CHECK:   Alignment:64
struct AlignedBase {
};

// CHECK: Type: struct Derived
// CHECK:   Alignment:64
struct Derived : AlignedBase {
};

void use_structs() {
  Derived d;
}

/*
17.txt:
*** Dumping AST Record Layout
Type: struct AlignedBase

Layout: <ASTRecordLayout
  Size:64
  Alignment:64
  BaseOffsets: []>
  VBaseOffsets: []>
  FieldOffsets: []>

*** Dumping AST Record Layout
Type: struct Derived

Layout: <ASTRecordLayout
  Size:64
  Alignment:64
  BaseOffsets: [0]>
  VBaseOffsets: []>
  FieldOffsets: []>
*/
/* 20.txt:
*** Dumping AST Record Layout
Type: struct AlignedBase

Layout: <ASTRecordLayout
  Size:8
  Alignment:8
  BaseOffsets: []>
  VBaseOffsets: []>
  FieldOffsets: []>

*** Dumping AST Record Layout
Type: struct Derived

Layout: <ASTRecordLayout
  Size:8
  Alignment:8
  BaseOffsets: [0]>
  VBaseOffsets: []>
  FieldOffsets: []>
*/