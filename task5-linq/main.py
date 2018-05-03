class Range:
    def __init__(self, input_generator):
        self.inp = input_generator

    def __next__(self):
        return next(self.inp)

    def __rshift__(self, other):
        other.inp = self

class ToList:
    def __init__(self):
        pass

    def __call__(self):
        return list(self.inp)

    def __rshift__(self, other):
        other.inp = self


Range(range(1, 10)) >> ToList()
