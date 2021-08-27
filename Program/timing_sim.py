nr_of_devices = 32
id_length_bytes = 6
id_tx_bytes = id_length_bytes*2 + 2
temp_bytes = 5
single_measure_bytes = temp_bytes + 2
baud_rate = 9600
stop_bit = 1
byte_tx_time_ms = (8 + stop_bit)*1000/baud_rate
max_temp_conversion_time_ms = 93.75

single_measure_tx_time_ms = byte_tx_time_ms*single_measure_bytes

print("Single measure format: ;30.00")
print("Transmission of single measure takes " + str(single_measure_tx_time_ms) + " ms")

single_id_tx_time_ms = byte_tx_time_ms*id_tx_bytes

print("Single id format: ;0123456789ab")
print("Transmission of single id takes " + str(single_id_tx_time_ms) + " ms")

execution_time = 0

for dev_nr in range(nr_of_devices):
    execution_time += single_measure_tx_time_ms*(dev_nr+1)
    
print("Execution with temp measurements takes " + str(execution_time) + " ms")

execution_time = 0

for dev_nr in range(nr_of_devices):
    execution_time += single_id_tx_time_ms*(dev_nr+1)
    
print("Execution with id's takes " + str(execution_time) + " ms")

print()