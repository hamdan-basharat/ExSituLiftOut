from liftout_functions import *

# get image of sample
# getWindow('teamviewer')
# img = cv2.imread('TeamViewerCapture.png')
img = cv.imread('sample.png', cv.IMREAD_GRAYSCALE)

ser = serial.Serial(port='COM4', baudrate=9600, timeout=.1)

# calculate sample locations and required motor movements
pixel2metric, sampleCoords = shape_detect(img)
move_motor(img, ser, pixel2metric, sampleCoords[0][0], sampleCoords[1][0], "w") # w for whole, m for micro

ser.close()





