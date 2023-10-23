import cv2
class HOG():
    def __init__(self, windowSize):
        # the size from paper
        # the size of window
        self.windowSize = windowSize
        # the size of block
        self.blockSize = (8, 8)
        # the sliding stride
        self.blockStride = (4, 4)
        # the size of cell
        self.cellSize = (4, 4)
        # the size of bin under cell
        self.binSize = 9
        # use cv2 function to describe hog
        self.hog = cv2.HOGDescriptor(windowSize, self.blockSize, self.blockStride, self.cellSize, self.binSize)
        # split windowSize
        self.width, self.height = self.windowSize
        # split blockSize
        self.stride_width, self.stride_height = self.blockStride
    def get_hog_feature(self, image):
        hog_feature = self.hog.compute(image, self.windowSize, padding=(0, 0))
        # compute the result of weight and height after sliding
        reshape_weight = self.width // self.stride_width - 1
        reshape_height = self.height // self.stride_height - 1
        # return res in the shape of sliding
        return hog_feature.reshape(reshape_weight, reshape_height, 36).transpose(2, 1, 0)