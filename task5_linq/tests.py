import unittest
from main import *


class Test(unittest.TestCase):
    def test_lazy(self):
        temp = LinqWrapper(range(10), print_on_gen=True) \
               >> Where(lambda x: x % 2 == 0) \
               >> Select(lambda x: x**2) \
               >> Take(2)
        # Because "Generated ..." messages are between these prints, this Linq is lazy.
        print(temp.__next__())
        print(temp.__next__())
        with self.assertRaises(StopIteration):
            temp.__next__()

    def test_where(self):
        self.assertEqual([2, 4, 6, 8],
                         LinqWrapper(range(1, 10)) >> Where(lambda x: x % 2 == 0) >> ToList()
                         )

    def test_fib(self):
        self.assertEqual([0, 1, 1, 2, 3, 5, 8, 13, 21, 34],
                         LinqWrapper(fibonacci_generator()) >> Take(10) >> ToList())

    def test_flatten(self):
        seq = [[i * 3, i * 3 + 1, i * 3 + 2] for i in range(0, 3)]
        self.assertEqual([0, 1, 2, 3, 4, 5, 6, 7, 8],
                         LinqWrapper(seq) >> Flatten() >> ToList())

    def test_groupby(self):
        self.assertEqual([(0, [0, 3, 6, 9]), (1, [1, 4, 7]), (2, [2, 5, 8])],
                         LinqWrapper(range(10)) >> GroupBy(lambda x: x % 3) >> ToList())

    def test_orderby(self):
        self.assertEqual([9, 8, 7, 6, 5, 4, 3, 2, 1, 0],
                         LinqWrapper(range(10)) >> OrderBy(reverse=True) >> ToList())

    def test_task1(self):
        self.assertEqual([0, 3, 21, 20736, 987],
                         LinqWrapper(fibonacci_generator())
                         >> Where(lambda x: x % 3 == 0)
                         >> Select(lambda x: x**2 if x % 2 == 0 else x)
                         >> Take(5)
                         >> ToList())

    def test_task2(self):
        self.assertEqual(
            [('\n', 30994), ('и', 24114), ('в', 17829), ('не', 10497), ('на', 10125), ('я', 9136), ('а', 8906),
             ('с', 5796), ('как', 4373), ('что', 4359)],
            LinqWrapper(get_lines("perashki.txt"))
            >> Select(lambda s: s.split(' '))
            >> Flatten()
            >> GroupBy(lambda x: x)
            >> Select(lambda pair: (pair[0], len(pair[1])))
            >> OrderBy(lambda pair: pair[1], reverse=True)
            >> Take(10)
            >> ToList())


if __name__ == "__main__":
    unittest.main()
