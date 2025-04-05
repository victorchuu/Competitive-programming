import sys
sys.stdin = open('input.txt')
# sys.stdout = open('output.txt')

# ---------------------------------------------

import functools as f
import math as m
import re

ii = lambda input: int(input())
intList = lambda input: [int(x) for x in input.split()]
istr = lambda input: str(input())

TOTAL = 0

def untilEOF(solveCase): 
    with open('input.txt') as f:
        for l in f:
            solveCase(l)
    print(f"Solution: {TOTAL}")
    

def infer(sequence):
    sol = [sequence[i] - sequence[i-1] for i in range(1, len(sequence))]
    return sol

def areAllZero(sequence):
    return not any(sequence)

def solve(line: str):
    sequence = intList(line)
    print(sequence)
    first_numbers = [sequence[0]]
    while not areAllZero(sequence):
        sequence = infer(sequence)
        first_numbers.append(sequence[0])
        print(f"New sequence {sequence}")
    first_numbers.reverse()
    inferred_column = [0]
    for i in range(1, len(first_numbers)):
        inferred_column.append(first_numbers[i] - inferred_column[i-1])
    print(f"The number is {inferred_column[-1]}")

    global TOTAL
    TOTAL += inferred_column[-1]

    

untilEOF(solve)


