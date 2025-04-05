
# Define constants
EMPTY = "."
WALL = "#"
GUARD = "^"
VISITED = "X"

UP = (-1, 0)
RIGHT = (0, 1)
DOWN = (1, 0)
LEFT = (0, -1)
DIRECTIONS = [UP, RIGHT, DOWN, LEFT]

with open('input.txt', 'r') as file:
    grid = [list(line.strip()) for line in file.readlines()]
    for x in range(len(grid)):
        for y in range(len(grid[x])):
            if grid[x][y] == GUARD:
                starting_i = x
                starting_j = y
                starting_direction = 0 # UP

def move(grid, i, j, direction):
    di, dj = DIRECTIONS[direction]
    if i + di < 0 or i + di >= len(grid) or j + dj < 0 or j + dj >= len(grid[i]):
        return i, j, direction, True
    if grid[i + di][j + dj] == WALL:
        return i, j, (direction + 1) % len(DIRECTIONS), False
    return i + di, j + dj, direction, False

def find_loop(grid, i, j, direction):
    slow_i, slow_j, slow_direction = i, j, direction
    fast_i, fast_j, fast_direction = i, j, direction

    while True:
        slow_i, slow_j, slow_direction, _ = move(grid, slow_i, slow_j, slow_direction)
        fast_i, fast_j, fast_direction, left_the_area = move(grid, fast_i, fast_j, fast_direction)
        fast_i, fast_j, fast_direction, left_the_area2 = move(grid, fast_i, fast_j, fast_direction)

        if (slow_i, slow_j, slow_direction) == (fast_i, fast_j, fast_direction):
            return True
        if left_the_area or left_the_area2:
            return False
        
TOTAL = 0
print(f"Grid of size {len(grid)}x{len(grid[0])}")
for i in range(len(grid)):
    for j in range(len(grid[i])):
        if grid[i][j] == EMPTY:
            grid[i][j] = WALL
            print(f"Trying {i} {j}")
            if find_loop(grid, starting_i, starting_j, starting_direction):
                TOTAL += 1
            grid[i][j] = EMPTY

print(f"Solution: {TOTAL}")

