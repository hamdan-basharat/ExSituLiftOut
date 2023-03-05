from liftout_functions import *

img = cv2.imread('shape_image.png')
#ser = serial.Serial(port='COM4', baudrate=115200, timeout=1)

pixel2metric = fiducial_detect(img)

x, y = 1
while x and y != 0:
    x, y = trench_detect(img)
    #move_motor(img, ser, pixel2metric, x, y)
    move_motor(img, pixel2metric, x, y)

#ser.close()