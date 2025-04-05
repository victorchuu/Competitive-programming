
from dataclasses import dataclass


EMPTY = '.'

@dataclass(frozen=True)
class Coord:
    x: int
    y: int

    def __add__(self, other):
        return Coord(self.x + other.x, self.y + other.y)
    
    def __sub__(self, other):
        return Coord(self.x - other.x, self.y - other.y)


antennas: dict[str, list[Coord]] = dict()
antinodes: set[Coord] = set()

with open('input.txt', 'r') as file:
    grid = [list(line.strip()) for line in file.readlines()]
    for x in range(len(grid)):
        for y in range(len(grid[x])):
            char = grid[x][y]
            if char != EMPTY:
                antennas[char] = antennas.get(char, []) + [Coord(x, y)]
            
N, M = len(grid), len(grid[0])

def valid_range(a: Coord):
    return 0 <= a.x < N and 0 <= a.y < M

def find_antinodes(a: Coord, b: Coord):
    vector = b - a
    sol = []
    c = b + vector
    d = a - vector
    if valid_range(c):
        sol.append(c)
    if valid_range(d):
        sol.append(d)
    return sol


for antenna in antennas:
    for i in range(len(antennas[antenna])):
        for j in range(i + 1, len(antennas[antenna])):
            antinodes.update(find_antinodes(antennas[antenna][i], antennas[antenna][j]))


print(f"Solution: {len(antinodes)}")