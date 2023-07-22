import cv2
import numpy as np
import os

def get_frames():
    vidcap = cv2.VideoCapture('bad apple.mp4')
    success,image = vidcap.read()
    count = 0
    prev = None
    while success:
        res = cv2.resize(image, dsize=(100,100), interpolation=cv2.INTER_CUBIC)
        asc = make_ascii_matrix(res)
        if count == 0:
            clear_console()
            print_inconsole(asc) 
            prev = asc
        else:
            update_console(prev, asc)
            prev = asc
        # cv2.imwrite("bad-apple-frames\\frame%d.jpg" % count, res)     # save frame as JPEG file      
        success,image = vidcap.read()
        # print('Read a new frame: ', success)
        count += 1


def make_ascii_matrix(frame):
    nrows = len(frame)
    ncols = len(frame[0])

    ascii_matrix = np.empty((nrows, ncols), dtype=str)

    for i in range(nrows):
        for j in range(ncols):
            avg_val = np.mean(frame[i][j])

            if avg_val > 200:
                ascii_matrix[i, j] = "#"
            else:
                ascii_matrix[i, j] = "."

    return ascii_matrix


def update_console(prev, new):
    # it's kinda like double buffering
    for i in range(len(prev)):
        for j in range(len(prev)):
            if prev[i, j] is None:
                if new[i, j] is None:
                    continue
                else:
                    move(i, j)
                    print(new[i, j], end='')
            elif new[i, j] is None:
                move(i, j)
                print(' ', end='')
   
            elif prev[i, j] == new[i, j]:
                continue

            else:
                move(i, j)
                print(new[i, j], end='')

        move(i, len(prev))
        print()


def move (y, x):
    print("\033[%d;%dH" % (y, x), end='')  


def print_inconsole(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            if matrix[i, j] is None:
                matrix[i, j] = " "
                print(" ", end="")
            else:
                print(matrix[i, j], end="")
        print()

def clear_console():
    # Windows
    if os.name == 'nt':
        _ = os.system('cls')
    # Linux and macOS
    else:
        _ = os.system('clear')


get_frames()