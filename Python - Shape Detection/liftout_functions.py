import cv2
import serial
import time
def fiducial_detect(img):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # setting threshold of gray image
    _, threshold = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)
    # using a findContours() function
    contours, _ = cv2.findContours(
        threshold, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    i = 0
    fidSize = 60  # 60 microns
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
            cv2.rectangle(img, (x, y), (x + w, y + h), (255, 0, 0), 2)
            pixel2metric = w / fidSize
            print("There are " + str(pixel2metric) + " pixels for each micron")

    return pixel2metric

def trench_detect(img):
    # converting image into grayscale image
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # setting threshold of gray image
    _, threshold = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)
    # using a findContours() function
    contours, _ = cv2.findContours(
        threshold, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    i = 0

    # list for storing names of shapes
    for contour in contours:
        # here we are ignoring first counter because
        # findcontour function detects whole image as shape
        if i == 0:
            i = 1
            continue
        # cv2.approxPloyDP() function to approximate the shape
        approx = cv2.approxPolyDP(
            contour, 0.01 * cv2.arcLength(contour, True), True)
        # using drawContours() function
        cv2.drawContours(img, [contour], 0, (0, 0, 255), 5)
        if len(approx) == 4:
            # finding center point of shape
            M = cv2.moments(contour)
            if M['m00'] != 0.0:
                x = int(M['m10'] / M['m00'])
                y = int(M['m01'] / M['m00'])
            cv2.circle(img, (x, y), 1, (0, 0, 255), -1)

    # displaying the image after drawing contours
    # cv2.imshow('shapes', img)
    # cv2.waitKey(0)
    # cv2.destroyAllWindows()

    return x, y

#def move_motor(img, ser, pixel2metric , x, y):
def move_motor(img, pixel2metric, x, y):
    x_origin, y_origin, depth = img.shape
    x_steps = pixel2metric * (x_origin - x)
    x_dir = 0 if x_steps > 0 else 1
    y_steps = pixel2metric * (y_origin - y)
    y_dir = 0 if y_steps > 0 else 1

    msg = str(abs(x_steps)) + " " + str(x_dir) + " " + str(abs(y_steps)) + " " + str(y_dir)
    #ser.write(msg.encode())
    print(msg)
