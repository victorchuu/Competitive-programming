import sys
sys.stdin = open('input.txt')
# sys.stdout = open('output.txt')

# ---------------------------------------------

import functools as f
import math as m
import re

ii = lambda : int(input())
intList = lambda: [int(x) for x in input().split()]
istr = lambda : str(input())

TOTAL = 0

def forEachCase(solveCase): 
    cases = ii()
    for i in range(cases):
        print(f"{solveCase()}")

def untilEOF(solveCase): 
    with open('input.txt') as f:
        for l in f:
            solveCase(l)
    print(f"Solution: {TOTAL}")

def solve(word):
    is_digit = lambda x: x=='0' or x=='1' or x=='2' or x=='3' or x=='4' or x=='5' or x=='6' or x=='7' or x=='8' or x=='9'
    filtered = list(filter(is_digit, word))
    sol :int = int(filtered[0] + filtered[-1])
    global TOTAL
    TOTAL += sol
    return sol

untilEOF(solve)
