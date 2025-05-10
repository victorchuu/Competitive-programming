import sys
import os

if 'victor' in os.path.abspath('.'):
    sys.stdin = open('input.txt')


# ---------------------------------------------

import functools as f
import math
import re

ii = lambda : int(input())
iii = lambda: [int(x) for x in input().split()]
istr = lambda : str(input())

def forEachCase(solveCase): 
    cases = ii()
    for i in range(cases):
        print(f"{solveCase()}")

def untilEOF(solveCase): 
    with open('input.txt') as f:
        for l in f:
            solveCase(l)
    print(f"Solution: {TOTAL}")

def solve():
    pass

untilEOF(solve)
