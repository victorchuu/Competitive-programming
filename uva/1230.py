import sys
import os

if 'victor' in os.path.abspath('.'):
    sys.stdin = open('input.txt')



ii = lambda : int(input())
iii = lambda: [int(x) for x in input().split()]


def forEachCase(solveCase): 
    cases = ii()
    for i in range(cases):
        print(f"{solveCase()}")


def solve():
    x, y, n = iii()
    code = bin(y)
    p = 1
    for b in code:
        if b == '0' or b == '1':
            p = (p*p) % n
        if b == '1':
            p = (p * x) % n
    return p


forEachCase(solve)
