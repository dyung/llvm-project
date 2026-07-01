// RUN: %clang_cc1 -std=c++17 -fms-extensions -fsyntax-only -verify %s -Wno-microsoft
// RUN: %clang_cc1 -std=c++17 -fms-extensions -fdelayed-template-parsing -fsyntax-only -verify %s -Wno-microsoft
// RUN: %clang_cc1 -std=c++20 -fms-extensions -fsyntax-only -verify=expected,cpp20 %s -Wno-microsoft
// RUN: %clang_cc1 -std=c++20 -fms-extensions -fdelayed-template-parsing -fsyntax-only -verify=expected,cpp20 %s -Wno-microsoft

class A {
public:
  template<typename T> struct X { typedef int x; };

  X<int>::x a; // expected-note {{implicit instantiation first required here}}

  template<> struct X<int>; // expected-error {{explicit specialization of 'A::X<int>' after instantiation}}
  template<> struct X<char>; // expected-note {{forward declaration}}
			     // cpp20-note@-1 {{forward declaration}}

  X<char>::x b; // expected-error {{incomplete type 'A::X<char>' named in nested name specifier}}
		// cpp20-error@-1 {{incomplete type 'A::X<char>' named in nested name specifier}}

  template<> struct X<double> {
    typedef int y;
  };

  X<double>::y c;

  template<> struct X<float> {}; // expected-note {{previous definition is here}}
  template<> struct X<float> {}; // expected-error {{redefinition of 'X<float>'}}
};

A::X<void>::x axv;
A::X<float>::x axf; // expected-error {{no type named 'x'}}

template<class T> class B {
public:
  template<typename U> struct X { typedef int x; };

  typename X<int>::x a; // expected-note {{implicit instantiation first required here}}

  template<> struct X<int>; // expected-error {{explicit specialization of 'X<int>' after instantiation}}
  template<> struct X<char>; // expected-note {{forward declaration}}

  typename X<char>::x b; // expected-error {{incomplete type 'B<float>::X<char>' named in nested name specifier}}

  template<> struct X<double> {
    typedef int y;
  };

  typename X<double>::y c;

  template<> struct X<float> {}; // expected-note {{previous definition is here}}
  template<> struct X<T> {}; // expected-error {{redefinition of 'X<float>'}}
};

B<float> b; // expected-note {{in instantiation of}}
