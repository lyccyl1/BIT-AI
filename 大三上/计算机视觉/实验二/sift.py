import numpy as np
import cv2 as cv
# 建立高斯滤波器
def gaussian(standard_deviation, size=9):
    filter = np.zeros((size, size))
    sum = 0
    for i in range(size):
        for j in range(size):
            x = abs(i - size // 2)
            y = abs(j - size // 2)
            filter[i][j] = np.exp(-1 * (x ** 2 + y ** 2) / (2 * standard_deviation ** 2)) / (2 * np.pi * standard_deviation ** 2)
            sum += filter[i][j]
    return filter / sum


# 构建卷积核
def convolution(image, filter):
    y = np.zeros(image.shape)
    s = len(filter)
    image1 = np.zeros((image.shape[0] + s // 2 * 2,
                       image.shape[1] + s // 2 * 2))

    for i in range(image1.shape[0]):
        for j in range(image1.shape[1]):
            if s // 2 <= i < image1.shape[0] - s // 2 and \
                    s // 2 <= j < image1.shape[1] - s // 2:
                image1[i][j] = image[i - s // 2][j - s // 2]

    # show
    print('Convoluting...')
    for i in range(image1.shape[0]):
        for j in range(image1.shape[1]):
            if s // 2 <= i < image1.shape[0] - s // 2 and s // 2 <= j < image1.shape[1] - s // 2:
                x = image1[i - s // 2:i + s // 2 + 1, j - s // 2:j + s // 2 + 1]
                p = 0
                for i1 in range(s):
                    for j1 in range(s):
                        p += x[i1][j1] * filter[i1][j1]
                y[i - s // 2][j - s // 2] = p
    return y


# 构建L、D矩阵对于per octaves
def octaves(img, scales, octave):
    n = scales
    a = 2 ** 0.5
    std = 1 / a
    L, D = [], []
    # show
    for oct in range(octave):
        print('Octave', oct + 1, '(5 convolutions per octave)')
        img1 = cv.resize(img, (int(img.shape[0] / 2 ** oct), int(img.shape[1] / 2 ** oct)))
        temp1, temp2 = [], []
        for i in range(n):
            fil = gaussian(2 ** oct * std * a ** i, int(6 * 2 ** oct * std * a ** i))
            temp1.append(convolution(img1, fil))
        L.append(temp1)
        for i in range(n - 1):
            temp2.append(temp1[i] - temp1[i + 1])
        D.append(temp2)
    return L, D
