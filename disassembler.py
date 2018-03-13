from common import *
import struct


class Disassembler:
    def __init__(self):
        self.memory = []
        self.labels = {0: 'IP', 1: 'SP', 2: 'BP', 3: 'CFL'}
        self.commands = []
        self.labels_count = {'VAR': 0, 'FUN': 0, 'LABEL': 0}

    def get_next_name(self, prefix='VAR'):
        ret = "%s%d"%(prefix, self.labels_count[prefix])
        self.labels_count[prefix] += 1
        return ret

    def load_file_to_mem(self, filename):
        with open(filename, 'rb') as f:
            smth = f.read(6)
            while smth:
                d = struct.unpack('hhh', smth)
                self.memory.append(list(d))
                smth = f.read(6)

    def disassemble(self, filename):
        self.load_file_to_mem(filename)

        ip = 4
        while ip < len(self.memory):
            c = self.memory[ip]
            # print(c)
            l = [None]*3
            l[0] = OPType(c[0])
            l = l[:get_num_operands(l[0]) + 1]

            if l[0] == OPType.VAR:
                if ip > 3:
                    self.labels[ip] = self.get_next_name()
                    l[1] = self.labels[ip]
                else:
                    l[1] = self.labels[ip]
                l[2] = int(c[2])
            elif l[0] == OPType.C2M:
                l[1] = int(c[1])
            elif l[0] == OPType.CALL:
                if c[1] not in self.labels:
                    self.labels[c[1]] = self.get_next_name('FUN')
                l[1] = self.labels[c[1]]
            elif l[0] == OPType.IF:
                if c[1] not in self.labels:
                    self.labels[c[1]] = self.get_next_name('LABEL')
                l[1] = self.labels[c[1]]
            else:
                if len(l) > 1:
                    l[1] = self.labels[c[1]]
                if len(l) > 2:
                    l[2] = self.labels[c[2]]

            if ip in self.labels:
                prefix = ':' + self.labels[ip] + ' '
            else:
                prefix = ''
            l[0] = l[0].name
            l = list(map(lambda x: str(x), l))
            print("%s%s"%(prefix, ' '.join(l)))

            ip += 1


disasm = Disassembler()
disasm.disassemble('a.out')
