from liftout_functions import *

# getWindow('teamviewer')
# img = cv2.imread('TeamViewerCapture.png')
img = cv.imread('sample.png', cv.IMREAD_GRAYSCALE)

# ser = serial.Serial(port='COM4', baudrate=115200, timeout=1)

pixel2metric, sampleCoords = shape_detect(img)

# move_motor(img, ser, pixel2metric, sampleCoords[0][0], sampleCoords[1][0])
# move_motor(img, pixel2metric, sampleCoords[0][0], sampleCoords[1][0])

# ser.close()