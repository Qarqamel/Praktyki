import serial
import time
import matplotlib.pyplot as plt
import numpy as np
import keyboard

#serialPort = serial.Serial(port="COM4", baudrate=9600,bytesize = 8, 
#                             timeout = None, stopbits=serial.STOPBITS_ONE)

with serial.Serial(port="COM4", baudrate=9600,bytesize = 8, 
                   timeout = None, stopbits=serial.STOPBITS_ONE) as serialPort:

    y = []
    
    time.sleep(5)
    
    while(keyboard.read_key()!='q'):
        serialPort.write('tempval\n'.encode('utf-8'))
        temp_buff = serialPort.readline().strip(' \n'.encode('utf-8'))
        single_read_buff = []
        for val in temp_buff.split():
            val = float(val)
            single_read_buff.append(val)
        y.append(single_read_buff)
        
    plt.plot(np.array(y), '.')
    
