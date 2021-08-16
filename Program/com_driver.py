import serial
import time

serialPort = serial.Serial(port="COM4", baudrate=9600,bytesize = 8, 
                             timeout = 1, stopbits=serial.STOPBITS_ONE)

while(True):
        serialPort.write('tempval\n'.encode('utf-8'))
        print(serialPort.readline())
        time.sleep(5)