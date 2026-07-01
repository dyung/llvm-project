// RUN: %clang_cc1 -fsyntax-only -verify -std=c++17 %s
// RUN: %clang_cc1 -fsyntax-only -verify=expected,cpp20 -std=c++20 %s

volatile int i;

const int &inc = i++; // cpp20-warning {{increment of object of volatile-qualified type}}
const int &dec = i--; // cpp20-warning {{decrement of object of volatile-qualified type}}

const int &incfail = ++i; // expected-error {{drops 'volatile' qualifier}}
			  // cpp20-warning@-1 {{increment of object of volatile-qualified type}}
const int &decfail = --i; // expected-error {{drops 'volatile' qualifier}}
			  // cpp20-warning@-1 {{decrement of object of volatile-qualified type}}

// PR7794
void f0(int e) {
  ++(int&)e;
}
