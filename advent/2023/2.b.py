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

def getmapa() :
    return {
        'blue': 0, 'red': 0, 'green': 0,
    }


def solve(word):
    [game, subsets] = word.split(':')
    id = int(game.split(' ')[1])
    print(id)
    mapa = getmapa()
    for subset in subsets.split(';'):
        for pair in subset.split(','):
            [_, num, color] = pair.split(' ')
            if color[-1] == '\n':
                color = color[0:-1]
            mapa[color] = max(mapa[color],int(num))

    global TOTAL
    power = mapa['red'] * mapa['green'] * mapa['blue']
    TOTAL += power

untilEOF(solve)
