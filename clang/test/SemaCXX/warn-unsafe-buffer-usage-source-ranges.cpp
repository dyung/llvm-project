// RUN: %clang_cc1 -std=c++17 -Wno-everything -Wunsafe-buffer-usage \
// RUN:            -fsafe-buffer-usage-suggestions \
// RUN:            -fdiagnostics-print-source-range-info %s 2>&1 | FileCheck --check-prefixes=CHECK,CHECK17 %s

// RUN: %clang_cc1 -std=c++20 -Wno-everything -Wunsafe-buffer-usage \
// RUN:            -fsafe-buffer-usage-suggestions \
// RUN:            -fdiagnostics-print-source-range-info %s 2>&1 | FileCheck --check-prefixes=CHECK,CHECK20 %s

void foo(int i) {
  int * ptr;
  // CHECK20: {[[@LINE-1]]:3-[[@LINE-1]]:12}: warning: 'ptr' is an unsafe

  ptr++;
  // CHECK17: {[[@LINE-1]]:3-[[@LINE-1]]:6}
   ptr--;
  // CHECK17: {[[@LINE-1]]:4-[[@LINE-1]]:7}
  ++ptr;
  // CHECK17: {[[@LINE-1]]:5-[[@LINE-1]]:8}
   --ptr;
  // CHECK17: {[[@LINE-1]]:6-[[@LINE-1]]:9}


  ptr + 1;
  // CHECK: {[[@LINE-1]]:3-[[@LINE-1]]:6}
  2 + ptr;
  // CHECK: {[[@LINE-1]]:7-[[@LINE-1]]:10}
  ptr + i;
  // CHECK: {[[@LINE-1]]:3-[[@LINE-1]]:6}
  i + ptr;
  // CHECK: {[[@LINE-1]]:7-[[@LINE-1]]:10}


  ptr - 3;
  // CHECK: {[[@LINE-1]]:3-[[@LINE-1]]:6}
  ptr - i;
  // CHECK: {[[@LINE-1]]:3-[[@LINE-1]]:6}


  ptr += 4;
  // CHECK: {[[@LINE-1]]:3-[[@LINE-1]]:6}
  ptr += i;
  // CHECK: {[[@LINE-1]]:3-[[@LINE-1]]:6}


  ptr -= 5;
  // CHECK: {[[@LINE-1]]:3-[[@LINE-1]]:6}
  ptr -= i;
  // CHECK: {[[@LINE-1]]:3-[[@LINE-1]]:6}


  ptr[5];
  // CHECK17: {[[@LINE-1]]:3-[[@LINE-1]]:6}
  5[ptr];
  // CHECK: {[[@LINE-1]]:5-[[@LINE-1]]:8}
}
