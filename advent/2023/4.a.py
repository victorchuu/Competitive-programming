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

def solve(line):
    [_, l] = line.split(':')
    [a, b] = l.split('|')
    winning = set([int(x) for x in a.split(' ') if not x == ''])
    mine = [int(x) for x in b.split(' ') if not x == '']
    p = len([x for x in mine if x in winning])
    global TOTAL
    sol = int(2**(p-1))
    if p > 0:     
        TOTAL += sol
        print(f"2**{p-1} = {sol}")
    print(TOTAL)

untilEOF(solve)
