#include "exceptions.h"

// setjmp example: error handling
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

class BaseException {
};

class TestException: public BaseException {

};

// if (1) нужно, чтобы потребовать то, чтобы дальше шёл обязательно блок.
#define TRY \
jmp_buf env; \
int val=0; \
val = setjmp (env); \
if (val == 0) { \
    if (1)

#define THROW(code) longjmp (env, code)

//if (val != 0) нужно, потому что надо выполнить и свой обработчик, и пользовательский.
#define EXCEPT(e)\
    else {}\
} else {\
    printf("Error %d happened\n", e); \
}\
if (val != 0)

int main() {
    TRY {
        int i = 12;
        printf("Hello world\n");
        THROW(1);
    } EXCEPT(1) {
        printf("excepting Error 1\n"); \
    };

    return 0;
}

/*
int main()
{
    jmp_buf env;
    int val = 0;

    val = setjmp (env);
    if (val) {
        fprintf (stderr,"Error %d happened",val);
        exit (val);
    }

    // code here //

    longjmp (env,101);   // signaling an error

    return 0;
}
*/
// longjmp example
/*#include <stdio.h>      // printf
#include <setjmp.h>     // jmp_buf, setjmp, longjmp

int main()
{
    jmp_buf env;
    int val;
    printf("val %d\n", val);

    val=setjmp(env);

    printf ("val is %d\n",val);

    if (!val) longjmp(env, 2);

    return 0;
}*/