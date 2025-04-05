import time

def mutate(stone: int) -> list[int]:
    if stone == 0:
        return [1]
    string = str(stone)
    if len(string) % 2 == 0:
        center = len(string) // 2
        return [int(string[:center]), int(string[center:])]
    return [2024 * stone]

ITERATIONS = 75

initial_state = "2 54 992917 5270417 2514 28561 0 990"
state = dict()
for x in initial_state.split():
    if int(x) not in state:
        state[int(x)] = 0
    state[int(x)] += 1

for i in range(ITERATIONS):
    new_state = dict()
    for s, count in state.items():
        next_stones = mutate(s)
        for stone in next_stones:
            if stone not in new_state:
                new_state[stone] = 0
            new_state[stone] += count
    state = new_state

print(sum([x for x in state.values()]))
