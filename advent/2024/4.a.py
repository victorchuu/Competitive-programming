import sys

def count_word(grid, word):
    rows = len(grid)
    cols = len(grid[0])
    word_len = len(word)
    directions = [
        (0, 1), (0, -1), (1, 0), (-1, 0),  # horizontal and vertical
        (1, 1), (1, -1), (-1, 1), (-1, -1)  # diagonals
    ]
    
    def is_valid(x, y):
        return 0 <= x < rows and 0 <= y < cols
    
    def search_from(x, y, dx, dy):
        for k in range(word_len):
            nx, ny = x + k * dx, y + k * dy
            if not is_valid(nx, ny) or grid[nx][ny] != word[k]:
                return False
        return True
    
    count = 0
    for i in range(rows):
        for j in range(cols):
            for dx, dy in directions:
                if search_from(i, j, dx, dy):
                    count += 1
    return count

def solveCase():
    global TOTAL
    grid = [list(line.strip()) for line in open('input.txt').readlines()]
    word = "XMAS"
    TOTAL = count_word(grid, word)
    print(f"Solution: {TOTAL}")

solveCase()