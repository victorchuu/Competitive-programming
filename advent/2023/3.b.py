import re


def is_gear(field, x, y):
    if x < 0 or y < 0 or y >= len(field) or x >= len(field[0]) :
        return False
    return field[y][x] == '*'


def find_all_numbers(field):
    number_finder = re.compile('\d+')
    numbers = list()
    for y, row in enumerate(field):
        all_numbers = number_finder.finditer(row)
        numbers.extend([ (finding.group(0), finding.start(), y) for finding in all_numbers])
    return numbers


def get_gears_touched(field, number):
    (value, x, y) = number
    gears_touched = []
    if is_gear(field, x-1, y):
        gears_touched.append((x-1, y))
    if is_gear(field, x + len(value), y):
        gears_touched.append((x + len(value), y))
    for i in range(x-1, x + len(value) + 1):
        if is_gear(field, i, y-1):
            gears_touched.append((i, y-1))
        if is_gear(field, i, y+1):
            gears_touched.append((i, y+1))
    return gears_touched



def read_field():
    with open('input.txt', 'r') as f:
        field = [line.rstrip() for line in f]
        return field

field = read_field()
numbers = find_all_numbers(field)
gears_touched = [get_gears_touched(field, num) for num in numbers]

mapa = {}
for i, gears in enumerate(gears_touched):
    for gear in gears:
        if gear not in mapa:
            mapa[gear] = []
        mapa[gear].append(numbers[i])

total = 0
for adjacent_numbers in mapa.values():
    if len(adjacent_numbers) == 2:
        [number1, number2] = adjacent_numbers
        (value1, _, __) = number1
        (value2, _, __) = number2
        total += int(value1) * int(value2)

print(f"Total: {total}")
