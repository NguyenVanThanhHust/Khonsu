import os
import math
import random

def generate_points(center_x, center_y, mean_radius, sigma_radius, num_points):
    points = []
    for i in range(num_points):
        theta = random.uniform(0, 2*math.pi)
        radius = random.gauss(mean_radius, sigma_radius)
        x = center_x + radius * math.cos(theta)
        y = center_y + radius * math.sin(theta)
        points.append([x,y])
    return points


if __name__ == "__main__":
    y1, y2 = 1, -1
    c1 = (1, 1)
    c2 = (-1, -1)
    first_cluster = generate_points(c1[0], c1[1], 1.0, 0.5, 20)
    second_cluster = generate_points(c2[0], c2[1], 1.0, 0.5, 20)
    print(first_cluster)
    print(second_cluster)
    with open('data.txt', 'w') as handle:
        for point in first_cluster:
            handle.write(str(point[0]))
            handle.write(" ")
            handle.write(str(point[1]))
            handle.write("\n")

        for point in second_cluster:
            handle.write(str(point[0]))
            handle.write(" ")
            handle.write(str(point[1]))
            handle.write("\n")
        
