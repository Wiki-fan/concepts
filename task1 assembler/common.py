from enum import Enum

import logging as log
log.basicConfig(level=log.INFO)

MEM_SIZE = 1000


def get_num_operands(op):
    if op in {OPType.VAR, OPType.M2M, OPType.C2M, OPType.EQ, OPType.ADD}:
        return 2
    elif op in {OPType.STOP, OPType.RET}:
        return 0
    else:
        return 1


class OPType(Enum):
    VAR = 1
    STR = 2

    READ = 5
    WRITE = 6
    WRITESTR = 7
    STOP = 8

    M2M = 10  # memory to memory
    C2M = 11  # constant to memory

    EQ = 20
    IF = 21
    ADD = 22

    PUSH = 31
    POP = 32

    CALL = 40
    RET = 41


class Reg:
    IP = 0
    SP = 1
    BP = 2
    CFL = 3
