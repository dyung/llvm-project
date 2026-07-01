// RUN: %clang_cc1 -x c -fsyntax-only -verify=expected,c -pedantic %s

// RUN: %clang_cc1 -x c++ -std=c++17 -fsyntax-only -verify=expected,cpp -Wshift-negative-value %s
// RUN: %clang_cc1 -x c++ -std=c++17 -fsyntax-only -verify=expected,cpp -Wall %s
// RUN: %clang_cc1 -x c++ -std=c++20 -fsyntax-only -verify -Wshift-negative-value %s
// RUN: %clang_cc1 -x c++ -std=c++20 -fsyntax-only -verify -Wall %s

// RUN: %clang_cc1 -x c++ -std=c++98 -fsyntax-only -verify=expected,cpp -Wshift-negative-value %s
// RUN: %clang_cc1 -x c++ -std=c++98 -fsyntax-only -verify=expected,cpp -Wall %s
// RUN: %clang_cc1 -x c++ -std=c++11 -fsyntax-only -verify=expected,cpp -Wshift-negative-value %s
// RUN: %clang_cc1 -x c++ -std=c++11 -fsyntax-only -verify=expected,cpp -Wall %s

enum shiftof {
#if defined(__cplusplus) && __cplusplus >= 202002L
    // No diagnostics are emitted in c++20 mode.
    // expected-no-diagnostics
#else
    X = (-1<<29) // c-warning {{expression is not an integer constant expression; folding it to a constant is a GNU extension}}
                 // cpp-error@-1 {{expression is not an integral constant expression}}
                 // expected-note@-2 {{left shift of negative value -1}}
#endif
};
