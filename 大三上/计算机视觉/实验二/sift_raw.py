import cv2 as cv
import numpy as np
from matplotlib import pyplot as plt
import random
from sift import gaussian,convolution,octaves
imgnames = ['friend.jpg', '6.jpg']
desc = [0, 0]
imgsize = 512


# 用于寻找每个图像中的关键点和描述子的循环
for imgname in range(len(imgnames)):
    img = cv.resize(cv.imread(imgnames[imgname], 0), (imgsize, imgsize))
    n, octave = 5, 4
    L, D = octaves(img, n, octave)

    # show
    for oct in range(octave):
        imm = np.concatenate((L[oct][0], L[oct][1], L[oct][2], L[oct][3], L[oct][4]), axis=1)
        plt.figure(figsize=(20, 4))
        plt.title('Gaussian scale space')
        plt.imshow(imm, cmap='gray')
        plt.show()
    for oct in range(octave):
        imm = np.concatenate((D[oct][0], D[oct][1], D[oct][2], D[oct][3]), axis=1)
        plt.figure(figsize=(16, 4))
        plt.title('DoG scale space')
        plt.imshow(imm, cmap='gray')
        plt.show()

    plt.show()
    # show end


    keys = []
    # 依据高斯差分矩阵寻找关键点
    for oct in range(octave):
        count = 0
        key_scale = []
        for scale in range(1, len(D[0]) - 1):
            t1, t2, t3 = D[oct][scale - 1], D[oct][scale], D[oct][scale + 1]
            key = np.zeros(t1.shape)
            for i in range(1, t1.shape[0] - 1):
                for j in range(1, t1.shape[1] - 1):
                    x = [t1[i - 1:i + 2, j - 1:j + 2], t2[i - 1:i + 2, j - 1:j + 2], t3[i - 1:i + 2, j - 1:j + 2]]
                    if np.min(x) == t2[i][j] or np.max(x) == t2[i][j]:
                        dx2 = t2[i][j + 1] + t2[i][j - 1] - 2 * t2[i][j]
                        dy2 = t2[i + 1][j] + t2[i - 1][j] - 2 * t2[i][j]
                        dxy = t2[i + 1][j + 1] + t2[i - 1][j - 1] - t2[i + 1][j - 1] - t2[i - 1][j + 1]
                        H = (dx2 + dy2) ** 2 / (dx2 * dy2 - dxy ** 2)
                        if H < (10 + 1) ** 2 / 10 and abs(t2[i][j]) >= 0.5:
                            key[i][j] = 1
                            count += 1
            key_scale.append(key)
            imm = L[oct][scale]
            for ii in range(key.shape[0]):
                for jj in range(key.shape[1]):
                    if key[ii][jj] == 1:
                        cv.circle(imm, (jj, ii), 3, (255, 0, 0, 1))
            plt.figure(figsize=(8, 8))
            plt.title('Keypoints scale ' + str(scale) + ' octave ' + str(oct))
            plt.imshow(imm, cmap='gray')
            plt.show()
        print(count)
        keys.append(key_scale)

    all_keys = {}
    print('Calculating orientations and theeta...')
    # 对关键点计算大小和方向
    img1 = cv.resize(cv.imread(imgnames[imgname], 1), (imgsize, imgsize))
    for oct in range(octave):
        for i in range(len(keys[oct])):
            for j in range(keys[oct][i].shape[0]):
                for k in range(keys[oct][i].shape[1]):
                    if keys[oct][i][j][k] == 1:
                        cv.circle(img1, (k, j), 1, (255, 255, 0), 0)
                        bin = {}
                        for l1 in range(-8, 9):
                            for l2 in range(-8, 9):
                                try:
                                    l = L[oct][i + 1]
                                    x1 = j + l1
                                    y1 = k + l2
                                    m1 = ((l[x1 + 1][y1] - l[x1 - 1][y1]) ** 2 + (
                                                l[x1][y1 + 1] - l[x1][y1 - 1]) ** 2) ** 0.5
                                    s1 = 2 ** oct * (1 / 2 ** 0.5) * (2 ** 0.5) ** (i + 1)
                                    theeta1 = np.arctan2((l[x1 + 1][y1] - l[x1 - 1][y1]),
                                                         (l[x1][y1 + 1] - l[x1][y1 - 1])) * 180 / np.pi + 180
                                    ws = int(6 * 1.5 * s1)
                                    gfil = gaussian(1.5 * s1, ws)
                                    try:
                                        bin[int(theeta1 / 10) * 10] += m1 * gfil[l1 + int(ws / 2)][l2 + int(ws / 2)]
                                    except:
                                        bin[int(theeta1 / 10) * 10] = m1 * gfil[l1 + int(ws / 2)][l2 + int(ws / 2)]
                                except:
                                    continue
                        max1, d1 = 0, 0
                        for d in bin:
                            if bin[d] > max1:
                                max1 = bin[d]
                                d1 = d
                        all_keys[oct, i, j, k] = [(max1, d1)]
                        for d in bin:
                            if d != d1 and bin[d] >= 0.8 * bin[d1]:
                                all_keys[oct, i, j, k].append((bin[d], d))

    plt.figure(figsize=(8, 8))
    qq = np.zeros((len(all_keys), 4, 3))
    ind = 0
    # 画出关键点的方向
    print('Plotting key points with orientations...')
    for dd in all_keys:
        a, b, c, d = dd
        if a == 0:
            qq[ind][a] = np.array([c, d, np.pi / 180 * all_keys[dd][0][1]])
            ind += 1
        elif a == 1:
            qq[ind][a] = np.array([c * 2, d * 2, np.pi / 180 * all_keys[dd][0][1]])
            ind += 1
        elif a == 2:
            qq[ind][a] = np.array([c * 4, d * 4, np.pi / 180 * all_keys[dd][0][1]])
            ind += 1
        elif a == 3:
            qq[ind][a] = np.array([c * 8, d * 8, np.pi / 180 * all_keys[dd][0][1]])
            ind += 1
    plt.imshow(img1, cmap='gray')
    plt.quiver(qq[:, 0, 1], qq[:, 0, 0], 4 * np.cos(qq[:, 0, 2]), 4 * np.sin(qq[:, 0, 2]), units='width', color='r')
    plt.quiver(qq[:, 1, 1], qq[:, 1, 0], 4 * np.cos(qq[:, 1, 2]), 4 * np.sin(qq[:, 1, 2]), units='width', color='g')
    plt.quiver(qq[:, 2, 1], qq[:, 2, 0], 4 * np.cos(qq[:, 2, 2]), 4 * np.sin(qq[:, 2, 2]), units='width', color='b')
    plt.quiver(qq[:, 3, 1], qq[:, 3, 0], 4 * np.cos(qq[:, 3, 2]), 4 * np.sin(qq[:, 3, 2]), units='width', color='y')
    plt.show()

    # 得到描述子
    descriptor = {}
    print('Calculating descriptor...')
    for kk in all_keys:
        oct, i, j, k = kk
        s1 = 2 ** oct * (1 / 2 ** 0.5) * (2 ** 0.5) ** (i + 1)
        bins = np.zeros((4, 4, 8))
        for x in range(-8, 8):
            for y in range(-8, 8):
                try:
                    x1 = x + j
                    y1 = y + k
                    l = L[oct][i + 1]
                    m1 = ((l[x1 + 1][y1] - l[x1 - 1][y1]) ** 2 + (l[x1][y1 + 1] - l[x1][y1 - 1]) ** 2) ** 0.5
                    theeta1 = np.arctan2((l[x1 + 1][y1] - l[x1 - 1][y1]),
                                         (l[x1][y1 + 1] - l[x1][y1 - 1])) * 180 / np.pi + 180
                    inx, indy = 0, 0
                    if x <= -5:
                        indx = 0
                    elif -4 <= x <= -1:
                        indx = 1
                    elif 0 <= x <= 3:
                        indx = 2
                    elif 4 <= x <= 7:
                        indx = 3
                    if y <= -5:
                        indy = 0
                    elif -4 <= y <= -1:
                        indy = 1
                    elif 0 <= y <= 3:
                        indy = 2
                    elif 4 <= y <= 7:
                        indy = 3

                    gfil = gaussian(8, 16)
                    bins[indx][indy][int(theeta1 / 45)] += m1 * gfil[8 + x][8 + y]
                except:
                    continue
        feat = []
        for ii in range(4):
            for jj in range(4):
                for ang in range(8):
                    feat.append(bins[ii][jj][ang])
        # 归一化
        sum2 = 0
        feat = np.array(feat)
        for ii in feat:
            sum2 += ii ** 2
        sum2 = sum2 ** 0.5
        feat = feat / sum2
        for ii in range(128):
            if feat[ii] > 0.2:
                feat[ii] = 0.2
        descriptor[oct, i, j, k] = feat
        desc[imgname] = descriptor
    # 输出描述子
    for i in desc[imgname]:
        print(desc[imgname][i])


# 关键点匹配
img1 = cv.resize(cv.imread(imgnames[0], 1), (imgsize, imgsize))
img2 = cv.resize(cv.imread(imgnames[1], 1), (imgsize, imgsize))
print('Finding match points...')
rank = {}

for d1 in desc[0]:
    for d2 in desc[1]:
        or1, ii1, x1, y1 = d1
        or2, ii2, x2, y2 = d2
        dist = (desc[0][d1] - desc[1][d2]) ** 2
        s = 0
        for ss in dist:
            s += ss
        s = s ** 0.5
        rank[s] = (x1 * 2 ** or1, y1 * 2 ** or1, x2 * 2 ** or2, y2 * 2 ** or2)

imm = np.concatenate((img1, img2), axis=1)
for i in sorted(rank.keys())[:20]:
    x1, y1, x2, y2 = rank[i]
    print(x1, y1, x2, y2)
    cv.circle(imm, (y1, x1), 3, (255, 0, 0), 1)
    cv.line(imm, (y1, x1), (y2 + imgsize, x2), (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)),
            1)
    cv.circle(imm, (y2 + imgsize, x2), 3, (255, 0, 0), 1)

plt.figure(figsize=(20, 10))
plt.imshow(imm, cmap='gray')
plt.show()