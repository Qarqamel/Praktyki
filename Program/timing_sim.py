nr_of_devices = 32
id_bytes = 6
temp_bytes = 5
single_measure_bytes = id_bytes + temp_bytes + 3
baud_rate = 9600
stop_bit = 1
byte_tx_time_ms = (8 + stop_bit)*1000/baud_rate
max_temp_conversion_time_ms = 93.75

execution_time = 0

for dev_nr in range(nr_of_devices):
    execution_time += byte_tx_time_ms*single_measure_bytes*(dev_nr+1) + max_temp_conversion_time_ms
    
print("Execution with temp measurements takes " + str(execution_time) + " ms")

execution_time = 0

for dev_nr in range(nr_of_devices):
    execution_time += byte_tx_time_ms*(single_measure_bytes - temp_bytes - 1)*(dev_nr+1)
    
print("Execution time without temp measurements takes " + str(execution_time) + " ms")