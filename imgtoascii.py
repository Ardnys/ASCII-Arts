import numpy as np
import imageio.v3 as iio 
import matplotlib.pyplot as plt
from pathlib import Path
from math import cos, sin
import sys

np.set_printoptions(threshold=sys.maxsize)
'''
TODO
cartesian coordinate system
-----------------------
i kinda try to mash the matrix indices and coordinates together and it's just a mess
so i need a CCS representation of the image. probs a field too
then the transformation between the two. given the indices of the matrix, 
where does it land on the CCS?

essentially i need to represent a 2D cartesian space.
verify this my drawing dots and lines.
maybe first rotate the dot and a line.
of course lines aren't smooth. just / or consecutive dots.


'''
class CoordinatePlane:
    def __init__(self) -> None:
        pass      


class Pixel:
    def __init__(self, indexes: list, char: str) -> None:
        self.indexes = indexes
        self.char = char
        # cartesian indexes and indexes

    def __str__(self) -> str:
        return f'indexes: {self.indexes}\nchar: {self.char}'
    
    def set_indexes(self, indexes: list):
        self.indexes = indexes
    
    def set_char(self, char: str):
        self.char = char
    

def get_them_imgs(image_path: str) -> list:
    images = list()

    for file in Path(image_path).iterdir():
        if not file.is_file():
            continue

        images.append(iio.imread(file))
        # print("read " + file.name)

    return images

# just the dots
def simple_ascii(images):
    img = images[3]
    nrows = len(img)
    ncols = len(img[0])
    # print(f'rows: {nrows} \ncols: {ncols}')
    ascii_matrix = np.empty((nrows, ncols), dtype=Pixel)
    # mrows = len(ascii_matrix[0])
    # mcols = len(ascii_matrix)
    # print(f'matrix rows: {mrows}\nmatrix cols: {mcols}')
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
                    pixel = Pixel([i, j, 0], '  ')
                    ascii_matrix[i][j] = pixel
                    img1.write('  ')
                else:
                    pixel = Pixel([i, j, 0], '# ')
                    ascii_matrix[i][j] = pixel
                    img1.write('# ')
            img1.write('\n')
       
        # print_inconsole(ascii_matrix) 

        # rotated_matrix = uh(ascii_matrix)
        # print_inconsole(rotated_matrix)
        # print(rotated_matrix)

    return ascii_matrix



def uh(matrix):  
    cos_theta = round(cos(np.pi/4), 4) # 45 degrees
    sin_theta = round(sin(np.pi/4), 4)
    Rx_matrix = [[1,      0,          0     ],
                 [0, cos_theta, -1*sin_theta],
                 [0, sin_theta, cos_theta  ]]
    
    # column_vectors = list()
    # # add third dimension
    # for i in range(len(matrix)):
    #     for j in range(len(matrix[0])):
    #         column_vectors.append([i, j, 0])

    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            for x in range(len(Rx_matrix)):
                points = matrix[i, j].indexes
                print(f'prev indexes: {points}')
                c = dot_product(points, Rx_matrix[x])
                print(f'new coord: {c}')
                matrix[i, j].set_indexes(c)

    # transformed_vectors = list()
    # for x in column_vectors:
    #     for i in range(len(Rx_matrix)):
    #         c = dot_product(Rx_matrix[i], x)
    #         transformed_vectors.append(c)
    #         print(f'prev coord: {x}\nnew coord: {c}')
    # ctr = 0
    # for i in range(len(matrix)):
    #     for j in range(len(matrix[0])):
    #         matrix[i, j] = transformed_vectors[ctr]
    #         ctr += 1
    # return transformed_vectors

def dot_product(vec_1: list, vec_2: list) -> list:
    if len(vec_1) != len(vec_2):
        raise Exception("can't dot product different size vectors")
        # i don't even know if it's true but it feels like it
    vec = list()
    for i,j in zip(vec_1, vec_2):
        vec.append(i * j)
    
    return vec

def freebird(matrix):
    '''
    create a new matrix
    traverse the given matrix
    put the characters in their new coords
    '''
    new_matrix = np.empty((len(matrix), len(matrix[0])), dtype=Pixel)
    for i, row in enumerate(matrix):
        for j, element in enumerate(row):
            indexes = element.indexes
            x = int(indexes[0])
            y = int(indexes[1])
            if x < len(new_matrix) and y < len(new_matrix[0]):
                new_matrix[x, y] = element
                # print(f'change indexes from ({i},{j}) to ({x},{y})')

            else:
                print("oops. out of bounds")

    return new_matrix

def print_inconsole(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            print(matrix[i, j].char, end="")
        print()

def write_to_file(matrix):
    with open("img1.txt", "w") as f:
        for i in range(len(matrix)):
            for j in range(len(matrix[0])):
                # if matrix[i, j] is None:
                #     f.write('  ')
                #     print("it's none")
                # else:
                f.write(matrix[i, j].char)
            f.write('\n')

def img_plot(images: list):
    fig, ax = plt.subplots(2, 3)

    img_idx = 0
    for i in range(2):
        for j in range(3):
            if img_idx >= len(images):
                break
            ax[i, j].imshow(images[img_idx])
            img_idx += 1

    plt.show()



if __name__ == '__main__':
    # i guess i'd rather public static void main string args
    images = get_them_imgs("images")
    matrix = simple_ascii(images)
    print_inconsole(matrix)
    uh(matrix)
    # new_matrix = freebird(matrix)
    # write_to_file(new_matrix)
    # print_inconsole(matrix)

