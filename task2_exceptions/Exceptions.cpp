#include "Exceptions.h"
#include <csetjmp>

jmp_buf start_env;
jmp_buf* env = &start_env;
BaseException* current_exception_ptr = 0;
