import serial
import time
import matplotlib.pyplot as plt
import numpy as np
import keyboard

def show():
    loaded_arr = np.load('archive.npy')
    plt.plot(np.array(loaded_arr), '-p')         

with serial.Serial(port="COM4", baudrate=9600,bytesize = 8, 
                   timeout = None, stopbits=serial.STOPBITS_ONE) as serialPort:
    y = []
    time.sleep(2)
    while(keyboard.read_key()!='q'):
        serialPort.write('tempval\n'.encode('utf-8'))
        temp_buff = serialPort.readline().strip('\n'.encode('utf-8'))
        single_read_buff = list(map(float, temp_buff.split()))
        print(single_read_buff)
        y.append(single_read_buff)
np.save('archive.npy', np.array(y))
show()