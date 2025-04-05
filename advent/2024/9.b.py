
from dataclasses import dataclass


with open('input.txt', 'r') as file:
    line = file.readline()

def flatmap(l: list[list]):
    return [ele for sublist in l for ele in sublist]


"""
Instead of representing the whole content of the memory, like 
    11111777888888
We will represent it as a list of Fileblock objects, which will contain the value of the file and the number of repetitions
    (value=1,size=5) -> 11111
    (value=7,size=3) -> 777
    (value=8,size=6) -> 888888
"""
@dataclass
class Fileblock: 
    value: int
    size: int

files: list[Fileblock] = [Fileblock(size=int(x), value=value) for value,x in enumerate(line[::2])]
blanks = [int(x) for x in line[1::2]]
if len(blanks) < len(files):
    blanks.append(0)

movedFiles: list[list[Fileblock]] = [[] for _ in range(len(blanks))]
i = len(files) - 1
for i in range(len(files) - 1, -1, -1):
    file = files[i]

    j = 0
    while j < i and blanks[j] < file.size:
        j += 1

    if j >= i:
        continue

    blanks[j] -= file.size
    blanks[i] += file.size
    movedFiles[j].append(file)
    files[i] = Fileblock(value=0, size=0)

all_files: list[Fileblock] = []
for i in range(len(files)):
    print(f"Original files: {files[i]}")
    all_files.append(files[i])
    if i < len(movedFiles):
        print(f"Moved files: {movedFiles[i]}")
        all_files.extend(movedFiles[i])
    if i < len(blanks) and blanks[i] > 0:
        print(f"blanks: {blanks[i]}")
        all_files.extend([Fileblock(value=None, size=blanks[i])])
    
"""
Even though we could leverage the compacted representation of the files, 
we will expand it to the original representation since it passes the test cases in a timely manner
Compacted representation would be more efficient for large inputs
"""

all_files_raw = flatmap([[x.value] * x.size for x in all_files])

print(all_files)
print(''.join(['.' if x == None else str(x) for x in all_files_raw]))
print(f"Sol: {sum([i * x for i,x in enumerate(all_files_raw)])}")

0099211177744..333....5555.6666.....8888..
00992111777.44.333....5555.6666.....8888..
