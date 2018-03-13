import struct

from common import *


class Assembler:
    def __init__(self):
        self.opers = []

        # Предопределённые переменные
        self.label_tbl = {'IP': Reg.IP, 'SP': Reg.SP, 'BP': Reg.BP, 'CFL': Reg.CFL}
        self.source = []
        self.code = [[0, 0, len(self.label_tbl)], [0, 0, 0], [0, 0, 0], [0, 0, 0]]
        self.IP = None

    def print_code(self):
        for line in self.code:
            print("%s"%line)

    def read_file(self, filename):
        with open(filename, 'r') as inf:
            for line in inf:
                self.source.append(line)

    def process_line(self, line):
        l = line.split()
        print(l)
        if l[0][0] == ':':
            l = l[1:]

        c = [0, 0, 0]  # code
        l[0] = OPType[l[0]]
        c[0] = l[0].value
        if l[0] == OPType.VAR:
            self.label_tbl[l[1]] = self.IP
            c[2] = int(l[2])
            c[0] = 0
        elif l[0] == OPType.C2M:
            c[1] = int(l[1])
            c[2] = self.label_tbl[l[2]]
        elif l[0] == OPType.CALL:
            c[1] = self.label_tbl[l[1]]
        else:
            if len(l) > 1:
                c[1] = self.label_tbl[l[1]]
            if len(l) > 2:
                c[2] = self.label_tbl[l[2]]
        print(c)
        return c

    def assemble(self, filename):
        self.read_file(filename)

        ip = len(self.label_tbl)
        self.IP = ip
        for i, line in enumerate(self.source):
            if line[0] != '#':
                if line[0] == ':':
                    label_name = line.split()[0][1:]
                    print(label_name)
                    self.label_tbl[label_name] = self.IP
                self.IP += 1

        self.IP = ip
        for line in self.source:
            if line[0] != '#':
                self.code.append(self.process_line(line))
                self.IP += 1
        self.print_code()
        with open('a.out', 'wb') as outf:
            for c in self.code:
                outf.write(struct.pack('hhh', c[0], c[1], c[2]))


asm = Assembler()
asm.assemble('fib.asm')
