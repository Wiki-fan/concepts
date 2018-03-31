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

#define TRY \
{ \
jmp_buf* prev_env = &env; \
jmp_buf env; \
assert(*prev_env != env); \
destroyer.createFrame(); \
bool found = false; \
bool error_occured = setjmp (env); \
if (error_occured == 0) { \
    if (1)

#define THROW(exception) \
current_exception_ptr = new exception; \
longjmp (env, 1)

#define EXCEPT(etype, e, whattodo)\
    else {}\
} else {\
    debug(printf("Error happened\n")); \
    if (dynamic_cast<etype*>(current_exception_ptr) != nullptr) { \
        BaseException& e = *current_exception_ptr; \
        found = true; \
        debug(printf("The message was '%s'\n", e.msg().c_str())); \
        whattodo; \
        delete current_exception_ptr; \
        destroyer.unwindFrame(); \
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

class BaseException {
 public:
    virtual std::string msg() {
        printf("I'm base\n");
        return "I'm base";
    }
};
