import sys
sys.stdin = open('input.txt')
# sys.stdout = open('output.txt')

# ---------------------------------------------

import functools as f
import math as m
import re

ii = lambda : int(input())
intList = lambda line: [int(x) for x in line.split()]
istr = lambda : str(input())

TOTAL = 1


# record = x(n-x) = nx - x^2 
# xx - nx + record = 0

def solve_equation(n, record):
    a, b ,c = 1, -n, record
    # print(f"{a}*x^2 + {b}*x + {c} = 0")
    discriminant = m.sqrt(b*b - 4*a*c);
    return ( (-b - discriminant) / (2*a), (-b + discriminant) / (2*a) )


def untilEOF(solveCase): 
    with open('input.txt') as f:
        l1, l2 = f.readline().split(':')[1], f.readline().split(':')[1]
        times = intList(l1)
        distances = intList(l2)

        global TOTAL

        for time, distance in zip(times, distances):
            (x1, y1) = solve_equation(time, distance)
            print(f"{x1} is integer: {x1.is_integer()} + {y1} is integer: {y1.is_integer()}")
            collides_with_extremes = x1.is_integer() + y1.is_integer()
            print(collides_with_extremes)
            (x, y) = m.ceil(x1), m.floor(y1)
            print(f"From {x} to {y} there are {y - x + 1 - collides_with_extremes} possibilities")
            TOTAL *= (y - x + 1 - collides_with_extremes)            

    print(f"Solution: {TOTAL}")

def solve():
    pass

untilEOF(solve)
