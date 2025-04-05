from functools import lru_cache
import re

def read_input():
    with open('input.txt', 'r') as file:
        content = file.read()

    # Split the content into two parts based on the blank line
    part1, part2 = content.strip().split('\n\n')

    # Parse each part into a list of strings
    towels = part1.replace(" ", "").split(',')
    goals = part2.split('\n')

    return towels, goals



towels, goals = read_input()
pattern = "(" + '|'.join(towels) + ")*"

@lru_cache
def combinations(goal: str, i: int):
    if i >= len(goal):
        return 1
    total_combinations = 0
    for towel in towels:
        if goal[i:i+len(towel)] == towel:
            total_combinations += combinations(goal, i+len(towel))
    return total_combinations

possible_towels = 0
total_combinations = 0
for goal in goals:
    combs = combinations(goal, 0)
    possible_towels += combs > 0
    total_combinations += combs
print(f"Part 1: {possible_towels}")
print(f"Part 2: {total_combinations}")