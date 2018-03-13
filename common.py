from enum import Enum

MEM_SIZE = 1000

def get_num_operands(op):
    if op in {OPType.VAR, OPType.M2M, OPType.C2M, OPType.EQ, OPType.ADD}:
        return 2
    elif op in {OPType.STOP, OPType.RET}:
        return 0
    else:
        return 1
class OPType(Enum):
    VAR = 0

    READ = 5
    WRITE = 6
    STOP = 7


    M2M = 10  # memory to memory
    C2M = 11  # constant to memory

    EQ = 20
    IF = 21
    ADD = 22

    PUSH = 31
    POP = 32

    CALL = 40
    RET = 41
#
# FIRST_ARG_REG = {OPType.READ, OPType.EQ, OPType.ADD, OPType.PUSH, OPType.POP, OPType.RTM, OPType.MOV}
# SECOND_ARG_REG = {OPType.EQ, OPType.ADD, OPType.MOV, OPType.CTR}
# FIRST_ARG_ADDR = {OPType.WRITE, OPType.IF, OPType.MTR, OPType.CALL}
# SECOND_ARG_ADDR = {OPType.IF, OPType.RTM}
# FIRST_ARG_CONST = {OPType.CTR}

class Reg:
    IP = 0
    SP = 1
    BP = 2
    CFL = 3
