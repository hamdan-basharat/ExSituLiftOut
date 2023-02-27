from PIL import ImageGrab
from win32 import win32gui

toplist, winlist = [], []

def enum_cb(hwnd, results):
    winlist.append((hwnd, win32gui.GetWindowText(hwnd)))

#application = 'TeamViewer'
application = 'teamviewer'

win32gui.EnumWindows(enum_cb, toplist)

"""
for hwnd, title in winlist:
    if (application in title.lower()):
        print(title.lower())
    
"""
firefox = [(hwnd, title) for hwnd, title in winlist if application in title.lower()]
# just grab the hwnd for first window matching firefox
firefox = firefox[1]
hwnd = firefox[0]

win32gui.SetForegroundWindow(hwnd)
bbox = win32gui.GetWindowRect(hwnd)
img = ImageGrab.grab(bbox)
img.show()

