from dataclasses import dataclass


PLUS = lambda a,b: a+b
TIMES = lambda a,b: a*b
CONCAT = lambda a,b: int(str(a) + str(b))
OPERATORS = [PLUS, TIMES, CONCAT]

@dataclass
class Case:
    goal: int
    operands: list[int]
    
    def is_resolvable(self):
        if len(self.operands) == 1:
            return self.operands[0] == self.goal
        for operator in OPERATORS:
            if self.is_resolvable_rec(i=2, acc=operator(self.operands[0], self.operands[1])):
                return True
        return False
    
    def is_resolvable_rec(self, i, acc):
        if len(self.operands) - i == 0:
            return acc == self.goal
        for operator in OPERATORS:
            if self.is_resolvable_rec(i=i + 1, acc=operator(acc, self.operands[i])):
                return True
        return False

cases: list[Case] = []

with open('input.txt', 'r') as file:
    for line in file.readlines():
        goal, operands = line.split(':')
        cases.append(Case(int(goal), [int(x) for x in operands.split()]))

TOTAL = 0
for case in cases:
    if case.is_resolvable():
        print(f"Resolvable: {case}")
        TOTAL += case.goal

print(f"Solution: {TOTAL}")
