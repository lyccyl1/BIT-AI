import cv2
import numpy as np

def create_gaussian_peak(width, height):
    padding = 2.5
    output_sigma = 0.125
    output_sigma = np.sqrt(width * height) / padding * output_sigma
    mult = - 0.5 / (output_sigma ** 2)
    y, x = np.ogrid[0:height, 0:width]
    y, x = (y - height / 2) ** 2, (x - width / 2) ** 2
    res = np.exp(mult * (y + x))
    return res

def update_parameter(idx, width, height, scale_width, scale_height, width_roi,height_roi, scale):
    dx = int((idx % width - width / 2) / scale_width)
    dy = int((idx / width - height / 2) / scale_height)
    best_w = int(width_roi * scale)
    best_h = int(height_roi * scale)
    return dx, dy, best_w, best_h

def process_cos(x, y):
    res = 0.5 * (1 - np.cos(2 * np.pi * x / (y - 1)))
    return res

#正规化方法
def prewhiten(x):
    mean = np.mean(x)
    #标准差
    std = np.std(x)
    std_adj = np.maximum(std, 1.0/np.sqrt(x.size))
    y = np.multiply(np.subtract(x, mean), 1/std_adj)
    return y

# because of HOG feature, the res must be multiples of four
def find_four(x):
    res = int(x) // 4 * 4 + 4
    return res

# because of HOG feature , the res must be multiples of two
def find_double(x):
    res = int (x) // 2 * 2
    return res

def generate_array(x, y ):
    return np.ogrid[0:x, 0:y]

# l :lambda
def train(x, y, sigma, l):
    # compute kernel k ,k是高斯核函数
    # alpha = fft2(y) / (fft2(k) + lambda)
    k = kernel_correlation(x, x, sigma)
    alpha = np.fft.fft2(y) / (np.fft.fft2(k) + l)
    return alpha


def detect(alpha, x, z, sigma):
    # compute kernel k
    # 第二帧开始就算响应，f(z) = F(-1) (alpha * fft(k))
    k = kernel_correlation(x, z, sigma)
    responses = np.real(np.fft.ifft2(alpha * np.fft.fft2(k)))
    return responses


def kernel_correlation(x1, x2, sigma):
    if len(x1.shape) == 2:
        c = np.fft.ifft2(np.sum(np.conj(np.fft.fft2(x1)) * np.fft.fft2(x2), 2))
    else:
        c = np.fft.ifft2(np.sum(np.conj(np.fft.fft2(x1)) * np.fft.fft2(x2), axis=0))
    # 将零频点移到频谱的中间
    # c = np.fft.fftshift(c)
    d = np.sum(np.power(x1, 2)) + np.sum(np.power(x2, 2)) - 2 * c
    # k = exp(-1 / sigma ** 2 * np.abs(d) / numel(d))  numel : size of array
    k = np.exp(-1 / np.power(sigma, 2) * np.abs(d) / d.size)
    return k

def cos_smooth(image, weight , height ,hog):
    hog_flag = True
    feature = hog.get_hog_feature(image)
    feature_channel, feature_height, feature_width = feature.shape
    scale_weight = float(feature_width) / weight
    scale_height = float(feature_height) / height
    # create hanning window
    hanning_window_width, hanning_window_height = generate_array(feature_height, feature_width)
    if (hog_flag):
        feature = feature * \
              process_cos(hanning_window_width, feature_width) * \
              process_cos(hanning_window_height, feature_height)
    else :
        hann1d = feature.reshape(feature_height, feature_width)
        feature = np.zeros((feature_width, 1), np.float32) + hann1d
    return feature, scale_weight, scale_height

# 参考 构建出汉宁窗
# def createHanningMats(self):
#     hann2t, hann1t = np.ogrid[0:self.size_patch[0], 0:self.size_patch[1]]
#     hann1t = 0.5 * (1 - np.cos(2 * np.pi * hann1t / (self.size_patch[1] - 1)))
#     hann2t = 0.5 * (1 - np.cos(2 * np.pi * hann2t / (self.size_patch[0] - 1)))
#     hann2d = hann2t * hann1t