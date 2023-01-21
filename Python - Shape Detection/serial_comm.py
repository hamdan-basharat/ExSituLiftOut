import serial
import time

ser = serial.Serial(port='COM5', baudrate=9600, timeout=1)

while True:
    i = input("Input(on/off): ").strip()
    if i == 'Done':
        print('Finished program')
        break
    ser.write(i.encode())
    time.sleep(0.5)
    print(ser.readline().decode('ascii'))

ser.close()