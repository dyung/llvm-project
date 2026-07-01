// RUN: not %clang_cc1 -std=c++17 -x c++-module-map %s -emit-module -fmodule-name=Foo -o %t 2>&1 | FileCheck %s
// RUN: %clang_cc1 -std=c++20 -x c++-module-map %s -emit-module -fmodule-name=Foo -o %t 
// CHECK: module compilation requires '-fmodules'
module Foo {}
#pragma clang module contents
