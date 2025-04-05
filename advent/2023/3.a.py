import re


def is_symbol(field, x, y):
    if x < 0 or y < 0 or y >= len(field) or x >= len(field[0]) :
        return False
    if re.search('\.|\d', field[y][x]):
        return False
    return True


def find_all_numbers(field):
    number_finder = re.compile('\d+')
    numbers = list()
    for y, row in enumerate(field):
        all_numbers = number_finder.finditer(row)
        numbers.extend([ (finding.group(0), finding.start(), y) for finding in all_numbers])
    return numbers


def number_touches_symbol(field, number):
    (value, x, y) = number
    touches_symbol = is_symbol(field, x-1, y) or is_symbol(field, x + len(value), y)
    for i in range(x-1, x + len(value) + 1):
        touches_symbol = touches_symbol or is_symbol(field, i, y-1)
        touches_symbol = touches_symbol or is_symbol(field, i, y+1)
    return touches_symbol



def read_field():
    with open('input.txt', 'r') as f:
        field = [line.rstrip() for line in f]
        return field

field = read_field()
not_numbers = [int(num[0]) for num in find_all_numbers(field) if not number_touches_symbol(field, num)]
numbers = [int(num[0]) for num in find_all_numbers(field) if number_touches_symbol(field, num)]
total = sum(numbers)
print(f"Not Numbers: {not_numbers}")
print(f"Numbers: {numbers}")
print(f"Total: {total}")
