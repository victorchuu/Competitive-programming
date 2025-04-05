from dataclasses import dataclass


DIRECTIONS = [(0, 1), (1, 0), (0, -1), (-1, 0)]

def is_valid(grid, x, y):
    return 0 <= x < len(grid) and 0 <= y < len(grid[x])

with open('input.txt', 'r') as file:
    grid = [list(line.strip()) for line in file.readlines()]

perimeter = dict()
area = dict()

def find_corners(grid, x, y):
    char = grid[x][y]
    evaluate = lambda a,b: grid[a][b] if is_valid(grid, a, b) else None

    corners = 0
    for dx, dy in DIRECTIONS:
        adj_dx, adj_dy = -dy, dx
        diagonal_dx, diagonal_dy = dx + adj_dx, dy + adj_dy

        adj1 = evaluate(x + dx, y + dy)
        adj2 = evaluate(x + adj_dx, y + adj_dy)
        diagonal = evaluate(x + diagonal_dx, y + diagonal_dy)

        if adj1 == char and adj2 == char and diagonal != char:
            corners += 1
        if adj1 != char and adj2 != char:
            corners += 1

    return corners

def measure_zone(grid, x, y, visited):
    if not is_valid(grid, x, y) or visited[x][y]:
        return 0, 0

    visited[x][y] = True

    char = grid[x][y]
    corners = find_corners(grid, x, y)
    area = 1

    for dx, dy in DIRECTIONS:        
        if is_valid(grid, x + dx, y + dy) and grid[x + dx][y + dy] == char:
            c, a = measure_zone(grid, x + dx, y + dy, visited)
            corners += c
            area += a

    return corners, area

visited = [[False for _ in row] for row in grid]
total = 0
for x in range(len(grid)):
    for y in range(len(grid[x])):
        corners, area = measure_zone(grid, x, y, visited)
        if area > 0:
            print(f"Zone {grid[x][y]} at {x}, {y} has fences {corners} and area {area}")
        total += corners * area

print(f"Solution: {total}")