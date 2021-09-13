import serial    

with serial.Serial(port="COM10", baudrate=9600,bytesize = 8,
                   timeout = None, stopbits=serial.STOPBITS_ONE) as serialPort:

    for i in range(100):       
        print(serialPort.readline())

