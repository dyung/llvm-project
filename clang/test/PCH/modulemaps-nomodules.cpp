// Make sure we don't crash when serializing a PCH with an include from a
// modulemap file in nomodules mode.
// No need to pass -fno-modules explicitly, absence implies negation for cc1.
// RUN: %clang_cc1 -std=c++17 -I %S/Inputs/modulemaps-nomodules -fmodule-map-file=%S/Inputs/modulemaps-nomodules/module.modulemap %s -emit-pch -o /dev/null
// RUN: %clang_cc1 -std=c++20 -I %S/Inputs/modulemaps-nomodules -fmodule-map-file=%S/Inputs/modulemaps-nomodules/module.modulemap %s -emit-pch -o /dev/null -verify

#include "header.h" // expected-error{{module 'M' is needed but has not}}
