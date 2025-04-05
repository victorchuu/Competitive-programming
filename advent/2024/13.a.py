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
    prize_x: int
    prize_y: int

    def calculate_position(self, a, b):
        return a * self.A1 + b * self.B1, a * self.A2 + b * self.B2
    
    def best_combination(self, a, b):
        @lru_cache
        def _best_combination(a, b):
            x, y = self.calculate_position(a, b)
            if x == self.prize_x and y == self.prize_y:
                return cost(a, b)
            if a > 100 or b > 100 or x > self.prize_x or y > self.prize_y:
                return INFINITY
            
            return min(_best_combination(a + 1, b), _best_combination(a, b + 1))
        
        return _best_combination(a, b)
                



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
            prize_x = int(parts[0].split('=')[1])
            prize_y = int(parts[1].split('=')[1])
        
            cases.append(Case(A1, A2, B1, B2, prize_x, prize_y))

solutions = [case.best_combination(0, 0) for case in cases]
print(solutions)
print(sum([x for x in solutions if x != INFINITY]))
            