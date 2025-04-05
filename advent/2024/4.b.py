def count_x_mas(grid):
    rows = len(grid)
    cols = len(grid[0])
    
    def is_valid(x, y):
        return 0 <= x < rows and 0 <= y < cols
    
    def search_from(x, y):
        # Check for the "X-MAS" pattern in all 4 possible orientations
        patterns = [
            [(0, 0, 'A'), (-1, -1, 'M'), (-1, 1, 'M'), (1, -1, 'S'), (1, 1, 'S'), ],
            [(0, 0, 'A'), (-1, -1, 'M'), (-1, 1, 'S'), (1, -1, 'M'), (1, 1, 'S'), ],
            [(0, 0, 'A'), (-1, -1, 'S'), (-1, 1, 'M'), (1, -1, 'S'), (1, 1, 'M'), ],
            [(0, 0, 'A'), (-1, -1, 'S'), (-1, 1, 'S'), (1, -1, 'M'), (1, 1, 'M'), ],
        ]
        
        for pattern in patterns:
            if all(is_valid(x + dx, y + dy) and grid[x + dx][y + dy] == char for dx, dy, char in pattern):
                return True
        return False
    
    count = 0
    for i in range(rows):
        for j in range(cols):
            if search_from(i, j):
                count += 1
    return count

def solveCase():
    grid = [list(line.strip()) for line in open('input.txt').readlines()]
    total = count_x_mas(grid)
    print(f"Solution: {total}")

solveCase()