import struct

from common import *

import re

class Assembler:
    def __init__(self):
        self.opers = []

        # Предопределённые переменные
        self.label_tbl = {'IP': Reg.IP, 'SP': Reg.SP, 'BP': Reg.BP, 'CFL': Reg.CFL}
        self.num_registers_reserved = len(self.label_tbl)
        self.source = []
        self.code = [[0, 0, len(self.label_tbl)], [0, 0, 0], [0, 0, 0], [0, 0, 0]]
        self.IP = None
        self.last_static = self.num_registers_reserved
        self.static_strs = dict()

    def write_static_str_to_code(self, s):
        string_code = []
        for c in s:
            string_code.append()

    def print_code(self):
        for line in self.code:
            print("%s"%line)

    def read_file(self, filename):
        with open(filename, 'r') as inf:
            for line in inf:
                if line[0] != '#' and line != '\n' and line.strip() != '':
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
        elif l[0] == OPType.C2M:
            c[1] = int(l[1])
            c[2] = self.label_tbl[l[2]]
        elif l[0] == OPType.CALL:
            c[1] = self.label_tbl[l[1]]
        elif l[0] == OPType.STR:
            s = re.findall('"([^"]*)"', line)[0] + '\0'
            self.static_strs[self.last_static] = s
            self.label_tbl[l[1]] = self.last_static
            c[1] = self.last_static
            self.last_static += len(s)
        elif l[0] == OPType.WRITESTR:
            c[1] = self.label_tbl[l[1]]
        else:
            if len(l) > 1:
                c[1] = self.label_tbl[l[1]]
            if len(l) > 2:
                c[2] = self.label_tbl[l[2]]
        print(c)
        return c

    def assemble(self, filename, outf_name):
        self.read_file(filename)
        self.last_static += len(self.source)

        # Первый проход, смотрим метки
        ip = len(self.label_tbl)
        self.IP = ip
        for i, line in enumerate(self.source):
            if line[0] == ':':
                label_name = line.split()[0][1:]
                print(label_name)
                self.label_tbl[label_name] = self.IP
            self.IP += 1

        # Второй проход, пишем программу.
        self.IP = ip
        for line in self.source:
            self.code.append(self.process_line(line))
            self.IP += 1
        # self.print_code()

        # Дописываем статические строки
        for address, s in sorted(self.static_strs.items(), key=lambda x: x[0]):
            for c in s:
                print(c, c.encode('utf-8'), ord(c.encode('utf-8')))
                self.code.append([0, 0, ord(c.encode('utf-8'))])

        with open(outf_name, 'wb') as outf:
            for c in self.code:
                outf.write(struct.pack('hhh', c[0], c[1], c[2]))


asm = Assembler()
asm.assemble('fib.asm', 'a.out')
