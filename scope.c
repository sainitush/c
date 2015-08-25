#include <stdio.h>
#include "scope.h"

/*
 * A good artical here: http://norswap.com/c_scope_duration_linkage/
 *
 * The scope of a declaration is the part of the code where the declaration is seen
 * and can be used.
 * Note that this says nothing about whether the object associated
 * to the declaration can be accessed from some other part of the code via another
 * declaration. We uniquely identify an object by its memory: the storage for a
 * variable or the function code.
 * Finally, note that a declaration in a nested scope can hide a declaration in
 * an outer scope; but only if one of two has no linkage.
 *
 * Duration indicates whether the object associated to the declaration persists
 * throughout the program's execution or whether it is allocated dynamically when
 * the declaration's scope is entered.
 *
 * Linkage is what determines if multiple declarations of the same object refer to
 * the same object, or to separate ones. Each declaration can only have one of
 * five storage class specifier: static, extern, auto, register and typedef.
 *
 * Scope:
 * ----------
 * 1) block scope: every variable or function declaration that appears inside a block
 * (including a function body) has block scope. The scope goes from the declaration to
 * the end of the innermost block in which the declaration appears. Function parameter
 * declarations in function definitions (but not in prototypes) also have block scope.
 * The scope of a parameter declaration therefore includes the parameter declarations
 * that appears after it.
 *
 * 2) function scope: goto label is a bit special, which are implicitly declared at
 * the place where they appears, but they are visible throughout the function, even
 * if they appear inside a block.
 *
 * 3) function prototype scope: is the scope for function parameters that appears
 * inside a function prototype. It extends until the end of the prototype. This
 * scope exists to ensure that function parameters have distinct names.
 *
 * 4) file scope: all vairables and functions defined ouside functions have file
 * scope. They are visible from their declarration until the end of the file.
 * Here, the term 'file' should be understood as the source file being compiled,
 * after all includes have been resolved.
 * 
 * Storage Class Specifiers
 * ----------
 * 1) auto: can't apply to parameter declarations. It is the default for variable
 * declared inside a function body, and is in fact a historic leftover from C
 * predecessor's B.
 * 2) register: is a hint to the compiler that it might be a good idea to store
 * the variable in a register, but the compiler is not forced to do so. The
 * compiler does make sure that you do not take the address of a vairable with
 * the register storage class.
 *
 * Declarations & Definitions
 * ----------
 * 1) All declarations with no linkage are also definitions. Other declarations are
 * definitions if they have an intializer.
 * 2) A file-scope variable declaration without the extern storage class specifier
 * or initializer is a tentative definition.
 * 3) All definitions are declarations but not vice-versa.
 * 4) A definition of an identifier is a declaration for that identifier that:
 * for an object, causes storage to be reserved for that object.
 *
 * Linkage
 * ----------
 * 1) No Linkage: A declaration with no linkage is associated to an object that
 * is not shared with any other declaration. All declarations with no linkage
 * happen at block scope: all block scope declarations without the extern storage
 * class specifier have no linkage.
 * 2) Internal Linkage: within the compilation unit, all declarations with
 * internal linkage for the same identifier refer to the same object.
 * 3) External Linkage: within the whole program, all declarations with external
 * linkage for the same identifier refer to the same object.
 *
 * A. automatic variables:
 * 1) automatic variables includes global_auto_i0/i1, i0/i1;
 * 2) uninitialized variables will be set to 0;
 *
 * 
 */

/* file scope, declaration, definition with initializer  */
int i0 = 123;

/* file scope, declaration, tentative definition with initializer to 0 */
int i1;

/* file scope, extern declaration, must without initializer */
extern int i2;

/* function sub forward declaration */
void sub(int, int);

int main(int argc, char *argv[]) {
  
  printf("file scope: i0=%i\n", i0);
  
  int i0 = 321;
  printf("block scope in main: i0=%i\n", i0);

  {
    int i0 = 123+321;
    printf("block scope in main nested block: i0=%i\n", i0);
  }

  printf("block scope in main: i0=%i\n", i0);

  printf("function scope for function parameter: argc=%i\n", argc);
  {
    int argc = 123;
    printf("block scope in main nested block: argc=%i\n", argc);
  }

  if (i0 > 0) {
    goto i0;
    printf("this line bypassed via goto\n");
  }
  
  {
    /* goto lable has different namespace than objects,
     * so u can use i0 here
     */
    i0:
    printf("goto label i0 in main nested block, samed id with i0\n");
  }

  sub(i0, i0+1);

  {
    auto int i0 = 1;
    printf("auto int i0 in main nested block: i0=%i\n", i0);
  }

  printf("file scope, tentative definition: i1=%i\n", i1);

  printf("file scope, extern declaration: i2=%i\n", i2); 
  

}

void sub(int i0, int i1) {
  printf("block scope in sub: i0=%i\n", i0+i1);

  /* well, the i0 from function parameter i0, so u can't redefined it */
  /* int i0 += 1; */
}
