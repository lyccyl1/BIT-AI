import cv2
import numpy as np
from HOG import HOG
from kcfTracker import kernel_correlation, train, detect, cos_smooth, prewhiten, find_four, find_double, create_gaussian_peak, update_parameter

class Tracker():
    def __init__(self, image, roi):
        # initial parameter
        self.raw_flag = False
        self.HOG_flag = True
        self.deep_flag = False
        self.sigma = 0.6
        self.l = 0.0001
        self.interp_factor = 0.024
        # initial list
        self.range_list = [0.8, 0.9,  1.0, 1.05, 1.10 ]
        # self.range_list = [0.9, 1.0, 1.1]
        # get size
        if self.HOG_flag == True:
            xx, yy, width, height = roi
            self.roi = roi
            roi = (xx + width // 2, yy + height // 2, width, height)
            scale = find_four(254.625) / float(max(width, height))
            self.width_patch = find_four(width * scale)
            self.height_patch = find_four(height * scale)
            self.hog = HOG((self.width_patch, self.height_patch))
            x = self.get_feature(image, roi)
            self.x = x

        if self.raw_flag == True:
            x = x.astype('float64')
            self.x = prewhiten(x)
            self.sigma = 0.2
            self.cell_size = 1
            self.HOG_flag = False

        if self.deep_flag == True:
            self.HOG_flag = False
            self.feature_scale_width = float(self.width_patch) / width
            self.feature_scale_height = float(self.height_patch) / height
        y = create_gaussian_peak(x.shape[2], x.shape[1])
        # initial
        self.alpha = train(x, y, self.sigma, self.l)


    def get_feature(self, image, roi):
        channel_x, channel_y, width, height = roi
        # padding = 2.5  from paper
        padding = 2.5
        width = find_double(width * padding)
        height = find_double(height * padding)
        x, y = int(channel_x - width // 2), int(channel_y - height // 2)
        # get HOG feature
        sub_image = image[y:y + height, x:x + width, :]
        resized_image = cv2.resize(sub_image, (self.width_patch, self.height_patch))
        feature, self.scale_width, self.scale_height = cos_smooth(resized_image, width, height, self.hog)
        # if no HOG feature need to normalize
        if self.HOG_flag:
            feature = feature
        else:
            feature = feature.astype('float64')
            feature = prewhiten(feature)
        return feature

    def update(self, image):
        channel_x, channel_y, width_roi, height_roi = self.roi
        max_response = -np.inf
        for scale in self.range_list:
            roi = map(int, (channel_x, channel_y, width_roi * scale, height_roi * scale))
            z = self.get_feature(image, roi)
            # key part for updating
            responses = detect(self.alpha, self.x, z, self.sigma)
            height, width = responses.shape
            # update
            if np.max(responses) > max_response:
                max_response = np.max(responses)
                dx, dy, new_width, new_height = update_parameter(np.argmax(responses), width, height,
                                                                  self.scale_width, self.scale_height, width_roi, height_roi, scale)
        self.roi = (channel_x + dx, channel_y + dy, new_width, new_height)
        # update key parameter
        self.x = self.x * (1 - self.interp_factor) + z * self.interp_factor
        y = create_gaussian_peak(z.shape[2], z.shape[1])
        new_alpha = train(z, y, self.sigma, self.l)
        self.alpha = self.alpha * (1 - self.interp_factor) + new_alpha * self.interp_factor
        channel_x, channel_y, width_roi, height_roi = self.roi
        new_x = channel_x - width_roi // 2
        new_y = channel_y - height_roi // 2
        new_width_roi = width_roi
        new_height_roi = height_roi
        return new_x, new_y, new_width_roi, new_height_roi

        # some unused code
        # if (self._roi[0] + self._roi[2] <= 0):  self._roi[0] = -self._roi[2] + 1
        # if (self._roi[1] + self._roi[3] <= 0):  self._roi[1] = -self._roi[2] + 1
        # if (self._roi[0] >= image.shape[1] - 1):  self._roi[0] = image.shape[1] - 2
        # if (self._roi[1] >= image.shape[0] - 1):  self._roi[1] = image.shape[0] - 2
        #
        # cx = self._roi[0] + self._roi[2] / 2.
        # cy = self._roi[1] + self._roi[3] / 2.
        #
        # loc, peak_value = self.detect(self._tmpl, self.getFeatures(image, 0, 1.0))
        #
        # if (self.scale_step != 1):
        #     # Test at a smaller _scale
        #     new_loc1, new_peak_value1 = self.detect(self._tmpl, self.getFeatures(image, 0, 1.0 / self.scale_step))
        #     # Test at a bigger _scale
        #     new_loc2, new_peak_value2 = self.detect(self._tmpl, self.getFeatures(image, 0, self.scale_step))
        # train(x, self.interp_factor)