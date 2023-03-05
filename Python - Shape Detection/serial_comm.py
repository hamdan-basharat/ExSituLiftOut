import serial
import time

ser = serial.Serial(port='COM4', baudrate=115200, timeout=1)

while True:
    i = input("Input(on/off): ").strip()
    if i == 'Done':
        print('Finished program')
        break
    ser.write(i.encode())
    if ser.readline().decode('ascii') == " ":
        print('test')
    j = ser.readline().decode('ascii');
    time.sleep(0.5)
    print(ser.readline().decode('ascii'))

ser.close()