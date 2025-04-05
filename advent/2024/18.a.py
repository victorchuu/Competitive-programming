SIZE = 71
DIRECTIONS = [(0, 1), (1, 0), (0, -1), (-1, 0)]

def parse_input():
    with open('input.txt') as f:
        pixels = [line.split(',') for line in f]
    grid = [[float('inf') for _ in range(SIZE)] for _ in range(SIZE)]
    for i, pixel in enumerate(pixels):
        y, x = int(pixel[0]), int(pixel[1])
        grid[x][y] = i
    return pixels, grid

parse_input()

def is_valid(grid, x, y):
    return 0 <= x < SIZE and 0 <= y < SIZE

def bfs(grid, src, dest, min_tile_duration):
    distance = [[float('inf') for _ in range(SIZE)] for _ in range(SIZE)]

    distance[src[0]][src[1]] = 0
    queue = [src]
    while queue:
        x, y = queue.pop(0)
        for dx, dy in DIRECTIONS:
            nx, ny = x + dx, y + dy
            if not is_valid(grid, nx, ny):
                continue
            if not grid[x][y] >= min_tile_duration:
                continue
            if distance[nx][ny] > distance[x][y] + 1:
                distance[nx][ny] = distance[x][y] + 1
                queue.append((nx, ny))
    
    return distance[dest[0]][dest[1]]

def firstFalseIndexBinarySerch(begin, end, condition):
    if begin >= end:
        return begin
    middle = (begin + end) // 2
    bool = condition(middle)
    if bool:
        return firstFalseIndexBinarySerch(middle + 1, end, condition)
    else:
        return firstFalseIndexBinarySerch(begin, middle, condition)
         

tiles, grid = parse_input()
best_distance_with = lambda tile_duration: bfs(grid, (0, 0), (SIZE - 1, SIZE - 1), tile_duration)
print(f"Part 1: {best_distance_with(1024)}")

first_cutting_tile = firstFalseIndexBinarySerch(0, SIZE * SIZE, lambda tile_duration: best_distance_with(tile_duration) != float('inf'))
print(f"Part 2: {tiles[first_cutting_tile-1]}, at time {first_cutting_tile}")

