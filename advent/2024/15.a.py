WALL = '#'
BOX = 'O'
ROBOT = '@'
EMPTY = '.'

DIRECTIONS = {
    '^': (-1, 0),
    'v': (1, 0),
    '<': (0, -1),
    '>': (0, 1),
}

grid = []
directions = []
with open('input.txt', 'r') as file:

    for line in file.readlines():
        if line[0] == WALL:
            grid.append(list(line.strip()))
        elif line[0] in DIRECTIONS:
            directions.extend([DIRECTIONS[x] for x in line.strip()])
            
print(grid)
print(directions)

for i in range(len(grid)):
    for j in range(len(grid[i])):
        if grid[i][j] == ROBOT:
            x, y = i, j
            break

def move_pushing_boxes(grid, x, y, direction, depth=0):
    dx, dy = direction
    if grid[x + dx][y + dy] == WALL:
        return False
    if grid[x + dx][y + dy] == BOX:
        if not move_pushing_boxes(grid, x + dx, y + dy, direction, depth=depth + 1):
            return False
    grid[x + dx][y + dy] = ROBOT if depth == 0 else BOX
    grid[x][y] = EMPTY
    return True

def print_grid(grid):
    for row in grid:
        print(''.join(row))

for dir in directions:
    if move_pushing_boxes(grid, x, y, dir):
        x += dir[0]
        y += dir[1]
    
total = sum(100*x + y for x in range(len(grid)) for y in range(len(grid[x])) if grid[x][y] == BOX)
print(f"Total: {total}")
