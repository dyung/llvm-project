// RUN: %clang_cc1 -triple x86_64-linux -fsyntax-only -frounding-math -verify=expected,pre20 -std=c++17 %s
// RUN: %clang_cc1 -triple x86_64-linux -fsyntax-only -frounding-math -verify -std=c++20 %s

template <class b> b::a() {}
// pre20-warning@-1 {{missing 'typename' prior to dependent type name 'b::a' is a C++20 extension}}
// expected-error@-2 {{expected unqualified-id}}
