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
R = 'R'
L = 'L'
INI = 'AAA'
END = 'ZZZ'

def forEachCase(solveCase): 
    cases = ii()
    for i in range(cases):
        print(f"{solveCase()}")

def untilEOF(solveCase): 

    graph = {}
    with open('input.txt') as f:
        directions = f.readline().replace('\n','')
        _ = f.readline()
        nodes = [x for x in f.readlines()]
        nodes = list(map(lambda line: line.replace('\n','').replace('(','').replace(')','').replace(',','=').replace(' ','').split('='), nodes))
        graph = {src: (left, right) for [src, left, right] in nodes}

        for node in graph.keys():
            if node[2] == 'A':
                solve(graph,directions, node)

    print(f"Solution: {TOTAL}")

def solve(graph, directions, ini):
    length = len(directions)
    n = 0
    visited = {}
    node = ini
    end_pos = []
    while (node, n % length) not in visited:
        relative_step = n % length
        direction = directions[n % length]
        visited[(node, relative_step)] = n
        if node[2] == 'Z':
            end_pos.append(n)
        if direction == L:
            node = graph[node][0]
        else:
            node = graph[node][1]
        n += 1

    first_in_loop = (node, n % length)

    print(f"Loop starts at {visited[first_in_loop]} and has period of {n - visited[first_in_loop]}, ending in {end_pos}")
    return (visited[first_in_loop], n - visited[first_in_loop], end_pos)
    

untilEOF(solve)

""" The inputs in this test were created on purpose to make it easy, my program output was:

Loop starts at 2 and has period of 16579, ending in [16579]
Loop starts at 4 and has period of 18827, ending in [18827]
Loop starts at 3 and has period of 19951, ending in [19951]
Loop starts at 2 and has period of 12083, ending in [12083]
Loop starts at 2 and has period of 22199, ending in [22199]
Loop starts at 2 and has period of 17141, ending in [17141]

- The first loop finds the end at 16579, and repeats every 16579. So it will find an end at every multiple of 16579
- Same with all of the loops

Therefore, the first time they all collide at an end, it will be in the least common multiple of them all, 16342438708751

"""