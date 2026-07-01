// This error is emitted in C++17 mode only. C++20 mode emits no errors.
// Lambdas are allowed in unevaluated constext in C++20.
// RUN: %clang_cc1  -std=gnu++17 -triple x86_64-unknown-unknown -fsyntax-only -verify %s
// RUN: %clang_cc1  -std=gnu++20 -triple x86_64-unknown-unknown -fsyntax-only -verify=cpp20 %s

// cpp20-no-diagnostics
struct Bar {int a;};
const Bar arr[2] = {{1}};

struct Foo {};

const int b = 2;

void foo(int a) {
  Foo *foo_array;
  foo_array = new Foo[arr[0].a];
}

void Test(int N) {
  int arr[N];
  decltype([&arr]{}) *p; // expected-error {{lambda expression in an unevaluated operand}}
}
