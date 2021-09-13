import serial    

with serial.Serial(port="COM10", baudrate=9600,bytesize = 8,
                   timeout = None, stopbits=serial.STOPBITS_ONE) as serialPort:
    buffer = 0
    prev_diff = 0
    for i in range(100):
        current_read = int(serialPort.readline().decode('utf-8').rstrip('\n').rstrip('\r'))       
        print(current_read - buffer)
        buffer = current_read
