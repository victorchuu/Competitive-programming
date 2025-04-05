ORIGIN = 0
END = 9
DIRECTIONS = [(1, 0), (0, 1), (-1, 0), (0, -1)]

with open('input.txt', 'r') as file:
    grid = [[int(x) for x in line if x != '\n'] for line in file.readlines()]


origins = []
for x in range(len(grid)):
    for y in range(len(grid[x])):
        if ORIGIN == grid[x][y]:
            origins.append((x, y))


def is_valid(x, y):
    return x >= 0 and x < len(grid) and y >= 0 and y < len(grid[x])

def find_trails(x, y, visited):
    if (x, y) in visited:
        return visited[(x,y)]
    
    if grid[x][y] == END:
        visited[(x, y)] = 1
        return 1

    count = 0
    for dir in DIRECTIONS:
        next_x, next_y = x + dir[0], y + dir[1]
        if is_valid(next_x, next_y) and grid[next_x][next_y] == grid[x][y] + 1:
            count += find_trails(x + dir[0], y + dir[1], visited)
    visited[(x, y)] = count
    return count
        
sum = 0
for origin in origins:
    sum += find_trails(origin[0], origin[1], dict())
    
print(f"Solution: {sum}")