WALL = '#'
EMPTY = '.'
START = 'S'
END = 'E'
    
def directions_within_distance(distance):
    directions = set()
    for i in range(-distance - 1, distance + 1):
        for j in range(-distance - 1, distance + 1):
            if abs(i) + abs(j) <= distance:
                directions.add((i, j))
    return directions
                
CHEAT_STEPS = 20
DIRECTIONS = [(0, 1), (1, 0), (0, -1), (-1, 0)]
CHEAT_DIRECTIONS = directions_within_distance(CHEAT_STEPS)

def parse_input():
    with open('input.txt') as f:
        grid = [list(line.strip()) for line in f]
        return grid, find_position_of(grid, START), find_position_of(grid, END)
    

def find_position_of(grid, char):
    for i, row in enumerate(grid):
        for j, cell in enumerate(row):
            if cell == char:
                grid[i][j] = EMPTY
                return (i, j)
            
def is_valid(grid, x, y):
    return 0 <= x < len(grid) and 0 <= y < len(grid[0])
    

def populate_non_cheating_path(grid, start, end):
    x, y = start
    steps = 0
    path = list()

    while (x, y) != end:
        grid[x][y] = steps
        path.append((x, y))
        steps += 1
        for dx, dy in DIRECTIONS:
            if is_valid(grid, x + dx, y + dy) and grid[x + dx][y + dy] == EMPTY:
                x += dx
                y += dy
                break # The problem statement guarantees that there only exists one valid move
    grid[x][y] = steps
    path.append((x, y))
    return path

def print_grid(grid, marked = set()):
    marked_grid = [['XX' if (x,y) in marked else grid[x][y] for y in range(len(grid[x]))] for x in range(len(grid))]
    for row in marked_grid:
        print(['##' if cell == '#' else str(cell) for cell in row])


grid, start, end = parse_input()
path = populate_non_cheating_path(grid, start, end)

cheats = dict()
for x, y in path:
    for dx, dy in CHEAT_DIRECTIONS:
        if is_valid(grid, x + dx, y + dy) and isinstance(grid[x + dx][y + dy], int):
            cheated_amount = grid[x + dx][y + dy] - grid[x][y] - dx - dy
            if cheated_amount > 0:
                if cheated_amount not in cheats:
                    cheats[cheated_amount] = set()
                cheats[cheated_amount].add(((x, y),(x + dx, y + dy)))

print_grid(grid, marked={cheat[0] for cheat in cheats[70]})
print(cheats[70])

total_great_cheats = 0
for cheated_amount, nodes in cheats.items():
    if cheated_amount >= 50:
        print(f"{len(nodes)} -> {cheated_amount}ps")
        total_great_cheats += len(nodes)

print(f"Solution: {total_great_cheats}")
