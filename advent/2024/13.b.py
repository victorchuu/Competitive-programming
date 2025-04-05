from dataclasses import dataclass
from functools import lru_cache

INFINITY = float('inf')

def cost(a, b):
    return 3 * a + b

@dataclass
class Case:
    A1: int
    A2: int
    B1: int
    B2: int
    prize_1: int
    prize_2: int

    def resolve_equation(self):
        discriminant = self.A1 * self.B2 - self.A2 * self.B1
        matrix_range = self.prize_1 * self.B2 - self.prize_2 * self.B1
        if discriminant == 0 and matrix_range != 0:
            return None, None
        if discriminant == 0:
            print(f"System with many solutions: {self}")
            raise Exception("System with many solutions should not appear on the input")
        
        if matrix_range % discriminant != 0:
            return None, None

        x = matrix_range // discriminant

        if (self.prize_1 - self.A1 * x) % self.B1 != 0:
            return None, None
        
        y = (self.prize_1 - self.A1 * x) // self.B1
        if x < 0 or y < 0:
            return None, None
        return x, y
    
    def assert_is_solution(self, a, b):
        if not(a * self.A1 + b * self.B1 == self.prize_1 and a * self.A2 + b * self.B2 == self.prize_2):
            raise Exception(f"({a}, {b}) is not a solution for {self}")


with open('input.txt', 'r') as file:
    cases = list()
    for line in file.readlines():
        if line.startswith("Button A:"):
            parts = line.split(',')
            A1 = int(parts[0].split('+')[1])
            A2 = int(parts[1].split('+')[1])
        elif line.startswith("Button B:"):
            parts = line.split(',')
            B1 = int(parts[0].split('+')[1])
            B2 = int(parts[1].split('+')[1])
        elif line.startswith("Prize:"):
            parts = line.split(',')
            prize_1 = int(parts[0].split('=')[1]) + 10000000000000
            prize_2 = int(parts[1].split('=')[1]) + 10000000000000
        
            cases.append(Case(A1, A2, B1, B2, prize_1, prize_2))

solutions = list()
for case in cases:
    x, y = case.resolve_equation()

    if x is not None:
        if cost(x, y) == 184:
            print(case)
            print(x, y)
            case.assert_is_solution(x, y)
        solutions.append(cost(x, y))
    else:
        solutions.append(INFINITY)

print(solutions)
print(sum([x for x in solutions if x != INFINITY]))
            