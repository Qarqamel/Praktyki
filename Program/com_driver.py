import serial
import time
import matplotlib.pyplot as plt
import numpy as np

serialPort = serial.Serial(port="COM4", baudrate=9600,bytesize = 8, 
                             timeout = None, stopbits=serial.STOPBITS_ONE)

y = []

time.sleep(5)

for i in range(10):
        serialPort.write('tempval\n'.encode('utf-8'))
        temp_buff = serialPort.read_until('\n'.encode('utf-8'))
        y.append(temp_buff.split(' '.encode('utf-8'), 2))
        for j in range(len(y[-1])):
            y[-1][j] = float(y[-1][j])
        time.sleep(1)
        
plt.plot(range(len(y)), np.array(y), '.')
serialPort.close()
