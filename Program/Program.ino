#include <OneWire.h>
#include <DallasTemperature.h>

#define ID_BYTES 8

OneWire oneWire(A0);
DallasTemperature sensor(&oneWire);
char id_string_buffer[ID_BYTES*2];

void setup() {
  unsigned char therm_id[ID_BYTES];
      
  sensor.begin();  
  Serial.begin(9600);
  Serial.setTimeout(-1);

  sensor.getAddress(therm_id, 0);
  byte_array_to_hex_string(6, therm_id+1, id_string_buffer);
}

void loop (){

  char Rcvd_char[1];

  Serial.readBytes(Rcvd_char, 1);
  if(Rcvd_char[0] != '\n'){
    Serial.print(Rcvd_char[0]);
  }
  else{
    Serial.print(";");
    Serial.println(id_string_buffer);
  }
}

void byte_array_to_hex_string(unsigned char byte_array_size, unsigned char byte_array[], char hex_string[]){
  for(unsigned char i = 0; i<byte_array_size; i++){
    sprintf(hex_string+(2*i), "%.2X", byte_array[i]);
  }
  hex_string[byte_array_size*2] = NULL;
}
