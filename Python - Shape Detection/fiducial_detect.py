import cv2

# reading image
img = cv2.imread('shape_image.png')
# converting image into grayscale image
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
# setting threshold of gray image
_, threshold = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)
# using a findContours() function
contours, _ = cv2.findContours(
    threshold, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

i = 0
fidSize = 60 # 60 microns
pixel2metric = 0

# list for storing names of shapes
for contour in contours:
    # here we are ignoring first counter because
    # find contour function detects whole image as shape
    if i == 0:
        i = 1
        continue
    # cv2.approxPloyDP() function to approximate the shape
    approx = cv2.approxPolyDP(
        contour, 0.01 * cv2.arcLength(contour, True), True)
    # using drawContours() function
    cv2.drawContours(img, [contour], 0, (0, 0, 255), 2)
    if len(approx) == 3:
        x, y, w, h = cv2.boundingRect(contour)
        cv2.rectangle(img, (x, y), (x+w, y+h), (255, 0, 0), 2)
        pixel2metric = w/fidSize
        print("There are " + str(pixel2metric) + " pixels for each micron")

# displaying the image after drawing contours
cv2.imshow('Fiducial', img)
cv2.waitKey(0)
cv2.destroyAllWindows()
