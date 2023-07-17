import numpy as np
import imageio.v3 as iio
import sys
from math import cos, sin
np.set_printoptions(threshold=sys.maxsize)

"""
50x50 matrix to cartesian matrix
simple point class to represent a character in the matrix
"""


class Point:
    coords = ()
    rotated_coords = ()

    def __init__(self, char: str, index: tuple) -> None:
        self.char = char
        self.index = index

    def __str__(self) -> str:
        return f'Point idx: {self.index}\ncoords: {self.coords}\nchar: {self.char}'

    def set_coords(self, coords):
        self.coords = coords

    def set_rotated_coords(self, r_coords):
        self.rotated_coords = r_coords


def create_point_matrix(img):
    nrows = len(img)
    ncols = len(img[0])

    ascii_matrix = np.empty((nrows, ncols), dtype=Point)

    for i in range(nrows):
        for j in range(ncols):
            avg_val = np.mean(img[i][j])

            if avg_val > 200:
                p = Point('# ', (i, j))
                ascii_matrix[i, j] = p
            else:
                p = Point('. ', (i, j))
                ascii_matrix[i, j] = p

    return ascii_matrix


def calculate_coords(mat):
    vmid = int(len(mat) / 2)
    hmid = int(len(mat[0]) / 2)

    print(f'vertical: {vmid}, horizontal: {hmid}')

    for i in range(len(m)):
        for j in range(len(m[0])):
            x, y = i - 25, j - 25
            m[i, j].set_coords((x, y))


def rotate(matrix):
    cos_theta = round(cos(np.pi/4), 4)  # 45 degrees
    sin_theta = round(sin(np.pi/4), 4)
    Rx_matrix = [[1,      0,          0],
                 [0, cos_theta, -1*sin_theta],
                 [0, sin_theta, cos_theta]]

    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            for x in range(len(Rx_matrix)):
                points = matrix[i, j].coords
                # print(f'prev indexes: {points}')
                c = dot_product(points, Rx_matrix[x])
                # print(f'new coord: {c}')
                matrix[i, j].set_rotated_coords(c)


def dot_product(vec_1: tuple, vec_2: tuple) -> tuple:
    if len(vec_1) != len(vec_2):
        raise Exception("can't dot product different size vectors")
        # i don't even know if it's true but it feels like it
    vec = list()
    for i, j in zip(vec_1, vec_2):
        vec.append(i * j)

    return tuple(vec)


def print_inconsole(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            print(matrix[i, j].char, end="")
        print()


img = iio.imread("images\\notnotathreat.png")
m = create_point_matrix(img)
# print_inconsole(m)
calculate_coords(m)
m[25, 25].char = '$ '  # this is the origin if you will
print_inconsole(m)
rotate(m)

for i in range(5):
    for j in range(5):
        p = m[i, j]
        print(f'coords: {p.coords} -> rotated coords: {p.rotated_coords}')
