// RUN: rm -rf %t
// RUN: %clang_cc1 -std=c++17 -fmodules -fimplicit-module-maps -fno-modules-error-recovery -fmodules-local-submodule-visibility -fmodules-cache-path=%t -I%S/Inputs/submodule-visibility -verify=expected,pre20 %s
// RUN: %clang_cc1 -std=c++20 -fmodules -fimplicit-module-maps -fno-modules-error-recovery -fmodules-local-submodule-visibility -fmodules-cache-path=%t -I%S/Inputs/submodule-visibility -verify=expected,cpp20 %s

#include "cycle1.h"
C1 c1;
C2 c2; // pre20-error {{missing '#include "cycle2.h"'; 'C2' must be declared}}
       // cpp20-error@-1 {{declaration of 'C2' must be imported from module 'cycles.cycle2' before it is required}}
// expected-note@cycle2.h:6 {{here}}

#include "cycle2.h"
C2 c3;
