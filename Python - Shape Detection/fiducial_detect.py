import cv2 as cv
from matplotlib import pyplot as plt

img = cv.imread('sample.png', cv.IMREAD_GRAYSCALE)
assert img is not None, "file could not be read, check with os.path.exists()"

# Otsu's thresholding after Gaussian filtering
blur = cv.GaussianBlur(img, (5, 5), 0)
ret, th = cv.threshold(blur, 0, 255, cv.THRESH_BINARY + cv.THRESH_OTSU)
th = cv.bitwise_not(th)

# check image size to find halves
# print(th.shape[0])
# print(th.shape[1])

# fill in the squares by connecting black pixels across rows
filled = th.copy()
# left half
for row in range(int(filled.shape[0])):
    # Find the left-most and right-most pixel in the square
    start, stop = 0, 0
    for col in range(int(filled.shape[1] / 2 - 10)):
        # Find the left-most
        if filled[row, col] != 255 and start == 0: start = col, row
        # Find the right-most
        if filled[row, col] != 255: stop = col, row
    # If there was a pixel in that row, connect them with a line
    if start != 0:
        cv.line(filled, start, stop, 0, 1)

# right half
for row in range(int(filled.shape[0])):
    # Find the left-most and right-most pixel in the square
    start, stop = 0, 0
    for col in range(int(filled.shape[1] / 2), filled.shape[1]):
        # Find the left-most
        if filled[row, col] != 255 and start == 0: start = col, row
        # Find the right-most
        if filled[row, col] != 255: stop = col, row
    # If there was a pixel in that row, connect them with a line
    if start != 0:
        cv.line(filled, start, stop, 0, 1)

outline = filled.copy()
# using a findContours() function
contours, _ = cv.findContours(outline, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)
outline = cv.cvtColor(outline, cv.COLOR_GRAY2RGB)

i = 0
ind = 0
# 60 microns
fidSize = 60
pixel2metric = 0
sampleCoords = [[0, 0, 0], [0, 0, 0]]

# list for storing names of shapes
for contour in contours:
    # here we are ignoring first counter because
    # find contour function detects whole image as shape
    if i == 0:
        i = 1
        continue
    # cv2.approxPloyDP() function to approximate the shape
    approx = cv.approxPolyDP(contour, 0.01 * cv.arcLength(contour, True), True)
    # using drawContours() function
    cv.drawContours(outline, [contour], 0, (255, 0, 255), 2)

    # print(cv.contourArea(contour))
    # sample trenches
    if cv.contourArea(contour) > 5000:
        M = cv.moments(contour)
        cX = int(M["m10"] / M["m00"])
        cY = int(M["m01"] / M["m00"])
        cv.line(outline, (cX, cY), (cX, cY), (255, 0, 255), 5)

        # store sample center coordinates
        sampleCoords[0][ind] = cX
        sampleCoords[1][ind] = cY
        ind = ind + 1

    # fiducial
    if cv.contourArea(contour) < 5000:
        x, y, w, h = cv.boundingRect(contour)
        cv.rectangle(outline, (x, y), (x+w, y+h), (0, 255, 0), 2)
        # print(h)
        pixel2metric = h/fidSize
        print("There are " + str(pixel2metric) + " pixels for each micron")

print(sampleCoords)

fig = plt.figure()

fig.add_subplot(2, 2, 1)
plt.imshow(img, cmap='gray', vmin=0, vmax=255)
plt.axis('off')
plt.title("Original Image")

fig.add_subplot(2, 2, 2)
plt.imshow(th, cmap='gray', vmin=0, vmax=255)
plt.axis('off')
plt.title("Otsu's Thresholding")

fig.add_subplot(2, 2, 3)
plt.imshow(filled, cmap='gray', vmin=0, vmax=255)
plt.axis('off')
plt.title("Shape Filling")

fig.add_subplot(2, 2, 4)
plt.imshow(outline)
plt.axis('off')
plt.title("Contour Detection")

plt.show()

# cv.imshow('Stereoscope Image', img)
# cv.waitKey(0)
# cv.destroyAllWindows()