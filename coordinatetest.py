import numpy as np
import imageio.v3 as iio
import sys
import os
import time
from math import cos, sin
from copy import deepcopy
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

def create_frames(img):
    default_matrix = create_point_matrix(img)
    rotations = np.linspace(0, np.pi*2, 15)
    # frames = list()

    for rotation in rotations:
        mat = deepcopy(default_matrix)
        calculate_coords(mat)
        rotate(mat, rotation)
        mat = calc_indexes(mat)
        print_inconsole(mat)
        time.sleep(1)
        clear_console()



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
    for i in range(len(mat)):
        for j in range(len(mat[0])):
            x, y = i - vmid, j - hmid 
            mat[i, j].set_coords((y, x, 0))


def rotate(matrix, angle):
    cos_theta = round(cos(angle), 4)  # 45 degrees
    sin_theta = round(sin(angle), 4)
    Rx_matrix = np.array([[1,          0,          0],
                          [0,  cos_theta, -sin_theta],
                          [0,  sin_theta,  cos_theta]])
    Ry_matrix = np.array([[cos_theta,  0,  sin_theta],
                          [0,          1,          0],
                          [-sin_theta, 0, cos_theta]])
    Rz_matrix = np.array([[ cos_theta,-sin_theta,  0],
                          [ sin_theta, cos_theta,  0],
                          [ 0,          0,         1]])
    M = Ry_matrix
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            for x in range(len(M)):
                points = np.asarray(list(matrix[i, j].coords))

                rotated_coords = np.dot(M, points)
                rotated_coords = np.around(rotated_coords)
                rotated_coords = rotated_coords.astype(int)
                matrix[i, j].set_rotated_coords(rotated_coords)

def calc_indexes(matrix):
    nrows = len(matrix)
    ncols = len(matrix[0])
    vmid = int(nrows/2)
    hmid = int(ncols/2)
    ascii_matrix = np.empty((nrows, ncols), dtype=Point)

    for i in range(nrows):
        for j in range(ncols):
            p = matrix[i, j]
            rx = p.rotated_coords[0]
            ry = p.rotated_coords[1]
            x, y = rx + vmid, ry + hmid 
            if x >= 0 and x < nrows and y >= 0 and y < ncols:
                ascii_matrix[y, x] = Point(p.char, (y, x))

    return ascii_matrix
            
            # print(p.char, end="")
        # print()

    # for i in range(nrows):
    #     for j in range(ncols):
    #         if ascii_matrix[i, j] is None:
    #             ascii_matrix[i, j] = Point("  ", (i, j))
    #             print("  ", end="")
    #         else:
    #             print(ascii_matrix[i, j].char, end="")
    #     print()

def print_inconsole(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            if matrix[i, j] is None:
                matrix[i, j] = Point("  ", (i, j))
                print("  ", end="")
            else:
                print(matrix[i, j].char, end="")
        print()

def clear_console():
    # Windows
    if os.name == 'nt':
        _ = os.system('cls')
    # Linux and macOS
    else:
        _ = os.system('clear')


img = iio.imread("images\\notathreat50.png")
create_frames(img)


# m = create_point_matrix(img)
# # print_inconsole(m)
# calculate_coords(m)
# # m[25, 25].char = '$ '  # this is the origin if you will
# # print_inconsole(m)
# rotate(m, np.pi/4)

# m = calc_indexes(m)
# print_inconsole(m)



# for i in range(5):
#     for j in range(5):
#         p = m[i, j]
#         print(f'coords: {p.coords} -> rotated coords: {p.rotated_coords}')

