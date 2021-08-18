import serial
import time
import matplotlib.pyplot as plt
import numpy as np
import keyboard

def show():
    with open("archive.bin", "rb") as file:
        read_arr = np.fromfile(file, dtype = np.dtype([('temp1', 'float64'),
                                              ('temp2', 'float64'),
                                              ('temp3', 'float64')]))
    new_arr = [list(elem) for elem in read_arr]
    plt.plot(np.array(new_arr), '-p')         

with serial.Serial(port="COM4", baudrate=9600,bytesize = 8, 
                   timeout = None, stopbits=serial.STOPBITS_ONE) as serialPort:
    y = []
    time.sleep(2)
    while(keyboard.read_key()!='q'):
        serialPort.write('tempval\n'.encode('utf-8'))
        temp_buff = serialPort.readline().strip('\n'.encode('utf-8'))
        single_read_buff = [float(val) for val in temp_buff.split()]
        y.append(single_read_buff)
with open("archive.bin", "ab") as file:
    np.array(y).tofile(file)
plt.plot(np.array(y), '-p')
show()