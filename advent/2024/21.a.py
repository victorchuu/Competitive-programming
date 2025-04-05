UP, DOWN, LEFT, RIGHT = '^', 'v', '<', '>'
PRESS = 'A'
DIRECTIONS = {
    UP: (-1, 0),
    DOWN: (1, 0),
    LEFT: (0, -1),
    RIGHT: (0, 1),
}

def best_paths(dx: int, dy: int):
    path = ""

    move_x_axis = lambda dx: DOWN * dx if dx > 0 else UP * -dx
    move_y_axis = lambda dy: RIGHT * dy if dy > 0 else LEFT * -dy

    return move_x_axis(dx) + move_y_axis(dy) + PRESS, move_y_axis(dy) + move_x_axis(dx) + PRESS

def keep_only_best_combinations(combinations: set[str]):
    best_length = min(len(combination) for combination in combinations)
    return {combination for combination in combinations if len(combination) == best_length}


class Keyboard:
    keys: dict[str, tuple[int, int]]
    keyboard: list[list[str]]


    def __init__(self, keyboard: list[list[str]]):
        self.keyboard = keyboard
        self.keys = dict()
        for i, row in enumerate(keyboard):
            for j, key in enumerate(row):
                if key:
                    self.keys[key] = (i, j)


    def reproduce_sequence(self, instructions: str):
        position = self.keys[PRESS]
        sequence = ""
        for char in instructions:
            if char == PRESS:
                sequence += self.keyboard[position[0]][position[1]]
            if char in DIRECTIONS:
                dx, dy = DIRECTIONS[char]
                position = (position[0] + dx, position[1] + dy)
        return sequence


    def get_best_combinations(self, goal: str):
        position = self.keys[PRESS]
        combinations = {""}
        for char in goal:
            goal_position = self.keys[char]
            dx, dy = goal_position[0] - position[0], goal_position[1] - position[1]
            position = goal_position

            new_combinations = set()
            for combination in combinations:
                path1, path2 = best_paths(dx, dy)
                new_combinations.add(combination + path1)
                new_combinations.add(combination + path2)

            combinations = new_combinations
        
        return keep_only_best_combinations(combinations)



NUMERIC_KEYBOARD = Keyboard([
    ['7' ,'8', '9'],
    ['4', '5', '6'],
    ['1', '2', '3'],
    [None, '0', PRESS],
])

DIRECTIONAL_KEYBOARD = Keyboard([
    [None, UP, PRESS],
    [LEFT, DOWN, RIGHT],
])

def shortest_sequence(goal: str):
    combs1 = NUMERIC_KEYBOARD.get_best_combinations(goal)

    combs2 = set()
    for comb in combs1:
        combs2.update(DIRECTIONAL_KEYBOARD.get_best_combinations(comb))
    combs2 = keep_only_best_combinations(combs2)

    combs3 = set()
    for comb in combs2:
        combs3.update(DIRECTIONAL_KEYBOARD.get_best_combinations(comb))
    combs3 = keep_only_best_combinations(combs3)
        
    return combs3.pop()


def reproduce_sequence(instructions: str):
    inst2 = DIRECTIONAL_KEYBOARD.reproduce_sequence(instructions)
    inst1 = DIRECTIONAL_KEYBOARD.reproduce_sequence(inst2)
    return NUMERIC_KEYBOARD.reproduce_sequence(inst1)

goals = ['029A', '980A', '179A', '456A', '379A']


print(reproduce_sequence('<vA<AA>>^AvAA<^A>A<v<A>>^AvA^A<vA>^A<v<A>^A>AAvA^A<v<A>A>^AAAvA<^A>A'))



total_score = 0
for goal in goals:
    best_sequence = shortest_sequence(goal)
    print(f"{goal}: {best_sequence}")
    print(f"{len(best_sequence)} * {int(goal[:-1])}")
    total_score += len(best_sequence) * int(goal[:-1])

print(f"Solution: {total_score}")

