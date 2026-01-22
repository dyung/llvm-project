// RUN: rm -rf %t && mkdir -p %t
// RUN: %clang_cc1 -std=c++17 -fmodules -fblocks -fimplicit-module-maps -fmodules-cache-path=%t/ModulesCache/Tmpl -fdisable-module-hash -fapinotes-modules -fsyntax-only -I %S/Inputs/Headers -F %S/Inputs/Frameworks %s -x c++
// RUN: %clang_cc1 -std=c++17 -fmodules -fblocks -fimplicit-module-maps -fmodules-cache-path=%t/ModulesCache/Tmpl -fdisable-module-hash -fapinotes-modules -I %S/Inputs/Headers -F %S/Inputs/Frameworks %s -ast-dump -ast-dump-filter Box -x c++ | FileCheck -check-prefix=CHECK-BOX17 %s
// RUN: %clang_cc1 -std=c++17 -fmodules -fblocks -fimplicit-module-maps -fmodules-cache-path=%t/ModulesCache/Tmpl -fdisable-module-hash -fapinotes-modules -I %S/Inputs/Headers -F %S/Inputs/Frameworks %s -ast-dump -ast-dump-filter MoveOnly -x c++ | FileCheck -check-prefix=CHECK-MOVEONLY17 %s

// RUN: rm -rf %t && mkdir -p %t
// RUN: %clang_cc1 -std=c++20 -fmodules -fblocks -fimplicit-module-maps -fmodules-cache-path=%t/ModulesCache/Tmpl -fdisable-module-hash -fapinotes-modules -fsyntax-only -I %S/Inputs/Headers -F %S/Inputs/Frameworks %s -x c++
// RUN: %clang_cc1 -std=c++20 -fmodules -fblocks -fimplicit-module-maps -fmodules-cache-path=%t/ModulesCache/Tmpl -fdisable-module-hash -fapinotes-modules -I %S/Inputs/Headers -F %S/Inputs/Frameworks %s -ast-dump -ast-dump-filter Box -x c++ | FileCheck -check-prefix=CHECK-BOX20 %s
// RUN: %clang_cc1 -std=c++20 -fmodules -fblocks -fimplicit-module-maps -fmodules-cache-path=%t/ModulesCache/Tmpl -fdisable-module-hash -fapinotes-modules -I %S/Inputs/Headers -F %S/Inputs/Frameworks %s -ast-dump -ast-dump-filter MoveOnly -x c++ | FileCheck -check-prefix=CHECK-MOVEONLY20 %s

#include "Templates.h"



// CHECK-BOX17: Dumping Box:
// CHECK-BOX17-NEXT: ClassTemplateDecl {{.+}} imported in Templates Box
// CHECK-BOX17: SwiftAttrAttr {{.+}} <<invalid sloc>> "import_owned"

// Make sure the attributes aren't duplicated.
// CHECK-BOX17-NOT: SwiftAttrAttr {{.+}} <<invalid sloc>> "import_owned"



// CHECK-BOX20: Dumping Box:
// CHECK-BOX20-NEXT: ClassTemplateDecl {{.+}} imported in Templates hidden Box
// CHECK-BOX20: SwiftAttrAttr {{.+}} <<invalid sloc>> "import_owned"

// Make sure the attributes aren't duplicated.
// CHECK-BOX20-NOT: SwiftAttrAttr {{.+}} <<invalid sloc>> "import_owned"

// CHECK-MOVEONLY17: Dumping MoveOnly:
// CHECK-MOVEONLY17-NEXT: ClassTemplateDecl {{.+}} imported in Templates MoveOnly
// CHECK-MOVEONLY17: SwiftAttrAttr {{.+}} <<invalid sloc>> "~Copyable"

// Make sure the attributes aren't duplicated.
// CHECK-MOVEONLY17-NOT: SwiftAttrAttr {{.+}} <<invalid sloc>> "~Copyable"

// CHECK-MOVEONLY17: ClassTemplateSpecializationDecl {{.+}} imported in Templates {{.+}} MoveOnly
// CHECK-MOVEONLY17: TemplateArgument type 'int'
// CHECK-MOVEONLY17: SwiftAttrAttr {{.+}} <<invalid sloc>> "~Copyable"

// Make sure the attributes aren't duplicated.
// CHECK-MOVEONLY17-NOT: SwiftAttrAttr {{.+}} <<invalid sloc>> "~Copyable"

// CHECK-MOVEONLY17: ClassTemplateSpecializationDecl {{.+}} imported in Templates {{.+}} MoveOnly
// CHECK-MOVEONLY17: TemplateArgument type 'float'
// CHECK-MOVEONLY17: SwiftAttrAttr {{.+}} <<invalid sloc>> "~Copyable"

// Make sure the attributes aren't duplicated.
// CHECK-MOVEONLY17-NOT: SwiftAttrAttr {{.+}} <<invalid sloc>> "~Copyable"
