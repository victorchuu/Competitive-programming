DIRECTIONS = [(0, 1), (1, 0), (0, -1), (-1, 0)]

def is_valid(grid, x, y):
    return 0 <= x < len(grid) and 0 <= y < len(grid[x])

with open('input.txt', 'r') as file:
    grid = [list(line.strip()) for line in file.readlines()]

perimeter = dict()
area = dict()

def measure_zone(grid, visited, x, y, char):
    # If we find a border with another region, we put a fence, therefore perimeter is 1
    if not is_valid(grid, x, y) or char != grid[x][y]: 
        return 1, 0
    if visited[x][y]:
        return 0, 0

    visited[x][y] = True

    perimeter = 0
    area = 1

    for dx, dy in DIRECTIONS:
        p, a = measure_zone(grid, visited, x + dx, y + dy, char)
        perimeter += p
        area += a

    return perimeter, area

visited = [[False for _ in row] for row in grid]
total = 0
for x in range(len(grid)):
    for y in range(len(grid[x])):
        perimeter, area = measure_zone(grid, visited, x, y, grid[x][y])
        total += perimeter * area

print(f"Solution: {total}")