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
    rotated_coords = None

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

    # when you subtract, the x and y are switched places
    for i in range(len(m)):
        for j in range(len(m[0])):
            x, y = i - 25, j - 25
            m[i, j].set_coords((y, x, 0))


def rotate(matrix):
    cos_theta = round(cos(np.pi/4), 4)  # 45 degrees
    sin_theta = round(sin(np.pi/4), 4)
    Rx_matrix = np.array([[1,         0,          0],
                          [0, cos_theta, -sin_theta],
                          [0, sin_theta,  cos_theta]])
    Ry_matrix = np.array([[cos_theta, 0,  sin_theta],
                          [0,         1,          0],
                          [-sin_theta, 0, cos_theta]])
    Rz_matrix = np.array([[cos_theta,-sin_theta,  0],
                          [sin_theta, cos_theta,  0],
                          [0,          0,         1]])
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            for x in range(len(Rz_matrix)):
                points = np.asarray(list(matrix[i, j].coords))

                rotated_coords = np.dot(Rz_matrix, points)
                rotated_coords = np.around(rotated_coords)
                rotated_coords = rotated_coords.astype(int)
                # print(f'prev indexes: {points}')
                # c = dot_product(points, Rx_matrix[x])
                # print(f'new coord: {c}')
                matrix[i, j].set_rotated_coords(rotated_coords)


def dot_product(vec_1: tuple, vec_2: list) -> tuple:
    if len(vec_1) != len(vec_2):
        raise Exception("can't dot product different size vectors")
        # i don't even know if it's true but it feels like it
    vec = list()
    for i, j in zip(vec_1, vec_2):
        vec.append(int(i * j))

    return tuple(vec)


def print_inconsole(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            print(matrix[i, j].char, end="")
        print()


def calc_indexes(matrix):
    nrows = len(matrix)
    ncols = len(matrix[0])

    ascii_matrix = np.empty((nrows, ncols), dtype=Point)

    for i in range(nrows):
        for j in range(ncols):
            p = matrix[i, j]
            rx = p.rotated_coords[0]
            ry = p.rotated_coords[1]
            x, y = rx + 25, ry + 25
            if x >= 0 and x < nrows and y >= 0 and y < ncols:
                ascii_matrix[y, x] = Point(p.char, (y, x))
            else:
                print("point out of bounds")
            # print(p.char, end="")
        # print()

    for i in range(nrows):
        for j in range(ncols):
            if ascii_matrix[i, j] is None:
                ascii_matrix[i, j] = Point("  ", (i, j))
                print("  ", end="")
            else:
                print(ascii_matrix[i, j].char, end="")
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

calc_indexes(m)
