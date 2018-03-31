#pragma once
#include <csetjmp>
#include <cstdio>
#include <string>

#define DEBUG
#ifdef DEBUG
#define debug(command) command
#else
#define debug(command)
#endif

class BaseException {
 public:
    virtual std::string msg() {
        printf("I'm base\n");
        return "I'm base";
    }
};

extern jmp_buf* env;
extern BaseException* current_exception_ptr;

#define TRY \
{ \
jmp_buf* prev_env = env; \
jmp_buf local_env; \
assert(*prev_env != local_env); \
env = &local_env; \
destroyer.createFrame(); \
bool error_occured = setjmp (*env); \
if (error_occured == 0) { \
    if (1)

#define THROW(exception) \
do{ \
current_exception_ptr = new exception; \
destroyer.unwindFrame(); \
longjmp (*env, 1); \
} while(0)

#define EXCEPT(etype, e, whattodo)\
    else {}\
} else {\
    debug(/*printf("Error happened\n")*/); \
    if (dynamic_cast<etype*>(current_exception_ptr) != nullptr) { \
        BaseException& e = *current_exception_ptr; \
        debug(printf("Found error %s\n", e.msg().c_str())); \
        whattodo; \
        delete current_exception_ptr; \
    } else { \
        debug(printf("Unwind\n")); \
        destroyer.unwindFrame(); \
        longjmp(*prev_env, 1); \
    }\
}}
//if (error_occured != 0 && found)

#define MAIN(args...) \
main(args) { \
jmp_buf env; \
int error_occured = setjmp (env); \
if (error_occured != 0) { \
printf("Found an exception not caught. Exiting."); \
return 1; \
}

