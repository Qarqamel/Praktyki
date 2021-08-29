#include <OneWire.h>
#include <DallasTemperature.h>

#define ID_BYTES 8

enum Mode {ID, TEMP};

OneWire oneWire(A0);
DallasTemperature sensor(&oneWire);
char id_string_buffer[ID_BYTES*2+1];
float temp_buffer;
enum Mode ThermMode = ID;

void setup() {
  unsigned char therm_id[ID_BYTES];
      
  sensor.begin();
  sensor.setResolution(9);  
  Serial.begin(9600);
  Serial.setTimeout(-1);

  sensor.getAddress(therm_id, 0);
  byte_array_to_hex_string(6, therm_id+1, id_string_buffer);
  sensor.requestTemperatures();
  temp_buffer = sensor.getTempCByIndex(0);
}

void loop (){

  char Rcvd_char[1];
  
  Serial.readBytes(Rcvd_char, 1);
  if(Rcvd_char[0] != '\n'){
    ThermMode = (Rcvd_char[0] == 't' ? TEMP : (Rcvd_char[0] == 'i' ? ID : ThermMode));
    Serial.print(Rcvd_char[0]);
  }
  else{    
    switch(ThermMode){
      case ID:
        Serial.print(";");
        Serial.println(id_string_buffer);
        break;
      case TEMP:
        Serial.print(";");
        Serial.println(temp_buffer);
        sensor.requestTemperatures();
        temp_buffer = sensor.getTempCByIndex(0);
        break;
      default:
        Serial.println("nomode");
        break;
    }
  }
}

void byte_array_to_hex_string(unsigned char byte_array_size, unsigned char byte_array[], char hex_string[]){
  for(unsigned char i = 0; i<byte_array_size; i++){
    sprintf(hex_string+(2*i), "%.2X", byte_array[i]);
  }
  hex_string[byte_array_size*2] = NULL;
}
