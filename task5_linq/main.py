class Linq:
    def __iter__(self):
        return self

    # def __rshift__(self, other):
    #     other.inp = self
    #     return other
    def __rrshift__(self, other):
        self.inp = other
        if hasattr(self, 'to'):
            return self.to(self.inp)
        else:
            return self


class SequenceWrapper(Linq):
    def __init__(self, sequence):
        self.inp = iter(sequence)

    def __next__(self):
        ret = next(self.inp)
        print("Generated %s" % ret)
        return ret


class GeneratorWrapper(Linq):
    def __init__(self, generator):
        self.inp = generator

    def __next__(self):
        ret = next(self.inp)
        print("Generated %s" % ret)
        return ret


class Map(Linq):
    def __init__(self, map_expression):
        self.map_expression = map_expression

    def __next__(self):
        n = next(self.inp)
        return self.map_expression(n)


class Filter(Linq):
    def __init__(self, filter_expression):
        self.filter_expression = filter_expression

    def __next__(self):
        while True:
            n = next(self.inp)
            if self.filter_expression(n):
                return n


class Take(Linq):
    def __init__(self, n):
        self.n = n
        self.count = 0

    def __next__(self):
        if self.count < self.n:
            self.count += 1
            return next(self.inp)
        else:
            raise StopIteration


class Flatten:
    def __next__(self):
        elem = next(self.inp)
        # TODO
class ToList(Linq):
    def __init__(self):
        self.to = list


# temp = Range(range(1, 10))
# print(list(temp))
# while True:
#     print(temp.__next__())

# temp = Range(range(1, 10)) >> Filter(lambda x: x % 2 == 0)
# print(list(temp))

# temp = Range(range(10)) >> Filter(lambda x: x % 2 == 0) >> Map(lambda x: x**2) >> Take(2) >> ToList()
# print(temp)

temp = SequenceWrapper(range(10)) >> Filter(lambda x: x % 2 == 0) >> Map(lambda x: x**2) >> Take(2)
print(temp.__next__())
print(temp.__next__())
try:
    print(temp.__next__())
except StopIteration:
    print("End")


def fibonacci_generator():
    a, b = 0, 1
    while 1:
        yield a
        a, b = b, a + b

print(GeneratorWrapper(fibonacci_generator()) >> Take(10) >> ToList())
