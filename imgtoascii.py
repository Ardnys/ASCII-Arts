import numpy as np
import imageio.v3 as iio 
import matplotlib.pyplot as plt
from pathlib import Path

image_path = "images"
images = list()

for file in Path(image_path).iterdir():
    if not file.is_file():
        continue

    images.append(iio.imread(file))
    print("read " + file.name)


# just the dots
def simple_ascii():
    img = images[1]
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
                    ascii_matrix[i][j] = '#'
                    img1.write('.')
                else:
                    ascii_matrix[i][j] = '.'
                    img1.write('#')
            img1.write('\n')

    
    print(ascii_matrix)

simple_ascii()

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



