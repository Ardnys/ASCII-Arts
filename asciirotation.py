import numpy as np
import imageio.v3 as iio
import sys
import os
import time
from cv2 import resize, INTER_CUBIC
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

def play_anim(frames):
    fps = 24
    clear_console()
    prev = frames[0]
    frames.pop(0)
    for frame in frames:
        update_console(prev, frame)
        prev = frame
        time.sleep(1.0/fps)

    
        
def create_frames(img):
    default_matrix = create_point_matrix(img)
    # write to file for C hehe
    # write_to_txt(default_matrix)

    frame_num = 96
    rotations_x = np.linspace(0, np.pi*2, frame_num)
    rotations_y = np.linspace(np.pi/3, np.pi, frame_num)
    rotations_z = np.linspace(0, np.pi/2, frame_num)

    # frames = list()
    # frames.append(default_matrix)
    
    fps = 24
    clear_console()
    prev = default_matrix

    for (rx, ry, rz) in zip(rotations_x, rotations_y, rotations_z):
        mat = deepcopy(default_matrix)
        calculate_coords(mat)
        rotate(mat, rx, ry, rz)
        mat = calc_indexes(mat)

        update_console(prev, mat)
        prev = mat
        time.sleep(1.0/fps)
        # frames.append(mat)
        # print("processing...")
    # return frames
def update_console(prev, new):
    # it's kinda like double buffering
    for i in range(len(prev)):
        for j in range(len(prev)):
            if prev[i, j] is None:
                if new[i, j] is None:
                    continue
                else:
                    move(i, j)
                    print(new[i, j].char, end='')
            elif new[i, j] is None:
                move(i, j)
                print(' ', end='')
   
            elif prev[i, j].char == new[i, j].char:
                continue

            else:
                move(i, j)
                print(new[i, j].char, end='')

        move(i, len(prev))
        print()


def move_cursor_windows(x, y):
    _ = os.system(f'cmd /c echo \033[{y};{x}H')

def move (y, x):
    print("\033[%d;%dH" % (y, x), end='')    

def create_point_matrix(img):
    nrows = len(img)
    ncols = len(img[0])

    ascii_matrix = np.empty((nrows, ncols), dtype=Point)

    for i in range(nrows):
        for j in range(ncols):
            avg_val = np.mean(img[i][j])

            if avg_val > 200:
                p = Point('$', (i, j))
                ascii_matrix[i, j] = p
            else:
                p = Point('`', (i, j))
                ascii_matrix[i, j] = p

    return ascii_matrix


def calculate_coords(mat):
    vmid = int(len(mat) / 2)
    hmid = int(len(mat[0]) / 2)

    # print(f'vertical: {vmid}, horizontal: {hmid}')

    # when you subtract, the x and y are switched places
    for i in range(len(mat)):
        for j in range(len(mat[0])):
            x, y = i - vmid, j - hmid 
            mat[i, j].set_coords((y, x, 0))


def rotate(matrix, angle_x, angle_y, angle_z):
    cos_theta_x = round(cos(angle_x), 4)  
    sin_theta_x = round(sin(angle_x), 4)
    cos_theta_y = round(cos(angle_y), 4)  
    sin_theta_y = round(sin(angle_y), 4)   
    cos_theta_z = round(cos(angle_z), 4)  
    sin_theta_z = round(sin(angle_z), 4)

    Rx_matrix = np.array([[1,          0,          0],
                          [0,  cos_theta_x, -sin_theta_x],
                          [0,  sin_theta_x,  cos_theta_x]])
    Ry_matrix = np.array([[cos_theta_y,  0,  sin_theta_y],
                          [0,          1,          0],
                          [-sin_theta_y, 0, cos_theta_y]])
    Rz_matrix = np.array([[ cos_theta_z,-sin_theta_z,  0],
                          [ sin_theta_z, cos_theta_z,  0],
                          [ 0,          0,         1]])
    M = np.dot(Rx_matrix, Ry_matrix, Rz_matrix) 
    # M = Ry_matrix
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

def write_to_txt(matrix):
    with open("threat.txt", 'w') as f:
        for i in range(len(matrix)):
            for j in range(len(matrix[0])):
                c = matrix[i][j].char
                f.write(c)
            f.write('\n')

def print_inconsole(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            if matrix[i, j] is None:
                matrix[i, j] = Point(" ", (i, j))
                print(" ", end="")
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

project_dir = os.path.dirname(__file__)
images_dir = os.path.join(project_dir, "images")
image_name = "notathreat100.png"
image_path = os.path.join(images_dir, image_name)
img = iio.imread(image_path)
img = resize(img, dsize=(50,50), interpolation=INTER_CUBIC)
create_frames(img)
# play_anim(frames)


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

