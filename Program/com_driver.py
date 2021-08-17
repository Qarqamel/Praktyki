import serial
import time
import matplotlib.pyplot as plt
import numpy as np
import keyboard

def show():
    y = []
    with open("archive.bin", "rb") as file:
        bytes_buffer = file.read(18)
        while(bytes_buffer != ''.encode('utf-8')):
            sr_buffer = [float(val) for val in bytes_buffer.split()]
            y.append(sr_buffer)
            bytes_buffer = file.read(18)
    plt.plot(np.array(y), '-p')
            

with serial.Serial(port="COM4", baudrate=9600,bytesize = 8, 
                   timeout = None, stopbits=serial.STOPBITS_ONE) as serialPort:
    y = []
    time.sleep(2)
    with open("archive.bin", "ab") as file:
        while(keyboard.read_key()!='q'):
            serialPort.write('tempval\n'.encode('utf-8'))
            temp_buff = serialPort.readline().strip('\n'.encode('utf-8'))
            file.write(temp_buff)
            single_read_buff = [float(val) for val in temp_buff.split()]
            y.append(single_read_buff)        
    plt.plot(np.array(y), '-p')
    show()
