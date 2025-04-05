import sys
sys.stdin = open('input.txt')
# sys.stdout = open('output.txt')

# ---------------------------------------------

import functools as f
import math as m
import regex as re

ii = lambda : int(input())
intList = lambda: [int(x) for x in input().split()]
istr = lambda : str(input())

TOTAL = 0

def forEachCase(solveCase): 
    cases = ii()
    for i in range(cases):
        print(f"{solveCase()}")

def untilEOF(): 
    with open('input.txt') as f:
        ll = []
        for l in f:
            ll.append(l)

        lll = [decode(x) for x in ll]
        print(sum(lll))
        
mapa = {
    'zero': '0',
    'one': '1',
    'two': '2',
    'three': '3',
    'four': '4',
    'five': '5',
    'six': '6',
    'seven': '7',
    'eight': '8',
    'nine': '9',
    '0': '0',
    '1': '1',
    '2': '2',
    '3': '3',
    '4': '4',
    '5': '5',
    '6': '6',
    '7': '7',
    '8': '8',
    '9': '9',
}

regex = '|'.join(mapa.keys())
print(regex)

def decode(word):
    x = re.findall(regex, word, overlapped=True)
    sol = int(mapa[x[0]] + mapa[x[-1]])
    if (9 >= sol or 100 <= sol):
        print("ERROR" + word)
    return sol

untilEOF()

