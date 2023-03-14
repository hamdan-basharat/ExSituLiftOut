import cv2 as cv

img = cv.imread('sample.png', cv.IMREAD_GRAYSCALE)
assert img is not None, "file could not be read, check with os.path.exists()"

# Otsu's thresholding after Gaussian filtering
blur = cv.GaussianBlur(img,(5,5),0)
ret,th = cv.threshold(blur, 0, 255, cv.THRESH_BINARY + cv.THRESH_OTSU)

th = cv.bitwise_not(th)

# print(th.shape[0])
# print(th.shape[1])

# left half
for row in range(int(th.shape[0])):
    # Find the left-most and right-most pixel in the square
    start, stop = 0, 0
    for col in range(int(th.shape[1] / 2 - 10)):
        # Find the left-most
        if th[row,col] != 255 and start == 0: start = col, row
        # Find the right-most
        if th[row,col] != 255: stop = col, row
    # If there was a pixel in that row, connect them with a line
    if start != 0:
        cv.line(th, start, stop, 0, 1)

# right half
for row in range(int(th.shape[0])):
    # Find the left-most and right-most pixel in the square
    start, stop = 0, 0
    for col in range(int(th.shape[1] / 2), th.shape[1]):
        # Find the left-most
        if th[row,col] != 255 and start == 0: start = col, row
        # Find the right-most
        if th[row,col] != 255: stop = col, row
    # If there was a pixel in that row, connect them with a line
    if start != 0:
        cv.line(th, start, stop, 0, 1)

# using a findContours() function
contours, _ = cv.findContours(
    th, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)

i = 0
fidSize = 60 # 60 microns
pixel2metric = 0

th = cv.cvtColor(th, cv.COLOR_GRAY2RGB)

#list for storing names of shapes
for contour in contours:
    # here we are ignoring first counter because
    # find contour function detects whole image as shape
    if i == 0:
        i = 1
        continue
    # cv2.approxPloyDP() function to approximate the shape
    approx = cv.approxPolyDP(
        contour, 0.01 * cv.arcLength(contour, True), True)
    # using drawContours() function
    cv.drawContours(th, [contour], 0, (255, 0, 255), 2)

    #print(cv.contourArea(contour))
    if cv.contourArea(contour) > 5000:
        M = cv.moments(contour)
        cX = int(M["m10"] / M["m00"])
        cY = int(M["m01"] / M["m00"])
        cv.line(th, (cX, cY), (cX, cY), (255, 0, 255), 5)
    # if len(approx) == 4:
    #     x, y, w, h = cv.boundingRect(contour)
    #     cv.rectangle(th, (x, y), (x+w, y+h), (255, 0, 0), 2)
        # pixel2metric = w/fidSize
        # print("There are " + str(pixel2metric) + " pixels for each micron")

# displaying the image after drawing contours
cv.imshow('Stereoscope Image', th)
cv.waitKey(0)
cv.destroyAllWindows()
