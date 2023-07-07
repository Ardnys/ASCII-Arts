import numpy as np
import imageio.v3 as iio 
import matplotlib.pyplot as plt
from pathlib import Path
from math import cos, sin
import sys

np.set_printoptions(threshold=sys.maxsize)

image_path = "images"
images = list()

for file in Path(image_path).iterdir():
    if not file.is_file():
        continue

    images.append(iio.imread(file))
    print("read " + file.name)

def print_inconsole(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            print(matrix[i][j], end="")
        print()

def img_plot():
    fig, ax = plt.subplots(2, 3)

    img_idx = 0
    for i in range(2):
        for j in range(3):
            if img_idx >= len(images):
                break
            ax[i, j].imshow(images[img_idx])
            img_idx += 1

    plt.show()

def dot_product(vec_1: list, vec_2: list) -> list:
    if len(vec_1) != len(vec_2):
        raise Exception("can't dot product different size vectors")
        # i don't even know if it's true but it feels like it
    vec = list()
    for i,j in zip(vec_1, vec_2):
        vec.append(i * j)
    
    return vec

def uh(matrix):
    cos_theta = int(cos(np.pi/2)) # 45 degrees
    sin_theta = int(sin(np.pi/2))
    Rx_matrix = [[1,      0,          0     ],
                 [0, cos_theta, -1*sin_theta],
                 [0, sin_theta, cos_theta  ]]
    
    column_vectors = list()
    # add third dimension
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            column_vectors.append([i, j, 0])

    transformed_vectors = list()
    for x in column_vectors:
        for i in range(len(Rx_matrix)):
            c = dot_product(Rx_matrix[i], x)
            transformed_vectors.append(c)
            print(f'prev coord: {x}\nnew coord: {c}')
    # ctr = 0
    # for i in range(len(matrix)):
    #     for j in range(len(matrix[0])):
    #         matrix[i, j] = transformed_vectors[ctr]
    #         ctr += 1

    return matrix

# just the dots
def simple_ascii():
    img = images[4]
    nrows = len(img)
    ncols = len(img[0])
    print(f'rows: {nrows} \ncols: {ncols}')
    ascii_matrix = np.empty((nrows, ncols), dtype=str)
    mrows = len(ascii_matrix[0])
    mcols = len(ascii_matrix)
    print(f'matrix rows: {mrows}\nmatrix cols: {mcols}')
    # print(img)
    # plt.imshow(img)
    # plt.show()

    with open("img1.txt", "w") as img1:

        for i in range(nrows):
            for j in range(ncols):
                avg_val = np.mean(img[i][j])
                # print("avg val is " + str(avg_val))
                if avg_val > 200:
                    # bright pixel
                    ascii_matrix[i][j] = '# '
                    img1.write('  ')
                else:
                    ascii_matrix[i][j] = '  '
                    img1.write('# ')
            img1.write('\n')

        # print_inconsole(ascii_matrix) 

        rotated_matrix = uh(ascii_matrix)
        # print_inconsole(rotated_matrix)
        # print(rotated_matrix)
simple_ascii()