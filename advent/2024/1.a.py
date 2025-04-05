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
    l1, s2 = [], dict()
    with open('input.txt') as f:
        for l in f:
            a,b = [int(x) for x in l.split()]
            l1.append(a)
            if b in s2:
                s2[b] += 1
            else:
                s2[b] = 1
        

        TOTAL = 0
        for x in l1:
            TOTAL += x * s2[x] if x in s2 else 0
        print(TOTAL)

def solve():
    pass

untilEOF(solve)
