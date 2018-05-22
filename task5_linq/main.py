class Linq:
    def __iter__(self):
        return self

    def __rrshift__(self, other):
        self.inp = other
        return self


class LinqWrapper(Linq):
    def __init__(self, generator, print_on_gen=False):
        self.inp = iter(generator)
        self.print_on_gen = print_on_gen

    def __next__(self):
        ret = next(self.inp)
        if self.print_on_gen:
            print("Generated %s" % ret)
        return ret


class Select(Linq):
    def __init__(self, map_expression):
        self.map_expression = map_expression

    def __next__(self):
        n = next(self.inp)
        return self.map_expression(n)


class Flatten(Linq):

    def flatten(self, x):
        for y in iter(x):

            try:
                _ = iter(y)
                is_iterable = True
            except:
                is_iterable = False

            if is_iterable and not isinstance(y, str):
                yield from self.flatten(y)
            else:
                yield y

    def __next__(self):
        return next(self.inp)

    def __rrshift__(self, other):
        self.inp = iter(self.flatten(other))

        return self


class Where(Linq):
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


class GroupBy(Linq):
    def __init__(self, key=lambda x: x):
        self.key = key
        self.groups = dict()

    def __next__(self):
        return next(self.inp)

    def __rrshift__(self, other):
        self.inp = other

        for elem in self.inp:
            k = self.key(elem)
            if k in self.groups:
                self.groups[k].append(elem)
            else:
                self.groups[k] = [elem]

        self.inp = iter(self.groups.items())
        return self


class OrderBy(Linq):
    def __init__(self, key=lambda x: x, reverse=False):
        self.key = key
        self.reverse = reverse

    def __next__(self):
        return next(self.inp)

    def __rrshift__(self, other):
        self.inp = iter(sorted(other, key=self.key, reverse=self.reverse))

        return self


class ToList(Linq):
    def __init__(self):
        super().__init__()
        self.convert = list

    def __rrshift__(self, other):
        self.inp = other
        return self.convert(self.inp)


def fibonacci_generator():
    a, b = 0, 1
    while 1:
        yield a
        a, b = b, a + b


def get_lines(filename):
    with open(filename, "r") as f:
        yield from f
