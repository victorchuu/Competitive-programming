
from dataclasses import dataclass


with open('input.txt', 'r') as file:
    line = file.readline()

def flatmap(l: list[list]):
    return [ele for sublist in l for ele in sublist]

file_sizes: list[int] = [int(x) for x in line[::2]]
blanks = [int(x) for x in line[1::2]]

alternative_list: list[int] = []
for i in range(len(file_sizes)):
    alternative_list.extend([i] * file_sizes[i])
    if i < len(blanks):
        alternative_list.extend([None] * blanks[i])

i = 0
while i < len(alternative_list):
    if alternative_list[i] is None:
        while(alternative_list[-1] is None):
            alternative_list.pop()
        if i >= len(alternative_list):
            break
        alternative_list[i] = alternative_list[-1]
        alternative_list.pop()
    i += 1

print(f"Sol: {sum([i * x for i,x in enumerate(alternative_list)])}")
