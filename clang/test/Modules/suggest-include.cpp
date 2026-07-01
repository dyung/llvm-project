// RUN: rm -rf %t
// RUN: %clang_cc1 -std=c++17 -fmodules -fmodules-cache-path=%t -fimplicit-module-maps -I%S/Inputs/suggest-include %s -verify=expected,pre20

// RUN: rm -rf %t
// RUN: %clang_cc1 -std=c++20 -fmodules -fmodules-cache-path=%t -fimplicit-module-maps -I%S/Inputs/suggest-include %s -verify=expected,cpp20

#include "empty.h" // import the module file

// expected-note@usetextual1.h:2 {{here}}
// expected-note@textual2.h:1 {{here}}
// expected-note@textual3.h:1 {{here}}
// expected-note@textual4.h:1 {{here}}
// expected-note@textual5.h:1 {{here}}
// expected-note@private1.h:1 {{here}}
// expected-note@private2.h:1 {{here}}
// expected-note@private3.h:1 {{here}}

void f() {
  (void)::usetextual1; // pre20-error {{missing '#include "usetextual1.h"'}}
		       // cpp20-error@-1{{declaration of 'usetextual1' must be imported from module 'X.A'}}
  (void)::usetextual2; // pre20-error {{missing '#include "usetextual2.h"'}}
		       // cpp20-error@-1{{declaration of 'usetextual2' must be imported from module 'X.B'}}
  (void)::textual3; // pre20-error-re {{{{^}}missing '#include "usetextual3.h"'}}
		       // cpp20-error@-1{{declaration of 'textual3' must be imported from module 'X.C'}}
  // If the declaration is in an include-guarded header, make sure we suggest
  // including that rather than importing a module. In this case, there could
  // be more than one module, and the module name we picked is almost certainly
  // wrong.
  (void)::textual4; // pre20-error {{missing '#include "usetextual4.h"'; 'textual4' must be declared before it is used}}
		       // cpp20-error@-1{{declaration of 'textual4' must be imported from module 'X.D'}}
  (void)::textual5; // pre20-error {{missing '#include "usetextual5.h"'; 'textual5' must be declared before it is used}}
		       // cpp20-error@-1{{declaration of 'textual5' must be imported from module 'X.E'}}

  // Don't suggest #including a private header.
  // FIXME: We could suggest including "useprivate1.h" here, as it's the only
  // public way to get at this declaration.
  (void)::private1; // expected-error-re {{{{^}}declaration of 'private1'}}
  // FIXME: Should we be suggesting an import at all here? Should declarations
  // in private headers be visible when the surrounding module is imported?
  (void)::private2; // expected-error-re {{{{^}}declaration of 'private2'}}
  // Even if we suggest an include for private1, we should not do so here.
  (void)::private3; // expected-error-re {{{{^}}declaration of 'private3'}}
}
