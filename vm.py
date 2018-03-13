from common import *

import struct
import logging


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
        print('Registers', registers)
        stack_size = VM.decode(self.memory[Reg.SP])[2]
        if stack_size == 0:
            stack = []
        else:
            stack = list(map(lambda bytes: VM.decode(bytes), self.memory[-stack_size:]))
        print('Stack', stack_size, stack)
        print()

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
        #self.print_memory()

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
        # print(i, VM.decode(self.memory[i]))
        return VM.decode(self.memory[i])[pos]

    def exec(self, filename):
        self.load_file_to_mem(filename)
        i = 0
        while i < 100:
            i += 1
            ip = VM.decode(self.memory[Reg.IP])[2]
            c = VM.decode(self.memory[ip])
            print(c)
            l = [None]*3
            l[0] = OPType(c[0])
            print(l[0])
            if l[0] == OPType.READ:
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
                # print('ip is', self.get_val(Reg.IP, 2))
                # print('sp is', self.get_val(MEM_SIZE - 1 - Reg.SP, 2))
                self.memory[Reg.IP] = VM.encode([0, 0, c[1] - 1]) #TODO: было -1
            elif l[0] == OPType.VAR:
                pass
            else:
                raise Exception("Unknown operator %s"%l[0])
            self.memory[Reg.IP] = VM.encode([0, 0, self.get_val(Reg.IP) + 1])
            self.print_info()


# vm = VM()
# vm.exec('a.out')
vm = VM({4: 'A', 5: 'B', 6: 'S1', 7: 'S2', 8: 'RETA'})
vm.exec('a.out')
