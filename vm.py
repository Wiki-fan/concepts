from common import *

import struct

import re
import codecs

ESCAPE_SEQUENCE_RE = re.compile(r'''
    ( \\U........      # 8-digit hex escapes
    | \\u....          # 4-digit hex escapes
    | \\x..            # 2-digit hex escapes
    | \\[0-7]{1,3}     # Octal escapes
    | \\N\{[^}]+\}     # Unicode characters by name
    | \\[\\'"abfnrtv]  # Single-character escapes
    )''', re.UNICODE | re.VERBOSE)


def decode_escapes(s):
    def decode_match(match):
        return codecs.decode(match.group(0), 'unicode-escape')

    return ESCAPE_SEQUENCE_RE.sub(decode_match, s)



class VM:
    def __init__(self, additional_labels=dict()):
        self.memory = [None]*MEM_SIZE
        self.PROGRAM_LEN = None
        self.labels = {**{0: 'IP', 1: 'SP', 2: 'BP', 3: 'CFL'}, **additional_labels}

    def print_memory(self):
        for i in range(self.PROGRAM_LEN):
            print(VM.decode(self.memory[i]))
        print('Stack')
        stack_size = VM.decode(self.memory[Reg.SP])[2]

        if stack_size == 0:
            print([])
        else:
            print(list(map(lambda bytes: VM.decode(bytes), self.memory[-stack_size:])))
        print()

    def print_info(self):
        registers = [(self.labels[i], VM.decode(self.memory[i])[2]) for i in range(0, len(self.labels))]
        log.debug('Registers', registers)
        stack_size = VM.decode(self.memory[Reg.SP])[2]
        if stack_size == 0:
            stack = []
        else:
            stack = list(map(lambda bytes: VM.decode(bytes), self.memory[-stack_size:]))
        log.debug('Stack', stack_size, stack)
        log.debug('\n')

    def load_file_to_mem(self, filename):
        with open(filename, 'rb') as f:
            smth = f.read(6)
            i = 0
            while smth:
                d = struct.unpack('hhh', smth)
                self.memory[i] = smth
                i += 1
                smth = f.read(6)
        self.PROGRAM_LEN = i

    @staticmethod
    def decode(bytes):
        return struct.unpack('hhh', bytes)

    @staticmethod
    def encode(c):
        return struct.pack('hhh', c[0], c[1], c[2])

    # Пушит такую-то ячейку памяти
    def push(self, elem):
        sp = VM.decode(self.memory[Reg.SP])[2]
        self.memory[MEM_SIZE - 1 - sp] = self.memory[elem]
        self.memory[Reg.SP] = VM.encode([0, 0, sp + 1])

    def pop(self, elem):
        sp = VM.decode(self.memory[Reg.SP])[2]
        self.memory[Reg.SP] = VM.encode([0, 0, sp - 1])
        self.memory[elem] = self.memory[MEM_SIZE - 1 - sp + 1]

    def get_val(self, i, pos=2):
        return VM.decode(self.memory[i])[pos]

    def exec(self, filename):
        self.load_file_to_mem(filename)
        i = 0
        while True:
            i += 1
            ip = VM.decode(self.memory[Reg.IP])[2]
            c = VM.decode(self.memory[ip])
            log.debug(c)
            l = [None]*3
            l[0] = OPType(c[0])
            log.debug(l[0])
            if l[0] == OPType.READ:
                print('< ', end='')
                d = int(input())
                self.memory[c[1]] = VM.encode([0, 0, d])
            elif l[0] == OPType.WRITE:
                print('>', VM.decode(self.memory[c[1]])[2])
            elif l[0] == OPType.M2M:
                d = self.get_val(c[1], 2)
                self.memory[c[2]] = VM.encode([0, 0, d])
            elif l[0] == OPType.C2M:
                d = c[1]
                self.memory[c[2]] = VM.encode([0, 0, d])
            elif l[0] == OPType.ADD:
                d = VM.decode(self.memory[c[1]])[2] + VM.decode(self.memory[c[2]])[2]
                self.memory[c[1]] = VM.encode([0, 0, d])
            elif l[0] == OPType.STOP:
                print('Exiting')
                break
            elif l[0] == OPType.PUSH:
                self.push(c[1])
            elif l[0] == OPType.POP:
                self.pop(c[1])
            elif l[0] == OPType.EQ:
                if self.memory[c[1]] == self.memory[c[2]]:
                    self.memory[Reg.CFL] = VM.encode([0, 0, 1])
                else:
                    self.memory[Reg.CFL] = VM.encode([0, 0, 0])
            elif l[0] == OPType.IF:
                # Если условие верно, выполняться как обычно, иначе прыгать
                if self.get_val(Reg.CFL) == 1:
                    self.memory[Reg.IP] = VM.encode([0, 0, c[1]-1])
            elif l[0] == OPType.CALL:
                self.push(Reg.IP)
                self.memory[Reg.IP] = VM.encode([0, 0, c[1] - 1])
            elif l[0] == OPType.VAR:
                pass
            elif l[0] == OPType.STR:
                pass
            elif l[0] == OPType.WRITESTR:
                arr = []
                ptr = self.get_val(c[1], 1)
                d = self.get_val(ptr)
                while d != 0:
                    c = chr(d)
                    arr.append(c)
                    ptr += 1
                    d = self.get_val(ptr)
                s = ''.join(arr)
                print(decode_escapes(s))
            else:
                raise Exception("Unknown operator %s"%l[0])
            self.memory[Reg.IP] = VM.encode([0, 0, self.get_val(Reg.IP) + 1])
            self.print_info()

# vm = VM()
# vm.exec('a.out')
vm = VM({4: 'A', 5: 'B', 6: 'S1', 7: 'S2', 8: 'RETA'})
vm.exec('a.out')

