// RUN: %clang_cc1 -std=c++17 %s -ast-dump | FileCheck %s -check-prefix=CHECK,CHECK17
// RUN: %clang_cc1 -std=c++20 %s -ast-dump | FileCheck %s -check-prefix=CHECK,CHECK20

int(&&intu_rvref)[] {1,2,3,4};
// CHECK: VarDecl 0x[[GLOB_ADDR:[0-9a-f]+]] {{.*}} intu_rvref 'int (&&)[4]' listinit

// CHECK17-NEXT: ExprWithCleanups {{.*}} 'int[4]' xvalue
// CHECK17-NEXT: MaterializeTemporaryExpr {{.*}} 'int[4]' xvalue extended by Var 0x[[GLOB_ADDR]] 'intu_rvref' 'int (&&)[4]'

// CHECK20-NEXT: ExprWithCleanups {{.*}} 'int[]' xvalue
// CHECK20-NEXT: MaterializeTemporaryExpr {{.*}} 'int[]' xvalue extended by Var 0x[[GLOB_ADDR]] 'intu_rvref' 'int (&&)[4]'
// CHECK20-NEXT: ImplicitCastExpr {{.*}} 'int[]' <NoOp>

// CHECK-NEXT: InitListExpr {{.*}} 'int[4]'

// CHECK: FunctionDecl {{.*}} static_const
void static_const() {
  static const int(&&intu_rvref)[] {1,2,3,4};
  // CHECK: VarDecl 0x[[STATIC_ADDR:[0-9a-f]+]] {{.*}} intu_rvref 'const int (&&)[4]' static listinit

  // CHECK17-NEXT: ExprWithCleanups {{.*}} 'const int[4]' xvalue
  // CHECK17-NEXT: MaterializeTemporaryExpr {{.*}} 'const int[4]' xvalue extended by Var 0x[[STATIC_ADDR]] 'intu_rvref' 'const int (&&)[4]'

  // CHECK20-NEXT: ExprWithCleanups {{.*}} 'const int[]' xvalue
  // CHECK20-NEXT: MaterializeTemporaryExpr {{.*}} 'const int[]' xvalue extended by Var 0x[[STATIC_ADDR]] 'intu_rvref' 'const int (&&)[4]'
  // CHECK20-NEXT: ImplicitCastExpr {{.*}} 'const int[]' <NoOp>

  // CHECK-NEXT: InitListExpr {{.*}} 'const int[4]'
}

// CHECK: FunctionDecl {{.*}} const_expr
constexpr int const_expr() {
  int(&&intu_rvref)[]{1, 2, 3, 4};
  // CHECK: VarDecl 0x[[CE_ADDR:[0-9a-f]+]] {{.*}} intu_rvref 'int (&&)[4]' listinit

  // CHECK17-NEXT: ExprWithCleanups {{.*}} 'int[4]' xvalue
  // CHECK17-NEXT: MaterializeTemporaryExpr {{.*}} 'int[4]' xvalue extended by Var 0x[[CE_ADDR]] 'intu_rvref' 'int (&&)[4]'

  // CHECK20-NEXT: ExprWithCleanups {{.*}} 'int[]' xvalue
  // CHECK20-NEXT: MaterializeTemporaryExpr {{.*}} 'int[]' xvalue extended by Var 0x[[CE_ADDR]] 'intu_rvref' 'int (&&)[4]'
  // CHECK20-NEXT: ImplicitCastExpr {{.*}} 'int[]' <NoOp>

  // CHECK-NEXT: InitListExpr {{.*}} 'int[4]'
  return intu_rvref[0];
}
