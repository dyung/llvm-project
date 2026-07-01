// Make sure we treat includes that are part of modulemaps the same as textual
// headers when modules are not enabled (e.g do't generate import decls, but
// still perform layering checks).
// No need to pass -fno-modules explicitly, absence implies negation for cc1.
// RUN: %clang_cc1 -std=c++17 -I %S/Inputs/modulemaps-nomodules -fmodule-map-file=%S/Inputs/modulemaps-nomodules/module.modulemap %s -verify -ast-dump | FileCheck %s
// RUN: %clang_cc1 -std=c++20 -I %S/Inputs/modulemaps-nomodules -fmodule-map-file=%S/Inputs/modulemaps-nomodules/module.modulemap %s -verify=expected,cpp20 -ast-dump | FileCheck %s

#include "header.h" // expected-error{{use of private header from outside its module: 'header.h'}}
                    // cpp20-error@-1{{module 'M' is needed but has not been provided, and implicit use of module files is disabled}}
// CHECK-NOT: ImportDecl
