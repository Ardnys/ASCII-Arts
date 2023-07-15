import numpy as np
import imageio.v3 as iio
import sys

np.set_printoptions(threshold=sys.maxsize)

"""
50x50 matrix to cartesian matrix
simple point class to represent a character in the matrix
"""

class Point:
    coords = ()
    def __init__(self, char: str, index: tuple) -> None:
        self.char = char
        self.index = index

    def __str__(self) -> str:
        return f'Point idx: {self.index}\ncoords: {self.coords}\nchar: {self.char}'
    
    def set_coords(self, coords):
        self.coords = coords
    
def create_point_matrix(img):
    nrows = len(img)
    ncols = len(img[0])

    ascii_matrix = np.empty((nrows, ncols), dtype=Point)

    for i in range(nrows):
        for j in range(ncols):
            avg_val = np.mean(img[i][j])

            if avg_val > 200:
                p = Point('#', (i,j))
                ascii_matrix[i,j] = p
            else:
                p = Point('.', (i,j))
                ascii_matrix[i,j] = p

    return ascii_matrix

def calculate_coords(mat):
    vmid = int(len(mat) / 2)
    hmid = int(len(mat[0]) / 2)

    print(f'vertical: {vmid}, horizontal: {hmid}')


def print_inconsole(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            print(matrix[i, j].char, end="")
        print()


img = iio.imread("images\\notnotathreat.png")
m = create_point_matrix(img)
print_inconsole(m)
calculate_coords(m)