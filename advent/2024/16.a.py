from collections import deque
from dataclasses import dataclass


WALL = '#'
EMPTY = '.'
START = 'S'
END = 'E'
DIRECTIONS = [(0, 1), (1, 0), (0, -1), (-1, 0)]

with open('input.txt') as f:
    grid = [list(line.strip()) for line in f]

def find_position_of(grid, char):
    for i, row in enumerate(grid):
        for j, cell in enumerate(row):
            if cell == char:
                return i, j

@dataclass
class Candidate:
    x: int
    y: int
    direction: int
    cost: int
    comes_from: 'Candidate' = None

    def __hash__(self):
        return hash((self.x, self.y, self.direction))

    def visit(self, visited):
        visited[self.x][self.y][self.direction] = self.cost

    def is_visited(self, visited, best_path_comes_from):
        if visited[self.x][self.y][self.direction] == self.cost:
            best_path_comes_from[self.x][self.y][self.direction].add(self.comes_from)
            return True
        if visited[self.x][self.y][self.direction] < self.cost:
            return True
    
        best_path_comes_from[self.x][self.y][self.direction] = {self.comes_from}
        return False
    
    def is_valid(self, grid):
        return 0 <= self.x < len(grid) and 0 <= self.y < len(grid[0]) and grid[self.x][self.y] != WALL
    
    def advance(self):
        dx, dy = DIRECTIONS[self.direction]
        return Candidate(self.x + dx, self.y + dy, self.direction, self.cost + 1, comes_from=self)
    
    def turn_left(self):
        return Candidate(self.x, self.y, (self.direction + 1) % 4, self.cost + 1000, comes_from=self)
    
    def turn_right(self):
        return Candidate(self.x, self.y, (self.direction - 1) % 4, self.cost + 1000, comes_from=self)


x, y = find_position_of(grid, START)
visited: list[list[list[int]]] = [[[float('inf')] * len(DIRECTIONS) for _ in range(len(grid[0]))] for _ in range(len(grid))]
best_path_comes_from = [[[set()] * len(DIRECTIONS) for _ in range(len(grid[0]))] for _ in range(len(grid))]
candidates = deque([Candidate(x, y, 0, 0)])

best_candidate = Candidate(x,y,0,float('inf'))
while candidates:
    candidate = candidates.popleft()
    if not candidate.is_valid(grid):
        continue
    if grid[candidate.x][candidate.y] == END:
        if candidate.cost < best_candidate.cost:
            best_candidate = candidate
    if candidate.is_visited(visited, best_path_comes_from):
        continue

    candidate.visit(visited)

    candidates.append(candidate.advance())
    candidates.append(candidate.turn_left())
    candidates.append(candidate.turn_right())


print(f"Part 1 solution: {best_candidate.cost}")


### Reconstruct all best paths
x, y = find_position_of(grid, END)
visited_vertices: set[tuple[int,int]] = set()
visited_candidates: set[Candidate] = set()
candidates = deque([best_candidate])

while candidates:
    candidate = candidates.popleft()
    if not candidate or candidate in visited_candidates:
        continue
    visited_candidates.add(candidate)

    visited_vertices.add((candidate.x, candidate.y))

    for next_candidate in best_path_comes_from[candidate.x][candidate.y][candidate.direction]:
        candidates.append(next_candidate)

print(visited_vertices)
print(len(visited_vertices))