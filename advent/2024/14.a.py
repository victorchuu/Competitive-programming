import re
from dataclasses import dataclass
import matplotlib.pyplot as plt

@dataclass
class Point:
    x: int
    y: int

    def __hash__(self):
        return hash((self.x, self.y))

positions: list[Point] = []
velocities: list[Point] = []
with open("input.txt", 'r') as file:
    for line in file:
        # Use regular expressions to extract the position and velocity coordinates
        match = re.match(r'p=(-?\d+),(-?\d+) v=(-?\d+),(-?\d+)', line.strip())
        if match:
            px, py, vx, vy = map(int, match.groups())
            position = Point(px, py)
            velocity = Point(vx, vy)
            positions.append(position)
            velocities.append(velocity)

WIDTH = 101
HEIGHT = 103

def move_points(positions, velocities, steps):
    variances_x = []
    variances_y = []
    for iter in range(steps):
        for i in range(len(positions)):
            positions[i].x = (positions[i].x + velocities[i].x) % WIDTH
            positions[i].y = (positions[i].y + velocities[i].y) % HEIGHT
        
        x_coords = [point.x for point in positions]
        mean_x = sum(x_coords) / len(x_coords)
        variance_x = sum((x - mean_x) ** 2 for x in x_coords) / len(x_coords)

        y_coords = [point.y for point in positions]
        mean_y = sum(y_coords) / len(y_coords)
        variance_y = sum((y - mean_y) ** 2 for y in y_coords) / len(y_coords)

        variances_x.append(variance_x)
        variances_y.append(variance_y)

        if variance_x < 700 and variance_y < 700:
            print_points(positions)
            print(f"Potential Solution: {iter}")

        """
        if iter % 1000 == 0:
            plt.figure(figsize=(10, 5))
            plt.subplot(1, 2, 1)
            plt.plot(variances_x, label='Variance X')
            plt.xlabel('Steps')
            plt.ylabel('Variance')
            plt.legend()

            plt.subplot(1, 2, 2)
            plt.plot(variances_y, label='Variance Y')
            plt.xlabel('Steps')
            plt.ylabel('Variance')
            plt.legend()

            plt.tight_layout()
            plt.show()
        """



def print_points(positions):
    positions_set = set(positions)
    for y in range(HEIGHT):
        for x in range(WIDTH):
            if Point(x, y) in positions_set:
                print('#', end='')
            else:
                print('.', end='')
        print()

move_points(positions, velocities, 25000)

"""
vertical_line = WIDTH // 2
horizontal_line = HEIGHT // 2
cuadrants = [0,0,0,0]
for point in positions:
    if point.x < vertical_line and point.y < horizontal_line:
        cuadrants[0] += 1
    elif point.x > vertical_line and point.y < horizontal_line:
        cuadrants[1] += 1
    elif point.x < vertical_line and point.y > horizontal_line:
        cuadrants[2] += 1
    elif point.x > vertical_line and point.y > horizontal_line:
        cuadrants[3] += 1

print(f"Solution: {cuadrants[0] * cuadrants[1] * cuadrants[2] * cuadrants[3]}")

"""