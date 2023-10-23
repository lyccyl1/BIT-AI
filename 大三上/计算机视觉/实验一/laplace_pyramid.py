import cv2 as cv
import numpy as np
from matplotlib import pyplot as plt
A = cv.imread('apple.png')
B = cv.imread('orange.png')
m1 = cv.imread('mask1.png')
m2 = cv.imread('mask2.png')
n = 6
A = cv.resize(A,  (512, 512), interpolation=cv.INTER_CUBIC)
B = cv.resize(B ,  (512, 512), interpolation=cv.INTER_CUBIC)
def gaussian_pyramid(img,n):
    gaussian_img = img.copy()
    gpimg = [gaussian_img]
    for i in range (n):
        # gaussian blur
        gaussian_img = cv.GaussianBlur(gaussian_img, (601, 601), 30)
        gaussian_img = cv.GaussianBlur(gaussian_img, (5, 5), 15)
        gaussian_img = cv.pyrDown(gaussian_img)
        gpimg.append(gaussian_img)
    return gpimg
def laplace_pyramid(gpimg,n):
    lpimg = [gpimg[n-1]]
    for i in range (n-1, 0, -1):
        laplace_img = cv.pyrUp(gpimg[i])
        laplace_img_ = cv.subtract(gpimg[i-1],laplace_img)
        lpimg.append(laplace_img_)
    return lpimg

def img_multiply(gpimg, gaussian_gpimg,n):
    res = []
    for i in range(n):
        l = cv.multiply(gpimg[i-1],gaussian_gpimg[i-1])
        res.append(l)
    return res
def laplace_fusion(gpm,gpa,gpb,n):
    laf = []
    for i in range(n-1):
        m = gpm[i]
        m_inv = 1 -m
        bg = cv.bitwise_and(gpa[i],gpa[i],mask = m)
        fg = cv.bitwise_and(gpb[i],gpb[i],mask = m_inv)
        lapStack = cv.add(bg, fg)
        laf.append(lapStack)
    return laf

#生成A的高斯金字塔
gpA =gaussian_pyramid(A,n)
#生成B的高斯金字塔
gpB = gaussian_pyramid(B,n)
#生成A的拉普拉斯金字塔
lpA = laplace_pyramid(gpA, n)
#生成B的拉普拉斯金字塔
lpB = laplace_pyramid(gpB, n)
#掩模
gpm1 = gaussian_pyramid(m1,n)
gpm2 = gaussian_pyramid(m2,n)
LS = []
for la, lb in zip(lpA, lpB):
    rows, cols, dpt = la.shape
    ls = np.hstack((la[:, 0:int(cols/2)], lb[:, int(cols/2):]))
    LS.append(ls)
# rebuild
ls_img = LS[0]
for i in range(1, 6):
    ls_img = cv.pyrUp(ls_img)
    ls_img = cv.add(ls_img, LS[i])
#图像与直接连接的每一半
real_img = np.hstack((A, B))
real_add_img = np.hstack((A[:, 0:int(cols / 2)], B[:, int(cols / 2):]))
cv.imshow('real_img', real_img)
cv.imshow('real_add', real_add_img)
cv.imshow('ls_img', ls_img)
cv.waitKey(0)
cv.destroyAllWindows()